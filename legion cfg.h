#ifndef _LEGION_CFG_H
#define _LEGION_CFG_H

#include "soldier profile type.h"

extern BOOLEAN sUSTAW[500];
extern BOOLEAN sNPCSPEECH[171];
extern BOOLEAN sSPEECH[171];

extern void LoadGameLegionOptions();

typedef struct
{ 
  BOOLEAN			  CamoFaceLegion[256];
  BOOLEAN			  C1Legion[256];
  BOOLEAN			  C2Legion[256];
  BOOLEAN			  C3Legion[256];
  BOOLEAN			  C4Legion[256];
  BOOLEAN			  C5Legion[256];
  BOOLEAN			  C6Legion[256];
  BOOLEAN			  C7Legion[256];
  BOOLEAN			  C8Legion[256];
  BOOLEAN			  C9Legion[256];
  BOOLEAN			  C10Legion[256];
  BOOLEAN			  C11Legion[256];
  BOOLEAN			  C12Legion[256];
} Legion2Dane;


extern BOOLEAN HandleSlotA( SOLDIERTYPE *pSoldier, UINT32 uiHandPos, UINT16 usReplaceItem, UINT8 Profil_Legion, UINT32 Przedmiot, UINT8 Tekst_EDT );
extern BOOLEAN HandleSlotB( SOLDIERTYPE *pSoldier, UINT32 uiHandPos, UINT16 usReplaceItem, UINT8 Profil_Legion, UINT32 Przedmiot, UINT8 Tekst_EDT );

//--------------legion------------------------------
typedef struct
{
	
	//slot A
	INT32 		idAIM;
	UINT16		idEDT;
	UINT32		idSLOT;
	UINT32		idITEMS;
	//Slot B
	INT32 		idAIM2;
	UINT16		idEDT2;
	UINT32		idSLOT2;
	UINT32		idITEMS2;

} SLOTY_LEGION_VALUES;

//legion
extern UINT32	ProfileNum_Legion[200];
extern SLOTY_LEGION_VALUES gLegionSloty[200];
//---------------------------------------------------


typedef struct
{
	UINT16		uiIndex; // add
	BOOLEAN EnabledSound;

} SOUND_PROFILE_VALUES;

extern SOUND_PROFILE_VALUES gSoundProfileValue[NUM_PROFILES];

typedef struct
{
    BOOLEAN ZAIKONA1;
    BOOLEAN ZAIKONA2;
    BOOLEAN ZAIKONA3;
    BOOLEAN ZAIKONA4;
    BOOLEAN ZAIKONA5;
    BOOLEAN ZAIKONA6;
	
	BOOLEAN SF_UB;
    
	
    BOOLEAN LAPTOPZAIKONA1;
    BOOLEAN LAPTOPZAIKONA2;
    BOOLEAN LAPTOPZAIKONA3;
    BOOLEAN LAPTOPZAIKONA4;
    BOOLEAN LAPTOPZAIKONA5;
    BOOLEAN LAPTOPZAIKONA6;
	
	BOOLEAN EnemyXML;
	BOOLEAN EVENT_ATTACK_INITIAL_SECTOR_IF_PLAYER_STILL_THERE_UB;
	BOOLEAN HandleAddingEnemiesToTunnelMaps_UB;
	BOOLEAN BobbyRayInventory_UB;
	BOOLEAN InitTownLoyalty_UB;
	BOOLEAN AUTO_RESOLVE_UB;
	BOOLEAN ADD_RANDOM_ENEMY_TO_SECTOR_UB;
       
} GAME_LEGION_OPTIONS;

extern GAME_LEGION_OPTIONS gGameLegionOptions; 
extern Legion2Dane	gLegion2Dane; //legion
extern void RandomAddEnemy( UINT8 SectorX, UINT8 SectorY, UINT8 Level );
#endif