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
//	#include "XMLWriter.h"
#endif

#ifdef JA2UB
#include "Ja25 Strategic Ai.h"
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
UINT32	ProfileNum_Legion[200];
SLOTY_LEGION_VALUES gLegionSloty[200];

SOUND_PROFILE_VALUES gSoundProfileValue[NUM_PROFILES];
RANDOM_STATS_VALUES gRandomStatsValue[NUM_PROFILES];

#define				GAME_LEGION_OPTIONS_FILE	"UB_Options.ini"
#define				LAPTOP_OPTIONS_FILE	"Ja2_laptop.ini"

#define				BadSectorsList_FILE	"BadSectorsList.ini"

extern void Ustaw_NPC_SPEECH ();
extern void Ustaw_parametry ();

void LoadGameLegionOptions();

#ifdef JA2UB
void RandomAddEnemy( UINT8 SectorX, UINT8 SectorY, UINT8 Level );
#endif

BOOLEAN sUSTAW[500]; //legion2
BOOLEAN sNPCSPEECH[171]; //legion2
BOOLEAN sSPEECH[171]; //legion2

void RandomStats ()
{
UINT32 cnt;
INT8 bBaseAttribute = 0;
MERCPROFILESTRUCT * pProfile;

	for ( cnt = 0; cnt < NUM_PROFILES; cnt++ )
	{
		if ( gRandomStatsValue[cnt].Enabled == TRUE )
			{
				//if ( gRandomStatsValue[cnt].uiIndex == cnt )
				//	{
						bBaseAttribute = gRandomStatsValue[cnt].BaseAttribute + ( 4 * gRandomStatsValue[cnt].ExpLevel );
						pProfile = &(gMercProfiles[cnt]);
					
						pProfile->bExpLevel = gRandomStatsValue[cnt].ExpLevel;

						if ( gRandomStatsValue[cnt].RandomLife == TRUE )
							{
								pProfile->bLifeMax = (bBaseAttribute + Random( 9 ) + Random( 8 ));
								pProfile->bLife = pProfile->bLifeMax;
							}	
							
						if ( gRandomStatsValue[cnt].RandomAgility == TRUE )
							{
								pProfile->bAgility = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}							
							
						if ( gRandomStatsValue[cnt].RandomLeadership == TRUE )
							{
								pProfile->bLeadership = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}							
														
						if ( gRandomStatsValue[cnt].RandomDexterity == TRUE )
							{
								pProfile->bDexterity = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}	
							
						if ( gRandomStatsValue[cnt].RandomWisdom == TRUE )
							{
								pProfile->bWisdom = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}	
							
						if ( gRandomStatsValue[cnt].RandomMarksmanship == TRUE )
							{
								pProfile->bMarksmanship = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}	
							
						if ( gRandomStatsValue[cnt].RandomMedical == TRUE )
							{
								pProfile->bMedical = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}
							
						if ( gRandomStatsValue[cnt].RandomMechanical == TRUE )
							{
								pProfile->bMechanical = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}	

						if ( gRandomStatsValue[cnt].RandomExplosive == TRUE )
							{
								pProfile->bExplosive = (bBaseAttribute + Random( 9 ) + Random( 8 ));
							}								
				//	}	
			}
	}
}

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
	
	
			for ( cnt = 0; cnt < 200; cnt++ )
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
		if (usidSLOT == 1) val = VESTPOS; 
		if (usidSLOT == 2) val = LEGPOS;
		if (usidSLOT == 3) val = HEAD1POS; 
		if (usidSLOT == 4) val = HEAD2POS;  
		if (usidSLOT == 5) val = HANDPOS; 
		if (usidSLOT == 6) val = SECONDHANDPOS; 
		
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
	
	
			for ( cnt = 0; cnt < 200; cnt++ )
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
		if (usidSLOT == 1) val = VESTPOS; 
		if (usidSLOT == 2) val = LEGPOS;
		if (usidSLOT == 3) val = HEAD1POS; 
		if (usidSLOT == 4) val = HEAD2POS;  
		if (usidSLOT == 5) val = HANDPOS; 
		if (usidSLOT == 6) val = SECONDHANDPOS; 
		
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

//Wy³¹cz\W³¹czy dŸwiêk
void Ustaw_NPC_SPEECH ()
{
INT cnt,i;
BOOLEAN Wyb2; 
CHAR8						zFileName[255];

	for ( cnt = 0; cnt < 171; cnt++ )
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

	gGameLegionOptions.ZAIKONA1 = iniReader.ReadBoolean("UB","BORDER_TOWN", TRUE);
	gGameLegionOptions.ZAIKONA2 = iniReader.ReadBoolean("UB","BORDER_MINE", TRUE);
	gGameLegionOptions.ZAIKONA3 = iniReader.ReadBoolean("UB","BORDER_TEAMS", TRUE);
	gGameLegionOptions.ZAIKONA4 = iniReader.ReadBoolean("UB","BORDER_MILITIA", FALSE);
	gGameLegionOptions.ZAIKONA5 = iniReader.ReadBoolean("UB","BORDER_AIRSPACE", TRUE);
	gGameLegionOptions.ZAIKONA6 = iniReader.ReadBoolean("UB","BORDER_ITEM", TRUE);
	
	gGameLegionOptions.SF_UB = iniReader.ReadBoolean("UB","SF", FALSE);
	
	gGameLegionOptions.EnemyXML = iniReader.ReadBoolean("UB","USE_ENEMY_XML", TRUE);
	
	gGameLegionOptions.EVENT_ATTACK_INITIAL_SECTOR_IF_PLAYER_STILL_THERE_UB = iniReader.ReadBoolean("UB","EVENT_ATTACK_INITIAL_SECTOR_IF_PLAYER_STILL_THERE", TRUE);
	gGameLegionOptions.HandleAddingEnemiesToTunnelMaps_UB = iniReader.ReadBoolean("UB","HANDLE_ADDING_ENEMIES_TO_TUNNEL_MAPS", TRUE);

	gGameLegionOptions.AUTO_RESOLVE_UB = iniReader.ReadBoolean("UB","AUTO_RESOLVE", FALSE);
	
	gGameLegionOptions.ADD_RANDOM_ENEMY_TO_SECTOR_UB = iniReader.ReadBoolean("UB","ADD_RANDOM_ENEMY_TO_SECTOR", FALSE);
	
	gGameLegionOptions.StrategicMovementCostsXML = iniReader.ReadBoolean("UB","STRATEGIC_MOVEMENT_COSTS_XML", FALSE);
	
	gGameLegionOptions.CampaignSector = iniReader.ReadBoolean("UB","MAKE_STRATEGIC_MOVEMENT_COSTS", FALSE);
	
	gGameLegionOptions.MercStartingGear25XML = TRUE;//iniReader.ReadBoolean("UB","USE_MERC_STARTING_GEAR_XML", FALSE);
	
	gGameLegionOptions.MercStartingGear25XML = TRUE;//iniReader.ReadBoolean("UB","USE_MERC_STARTING_GEAR_XML", FALSE);
	
	gGameLegionOptions.INITIALHELIGRIDNO[ 0 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo1", 14947);
	gGameLegionOptions.INITIALHELIGRIDNO[ 1 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo2", 15584);
	gGameLegionOptions.INITIALHELIGRIDNO[ 2 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo3", 15754);
	gGameLegionOptions.INITIALHELIGRIDNO[ 3 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo4", 16232);
	gGameLegionOptions.INITIALHELIGRIDNO[ 4 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo5", 16067);
	gGameLegionOptions.INITIALHELIGRIDNO[ 5 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo6", 16230);
	gGameLegionOptions.INITIALHELIGRIDNO[ 6 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","GridNo7", 15272);
	
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 0 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes1",  1300);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 1 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes2",  2000);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 2 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes3",  2750);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 3 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes4",  3400);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 4 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes5",  4160);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 5 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes6",  4700);
	gGameLegionOptions.INITIALHELIRANDOMTIMES[ 6 ]  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","HeliRandomTimes7",  5630);
	
	gGameLegionOptions.LOCATEGRIDNO  = iniReader.ReadInteger("IN_GAME_HELI_CRASH","InternalLocateGridNo",  15427);
	
	
//	gGameLegionOptions.BobbyRayInventory_UB = iniReader.ReadBoolean("UB","INIT_BOBBYRAY_INVENTORY", FALSE);
//	gGameLegionOptions.InitTownLoyalty_UB = iniReader.ReadBoolean("UB","INIT_TOWN_LOYALTY", FALSE);

	/* 
	gGameLegionOptions.LAPTOPZAIKONA1	 		 = iniReader.ReadBoolean("UB","BUTTON_MAIL", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA2	 		 = iniReader.ReadBoolean("UB","BUTTON_WWW", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA3	 		 = iniReader.ReadBoolean("UB","BUTTON_FILES", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA4	 		 = iniReader.ReadBoolean("UB","BUTTON_PERSONAL", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA5	 		 = iniReader.ReadBoolean("UB","BUTTON_HISTORY", TRUE);
	gGameLegionOptions.LAPTOPZAIKONA6	 		 = iniReader.ReadBoolean("UB","BUTTON_FINANSE", TRUE);
	*/
}