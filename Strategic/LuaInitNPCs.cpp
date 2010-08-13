#include <iostream>
#include <string>
#include <sstream>

#include "Lua Interpreter.h"

#include "connect.h"
#include "FileMan.h"
#include "GameSettings.h"
#include "Game Init.h"
#include "interface Dialogue.h"
#include "opplist.h"
#include "Strategic All.h"
#include "pits.h"

#include "Luaglobal.h"
#include "Quests.h"
#include "ai.h"
#include "Game Clock.h"
#include "interface Dialogue.h"
#include "Map Screen Helicopter.h"
#include "NPC.h"
#include "Strategic AI.h"
#include "Tactical Save.h"
#include "Items.h"
#include "Handle Items.h"
#include "Overhead.h"
#include "LuaInitNPCs.h"
#include "ShopKeeper Interface.h"
#include "Explosion Control.h"
#include "soldier tile.h"
#include "Soldier Profile.h"
#include "Soldier Functions.h"
#include "soldier tile.h"
#include "Action Items.h"
#include "AIInternals.h"
#include "Handle Doors.h"
#include "soldier profile type.h"
#include "Soldier Profile.h"

#include "LOS.h"
#include "Music Control.h"

#include "Ja25 Strategic Ai.h"
#include "Ja25_Tactical.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

//Mercs
static int l_AddNPC(lua_State *L);
static int l_AddNPCTOSECTOR(lua_State *L);
static int l_bNPCData(lua_State *L);

//Sector
static int l_AddAlternateSector(lua_State *L);
static int l_AddAltUnderGroundSectorNew(lua_State *L);
static int l_AddAltUnderGroundSector(lua_State *L);
static int l_AddAlternateSectorNew(lua_State *L);

//Other
static int l_HospitalTempBalance(lua_State *L);
static int l_HospitalRefund(lua_State *L);
static int l_HospitalPriceModifier(lua_State *L);
static int l_gfPlayerTeamSawJoey(lua_State *L);
static int l_CheckForMissingHospitalSupplies(lua_State *L);

//transaction
static int l_AddTransactionToPlayersBook (lua_State *L);

//Time
static int l_GetWorldTotalMin (lua_State *L);

//GameExternalOptions
static int l_GetStartingCashNovice (lua_State *L);
static int l_GetStartingCashExperienced (lua_State *L);
static int l_GetStartingCashExpert (lua_State *L);
static int l_GetStartingCashInsane (lua_State *L);

//email
static int l_AddPreReadEmail (lua_State *L);
static int l_AddEmail (lua_State *L);

static int l_SectorInfoBloodCats(lua_State *L);
static int l_SectorEnemy(lua_State *L);

//Facts
static int l_SetFactFalse(lua_State *L);
static int l_SetFactTrue(lua_State *L);

static int lh_getIntegerFromTable(lua_State *L, const char * fieldname);
static std::string lh_getStringFromTable(lua_State *L, const char * fieldname);;
static bool locationStringToCoordinates_AltSector(std::string loc, UINT8* x, UINT8* y);
static bool locationStringToCoordinates(std::string loc, UINT8* x, UINT8* y, UINT8* z);

static int l_Ja25SaveStructJohnKulbaIsInGame(lua_State *L);
static int l_Ja25SaveCheckStructJohnKulbaIsInGame(lua_State *L);

static int l_Ja25SaveStructubJohnKulbaInitialSectorY(lua_State *L);
static int l_Ja25SaveStructubJohnKulbaInitialSectorX(lua_State *L);

static int l_GuaranteeAtLeastXItemsOfIndex(lua_State *L);

static int l_gMercProfileGearset(lua_State *L);

using namespace std;

void IniFunction(lua_State *L)
{
	lua_register(L, "AddNPC", l_AddNPC);
	lua_register(L, "AddNPCtoSector", l_AddNPCTOSECTOR);	
	
	//sector
	lua_register(L, "AddAlternateSector", l_AddAlternateSector);
	lua_register(L, "AddAltSector", l_AddAlternateSector);	
	
	lua_register(L, "AddAltUnderGroundSector", l_AddAltUnderGroundSector);
	lua_register(L, "AddAltUGSector", l_AddAltUnderGroundSector);	
	
	lua_register(L, "AddAltSectorNew", l_AddAlternateSectorNew);
	lua_register(L, "AddAltUGSectorNew", l_AddAltUnderGroundSectorNew);

	lua_register(L, "CheckForMissingHospitalSupplies", l_CheckForMissingHospitalSupplies);
	lua_register(L, "HospitalTempBalance", l_HospitalTempBalance);
	lua_register(L, "HospitalRefund", l_HospitalRefund);
	lua_register(L, "HospitalPriceModifier", l_HospitalPriceModifier);
	lua_register(L, "PlayerTeamSawJoey", l_gfPlayerTeamSawJoey);
	
	lua_register(L, "SetNPCData1", l_bNPCData);
	
	lua_register(L, "AddTransactionToPlayersBook", l_AddTransactionToPlayersBook );
	lua_register(L, "GetWorldTotalMin", l_GetWorldTotalMin );	
	
	//gGameExternalOptions
	
	lua_register(L, "GetStartingCashNovice", l_GetStartingCashNovice );
	lua_register(L, "GetStartingCashExperienced", l_GetStartingCashExperienced );
	lua_register(L, "GetStartingCashExpert", l_GetStartingCashExpert );
	lua_register(L, "GetStartingCashInsane", l_GetStartingCashInsane );
	
	//Email
	lua_register(L, "AddPreReadEmail", l_AddPreReadEmail);
	lua_register(L, "AddEmail", l_AddEmail);
	
	//Add enemy and bloodcats
	lua_register(L, "GetSectorInfoBloodCats", l_SectorInfoBloodCats);
	lua_register(L, "SectorEnemy", l_SectorEnemy);
	
	//Fact and Quest
	lua_register(L, "SetFactTrue", l_SetFactTrue);
	lua_register(L, "SetFactFalse", l_SetFactFalse);
	
	//john
	lua_register(L, "Ja25JohnKulbaIsInGame", l_Ja25SaveStructJohnKulbaIsInGame);
	lua_register(L, "Ja25CheckJohnKulbaIsInGame", l_Ja25SaveCheckStructJohnKulbaIsInGame);
	lua_register(L, "Ja25JohnKulbaInitialSectorY", l_Ja25SaveStructubJohnKulbaInitialSectorY);
	lua_register(L, "Ja25JohnKulbaInitialSectorX", l_Ja25SaveStructubJohnKulbaInitialSectorX);	
	
	//Shop
	lua_register(L, "GuaranteeAtLeastXItemsOfIndex", l_GuaranteeAtLeastXItemsOfIndex);	
	
	lua_register(L, "MercProfileSetBIGPOCK2POS", l_gMercProfileGearset);	

}


BOOLEAN LetLuaGameInit(UINT8 Init)
{
	char * filename = "scripts\\GameInit.lua";
	UINT32 size, bytesRead;
	char* buffer;

	HWFILE file = FileOpen(filename, FILE_ACCESS_READ, FALSE);

	if (!file)
		return false;

	size = FileSize(filename);
	buffer = new char[size+1];
	buffer[size] = 0;
	FileRead(file, buffer, size, &bytesRead);
	FileClose(file);

	lua_State *L = lua_open();
	luaL_openlibs(L);

	IniFunction(L);
	IniGlobalGameSetting(L);
	
	if (luaL_dostring(L, buffer))
	{
		// oh noes, error
		// TODO: write to log or something
		return false;
	}
	
	if ( Init == 0 )
	{
		lua_getglobal(L , "InitNewGame");
		lua_call(L,0,0); 
	}
	
	if ( Init == 1 )
	{
		lua_getglobal(L , "InitNPCs");
		lua_call(L,0,0); 
	}
	
	lua_close(L);

	delete[] buffer;
	
	
	return true;

}

static int l_gMercProfileGearset(lua_State *L)
{
UINT8 n = lua_gettop(L);
UINT8 ID;
UINT16 inv;
UINT8 status;
UINT8 number;
UINT8 drop;
int i;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) ID = lua_tointeger(L,i);
		if (i == 2 ) inv = lua_tointeger(L,i);
		if (i == 3 ) number = lua_tointeger(L,i);
		if (i == 4 ) status = lua_tointeger(L,i);
		if (i == 5 ) drop = lua_tointeger(L,i);
	}

		
gMercProfileGear[ID].inv[BIGPOCK2POS] = inv;
gMercProfileGear[ID].iNumber[BIGPOCK2POS] = number;
gMercProfileGear[ID].iStatus[BIGPOCK2POS] = status;
gMercProfileGear[ID].iDrop[BIGPOCK2POS] = drop;
	
	return 0;
}

static int l_GuaranteeAtLeastXItemsOfIndex(lua_State *L)
{
UINT8 n = lua_gettop(L);
UINT8 ShopID;
UINT16 ItemsID;
UINT32 VAL;
int i;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) ShopID = lua_tointeger(L,i);
		if (i == 2 ) ItemsID = lua_tointeger(L,i);
		if (i == 3 ) VAL = lua_tointeger(L,i);
	}

		
	GuaranteeAtLeastXItemsOfIndex( ShopID, ItemsID, VAL );
	
	return 0;
}

static int l_Ja25SaveStructubJohnKulbaInitialSectorY(lua_State *L)
{
UINT32 Y;
UINT8 n = lua_gettop(L);

	 Y = lua_tointeger(L,n);

	gJa25SaveStruct.ubJohnKulbaInitialSectorY = Y;
	return 0;
}

static int l_Ja25SaveStructubJohnKulbaInitialSectorX(lua_State *L)
{
UINT32 X;
UINT8 n = lua_gettop(L);

	 X = lua_tointeger(L,n);

	gJa25SaveStruct.ubJohnKulbaInitialSectorX = X;
	return 0;
}

//gJa25SaveStruct.fJohnKulbaIsInGame
static int l_Ja25SaveCheckStructJohnKulbaIsInGame(lua_State *L)
{
BOOLEAN FactFalse;
UINT8 n = lua_gettop(L);

	FactFalse = gJa25SaveStruct.fJohnKulbaIsInGame;
	
	lua_pushboolean(L, FactFalse);

	return 1;
}


//gJa25SaveStruct.fJohnKulbaIsInGame
static int l_Ja25SaveStructJohnKulbaIsInGame(lua_State *L)
{
BOOLEAN FactFalse;
UINT8 n = lua_gettop(L);

	 FactFalse = lua_toboolean(L,n);

	gJa25SaveStruct.fJohnKulbaIsInGame = FactFalse;
	return 0;
}

// set fact = false
static int l_SetFactFalse(lua_State *L)
{
UINT32 FactFalse;
UINT8 n = lua_gettop(L);

	 FactFalse = lua_tointeger(L,n);

	SetFactFalse (FactFalse);
	return 0;
}


//set fact = true
static int l_SetFactTrue(lua_State *L)
{
UINT32 FactTrue;
UINT8 n = lua_gettop(L);

	FactTrue = lua_tointeger(L,n);

	SetFactTrue (FactTrue);

	return 0;
}

static int l_SectorInfoBloodCats(lua_State *L)
{
UINT8  n = lua_gettop(L);
int i;
UINT8 idSector;
UINT8 val;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) idSector = lua_tointeger(L,i);
	}
					
			val = SectorInfo[ idSector ].bBloodCats;
		
	lua_pushinteger(L, val);
	
return 1;
}

static int l_SectorEnemy(lua_State *L)
{
UINT16 x = -1;
UINT16 y = -1;
UINT16 z = -1;
UINT8 TROOPS_ILOSC = 0;
UINT8 ELITA_ILOSC = 0;
UINT CREATURE_ILOSC = 0;

	if ( ( x >= 1 || x <= 16 ) && ( y >= 1 || y <= 16 ) )
		{
			x = lh_getIntegerFromTable(L, "SectorX");
			y = lh_getIntegerFromTable(L, "SectorY");
			
			TROOPS_ILOSC = lh_getIntegerFromTable(L, "Troops");
			ELITA_ILOSC = lh_getIntegerFromTable(L, "Elite");
			CREATURE_ILOSC = lh_getIntegerFromTable(L, "Creature");
				
			//z = lh_getIntegerFromTable(L, "SectorZ");
					
			SectorInfo[ (UINT8)SECTOR(  x,  y ) ].ubNumTroops = TROOPS_ILOSC;
			SectorInfo[ (UINT8)SECTOR(  x,  y ) ].ubNumElites = ELITA_ILOSC;
			SectorInfo[ (UINT8)SECTOR(  x,  y ) ].ubNumCreatures = CREATURE_ILOSC;	
		}
		
	return 0;
}

//AddEmail
static int l_AddEmail (lua_State *L)
{
UINT8  n = lua_gettop(L);
int i;
INT32 iMessageOffset;
INT32 iMessageLength;
UINT8 ubSender;
INT32 iCurrentIMPPosition;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) iMessageOffset = lua_tointeger(L,i);
		if (i == 2 ) iMessageLength = lua_tointeger(L,i);
		if (i == 3 ) ubSender = lua_tointeger(L,i);
		//if (i == 4 ) iDate = lua_tointeger(L,i);
		if (i == 4 ) iCurrentIMPPosition = lua_tointeger(L,i);
	}

	AddEmail(iMessageOffset,iMessageLength,ubSender,	GetWorldTotalMin(), iCurrentIMPPosition);	
	
return 0;
}
	
//AddPreReadEmail	
static int l_AddPreReadEmail (lua_State *L)
{
UINT8  n = lua_gettop(L);
int i;
INT32 iMessageOffset;
INT32 iMessageLength;
UINT8 ubSender;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) iMessageOffset = lua_tointeger(L,i);
		if (i == 2 ) iMessageLength = lua_tointeger(L,i);
		if (i == 3 ) ubSender = lua_tointeger(L,i);
	}

	AddPreReadEmail(iMessageOffset,iMessageLength,ubSender,	GetWorldTotalMin());	
	
return 0;
}

//set chracter NPCDATA1
static int l_bNPCData(lua_State *L)
{
UINT32 set;
UINT8 Profile;
UINT8 n = lua_gettop(L);
int i;


	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) Profile = lua_tointeger(L,i);
		if (i == 2 ) set = lua_tointeger(L,i);
	}
	
	gMercProfiles[Profile].bNPCData = set;

	return 0;
}

//CheckForMissingHospitalSupplies
static int l_CheckForMissingHospitalSupplies(lua_State *L)
{
	CheckForMissingHospitalSupplies ();
	return 0;
}

//Add undern Ground Sector
static int l_AddAltUnderGroundSectorNew(lua_State *L)
{
UINT8 x,y,z;
UINT8  n = lua_gettop(L);
int i;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) x = lua_tointeger(L,i);
		if (i == 2 ) y = lua_tointeger(L,i);
		if (i == 3 ) z = lua_tointeger(L,i);
	}
	
	if ((x>=1 || x<=16) && (y>=1 || y<=16) && (z>=0 || z<=3) )
	{	
		UNDERGROUND_SECTORINFO *pSector;
		pSector = FindUnderGroundSector( x, y, z ); 
		if( pSector )
		{
			pSector->uiFlags |= SF_USE_ALTERNATE_MAP;
		}
	}
	
	return 0;	
}


//----------------GameExternalOptions------------

//Get starting cash insane level
static int l_GetStartingCashInsane (lua_State *L)
{
UINT8  n = lua_gettop(L);
UINT32 val;
	
	val = gGameExternalOptions.iStartingCashInsane;
	
	lua_pushinteger(L, val);
	
return 1;
}

//Get starting cash expert level
static int l_GetStartingCashExpert (lua_State *L)
{
UINT8  n = lua_gettop(L);
UINT32 val;
	
	val = gGameExternalOptions.iStartingCashExpert;
	
	lua_pushinteger(L, val);
	
return 1;
}

//Get starting cash experienced level
static int l_GetStartingCashExperienced (lua_State *L)
{
UINT8  n = lua_gettop(L);
UINT32 val;
	
	val = gGameExternalOptions.iStartingCashExperienced;
	
	lua_pushinteger(L, val);
	
return 1;
}

//Get starting cash novice level
static int l_GetStartingCashNovice (lua_State *L)
{
UINT8  n = lua_gettop(L);
UINT32 val;
	
	val = gGameExternalOptions.iStartingCashNovice;
	
	lua_pushinteger(L, val);
	
return 1;
}

//Get world time
static int l_GetWorldTotalMin (lua_State *L)
{
UINT8  n = lua_gettop(L);
UINT32 uiDate; 

	uiDate = GetWorldTotalMin();
return 0;
}

//---------------------Other----------------------
//Add cash to player
static int l_AddTransactionToPlayersBook (lua_State *L)
{
UINT8  n = lua_gettop(L);
int i;
UINT8 ubCode;
UINT8 ubSecondCode; 
UINT32 uiDate; 
INT32 iAmount;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) ubCode = lua_tointeger(L,i);
		if (i == 2 ) ubSecondCode = lua_tointeger(L,i);
		if (i == 3 ) uiDate = lua_tointeger(L,i);
		if (i == 4 ) iAmount = lua_tointeger(L,i);
	}

	AddTransactionToPlayersBook(ubCode, ubSecondCode, uiDate, iAmount);
return 0;
}

//Add alternate sector
static int l_AddAlternateSectorNew(lua_State *L)
{
UINT8 x,y;
UINT8  n = lua_gettop(L);
int i;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) x = lua_tointeger(L,i);
		if (i == 2 ) y = lua_tointeger(L,i);
	}

	if ((x>=1 || x<=16) && (y>=1 || y<=16))
	{	
		SectorInfo[ SECTOR( x, y ) ].uiFlags |= SF_USE_ALTERNATE_MAP;
	}
	
	return 0;
}

//Add npc to sector
static int l_AddNPCTOSECTOR(lua_State *L)
{
MERCPROFILESTRUCT * pProfile;
UINT8 x,y,z,id;
UINT8  n = lua_gettop(L);
int i;

	for (i= 1; i<=n; i++ )
	{
		if (i == 1 ) id = lua_tointeger(L,i);
		if (i == 2 ) x = lua_tointeger(L,i);
		if (i == 3 ) y = lua_tointeger(L,i);
		if (i == 4 ) z = lua_tointeger(L,i);
	}
	 
	if ( (x>=0 || x<=16) && (y>=0 || y<=16) && (z>=0 || z<=3) )
		{
		pProfile = &(gMercProfiles[ id ]);
	
		pProfile->sSectorX = x;
		pProfile->sSectorY = y;
		pProfile->bSectorZ = z;
		}
	
	return 0;
}

//set Hospital Temp Balance
static int l_HospitalTempBalance(lua_State *L)
{
UINT32 Balance;
UINT8 n = lua_gettop(L);

	 Balance = lua_tointeger(L,n);

	giHospitalTempBalance = Balance;
	return 0;
}

//set PlayerTeamSawJoey
static int l_gfPlayerTeamSawJoey(lua_State *L)
{
BOOLEAN set;
UINT8 n = lua_gettop(L);

	 set = lua_toboolean(L,n);

	gfPlayerTeamSawJoey = set;
	return 0;
}

// set
static int l_HospitalRefund(lua_State *L)
{
UINT32 Balance;
UINT8 n = lua_gettop(L);

	 Balance = lua_tointeger(L,n);

	giHospitalRefund = Balance;
	return 0;
}

//set
static int l_HospitalPriceModifier(lua_State *L)
{
UINT32 Balance;
UINT8 n = lua_gettop(L);

	 Balance = lua_tointeger(L,n);

	gbHospitalPriceModifier = Balance;
	return 0;
}
static int l_AddNPC(lua_State *L)
{
MERCPROFILESTRUCT * pProfile;

std::string sector_id = lh_getStringFromTable(L, "sector");
UINT8 idNPC;
UINT8 x,y,z;

	if (locationStringToCoordinates(sector_id, &x, &y, &z))
	{
		idNPC = lh_getIntegerFromTable(L, "MercProfiles");

		pProfile = &(gMercProfiles[ idNPC ]);
	
		pProfile->sSectorX = x;
		pProfile->sSectorY = y;
		pProfile->bSectorZ = z;
	}
			
	return 0;
}

static int l_AddAlternateSector(lua_State *L)
{

std::string sector_id = lh_getStringFromTable(L, "altSector");

UINT8 x,y;

	if (locationStringToCoordinates_AltSector(sector_id, &x, &y))
	{
		//x = lh_getIntegerFromTable(L, "AltSecX");
		//y = lh_getIntegerFromTable(L, "AltSecY");
		SectorInfo[ SECTOR( x, y ) ].uiFlags |= SF_USE_ALTERNATE_MAP;
	}
	return 0;
}

static int l_AddAltUnderGroundSector(lua_State *L)
{

std::string sector_id = lh_getStringFromTable(L, "altSector");

UINT8 x,y,z;

	if (locationStringToCoordinates(sector_id, &x, &y, &z))
	{
		UNDERGROUND_SECTORINFO *pSector;
		pSector = FindUnderGroundSector( x, y, z ); 
		if( pSector )
		{
			pSector->uiFlags |= SF_USE_ALTERNATE_MAP;
		}
	}
	
	return 0;	// number of results
}

static int lh_getIntegerFromTable(lua_State *L, const char * fieldname)
{
	lua_getfield(L, -1, fieldname);
	int i = lua_tointeger(L, -1);
	lua_pop(L, 1);
	return i;
}

static std::string lh_getStringFromTable(lua_State *L, const char * fieldname)
{
	lua_getfield(L, -1, fieldname);
	string s = lua_tostring(L, -1);
	lua_pop(L, 1);
	return s;
}

static bool locationStringToCoordinates_AltSector(std::string loc, UINT8* x, UINT8* y)
{
	int length = loc.length();
	
	// gather row
	if (length < 2 || length > 3)
		return false;
	
	char row = loc[0];
	if (row >= 'A' && row <= 'P')
	{
		*y = row - 'A' + 1;
	}
	else if (row >= 'a' && row <= 'p')
	{
		*y = row - 'a' + 1;
	}
	else
	{
		return false;
	}
	
	// gather column
#if 0
	loc = loc.substr(1);
	stringstream ss = stringstream();
	if (loc[0] >= '0' && loc[0] <= '9')
	{
		ss << loc[0];
		loc = loc.substr(1);
	}
	if (loc[0] >= '0' && loc[0] <= '9')
	{
		ss << loc[0];
		loc = loc.substr(1);
	}
#else
	stringstream ss(loc.substr(1));
#endif
	int col = 0;
	ss >> col;
	if (col >= 1 && col <= 16)
	{
		*x = col;
	}
	else
	{
		return false;
	}
	
	return true;
}

// extract x,y,z from strings like "D13-1"
static bool locationStringToCoordinates(std::string loc, UINT8* x, UINT8* y, UINT8* z)
{
	int length = loc.length();
	
	// gather row
	if (length < 4 || length > 5)
		return false;
	
	char row = loc[0];
	if (row >= 'A' && row <= 'P')
	{
		*y = row - 'A' + 1;
	}
	else if (row >= 'a' && row <= 'p')
	{
		*y = row - 'a' + 1;
	}
	else
	{
		return false;
	}
	
	// gather column
#if 0
	loc = loc.substr(1);
	stringstream ss = stringstream();
	if (loc[0] >= '0' && loc[0] <= '9')
	{
		ss << loc[0];
		loc = loc.substr(1);
	}
	if (loc[0] >= '0' && loc[0] <= '9')
	{
		ss << loc[0];
		loc = loc.substr(1);
	}
#else
	stringstream ss(loc);
#endif
	int col = 0;
	ss >> col;
	if (col >= 1 && col <= 16)
	{
		*x = col;
	}
	else
	{
		return false;
	}
	
	// gather level
	char lvl = loc[loc.length() - 1];
	if (lvl >= '0' && lvl <= '3')
	{
		*z = lvl - '0';
	}
	else
	{
		return false;
	}
	return true;
}