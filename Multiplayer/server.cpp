
#include "MessageIdentifiers.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"


#include "FileListTransfer.h"
#include "FileListTransferCBInterface.h"
#include "FileOperations.h"
#include "SuperFastHash.h"
#include "RakAssert.h"
#include "IncrementalReadInterface.h"

#include "BitStream.h"
#include "RakSleep.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <list>

#include "connect.h"

#include "types.h"
#include "gamesettings.h"
#include "message.h"
#include "FileMan.h"

#include "IniReader.h"
#include <vfs/Core/vfs.h>
#include "transfer_rules.h"
#include "MPJoinScreen.h"

#include "game init.h"

#include "text.h"
#include "network.h"

#include "message.h"
#include "overhead.h"
#include "fresh_header.h"
#include "Debug Control.h"

#include "MPXmlTeams.hpp"

extern CHAR16 gzFileTransferDirectory[100];

// WANNE: FILE TRANSFER
unsigned int setID;

// Sender progress notification
class ServerFileListProgress : public FileListProgress
{
	virtual void OnFilePush(const char *fileName, unsigned int fileLengthBytes, unsigned int offset, unsigned int bytesBeingSent, bool done, SystemAddress targetSystem)
	{
		// WANNE: Removed output in strategy log screen, because otherwise we do not see chat messages easily
		/*
		if (done)
		{
			char* filename = ExtractFilename((char*)fileName);
			ScreenMsg( FONT_RED, MSG_MPSYSTEM, MPServerMessage[10], filename);
		}
		*/
	}

	char *ExtractFilename(char *pathname) 
	{
		char *s;

		if ((s=strrchr(pathname, '\\')) != NULL) s++;
		else if ((s=strrchr(pathname, '/')) != NULL) s++;
		else if ((s=strrchr(pathname, ':')) != NULL) s++;
		else s = pathname;
		return s;
	}
} serverFileListProgress;



char kbag[100];
char net_div[30];
INT32 gsMAX_MERCS;
bool gsMORALE;
int gsREPORT_NAME;


UINT16 nc; //number of open connection
UINT16 ncr; //number of ready confirmed connections
//something keep record of ready connections ..
int mercs_ready[255];

bool gsDis_Bobby;
bool gsDis_Equip;

int gsSAME_MERC;
float gsDAMAGE_MULTIPLIER;
int gsINTERRUPTS ;
int gsMAX_CLIENTS ;
int gsPLAYER_BSIDE;
int gsTESTING;
int gsDIFFICULT_LEVEL;
char gsFILE_TRANSFER_DIRECTORY_SERVER[100];

int gsSYNC_CLIENTS_MP_DIR;

INT32 gssecs_per_tick;
INT32 gsstarting_balance;
float TIME;
int sWEAPON_READIED_BONUS;
int sALLOW_CUSTOM_NIV;
int sDISABLE_SPEC_MODE;

// OJW - 20090403 - override max enemies for co-op
int OVERRIDE_MAX_AI;

unsigned char SGetPacketIdentifier(Packet *p);
unsigned char SpacketIdentifier;

RakPeerInterface *server;



// WANNE: FILE TRANSFER
FileListTransfer fltServer;	// flt1
IncrementalReadInterface incrementalReadInterface;
FileList fileList;
// OJW - 20090405
long fileListTotalBytes=0;



int numreadyteams;
int readyteamreg[10];

bool Sawarded;

SystemAddress blank;

typedef struct
{
	SystemAddress address;
	int cl_number;
	
}client_data;

client_data client_d[4];

// OJW - 20081223
// Random Merc teams
// First attempt at "balanced" teams
// moved to mpxmlteams.cpp
/*
int random_merc_teams[4][7] =
{
	{ 16, 10, 19, 25, 4 , 11, 39 } ,	// Gus , Shadow, Spider , Raven , Vicki , Red , Meltdown
	{ 29, 36, 28, 2 , 22, 8 , 32 } ,	// Magic , Scope, Danny , Lynx , Hitman , Steroid , Malice
	{ 12, 5 , 20, 23, 48, 34, 17 } ,	// Reaper , Trevor, Cliff , Buzz , Cougar , Nails , Buns
	{ 31, 7 , 33, 35, 27, 37, 1 }		// Scully , Ivan , Dr Q  , Thor , Len , Wolf , Blood
};
*/

int client_mercteam[4] = { 0 , 1 , 2 , 3 }; // random index of random_merc_teams per player

bool inline can_joingame();

char *ReplaceCharactersInString_Server(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	char *p;

	if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
		return str;

	strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
	buffer[p-str] = '\0';

	sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

	return buffer;
}

int f_rec_num(int mode, SystemAddress sender)//from client data
{
	int x;
	client_data cl_record;
	for ( x=0; x<4;x++)
	{
		cl_record = client_d[x];

		if(mode==0)//find empty slot for new record
		{
			if(cl_record.address.binaryAddress==0)
				return(x);
		}
		if(mode==1)//wipe clean all
		{
			client_d[x].address.binaryAddress=0;
			client_d[x].address.port=0;
			client_d[x].cl_number=0;
		}
		if(mode==2)//clear one record
		{
			if(cl_record.address.binaryAddress==sender.binaryAddress && cl_record.address.port==sender.port)
			{
				client_d[x].address.port=0;
				client_d[x].cl_number=0;
				client_d[x].address.binaryAddress=0;
				return(254);
			}

		}
		// OJW - 090212 - look up client number
		if (mode == 3)
		{
			if(cl_record.address.binaryAddress==sender.binaryAddress && cl_record.address.port==sender.port)
			{
				return (x);
			}
		}
	}
	if(mode == 0)//'no free slots'
	{
	ScreenMsg( FONT_RED, MSG_MPSYSTEM, L"Client Record Error, Restart Server, and Report Error." );
	return (255);
	}
	return(254);
}

// use UNASSIGNED_SYSTEM_ADDRESS instead of rpcParameters->sender to send it back to yourself (the sender)
// there is very little in here dependant on the game engine and originally started out as an independant dedicated server .exe, and could if go ther again ... hayden.
//********* RPC SECTION ************

void sendPATH(RPCParameters *rpcParameters)
{
	server->RPC("recievePATH",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

// OJW - 20090405
void sendDOWNLOADSTATUS(RPCParameters *rpcParameters)
{
	server->RPC("recieveDOWNLOADSTATUS",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendSTANCE(RPCParameters *rpcParameters)
{
	server->RPC("recieveSTANCE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDIR(RPCParameters *rpcParameters)
{
	server->RPC("recieveDIR",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendFIRE(RPCParameters *rpcParameters)
{
	server->RPC("recieveFIRE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendHIT(RPCParameters *rpcParameters)
{
	EV_S_WEAPONHIT* hit = (EV_S_WEAPONHIT*)rpcParameters->input;
	
	int team = MercPtrs[ hit->ubAttackerID ]->bTeam;
	
	// AI
	if (team == 1) 
		team = 4;
	// Client
	else if (team >= 6) 
		team -= 6;
	else if (team == 0) 
		team = CLIENT_NUM-1; // this case should not be possible, including as a precaution

	gMPPlayerStats[team].hits++;

	server->RPC("recieveHIT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDISMISS(RPCParameters *rpcParameters)
{
	server->RPC("recieveDISMISS",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendHIRE(RPCParameters *rpcParameters)
{
	server->RPC("recieveHIRE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendguiPOS(RPCParameters *rpcParameters)
{
	server->RPC("recieveguiPOS",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendguiDIR(RPCParameters *rpcParameters)
{
	server->RPC("recieveguiDIR",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendEndTurn(RPCParameters *rpcParameters)
{
	server->RPC("recieveEndTurn",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendAI(RPCParameters *rpcParameters)
{
	server->RPC("recieveAI",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendSTOP(RPCParameters *rpcParameters)
{
	server->RPC("recieveSTOP",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}
void sendINTERRUPT(RPCParameters *rpcParameters)
{
	server->RPC("recieveINTERRUPT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}
void sendREADY(RPCParameters *rpcParameters)
{
	server->RPC("recieveREADY",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendGUI(RPCParameters *rpcParameters)
{
	server->RPC("recieveGUI",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendBULLET(RPCParameters *rpcParameters)
{
	server->RPC("recieveBULLET",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendGRENADE(RPCParameters *rpcParameters)
{
	server->RPC("recieveGRENADE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendGRENADERESULT(RPCParameters *rpcParameters)
{
	server->RPC("recieveGRENADERESULT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendPLANTEXPLOSIVE(RPCParameters *rpcParameters)
{
	server->RPC("recievePLANTEXPLOSIVE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDETONATEEXPLOSIVE(RPCParameters *rpcParameters)
{
	server->RPC("recieveDETONATEEXPLOSIVE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDISARMEXPLOSIVE(RPCParameters *rpcParameters)
{
	server->RPC("recieveDISARMEXPLOSIVE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendSPREADEFFECT(RPCParameters *rpcParameters)
{
	server->RPC("recieveSPREADEFFECT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendNEWSMOKEEFFECT(RPCParameters *rpcParameters)
{
	server->RPC("recieveNEWSMOKEEFFECT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendEXPLOSIONDAMAGE(RPCParameters *rpcParameters)
{
	server->RPC("recieveEXPLOSIONDAMAGE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendSTATE(RPCParameters *rpcParameters)
{
	server->RPC("recieveSTATE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDEATH(RPCParameters *rpcParameters)
{
	// the master copy of the scoreboard is kept on the server
	death_struct* nDeath = (death_struct*)rpcParameters->input;

	// Save Stats on the server side
	gMPPlayerStats[nDeath->soldier_team-1].deaths++;
	gMPPlayerStats[nDeath->attacker_team-1].kills++;
	
	// get the client number of the client sending the message
	int iCLnum = f_rec_num(3,rpcParameters->sender)+1;

	server->RPC("recieveDEATH",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);

#ifdef JA2BETAVERSION
	wchar_t ateam[5];
	wchar_t steam[5];
	wchar_t clnum[5];
	_itow(nDeath->attacker_team,ateam,10);
	_itow(nDeath->soldier_team,steam,10);
	_itow(iCLnum,clnum,10);
	ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, L"DEBUG: Soldier Killed : Attacking team %s , Soldier Team %s, Sender %s",ateam,steam,clnum);
	char logmsg[100];
	sprintf(logmsg, "MP DEBUG: Soldier Killed #%i : Attacking team %i , Soldier Team %i, Sender %i\n",nDeath->soldier_id,nDeath->attacker_team,nDeath->soldier_team,iCLnum);
	MPDebugMsg( logmsg );
#endif
}
void sendhitSTRUCT(RPCParameters *rpcParameters)
{
	EV_S_STRUCTUREHIT* miss = (EV_S_STRUCTUREHIT*)rpcParameters->input;
	
	SOLDIERTYPE* pAttacker = MercPtrs[ miss->ubAttackerID ];
	if (pAttacker != NULL)
	{
		int team = MercPtrs[ miss->ubAttackerID ]->bTeam;
		
		// AI
		if (team == 1) 
			team = 4;
		// Clients
		else if (team >= 6) 
			team -= 6;
		else if (team == 0) 
			team = CLIENT_NUM-1; // this case should not be possible, including as a precaution

		gMPPlayerStats[team].misses++;
	}

	server->RPC("recievehitSTRUCT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}
void sendhitWINDOW(RPCParameters *rpcParameters)
{
	EV_S_WINDOWHIT* miss = (EV_S_WINDOWHIT*)rpcParameters->input;
	

	SOLDIERTYPE* pAttacker = MercPtrs[ miss->ubAttackerID ];
	if (pAttacker != NULL)
	{
		int team = MercPtrs[ miss->ubAttackerID ]->bTeam;
		
		// AI
		if (team == 1) 
			team = 4;
		// Clients
		else if (team >= 6) 
			team -= 6;
		else if (team == 0) 
			team = CLIENT_NUM-1; // this case should not be possible, including as a precaution

		gMPPlayerStats[team].misses++;
	}

	server->RPC("recievehitWINDOW",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}
void sendMISS(RPCParameters *rpcParameters)
{
	EV_S_MISS* miss = (EV_S_MISS*)rpcParameters->input;

	SOLDIERTYPE* pAttacker = MercPtrs[ miss->ubAttackerID ];
	if (pAttacker != NULL)
	{
		int team = MercPtrs[ miss->ubAttackerID ]->bTeam;
		
		// AI
		if (team == 1) 
			team = 4;
		// Clients
		else if (team >= 6) 
			team -= 6;
		else if (team == 0) 
			team = CLIENT_NUM-1; // this case should not be possible, including as a precaution

		gMPPlayerStats[team].misses++;
	}

	server->RPC("recieveMISS",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}
void updatenetworksoldier(RPCParameters *rpcParameters)
{
	server->RPC("UpdateSoldierFromNetwork",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void Snull_team(RPCParameters *rpcParameters)
{
	server->RPC("null_team",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendFIREW(RPCParameters *rpcParameters)
{
	server->RPC("recieve_fireweapon",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendDOOR(RPCParameters *rpcParameters)
{
	server->RPC("recieve_door",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void endINTERRUPT(RPCParameters *rpcParameters)
{
	server->RPC("resume_turn",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendWIPE(RPCParameters *rpcParameters)
{
	server->RPC("recieve_wipe",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendHEAL(RPCParameters *rpcParameters)
{
	server->RPC("recieve_heal",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

// OJW - edge and team changes
void sendEDGECHANGE(RPCParameters *rpcParameters)
{
	server->RPC("recieveEDGECHANGE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendTEAMCHANGE(RPCParameters *rpcParameters)
{
	server->RPC("recieveTEAMCHANGE",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void requestSETID(SystemAddress addr)
{
	server->RPC("requestSETID","", 0, HIGH_PRIORITY, RELIABLE, 0, addr, false, 0, UNASSIGNED_NETWORK_ID,0);
}

void receiveSETID(RPCParameters *rpcParameters)
{
	setID = atoi((const char *)rpcParameters->input);

	// WANNE: FILE TRANSFER: Send the files to the client
	fltServer.Send(&fileList,server,rpcParameters->sender,setID,MEDIUM_PRIORITY,0,false, &incrementalReadInterface, 5000);
}

//void sendALLFILESRECEIVED(RPCParameters *rpcParameters)
//{
//	ScreenMsg( FONT_BCOLOR_ORANGE, MSG_MPSYSTEM, L"%S", rpcParameters->input);
//}


//
//void rINT(RPCParameters *rpcParameters)//who is first
//{
//
//		AIint* data = (AIint*)rpcParameters->input;
//
//		if( !Sawarded )
//		{
//			PauseAITemporarily();
//			Sawarded=true;
//			//send back to sender
//			server->RPC("awardINT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, false, 0, UNASSIGNED_NETWORK_ID,0);
//		}
//}

void startCOMBAT(RPCParameters *rpcParameters)
{
	if(!( gTacticalStatus.uiFlags & INCOMBAT ))
	
	{

		gTacticalStatus.uiFlags |= INCOMBAT;

		sc_struct* data = (sc_struct*)rpcParameters->input;
		EndTurn( data->ubStartingTeam );
	}

}





void sendREAL(RPCParameters *rpcParameters)
{
	real_struct* rData = (real_struct*)rpcParameters->input;


	
	//ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, L"netbTeam %d is ready for realtime",rData->bteam );//diabled unless testing as cheats
	if(readyteamreg[rData->bteam]==0)
	{
		readyteamreg[rData->bteam]=1;//register vote, to prevent double voting ;p~ //hayden
		numreadyteams++;

					int numactiveteams=0;
					int b;
					for(int i=6;i<=LAST_TEAM;i++)
					{
						if(i==6)b=0;
						else b=i;

						if(gTacticalStatus.Team[ b ].bTeamActive)numactiveteams++;

					}//same
					//ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, MPServerMessage[5], numreadyteams, numactiveteams );
					//check # clients ready for realtime
					if (numreadyteams >= numactiveteams)
					{
						//if all send notification for realtime changeover
						//ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, L"Switching to realtime..." );
						numreadyteams=0;
						memset( &readyteamreg , 0 , sizeof (int) * 10);

						server->RPC("gotoRT",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
					}
	}
}

// 20081222 - OJW
void sendGAMEOVER(RPCParameters *rpcParameters)
{
	// ignore the RPCParams and send the server side scoreboard
	server->RPC("recieveGAMEOVER",(const char*)gMPPlayerStats, sizeof(gMPPlayerStats)*8, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
}

void sendCHATMSG(RPCParameters *rpcParameters)
{
	// ignore the RPCParams and send the server side scoreboard
	server->RPC("recieveCHATMSG",(const char*)rpcParameters->input, (*rpcParameters).numberOfBitsOfData, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
}




// OJW - 20081223
// fix client disconnecting mid game, allowing the game to proceed
void HandleDisconnect(SystemAddress sender)
{
	// find the CLIENT_NUM of the player
	int x;
	client_data cl_record;

	for ( x=0; x<4;x++)
	{
		cl_record = client_d[x];
		if(cl_record.address.binaryAddress==sender.binaryAddress && cl_record.address.port==sender.port)
		{
			// notify all the clients of the disconnect
			server->RPC("recieveDISCONNECT",(const char*)&cl_record.cl_number , sizeof(int)*8, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
			f_rec_num(2,sender); // remove from server's client list
			break;
		}
	}
}

// OJW - 20081218
// shuffle an integer array
//<TODO> remove shuffledList and put directly into arr[]
void rSortArray(int* arr, int len)
{
	std::list<int> tmpList;
	std::list<int> shuffledList;
	std::list<int>::iterator Iter;
	int i=0;

	// add all our array items
	for(i=0; i<len; i++)
		tmpList.push_front(arr[i]);

	// shuffle the items
	while(tmpList.size())
	{
		int iRandPos =  rand() % tmpList.size();
		for(Iter = tmpList.begin(); iRandPos>0; iRandPos--, Iter++);
		//Iter += iRandPos;
		shuffledList.push_front(*Iter);
		tmpList.erase(Iter);
	}

	// add all our elements
	for(i=0; i<len; i++)
	{
		arr[i] = shuffledList.back();
		shuffledList.pop_back();
	}
}

// WANNE: FILE TRANSFER: Send all the settings the client needs to know for the file transfer before file transfer starts
void requestFILE_TRANSFER_SETTINGS(RPCParameters *rpcParameters)
{
	SystemAddress sender = rpcParameters->sender;//get senders address
#ifndef USE_VFS
	STRING512 executableDir;
	GetExecutableDirectory(executableDir);

	STRING512 fileTransferDir;
	strcpy(fileTransferDir, executableDir);
	strcat(fileTransferDir, "\\");
	strcat(fileTransferDir, gsFILE_TRANSFER_DIRECTORY_SERVER);

	// Replace all "/" with "\" from the server path
	char* correctFileTransferDir = ReplaceCharactersInString_Server(fileTransferDir, "/", "\\");
	
	filetransfersettings_struct fts;

	fts.syncClientsDirectory = gsSYNC_CLIENTS_MP_DIR;
	strcpy(fts.fileTransferDirectory, correctFileTransferDir);
	strcpy(fts.serverName, SERVER_NAME);
	fts.totalTransferBytes = fileListTotalBytes;
#else
	filetransfersettings_struct fts;

	fts.syncClientsDirectory = gsSYNC_CLIENTS_MP_DIR;
	strcpy(fts.fileTransferDirectory, s_ServerId.getServerId(vfs::Path(gzFileTransferDirectory)).utf8().c_str());
	strcpy(fts.serverName, SERVER_NAME);
	fts.totalTransferBytes = fileListTotalBytes;
#endif
	// OJW - 200907819 - Only send to the client that asked for it
	server->RPC("recieveFILE_TRANSFER_SETTINGS",(const char*)&fts, (int)sizeof(filetransfersettings_struct)*8, HIGH_PRIORITY, RELIABLE, 0, sender, false, 0, UNASSIGNED_NETWORK_ID,0);
}


//************************* //UNASSIGNED_SYSTEM_ADDRESS
//START INTERNAL SERVER
//*************************
//void send_settings (void)//send server settings to client
void requestSETTINGS(RPCParameters *rpcParameters )
{
	// dont generate or send settings to a new user if they are about to be disconnected
	// because no more players can join the the game
	if (can_joingame())
	{
		client_info* clinf = (client_info*)rpcParameters->input;

		// OJW - 20090507
		// Disconnect if version is wrong
		if (strcmp(clinf->client_version,MPVERSION)!=0)
		{
			CHAR16 verErrMsg[255];
			swprintf(verErrMsg,255, MPClientMessage[66], clinf->client_version,MPVERSION);

			// send disconnect reason only to this client
			server->RPC("recieveDISCONNECTREASON",(const char*)&verErrMsg, (int)sizeof(CHAR16)*255*8, HIGH_PRIORITY, RELIABLE, 0, rpcParameters->sender, false, 0, UNASSIGNED_NETWORK_ID,0);

			ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"CONNECTION REJECTED - CLIENT HAS WRONG VERSION");
			// disconnect this client
			server->CloseConnection(rpcParameters->sender, true);
			return;
		}

		// WANNE: FILE TRANSFER: A client connected -> start the file transfer!
		if (gsSYNC_CLIENTS_MP_DIR)
			requestSETID(rpcParameters->sender);

		//server assigned client numbers - hayden.
		SystemAddress sender = rpcParameters->sender;//get senders address
		int bslot = f_rec_num(0,blank);//get empty record slot
		client_d[bslot].address=sender; //record clients address
		int new_cl_num = bslot+1;//client number to assign
		client_d[bslot].cl_number=new_cl_num; //record clients number


		settings_struct lan;

		//lan.client_num = clinf->client_num;//old client assigned number
		lan.client_num = new_cl_num; //new server assigned number
		strcpy(lan.client_name , clinf->client_name);

		lan.RANDOM_SPAWN = RANDOM_SPAWN;
		lan.RANDOM_MERCS = RANDOM_MERCS;

		lan.max_clients = gsMAX_CLIENTS;
		memcpy(lan.kitbag , kbag,sizeof (char)*100);
		lan.damage_multiplier = gsDAMAGE_MULTIPLIER;

		lan.same_merc = gsSAME_MERC;
		lan.gsMercArriveSectorX=gsMercArriveSectorX;
		lan.gsMercArriveSectorY=gsMercArriveSectorY;

		lan.ENEMY_ENABLED=ENEMY_ENABLED;
		lan.CREATURE_ENABLED=CREATURE_ENABLED;
		lan.MILITIA_ENABLED=MILITIA_ENABLED;
		lan.CIV_ENABLED=CIV_ENABLED;

		lan.gsPLAYER_BSIDE=gsPLAYER_BSIDE;

		lan.emorale=gsMORALE;
		lan.gsREPORT_NAME=gsREPORT_NAME;
//something new
		lan.secs_per_tick=gssecs_per_tick;
		lan.soubBobbyRay=gGameOptions.ubBobbyRay;
		lan.sofGunNut=gGameOptions.fGunNut;	
		lan.soubGameStyle=gGameOptions.ubGameStyle;
		lan.soubDifficultyLevel=gsDIFFICULT_LEVEL;
		lan.sofTurnTimeLimit=gGameOptions.fTurnTimeLimit;
		lan.sofIronManMode=gGameOptions.fIronManMode;
		lan.starting_balance=gsstarting_balance;

		// OJW - 20090319 - Changing allow custom NIV to force NIV on all clients
		// as with the new join screen setup, no way for the individual client to choose
		// whether or not to use NIV. If this is wrong, its easily fixed...
		// just change description text for the toggle option on the host screen to
		// "Allow custom inventory" and delete this if statement.
		if (sALLOW_CUSTOM_NIV==1 && IsNIVModeValid(true))
			gGameOptions.ubInventorySystem = INVENTORY_NEW;
		else
			gGameOptions.ubInventorySystem = INVENTORY_OLD;
		
		lan.sofNewInv=gGameOptions.ubInventorySystem;

		lan.soDis_Bobby=gsDis_Bobby;
		lan.soDis_Equip=gsDis_Equip;

		lan.gsMAX_MERCS=gsMAX_MERCS;
		
		memcpy( lan.client_names , client_names, sizeof( char ) * 4 * 30 );
		lan.team=clinf->team;
		// OJW - 20090530 - fix teams not initialised properly
		client_teams[ lan.client_num - 1 ] = lan.team;

		lan.TESTING=gsTESTING;

		// OJW - 20081218
		if (RANDOM_SPAWN)
		{
			// Get the edge from the randomized "client_edges"
			lan.cl_edge = client_edges[lan.client_num-1];
		}
		else
		{
			// WANNE: on DM, each client should get a unique starting edge per default
			if (gsPLAYER_BSIDE == MP_TYPE_DEATHMATCH || gsPLAYER_BSIDE == MP_TYPE_TEAMDEATMATCH)
			{
				client_edges[0] = MP_EDGE_NORTH;	// client 1
				client_edges[1] = MP_EDGE_SOUTH;	// client 2
				client_edges[2] = MP_EDGE_EAST;		// client 3
				client_edges[3] = MP_EDGE_WEST;		// client 4

				lan.cl_edge = client_edges[lan.client_num-1];
			}
			else
			{
				lan.cl_edge=clinf->cl_edge;
			}
		}

		// OJW - 20081223
		if (RANDOM_MERCS)
		{
			//memcpy(lan.random_mercs, random_merc_teams[client_mercteam[lan.client_num - 1]], sizeof(int) * 7);
			mpTeams.SerializeProfiles(lan.random_mercs);
		}

		lan.TIME=TIME;
		lan.WEAPON_READIED_BONUS=sWEAPON_READIED_BONUS;
		lan.ALLOW_CUSTOM_NIV=sALLOW_CUSTOM_NIV;
		lan.DISABLE_SPEC_MODE=sDISABLE_SPEC_MODE;

		// OJW - 20081204
		strcpy(lan.server_name , SERVER_NAME);
		memcpy(lan.client_edges,client_edges,sizeof(int)*5);
		memcpy(lan.client_teams,client_teams,sizeof(int)*4);

		// OJW - 20091024 - send servers random table
		memcpy(lan.random_table,guiPreRandomNums,sizeof(UINT32)*MAX_PREGENERATED_NUMS);

		// OJW - 20090507
		// send server version to client
		strcpy(lan.server_version,MPVERSION);

		server->RPC("recieveSETTINGS",(const char*)&lan, (int)sizeof(settings_struct)*8, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);

	} // end if(can_joingame)
}

// added 081201 by Owen , allow the server to change the map while its still not in laptop mode
void send_mapchange(void)
{
	if (is_server  && !allowlaptop)
	{
		mapchange_struct lan;

		lan.gsMercArriveSectorX=gsMercArriveSectorX;
		lan.gsMercArriveSectorY=gsMercArriveSectorY;
		lan.TIME=TIME;

		server->RPC("recieveMAPCHANGE",(const char*)&lan, (int)sizeof(mapchange_struct)*8, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true, 0, UNASSIGNED_NETWORK_ID,0);
	}
	else
	{
		ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, MPServerMessage[45]);
	}
}

// OJW 090212
bool inline can_joingame()
{
	return !allowlaptop;
}

// Allow server to disconnect incoming clients after the game has started
void CheckIncomingConnection(Packet* p)
{
	// some clients might reconnect after disconnecting, either after the laptop is unlocked
	// or after the game has started
	// we dont want to allow this as thier game will be out of state
	if (!can_joingame())
	{
		ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, L"CONNECTION REJECTED - GAME HAS STARTED");
		// disconnect this client, no need to notify them as they will know if they disconnected
		// before receiving a settings packet that they were not allowed to join
		server->CloseConnection(p->systemAddress, true);
	}
}

void AddFilesToSendList()
{
#ifndef USE_VFS
	STRING512 executableDir;
	GetExecutableDirectory(executableDir);

	HANDLE				hFileIn;
	HCONTAINER hStack = CreateStack( 100000, 600 );
	WIN32_FIND_DATA		find, inFind;

	find.dwFileAttributes = FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_DIRECTORY;
	inFind.dwFileAttributes = FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_DIRECTORY;

	STRING512 fileTransferDir;
	strcpy(fileTransferDir, executableDir);

	// WANNE: Build the complete file transfer directory for the server
	strcat(fileTransferDir, "\\");
	strcat(fileTransferDir, gsFILE_TRANSFER_DIRECTORY_SERVER);
	
	char* correctFileTransferDir = ReplaceCharactersInString_Server(fileTransferDir, "/", "\\");
	if (DirectoryExists(correctFileTransferDir))
	{
		strcat(correctFileTransferDir, "\\*.*");

		hFileIn = FindFirstFile( correctFileTransferDir, &inFind );

		// Get all files (recursive) inside the folder "cSubDir" == FILE_TRANSFER_DIR_SERVER
		INT32 iNumFiles = GetFilesInDirectory( hStack, correctFileTransferDir, hFileIn, &inFind );

		CHAR		filename[600];
		INT32 i;
		for ( i=0 ; i<iNumFiles ; i++ )
		{
			Pop( hStack, filename );

			unsigned int fileLength = GetFileLength(filename);
			fileListTotalBytes += fileLength;
			fileList.AddFile(filename, 0, fileLength, fileLength, FileListNodeContext(0,0), true);
		}

		DeleteStack( hStack );
	}
	else
	{
		char* outputTransferDir = ReplaceCharactersInString_Server(correctFileTransferDir, "\\*.*", "");
		ScreenMsg( FONT_RED, MSG_MPSYSTEM, L"The Sync. MP Directory '%S' does not exist on the server. Cannot send any files to the clients!", outputTransferDir);
	}
#else
	// we cannot just iterate over "*/*" as we would get ALL files and we don't want to send all files
	// instead we only iterate over the files in the "_MULTIPLAYER" profile
	vfs::CProfileStack *PS = getVFS()->getProfileStack();
	vfs::CVirtualProfile *prof = PS->getProfile("_MULTIPLAYER");
	if(prof != PS->topProfile())
	{
		// there is not supposed to be another profile?
		// output error message
		return;
	}
	CTransferRules transferRules;
	transferRules.initFromTxtFile("transfer_rules.txt");
	vfs::IBaseLocation* loc = prof->getLocation("");
	SGP_THROW_IFFALSE(loc != NULL, "MP profile was successfully created, but the root directory is not included");
	vfs::IBaseLocation::Iterator it = loc->begin();
	int i=0;
	for(; !it.end(); it.next(), i++)
	{
		vfs::Path const& valid_path = it.value()->getPath();
		if(transferRules.applyRule(valid_path()) == CTransferRules::ACCEPT)
		{
			// transfer only those files that are not on the ignore list
			vfs::tReadableFile* rfile = vfs::tReadableFile::cast(it.value());
			if(!rfile)
			{
				continue;
			}
			vfs::size_t fsize = rfile->getSize();
			fileListTotalBytes += (long)fsize;
			if( (fsize>0) && rfile->openRead())
			{
				std::vector<vfs::Byte> data(fsize,0);
				rfile->read(&data[0], fsize);
				rfile->close();
				fileList.AddFile(vfs::String::as_utf8(valid_path()).c_str(),&data[0], fsize,fsize,FileListNodeContext(0,0), false);
			}
		}
	}
	if(i == 0)
	{
		// no files? 
		//char* outputTransferDir = ReplaceCharactersInString_Server(correctFileTransferDir, "\\*.*", "");
		//ScreenMsg( FONT_RED, MSG_MPSYSTEM, L"The Sync. MP Directory '%S' does not exist on the server. Cannot send any files to the clients!", outputTransferDir);
	}
#endif
}

void start_server (void)
{
	if(!is_server)
	{	
#ifndef USE_VFS
		CIniReader iniReader("..\\Ja2_mp.ini");
#else
		CIniReader iniReader("Ja2_mp.ini");
#endif
			//retrieve settings from .ini

			f_rec_num(1,blank);//wipe clean
			//char maxclients[30];
			char port[30];
			char SERVER_PORT[30];
			//char MAX_CLIENTS[30] ;
#ifndef USE_VFS
		//	GetPrivateProfileString( "Ja2_mp Settings","MAX_CLIENTS", "4", maxclients, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","SERVER_PORT", "60005", port, MAX_PATH, "..\\Ja2_mp.ini" );
		//	strcpy( MAX_CLIENTS , maxclients );
			strcpy( SERVER_PORT, port );
#else
		//	GetPrivateProfileString( "Ja2_mp Settings","MAX_CLIENTS", "", maxclients, MAX_PATH, "..\\Ja2_mp.ini" );
			strcpy(port, iniReader.ReadString("Ja2_mp Settings","SERVER_PORT", "60005"));
		//	strcpy( MAX_CLIENTS , maxclients );
			strcpy( SERVER_PORT, port );
#endif

			char ints[30];
			char maxclients[30];
		
			char hire_same_merc[30];
			char bteam1_enabled[30];
			//char bteam2_enabled[30];
			char bteam3_enabled[30];
			char bteam4_enabled[30];

			char player_bside[30];
			char difficult_level[30];

			char sBalance[30];
			char time_div[30];
			char mor[30];

			char sRandomMercs[30];
			char sRandomEdges[30];

			// OJW - 20081204
#ifndef USE_VFS
			GetPrivateProfileString( "Ja2_mp Settings","SERVER_NAME", "Server Name", SERVER_NAME, MAX_PATH, "..\\Ja2_mp.ini" );

			GetPrivateProfileString( "Ja2_mp Settings","SAME_MERC", "1", hire_same_merc, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","DISABLE_MORALE", "0", mor, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","MAX_CLIENTS", "4", maxclients, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","DAMAGE_MULTIPLIER", "0.7", net_div, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","RANDOM_MERCS", "0", sRandomMercs, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","RANDOM_EDGES", "0", sRandomEdges, MAX_PATH, "..\\Ja2_mp.ini" );
			
			GetPrivateProfileString( "Ja2_mp Settings","ENEMY_ENABLED", "0", bteam1_enabled, MAX_PATH, "..\\Ja2_mp.ini" );
			//GetPrivateProfileString( "Ja2_mp Settings","CREATURE_ENABLED", "0", bteam2_enabled, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","MILITIA_ENABLED", "0", bteam3_enabled, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","CIV_ENABLED", "0", bteam4_enabled, MAX_PATH, "..\\Ja2_mp.ini" );

			GetPrivateProfileString( "Ja2_mp Settings","GAME_MODE", "0", player_bside, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","DIFFICULT_LEVEL", "3", difficult_level, MAX_PATH, "..\\Ja2_mp.ini" );

			// OJW - 20090304 - override max number of ai's in co-op
			char sOverrideMaxAI[30];
			OVERRIDE_MAX_AI = 0;
			GetPrivateProfileString( "Ja2_mp Settings","OVERRIDE_MAX_AI", "0", sOverrideMaxAI, MAX_PATH, "..\\Ja2_mp.ini" );
			
			// WANNE: FILE TRANSFER
			GetPrivateProfileString( "Ja2_mp Settings", "FILE_TRANSFER_DIRECTORY", "Data-MP", gsFILE_TRANSFER_DIRECTORY_SERVER, MAX_PATH, "..\\Ja2_mp.ini" ); 

			char sendFiles[30];
			GetPrivateProfileString( "Ja2_mp Settings", "SYNC_CLIENTS_MP_DIR", "1", sendFiles, MAX_PATH, "..\\Ja2_mp.ini" ); 
			gsSYNC_CLIENTS_MP_DIR = atoi(sendFiles);
#else
			strncpy(SERVER_NAME, iniReader.ReadString("Ja2_mp Settings","SERVER_NAME", "Server Name"), 30);

			strncpy(hire_same_merc, iniReader.ReadString("Ja2_mp Settings","SAME_MERC", "1"), 30);
			strncpy(mor, iniReader.ReadString("Ja2_mp Settings","DISABLE_MORALE", "0"), 30);
			strncpy(maxclients, iniReader.ReadString("Ja2_mp Settings","MAX_CLIENTS", "4"), 30);
			strncpy(net_div, iniReader.ReadString("Ja2_mp Settings","DAMAGE_MULTIPLIER", "0.7"), 30);
			strncpy(sRandomMercs, iniReader.ReadString("Ja2_mp Settings","RANDOM_MERCS", "0"), 30);
			strncpy(sRandomEdges, iniReader.ReadString("Ja2_mp Settings","RANDOM_EDGES", "0"), 30);
			
			strncpy(bteam1_enabled, iniReader.ReadString("Ja2_mp Settings","ENEMY_ENABLED", "0"), 30);
			//GetPrivateProfileString( "Ja2_mp Settings","CREATURE_ENABLED", "", bteam2_enabled, MAX_PATH, "..\\Ja2_mp.ini" );
			strncpy(bteam3_enabled, iniReader.ReadString("Ja2_mp Settings","MILITIA_ENABLED", "0"), 30);
			strncpy(bteam4_enabled, iniReader.ReadString("Ja2_mp Settings","CIV_ENABLED", "0"), 30);

			strncpy(player_bside, iniReader.ReadString( "Ja2_mp Settings","GAME_MODE", "0"), 30);
			strncpy(difficult_level, iniReader.ReadString( "Ja2_mp Settings", "DIFFICULT_LEVEL", "3"), 30);
			
			// OJW - 20090304 - override max number of ai's in co-op
			char sOverrideMaxAI[30];
			OVERRIDE_MAX_AI = 0;
			strncpy(sOverrideMaxAI, iniReader.ReadString("Ja2_mp Settings","OVERRIDE_MAX_AI", "0"), 30);
			
			// WANNE: FILE TRANSFER
			strncpy(gsFILE_TRANSFER_DIRECTORY_SERVER, iniReader.ReadString("Ja2_mp Settings", "FILE_TRANSFER_DIRECTORY", "Data-MP"), 100 ); 

			char sendFiles[30];
			strncpy(sendFiles, iniReader.ReadString( "Ja2_mp Settings", "SYNC_CLIENTS_MP_DIR", "1"), 30 ); 
			gsSYNC_CLIENTS_MP_DIR = atoi(sendFiles);
			
#endif
			gsSYNC_CLIENTS_MP_DIR = atoi(sendFiles);

//something new
			gsMORALE=0;
			if(atoi(mor)==1)gsMORALE=1;

#ifndef USE_VFS
			GetPrivateProfileString( "Ja2_mp Settings","KIT_BAG", "[201,214,243]", kbag, MAX_PATH, "..\\Ja2_mp.ini" );

			char rpn[30];
			GetPrivateProfileString( "Ja2_mp Settings","REPORT_NAME", "1", rpn, MAX_PATH, "..\\Ja2_mp.ini" );
			gsREPORT_NAME=atoi(rpn);

			GetPrivateProfileString( "Ja2_mp Settings","STARTING_BALANCE", "25000", sBalance, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","TIMED_TURN_SECS_PER_TICK", "13.50", time_div, MAX_PATH, "..\\Ja2_mp.ini" );

			char dis_bob[30];
			char dis_equip[30];
			char max_merc[30];
			char test[30];
			GetPrivateProfileString( "Ja2_mp Settings","DISABLE_BOBBY_RAYS", "", dis_bob, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","DISABLE_AIM_AND_MERC_EQUIP", "", dis_equip, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","MAX_MERCS", "5", max_merc, MAX_PATH, "..\\Ja2_mp.ini" );
			GetPrivateProfileString( "Ja2_mp Settings","TESTING", "0", test, MAX_PATH, "..\\Ja2_mp.ini" );
			gsDis_Bobby=false;
			gsDis_Equip=false;
#else
			strncpy(kbag, iniReader.ReadString("Ja2_mp Settings","KIT_BAG", "[201,214,243]"), 100);

			char rpn[30];
			strncpy(rpn, iniReader.ReadString("Ja2_mp Settings","REPORT_NAME", "1"), 30);
			gsREPORT_NAME=atoi(rpn);

			strncpy(sBalance, iniReader.ReadString("Ja2_mp Settings","STARTING_BALANCE", "25000"), 30);
			strncpy(time_div, iniReader.ReadString("Ja2_mp Settings","TIMED_TURN_SECS_PER_TICK", "25"), 30);
			
			char dis_bob[30];
			char dis_equip[30];
			char max_merc[30];
			char test[30];
			strncpy(dis_bob, iniReader.ReadString("Ja2_mp Settings","DISABLE_BOBBY_RAYS", "0"), 30);
			strncpy(dis_equip, iniReader.ReadString("Ja2_mp Settings","DISABLE_AIM_AND_MERC_EQUIP", "0"), 30);
			strncpy(max_merc, iniReader.ReadString("Ja2_mp Settings","MAX_MERCS", "5"), 30);
			strncpy(test, iniReader.ReadString("Ja2_mp Settings","TESTING", "0"), 30);
			gsDis_Bobby=false;
			gsDis_Equip=false;
#endif

			if(atoi(dis_bob)==1)gsDis_Bobby=true;
			if(atoi(dis_equip)==1)gsDis_Equip=true;

			gsMAX_MERCS=atoi(max_merc);
			gsTESTING = atoi(test);

			gsPLAYER_BSIDE = atoi(player_bside);

			gsDIFFICULT_LEVEL = atoi(difficult_level);
			ENEMY_ENABLED=0;
			CREATURE_ENABLED=0;
			MILITIA_ENABLED=0;
			CIV_ENABLED=0;

			RANDOM_MERCS = atoi(sRandomMercs);
			RANDOM_SPAWN = atoi(sRandomEdges);

			if (RANDOM_SPAWN)
			{
				// create random starting edges
				int spawns[5] = { 0 , 1 , 2 , 3, 9 };
				
				// Randomize spawns
				rSortArray(spawns,5);
				memcpy(client_edges,spawns,sizeof(int)*5);
			}

			if (RANDOM_MERCS)
			{
				// randomly sort team indexes to give client
				// one of four random merc teams
				rSortArray(client_mercteam,4);
				mpTeams.HandleServerStarted();
			}

			if(gsPLAYER_BSIDE==2)//only enable ai during coop
			{
				ENEMY_ENABLED = 1; // always enable enemies in co-op
				MILITIA_ENABLED = atoi(bteam3_enabled);
				CIV_ENABLED = atoi(bteam4_enabled);
				// OJW - 20090403 - override max ais
				if (atoi(sOverrideMaxAI)==1)
					OVERRIDE_MAX_AI = 1;
			}

			// random_mercs implies same_merc
			gsSAME_MERC = RANDOM_MERCS ? 1 : atoi(hire_same_merc);
			gsDAMAGE_MULTIPLIER =(FLOAT)atof(net_div);
			gsINTERRUPTS = atoi(ints);
			gsMAX_CLIENTS = atoi(maxclients);

			gssecs_per_tick=atoi(time_div) ;
			gsstarting_balance=atoi(sBalance);
#ifndef USE_VFS
			char time[30];
			GetPrivateProfileString( "Ja2_mp Settings","TIME", "", time, MAX_PATH, "..\\Ja2_mp.ini" );
			TIME=(FLOAT)atof(time);

			char wpr[30];
			GetPrivateProfileString( "Ja2_mp Settings","WEAPON_READIED_BONUS", "", wpr, MAX_PATH, "..\\Ja2_mp.ini" );
			sWEAPON_READIED_BONUS=atoi(wpr);

			char acniv[30];
			GetPrivateProfileString( "Ja2_mp Settings","ALLOW_CUSTOM_NIV", "", acniv, MAX_PATH, "..\\Ja2_mp.ini" );
			sALLOW_CUSTOM_NIV=atoi(acniv);

			char dspec[30];
			GetPrivateProfileString( "Ja2_mp Settings","DISABLE_SPEC_MODE", "", dspec, MAX_PATH, "..\\Ja2_mp.ini" );
			sDISABLE_SPEC_MODE=atoi(dspec);
#else
			char time[30];
			strncpy(time, iniReader.ReadString("Ja2_mp Settings","TIME", "0"), 30);
			TIME=(FLOAT)atof(time);

			char wpr[30];
			strncpy(wpr, iniReader.ReadString("Ja2_mp Settings","WEAPON_READIED_BONUS", "0"), 30);
			sWEAPON_READIED_BONUS=atoi(wpr);

			char acniv[30];
			strncpy(acniv, iniReader.ReadString("Ja2_mp Settings","ALLOW_CUSTOM_NIV", "0"), 30);
			sALLOW_CUSTOM_NIV=atoi(acniv);

			char dspec[30];
			strncpy(dspec, iniReader.ReadString("Ja2_mp Settings","DISABLE_SPEC_MODE", "0"), 30);
			sDISABLE_SPEC_MODE=atoi(dspec);
#endif
			//**********************

		ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, MPServerMessage[0] );

		server=RakNetworkFactory::GetRakPeerInterface();
		bool b = server->Startup(gsMAX_CLIENTS, 30, &SocketDescriptor(atoi(SERVER_PORT),0), 1);

		server->SetMaximumIncomingConnections((gsMAX_CLIENTS));

		//RPC's
		REGISTER_STATIC_RPC(server, sendPATH);
		REGISTER_STATIC_RPC(server, sendDOWNLOADSTATUS);
		REGISTER_STATIC_RPC(server, sendSTANCE);
		REGISTER_STATIC_RPC(server, sendDIR);
		REGISTER_STATIC_RPC(server, sendFIRE);
		REGISTER_STATIC_RPC(server, sendHIT);
		REGISTER_STATIC_RPC(server, sendHIRE);
		REGISTER_STATIC_RPC(server, sendDISMISS);
		REGISTER_STATIC_RPC(server, sendguiPOS);
		REGISTER_STATIC_RPC(server, sendguiDIR);
		REGISTER_STATIC_RPC(server, sendEndTurn);
		REGISTER_STATIC_RPC(server, sendAI);
		REGISTER_STATIC_RPC(server, sendSTOP);
		REGISTER_STATIC_RPC(server, sendINTERRUPT);
		REGISTER_STATIC_RPC(server, sendREADY);
		REGISTER_STATIC_RPC(server, sendGUI);
		REGISTER_STATIC_RPC(server, sendBULLET);
		REGISTER_STATIC_RPC(server, sendGRENADE);
		REGISTER_STATIC_RPC(server, sendGRENADERESULT);
		REGISTER_STATIC_RPC(server, sendPLANTEXPLOSIVE);
		REGISTER_STATIC_RPC(server, sendDETONATEEXPLOSIVE);
		REGISTER_STATIC_RPC(server, sendDISARMEXPLOSIVE);
		REGISTER_STATIC_RPC(server, sendSPREADEFFECT);
		REGISTER_STATIC_RPC(server, sendNEWSMOKEEFFECT);
		REGISTER_STATIC_RPC(server, sendEXPLOSIONDAMAGE);
		REGISTER_STATIC_RPC(server, requestSETTINGS);
		REGISTER_STATIC_RPC(server, requestFILE_TRANSFER_SETTINGS);
		REGISTER_STATIC_RPC(server, sendSTATE);
		REGISTER_STATIC_RPC(server, sendDEATH);
		REGISTER_STATIC_RPC(server, sendhitSTRUCT);
		REGISTER_STATIC_RPC(server, sendhitWINDOW);
		REGISTER_STATIC_RPC(server, sendMISS);
		//REGISTER_STATIC_RPC(server, rOVH);

		REGISTER_STATIC_RPC(server, updatenetworksoldier);
		REGISTER_STATIC_RPC(server, Snull_team);
		REGISTER_STATIC_RPC(server, sendFIREW);
		REGISTER_STATIC_RPC(server, sendDOOR);
		REGISTER_STATIC_RPC(server, endINTERRUPT);
		REGISTER_STATIC_RPC(server, sendREAL);
		REGISTER_STATIC_RPC(server, startCOMBAT);
		REGISTER_STATIC_RPC(server, sendWIPE);
		REGISTER_STATIC_RPC(server, sendHEAL);
		REGISTER_STATIC_RPC(server, sendEDGECHANGE);
		REGISTER_STATIC_RPC(server, sendTEAMCHANGE);
		REGISTER_STATIC_RPC(server, sendGAMEOVER);
		REGISTER_STATIC_RPC(server, sendCHATMSG);
		REGISTER_STATIC_RPC(server, receiveSETID);
		//REGISTER_STATIC_RPC(server, sendALLFILESRECEIVED);
		//REGISTER_STATIC_RPC(server, rINT);
		//

		if (b)
		{
			ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, MPServerMessage[1]);
			//ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, MPServerMessage[2]);
			is_server = true;


			// WANNE: FILE TRANSFER
			server->AttachPlugin(&fltServer);
			server->SetSplitMessageProgressInterval(1);
			fltServer.SetCallback(&serverFileListProgress);

			fileListTotalBytes=0;
			if (gsSYNC_CLIENTS_MP_DIR == 1)
			{
				AddFilesToSendList();
			}

			connect_client();//connect client to server
		}
		else
		{
			ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, MPServerMessage[4]);
		}
	}
	else
	{
		ScreenMsg( FONT_LTBLUE, MSG_MPSYSTEM, MPServerMessage[3]);
	}
}



// recieve and process server info packets

void server_packet ( void )
{
	
	Packet* p;

	if (is_server)
	{

	p = server->Receive();

	while(p)
	{
			//continue; // Didn't get any packets

		// We got a packet, get the identifier with our handy function
		SpacketIdentifier = SGetPacketIdentifier(p);
		//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"packet recieved");
		// Check if this is a network message packet
		switch (SpacketIdentifier)
		{
			case ID_DISCONNECTION_NOTIFICATION://client disconnected purposefullly
				// Connection lost normally
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_DISCONNECTION_NOTIFICATION");
				HandleDisconnect(p->systemAddress);//clear record
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_ALREADY_CONNECTED");
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_REMOTE_DISCONNECTION_NOTIFICATION");
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_REMOTE_CONNECTION_LOST");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_REMOT/MING_CONNECTION");
				break;
			case ID_CONNECTION_ATTEMPT_FAILED:
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_CONNECTION_ATTEMPT_FAILED");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_NO_FREE_INCOMING_CONNECTIONS");
				break;
			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_CONNECTION_LOST");//client dropped
				HandleDisconnect(p->systemAddress);//clear record
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				// This tells the client they have connected
				ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_CONNECTION_REQUEST_ACCEPTED");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				//tells server client has connected
				#ifdef JA2BETAVERSION
					ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_NEW_INCOMING_CONNECTION");
				#endif
				// make sure they can connect
				CheckIncomingConnection(p);
				//send_settings();//send off server set settings

				break;
			case ID_MODIFIED_PACKET:
				// Cheater!
				#ifdef JA2BETAVERSION
					ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"ID_MODIFIED_PACKET");
				#endif
				break;
			default:
				#ifdef JA2BETAVERSION	
					ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, L"** a packet has been recieved for which i dont know what to do... **");
				#endif
				break;
		}


		// We're done with the packet, get more :)
		server->DeallocatePacket(p);
		p = server->Receive();
	}
	}
}
// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
unsigned char SGetPacketIdentifier(Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		assert(p->length > sizeof(unsigned char) + sizeof(unsigned long));
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	}
	else
		return (unsigned char) p->data[0];
}

void server_disconnect (void)
{
	if(is_server)
	{
		server->DetachPlugin(&fltServer);
	server->Shutdown(300);
	is_server = false;
	fileList.Clear();
	// We're done with the network
	RakNetworkFactory::DestroyRakPeerInterface(server);
	ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, MPServerMessage[6]);
	}
	else
	{
	ScreenMsg( FONT_ORANGE, MSG_MPSYSTEM, MPServerMessage[7]);
	}
}
