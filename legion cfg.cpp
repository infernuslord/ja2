//legion 2
#ifdef PRECOMPILEDHEADERS
	#include "Types.h"
	#include "types.h"
	#include "Strategic All.h"
	#include "XML.h"
	#include "INIReader.h"
	#include "GameSettings.h"
	#include "Soldier Profile.h"
	#include "XML.h"
	#include "Item Types.h"
	#include "Items.h"
	#include "Game Event Hook.h"
	#include "faces.h"
	#include "Language Defines.h"
	#include "Types.h"
	#include "Map Screen Interface Map.h"
	#include "legion cfg.h" //legion2
	//#include "XMLWriter.h"
#else
	#include "Types.h"
	#include "types.h"
	#include "Campaign Init.h"
	#include "Random.h"
	#include "Campaign Types.h"
	#include "Queen Command.h"
	#include "overhead.h"
	#include "Strategic Movement.h"
	#include "Strategic Status.h"
	#include "GameSettings.h"
	#include "Creature Spreading.h"
	#include "Strategic AI.h"
	#include "XML.h"
	#include "INIReader.h"
	#include "Game init.h"
	#include "Game Event Hook.h"
	#include "sgp.h"
	#include "jascreens.h"
	#include "laptop.h"
	#include "worlddef.h"
	#include "Soldier Control.h"
	#include "overhead.h"
	#include "fade screen.h"
	#include "gamescreen.h" 
	#include "email.h"
	#include "Game Clock.h"
	#include "soldier profile.h"
	#include "strategicmap.h"
	#include "game init.h"
	#include "animation data.h"
	#include "finances.h"
	#include "soldier create.h"
	#include "Soldier Init List.h"
	#include "music control.h"
	#include "strategic.h"
	#include "history.h"
	#include "merc entering.h"
	#include "Squads.h"
	#include "Campaign Init.h"
	#include "Strategic Town Loyalty.h"
	#include "Strategic Mines.h"
	#include "gameloop.h"
	#include "Random.h"
	#include "Map Screen Interface.h"
	#include "Tactical Save.h"
	#include "Campaign Types.h"
	#include "Message.h"
	#include "Game Event Hook.h"
	#include "Strategic Movement.h"
	#include "Creature Spreading.h"
	#include "Quests.h"
	#include "Strategic AI.h"
	#include "sound control.h"
	#include "Laptopsave.h"
	#include "AimMembers.h"
	#include "dialogue control.h"
	#include "npc.h"
	#include "Init.h"
	#include "GameSettings.h"
	#include "INIReader.h"
	#include "Soldier Profile.h"
	#include "XML.h"
	#include "Item Types.h"
	#include "Items.h"
	#include "text.h"
	#include "GameSettings.h"
//	#include "XMLWriter.h"
#endif

#ifdef JA2UB
#include "Ja25 Strategic Ai.h"
#include "Ja25Update.h"
#endif

#include "legion cfg.h" //legion2
#include "Campaign Types.h"
#include "Interface.h"
#include "Map Screen Interface Map.h"
#include "renderworld.h"
#include "aim.h"
#include "connect.h"
#include "expat.h"
#include "XMLWriter.h"
#include "Debug Control.h"
#include <vfs/Core/vfs.h>

GAME_LEGION_OPTIONS gGameLegionOptions; 
Legion2Dane	gLegion2Dane; //legion
UINT32	ProfileNum_Legion[NUM_PROFILES];
SLOTY_LEGION_VALUES gLegionSloty[NUM_PROFILES];

#define				GAME_LEGION_OPTIONS_FILE	"UB_Options.ini"
#define				LAPTOP_OPTIONS_FILE	"Ja2_laptop.ini"

#define				BadSectorsList_FILE	"BadSectorsList.ini"

extern void Ustaw_NPC_SPEECH ();
extern void Ustaw_parametry ();

void LoadGameLegionOptions();

#ifdef JA2UB
void RandomAddEnemy( UINT8 SectorX, UINT8 SectorY, UINT8 Level );
#endif

void RandomStats ();

#ifdef WFconvertUB
void WFtoUB ();
void MercProfilesConvertToDat ();
void ConvertBinaryData170to254 ();
#endif

BOOLEAN sUSTAW[500]; //legion2
BOOLEAN sNPCSPEECH[NUM_PROFILES]; //legion2
BOOLEAN sSPEECH[NUM_PROFILES]; //legion2

BOOLEAN JA2EncryptedFileWriteNEW( HWFILE hFile, PTR pDest, UINT32 uiBytesToWrite, UINT32 *puiBytesWritten );
BOOLEAN JA2EncryptedFileReadNEW( HWFILE hFile, PTR pDest, UINT32 uiBytesToRead, UINT32 *puiBytesRead );


//#define ROTATION_ARRAY_SIZE 46
UINT8 ubRotationArrayNew[46] = { 132, 235, 125, 99, 15, 220, 140, 89, 205, 132, 254, 144, 217, 78, 156, 58, 215, 76, 163, 187, 55, 49, 65, 48, 156, 140, 201, 68, 184, 13, 45, 69, 102, 185, 122, 225, 23, 250, 160, 220, 114, 240, 64, 175, 057, 233 };

BOOLEAN JA2EncryptedFileReadNEW( HWFILE hFile, PTR pDest, UINT32 uiBytesToRead, UINT32 *puiBytesRead )
{
	UINT32	uiLoop;
	UINT8		ubArrayIndex = 0;
	//UINT8		ubLastNonBlank = 0;
	UINT8		ubLastByte = 0;
//	UINT8		ubLastByteForNextLoop;
	BOOLEAN	fRet;
	UINT8 *	pMemBlock;

	fRet = FileRead( hFile, pDest, uiBytesToRead, puiBytesRead );
	if ( fRet )
	{
		pMemBlock = (UINT8 *)pDest;
		for ( uiLoop = 0; uiLoop < *puiBytesRead; uiLoop++ )
		{
		//	ubLastByteForNextLoop = pMemBlock[ uiLoop ];
		//	pMemBlock[ uiLoop ] -= (ubLastByte + ubRotationArrayNew[ ubArrayIndex ]);
		//	ubArrayIndex++;
		//	if ( ubArrayIndex >= ROTATION_ARRAY_SIZE )
		//	{
		//		ubArrayIndex = 0;
		//	}
		//	ubLastByte = ubLastByteForNextLoop;
		}
	}

	return( fRet );
}


BOOLEAN JA2EncryptedFileWriteNEW( HWFILE hFile, PTR pDest, UINT32 uiBytesToWrite, UINT32 *puiBytesWritten )
{
	UINT32	uiLoop;
	UINT8		ubArrayIndex = 0;
	//UINT8		ubLastNonBlank = 0;
	UINT8		ubLastByte = 0;//, ubTemp;
	UINT8 * pMemBlock;
	BOOLEAN	fRet;

	pMemBlock = (UINT8 *) MemAlloc( uiBytesToWrite );

	if ( !pMemBlock )
	{
		return( FALSE );
	}
	memset( pMemBlock, 0, uiBytesToWrite );


	memcpy( pMemBlock, pDest, uiBytesToWrite );
	for ( uiLoop = 0; uiLoop < uiBytesToWrite; uiLoop++ )
	{
		//ubTemp = pMemBlock[ uiLoop ];
	//	pMemBlock[ uiLoop ] += ubLastByte + ubRotationArrayNew[ ubArrayIndex ];
	//	ubArrayIndex++;
	//	if ( ubArrayIndex >= ROTATION_ARRAY_SIZE )
	//	{
	//		ubArrayIndex = 0;
	//	}
	//	ubLastByte = pMemBlock[ uiLoop ];

	}

	fRet = FileWrite( hFile, pMemBlock, uiBytesToWrite, puiBytesWritten );

	MemFree( pMemBlock );

	return( fRet );

}

#ifdef WFconvertUB

void ConvertBinaryData170to254 ()
{
	HWFILE fptr1;
	HWFILE fptr2;
	UINT32 uiLoop;
	UINT32	uiNumBytesRead;
	CHAR8	zFileName[255];
	
	fptr1 = FileOpen("binarydata\\JA25PROF.dat", FILE_ACCESS_READ, FALSE );  					
	
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{
	JA2EncryptedFileRead ( fptr1, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );	
	}
	FileClose( fptr1 );	
	
	fptr2 = FileOpen("binarydata\\JA25PROF-Out.dat", FILE_ACCESS_WRITE, FALSE );  	
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{	
	JA2EncryptedFileWrite ( fptr2, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );
	}
	FileClose( fptr2 );

}

void MercProfilesConvertToDat ()
{
	HWFILE fptr1;
	HWFILE fptr2;
	UINT32 uiLoop;
	UINT32	uiNumBytesRead;
	CHAR8	zFileName[255];
	
	fptr1 = FileOpen("binarydata\\JA25PROF.dat", FILE_ACCESS_READ, FALSE );  					
	
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{

	JA2EncryptedFileRead ( fptr1, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );	
	}
	FileClose( fptr1 );	
	
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{
	
	sprintf( zFileName, "TEMP2\\Mercs%03d.dat", uiLoop );	
	
	fptr2 = FileOpen(zFileName, FILE_ACCESS_WRITE, FALSE );  
	

	
	JA2EncryptedFileWriteNEW ( fptr2, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );
	
	FileClose( fptr2 );
	
	}


}

void WFtoUB ()
{
	HWFILE fptr1;
	HWFILE fptr2;
	HWFILE fptr3;
	STR8 pFileNameWF = "TEMP2\\Prof-WF.dat";
	STR8 pFileNameUB = "TEMP2\\Prof-UB.dat";
	STR8 pFileNameJA2 = "TEMP2\\Prof-JA2.dat";
	STR8 pFileNameOut = "TEMP2\\Prof-Out.dat";
	
	UINT32 uiLoop, uiLoop2;
	UINT32	uiNumBytesRead;

	fptr1 = FileOpen("TEMP2\\Prof-WF.dat", FILE_ACCESS_READ, FALSE );  
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{
	JA2EncryptedFileRead ( fptr1, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );
	}
	FileClose( fptr1 );
	
	fptr2 = FileOpen("TEMP2\\Prof-UB.dat", FILE_ACCESS_READ, FALSE );  
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{
	JA2EncryptedFileRead ( fptr2, &gMercProfilesUB[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );
	}
	FileClose( fptr2 );
	
	fptr3 = FileOpen("TEMP2\\Prof-Out.dat", FILE_ACCESS_WRITE, FALSE );
	for(uiLoop=0; uiLoop< NUM_PROFILES; uiLoop++)
	{
		if ( uiLoop < 51 )
		{
			JA2EncryptedFileWrite ( fptr3, &gMercProfilesWF[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );
		}
		else if ( uiLoop >= 51 )
		{
			JA2EncryptedFileWrite ( fptr3, &gMercProfilesUB[uiLoop], sizeof( MERCPROFILESTRUCT_OLD_WF ), &uiNumBytesRead );		
		}
	}
	FileClose( fptr3 );

}
#endif

#ifdef JA2UB

void RandomAddEnemy( UINT8 SectorX, UINT8 SectorY, UINT8 Level )
{
UNDERGROUND_SECTORINFO *pSector;
UINT8 ubNumAdmins = 0;
UINT8 ubNumTroops = 0;
UINT8 ubNumElites = 0;

	if ( Level != 0 )
	{
	pSector = FindUnderGroundSector( SectorX, SectorY, Level );
	if ( pSector )
	{
		if ( pSector->fVisited != TRUE )
		{
			switch( gGameOptions.ubDifficultyLevel )
			{
			case DIF_LEVEL_EASY:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 10 + Random( 5 );
				ubNumElites = Random( 4 );			
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_MEDIUM:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 15 + Random( 8 );
				ubNumElites = 1 + Random( 2 );		
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_HARD:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 20 + Random( 7 );
				ubNumElites = 2 + Random( 2 );	
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_INSANE:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 20 + Random( 3 );
				ubNumElites = 6 + Random( 3 );		
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			}
		}
	}
	}
	else
	{
		if ( !GetSectorFlagStatus( SectorX, SectorY, Level, SF_ALREADY_VISITED ) )
		{
			switch( gGameOptions.ubDifficultyLevel )
			{
			case DIF_LEVEL_EASY:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 10 + Random( 5 );
				ubNumElites = Random( 4 );			
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_MEDIUM:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 15 + Random( 8 );
				ubNumElites = 1 + Random( 2 );		
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_HARD:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 23 + Random( 7);
				ubNumElites = 2 + Random( 2 );	
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			case DIF_LEVEL_INSANE:
				ubNumAdmins = Random( 0 );
				ubNumTroops = 20 + Random( 3 );
				ubNumElites = 6 + Random( 3 );		
				SetNumberJa25EnemiesInSector( SectorX, SectorY, Level, ubNumAdmins, ubNumTroops, ubNumElites );
				break;
			}
		}
	}
}

#endif

//----LEGION 2---------
BOOLEAN HandleSlotA( SOLDIERTYPE *pSoldier, UINT32 uiHandPos, UINT16 usReplaceItem, UINT8 Profil_Legion, UINT32 Przedmiot, UINT8 Tekst_EDT )
{
	INT32							cnt;
	UINT32						usITEMS;
	UINT16	usidEDT;
	INT32	usidSLOT;
	UINT32 Profil_Legion2;
	BOOLEAN fRefuse = FALSE;
	UINT32 val;
	
	
			for ( cnt = 0; cnt < NUM_PROFILES; cnt++ )
			{
				// We've found one!
				if ( ProfileNum_Legion[ cnt ] == pSoldier->ubProfile )
				{
					usITEMS				= gLegionSloty[ cnt ].idITEMS;
					Profil_Legion2 = gLegionSloty[ cnt ].idAIM;
					usidEDT = gLegionSloty[ cnt ].idEDT;
					usidSLOT = gLegionSloty[ cnt ].idSLOT;			
				}
			}
			
	//if 	( Profil_Legion2 > -1 )	
	//{
	if ( pSoldier->ubProfile == Profil_Legion2 ) //Profil_Legion )
	{

		if (usidSLOT == 0) val = HELMETPOS; 
		else if (usidSLOT == 1) val = VESTPOS; 
		else if (usidSLOT == 2) val = LEGPOS;
		else if (usidSLOT == 3) val = HEAD1POS; 
		else if (usidSLOT == 4) val = HEAD2POS;  
		else if (usidSLOT == 5) val = HANDPOS; 
		else if (usidSLOT == 6) val = SECONDHANDPOS; 
		else val = HANDPOS; 
		
		if ( uiHandPos == val )//|| uiHandPos == SECONDHANDPOS )
		{
			if ( usReplaceItem == NOTHING )
			{
				fRefuse = TRUE;
			}
			else
			{	//legion
				// Do we have nothing or the leather vest or kevlar leather vest?
				if ( usReplaceItem == usITEMS ) 
				{
					// This is good....
					fRefuse = FALSE;
				}
				else
				{
					fRefuse = TRUE;
				}
			}

			if ( fRefuse )
			{
				// Say quote!
				TacticalCharacterDialogue( pSoldier, usidEDT );
				return( TRUE );
			}
		}
	}
//}
	return( FALSE );
}

BOOLEAN HandleSlotB( SOLDIERTYPE *pSoldier, UINT32 uiHandPos, UINT16 usReplaceItem, UINT8 Profil_Legion, UINT32 Przedmiot, UINT8 Tekst_EDT )
{
	INT32							cnt;
	UINT32						usITEMS;
	UINT16	usidEDT;
	INT32	usidSLOT;
	UINT32 Profil_Legion2;
	BOOLEAN fRefuse = FALSE;
	UINT32 val;
	
	
			for ( cnt = 0; cnt < NUM_PROFILES; cnt++ )
			{
				// We've found one!
				if ( ProfileNum_Legion[ cnt ] == pSoldier->ubProfile )
				{
					usITEMS				= gLegionSloty[ cnt ].idITEMS2;
					Profil_Legion2 = gLegionSloty[ cnt ].idAIM2;
					usidEDT = gLegionSloty[ cnt ].idEDT2;
					usidSLOT = gLegionSloty[ cnt ].idSLOT2;			
				}
			}
			
	//if 	( Profil_Legion2 > -1 )	
	//{
	if ( pSoldier->ubProfile == Profil_Legion2 ) //Profil_Legion )
	{

		if (usidSLOT == 0) val = HELMETPOS; 
		else if (usidSLOT == 1) val = VESTPOS; 
		else if (usidSLOT == 2) val = LEGPOS;
		else if (usidSLOT == 3) val = HEAD1POS; 
		else if (usidSLOT == 4) val = HEAD2POS;  
		else if (usidSLOT == 5) val = HANDPOS; 
		else if (usidSLOT == 6) val = SECONDHANDPOS; 
		else val = HANDPOS; 
		
		if ( uiHandPos == val )//|| uiHandPos == SECONDHANDPOS )
		{
			if ( usReplaceItem == NOTHING )
			{
				fRefuse = TRUE;
			}
			else
			{	//legion
				// Do we have nothing or the leather vest or kevlar leather vest?
				if ( usReplaceItem == usITEMS ) 
				{
					// This is good....
					fRefuse = FALSE;
				}
				else
				{
					fRefuse = TRUE;
				}
			}

			if ( fRefuse )
			{
				// Say quote!
				TacticalCharacterDialogue( pSoldier, usidEDT );
				return( TRUE );
			}
		}
	}
//}
	return( FALSE );
}
//-----------

//Wy��cz\W��czy d�wi�k
void Ustaw_NPC_SPEECH ()
{
INT cnt,i;
BOOLEAN Wyb2; 
CHAR8						zFileName[255];

	for ( cnt = 0; cnt < NUM_PROFILES; cnt++ )
		{	
		sNPCSPEECH[cnt]		= TRUE;
		sSPEECH[cnt]		= TRUE;
		}
		
		

			for( i = 0; i < NUM_PROFILES; i++ )
			{
			sprintf( zFileName, "TABLEDATA\\Profile\\aim\\prof%03d.ini", i );			

				if (FileExists(zFileName))
				{
				CIniReader iniReader(zFileName);
				Wyb2	= iniReader.ReadBoolean("PROF","SPEECH",TRUE);
				
				if (Wyb2 == TRUE) { sNPCSPEECH[i] = TRUE; } else sNPCSPEECH[i] = FALSE;
				if (Wyb2 == TRUE) { sSPEECH[i] = TRUE; } else sSPEECH[i] = FALSE;
				
				}
			}	
			
			for( i = 0; i < NUM_PROFILES; i++ )
			{
			sprintf( zFileName, "TABLEDATA\\Profile\\npc\\prof%03d.ini", i );			

				if (FileExists(zFileName))
				{
				CIniReader iniReader(zFileName);
				Wyb2	= iniReader.ReadBoolean("PROF","SPEECH",TRUE);
				if (Wyb2 == TRUE) { sNPCSPEECH[i] = TRUE; } else sNPCSPEECH[i] = FALSE;
				if (Wyb2 == TRUE) { sSPEECH[i] = TRUE; } else sSPEECH[i] = FALSE;
				}
			}	
			
			for( i = 0; i < NUM_PROFILES; i++ )
			{
			sprintf( zFileName, "TABLEDATA\\Profile\\merc\\prof%03d.ini", i );			

				if (FileExists(zFileName))
				{
				CIniReader iniReader(zFileName);
				Wyb2	= iniReader.ReadBoolean("PROF","SPEECH",TRUE);
				if (Wyb2 == TRUE) { sNPCSPEECH[i] = TRUE; } else sNPCSPEECH[i] = FALSE;
				if (Wyb2 == TRUE) { sSPEECH[i] = TRUE; } else sSPEECH[i] = FALSE;
				}
			}	

}

void LoadGameLegionOptions()
{

	CIniReader iniReader(GAME_LEGION_OPTIONS_FILE);

	//Unfinished Business
	
	gGameLegionOptions.ZAIKONA1 = iniReader.ReadBoolean("Unfinished Business","BORDER_TOWN", TRUE);
	gGameLegionOptions.ZAIKONA2 = iniReader.ReadBoolean("Unfinished Business","BORDER_MINE", TRUE);
	gGameLegionOptions.ZAIKONA3 = iniReader.ReadBoolean("Unfinished Business","BORDER_TEAMS", TRUE);
	gGameLegionOptions.ZAIKONA4 = iniReader.ReadBoolean("Unfinished Business","BORDER_MILITIA", FALSE);
	gGameLegionOptions.ZAIKONA5 = iniReader.ReadBoolean("Unfinished Business","BORDER_AIRSPACE", TRUE);
	gGameLegionOptions.ZAIKONA6 = iniReader.ReadBoolean("Unfinished Business","BORDER_ITEM", TRUE);
	
	//gGameLegionOptions.SF_UB = iniReader.ReadBoolean("Unfinished Business","SF", FALSE);
	
	gGameLegionOptions.EVENT_ATTACK_INITIAL_SECTOR_IF_PLAYER_STILL_THERE_UB = iniReader.ReadBoolean("Unfinished Business","EVENT_ATTACK_INITIAL_SECTOR_IF_PLAYER_STILL_THERE", TRUE);
	
	gGameLegionOptions.HandleAddingEnemiesToTunnelMaps_UB = iniReader.ReadBoolean("Unfinished Business","HANDLE_ADDING_ENEMIES_TO_TUNNEL_MAPS", TRUE);

	gGameLegionOptions.ubDefaultArrivalSectorX	= iniReader.ReadInteger("Unfinished Business","DEFAULT_ARRIVAL_SECTOR_X", 9, 1, 16);
	gGameLegionOptions.ubDefaultArrivalSectorY	= iniReader.ReadInteger("Unfinished Business","DEFAULT_ARRIVAL_SECTOR_Y", 1, 1, 16);

	gGameExternalOptions.ubDefaultArrivalSectorX	= gGameLegionOptions.ubDefaultArrivalSectorX;
	gGameExternalOptions.ubDefaultArrivalSectorY	= gGameLegionOptions.ubDefaultArrivalSectorY;
	
	JA2_5_START_SECTOR_X = gGameLegionOptions.ubDefaultArrivalSectorX;
	JA2_5_START_SECTOR_Y = gGameLegionOptions.ubDefaultArrivalSectorY;
	
	gGameLegionOptions.ubEndDefaultSectorX	= iniReader.ReadInteger("Unfinished Business","DEFAULT_END_SECTOR_X", 16, 1, 16);
	gGameLegionOptions.ubEndDefaultSectorY	= iniReader.ReadInteger("Unfinished Business","DEFAULT_END_SECTOR_Y", 11, 1, 16);
	gGameLegionOptions.ubEndDefaultSectorZ	= iniReader.ReadInteger("Unfinished Business","DEFAULT_END_SECTOR_Z", 0, 0, 16);

	gGameLegionOptions.iStartingCashNovice		= iniReader.ReadInteger("Unfinished Business", "STARTING_CASH_NOVICE",40000, 2000, 0x0FFFFFFF);
	gGameLegionOptions.iStartingCashExperienced	= iniReader.ReadInteger("Unfinished Business", "STARTING_CASH_EXPERIENCED",35000, 2000, 0x0FFFFFFF);
	gGameLegionOptions.iStartingCashExpert		= iniReader.ReadInteger("Unfinished Business", "STARTING_CASH_EXPERT",30000, 2000, 0x0FFFFFFF);
	gGameLegionOptions.iStartingCashInsane		= iniReader.ReadInteger("Unfinished Business", "STARTING_CASH_INSANE",15000, 2000, 0x0FFFFFFF);

	gGameExternalOptions.iStartingCashNovice		= gGameLegionOptions.iStartingCashNovice;
	gGameExternalOptions.iStartingCashExperienced	= gGameLegionOptions.iStartingCashExperienced;
	gGameExternalOptions.iStartingCashExpert		= gGameLegionOptions.iStartingCashExpert;
	gGameExternalOptions.iStartingCashInsane		= gGameLegionOptions.iStartingCashInsane;
	
	gGameLegionOptions.AUTO_RESOLVE_UB = iniReader.ReadBoolean("Unfinished Business","AUTO_RESOLVE", FALSE);
	
	gGameLegionOptions.INITIALHELIGRIDNO[ 0 ]  = iniReader.ReadInteger("Unfinished Business","GridNo1", 14947);
	gGameLegionOptions.INITIALHELIGRIDNO[ 1 ]  = iniReader.ReadInteger("Unfinished Business","GridNo2", 15584);
	gGameLegionOptions.INITIALHELIGRIDNO[ 2 ]  = iniReader.ReadInteger("Unfinished Business","GridNo3", 15754);
	gGameLegionOptions.INITIALHELIGRIDNO[ 3 ]  = iniReader.ReadInteger("Unfinished Business","GridNo4", 16232);
	gGameLegionOptions.INITIALHELIGRIDNO[ 4 ]  = iniReader.ReadInteger("Unfinished Business","GridNo5", 16067);
	gGameLegionOptions.INITIALHELIGRIDNO[ 5 ]  = iniReader.ReadInteger("Unfinished Business","GridNo6", 16230);
	gGameLegionOptions.INITIALHELIGRIDNO[ 6 ]  = iniReader.ReadInteger("Unfinished Business","GridNo7", 15272);
	
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 0 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes1",  1300);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 1 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes2",  2000);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 2 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes3",  2750);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 3 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes4",  3400);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 4 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes5",  4160);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 5 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes6",  4700);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 6 ]  = iniReader.ReadInteger("Unfinished Business","HeliRandomTimes7",  5630);

	gGameLegionOptions.LOCATEGRIDNO  = iniReader.ReadInteger("Unfinished Business","InternalLocateGridNo",  15427);
	
	
	//gGameLegionOptions.LOCATEGRIDNO2 = iniReader.ReadInteger("Unfinished Business","InternalLocateGridNo",  0);
	
	//if ( gGameLegionOptions.LOCATEGRIDNO == 0 )
	//	gGameLegionOptions.LOCATEGRIDNO = gMapInformation.sNorthGridNo;
	
	gGameLegionOptions.InGameHeliCrash = iniReader.ReadBoolean("Unfinished Business","InGameHeliCrash", TRUE);
	gGameLegionOptions.JerryQuotes = iniReader.ReadBoolean("Unfinished Business","JerryQuotes", TRUE);
	gGameLegionOptions.InJerry = iniReader.ReadBoolean("Unfinished Business","Jerry", TRUE);	
	gGameLegionOptions.JerryGridNo = iniReader.ReadInteger("Unfinished Business","JerryGridNo", 15109);	
	gGameLegionOptions.InGameHeli = iniReader.ReadBoolean("Unfinished Business","InGameHeli", FALSE);	
	
	if ( gGameLegionOptions.InGameHeli == TRUE ) 
		gGameLegionOptions.InGameHeliCrash = FALSE;
	
	if ( gGameLegionOptions.InGameHeliCrash == TRUE )
		gGameLegionOptions.InGameHeli = FALSE;
	
	if ( gGameLegionOptions.InGameHeli == TRUE && gGameLegionOptions.InGameHeliCrash == TRUE ) 
		{
			gGameLegionOptions.InGameHeliCrash = TRUE;
			gGameLegionOptions.InGameHeli = FALSE;
		}

	//Campaign Section
	
	gGameLegionOptions.EnemyXML = TRUE; //iniReader.ReadBoolean("Campaign","USE_ENEMY_XML", TRUE);
	gGameLegionOptions.ADD_RANDOM_ENEMY_TO_SECTOR_UB = iniReader.ReadBoolean("Campaign","ADD_RANDOM_ENEMY_TO_SECTOR", FALSE);
	gGameLegionOptions.StrategicMovementCostsXML = iniReader.ReadBoolean("Campaign","STRATEGIC_MOVEMENT_COSTS_XML", FALSE);
	gGameLegionOptions.CampaignSector = iniReader.ReadBoolean("Campaign","MAKE_STRATEGIC_MOVEMENT_COSTS", FALSE);
	
	gGameLegionOptions.LaptopQuestEnabled = iniReader.ReadBoolean("Campaign","Laptop_Quest", TRUE);
	
	gGameLegionOptions.pJA2UB = iniReader.ReadBoolean("Campaign","JA2UB", TRUE);
	
	gGameLegionOptions.fDeadMerc = iniReader.ReadBoolean("Campaign","AIM_SYSTEM", FALSE);
	
	
	gGameLegionOptions.MercStartingGear25XML = TRUE;//iniReader.ReadBoolean("UB","USE_MERC_STARTING_GEAR_XML", FALSE);
	gGameLegionOptions.MercStartingGear25XML = TRUE;//iniReader.ReadBoolean("UB","USE_MERC_STARTING_GEAR_XML", FALSE);
	
	gGameLegionOptions.LAPTOP_IMP_PASS_JA2  = iniReader.ReadBoolean("Laptop","IMP_PASS_JA2",  FALSE);
	
	gGameLegionOptions.LAPTOP_IMP_PASS_UB  = iniReader.ReadBoolean("Laptop","IMP_PASS_UB",  TRUE);
	
	gGameLegionOptions.LaptopLinkInsurance  = iniReader.ReadBoolean("Laptop","LINK_INSURANCE",  FALSE);
	gGameLegionOptions.LaptopLinkFuneral  = iniReader.ReadBoolean("Laptop","LINK_FUNERAL",  TRUE);
	gGameLegionOptions.LaptopLinkBobby  = iniReader.ReadBoolean("Laptop","LINK_BOBBY",  FALSE);
	gGameLegionOptions.fBobbyRSite  = iniReader.ReadBoolean("Laptop","BOBBY_SITE_ACCESSED",  FALSE);
	
	//LaptopSaveInfo.fBobbyRSiteCanBeAccessed = gGameLegionOptions.fBobbyRSite;

	//gGameLegionOptions.RISRAPORT  = iniReader.ReadBoolean("Laptop","RIS_RAPORT",  TRUE);
	
	gGameLegionOptions.OLDUBInventory = FALSE; //iniReader.ReadBoolean("Unfinished Business","OLD_UB_ITEMS", FALSE);	

	
	gGameLegionOptions.SWITCHINMORRISAREA_GRIDNOa = iniReader.ReadInteger("Unfinished Business","SWITCH_IN_MORRIS_AREA_GRIDNO", 15231);	
	gGameLegionOptions.SWITCHTOLAUNCHMISSLES_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","SWITCH_TO_LAUNCH_MISSLES_GRIDNO1", 14268);	
	gGameLegionOptions.SWITCHTOLAUNCHMISSLES_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","SWITCH_TO_LAUNCH_MISSLES_GRIDNO2", 15708);	
	gGameLegionOptions.RADIOLOCATORS_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","RADIO_LOCATORS_GRIDNO1", 15070);	
	gGameLegionOptions.RADIOLOCATORS_GRIDNO2a = iniReader.ReadInteger("Unfinished Business","RADIO_LOCATORS_GRIDNO2", 14744);	
	gGameLegionOptions.POWERGENSECTOR_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","POWERGEN_SECTOR_GRIDNO1", 15100);	
	gGameLegionOptions.POWERGENSECTOR_GRIDNO2a = iniReader.ReadInteger("Unfinished Business","POWERGEN_SECTOR_GRIDNO2", 12220);	
	gGameLegionOptions.POWERGENSECTOR_GRIDNO3a = iniReader.ReadInteger("Unfinished Business","POWERGEN_SECTOR_GRIDNO3", 14155);	
	gGameLegionOptions.POWERGENSECTOR_GRIDNO4a = iniReader.ReadInteger("Unfinished Business","POWERGEN_SECTOR_GRIDNO4", 13980);	
	
	gGameLegionOptions.POWERGENSECTOREXITGRID_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","POWERGEN_SECTOR_EXITGRID_GRIDNO", 19749);	
	gGameLegionOptions.POWERGENFANSOUND_GRIDNO1a = iniReader.ReadInteger("Unfinished Business","POWERGEN_FAN_SOUND_GRIDNO1", 10979);	
	gGameLegionOptions.POWERGENFANSOUND_GRIDNO2a = iniReader.ReadInteger("Unfinished Business","POWERGEN_FAN_SOUND_GRIDNO2", 19749);	
	gGameLegionOptions.STARTFANBACKUPAGAIN_GRIDNOa = iniReader.ReadInteger("Unfinished Business","START_FANBACKUP_AGAIN_GRIDNO", 10980);	
	gGameLegionOptions.STOPPOWERGENFAN_GRIDNOa = iniReader.ReadInteger("Unfinished Business","STOP_POWERGEN_FAN_GRIDNO", 10980);

	//sec J13
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[0] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO1", 10978);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[1] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO2", 10979);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[2] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO3", 10980);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[3] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO4", 10818);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[4] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO5", 10819);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[5] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO6", 10820);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[6] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO7", 10658);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[7] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO8", 10659);
	gGameLegionOptions.IsFanGraphicInSectorAtThisGridNoA[8] = iniReader.ReadInteger("Unfinished Business","ISFANGRAPHICINSECTORATTHISGRIDNO9", 10660);

//	gGameLegionOptions.BobbyRayInventory_UB = iniReader.ReadBoolean("Unfinished Business","INIT_BOBBYRAY_INVENTORY", FALSE);
//	gGameLegionOptions.InitTownLoyalty_UB = iniReader.ReadBoolean("Unfinished Business","INIT_TOWN_LOYALTY", FALSE);

	/* 
	gGameLegionOptions.LAPTOPZAIKONA1	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_MAIL", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA2	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_WWW", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA3	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_FILES", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA4	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_PERSONAL", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA5	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_HISTORY", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA6	 		 = iniReader.ReadBoolean("Unfinished Business","BUTTON_FINANSE", TRUE);
	*/
}