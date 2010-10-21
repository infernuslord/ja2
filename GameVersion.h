#ifndef _GAME_VERSION_H_
#define _GAME_VERSION_H_


#ifdef __cplusplus
extern "C" {
#endif


//
//	Keeps track of the game version
//

extern	CHAR16		zVersionLabel[256];
extern	CHAR8		czVersionNumber[16];
extern	CHAR16		zTrackingNumber[16];


//ADB:	I needed these here so I moved them, and why put them in *.cpp anyways?
//
//		Keeps track of the saved game version.	Increment the saved game version whenever 
//	you will invalidate the saved game file
#define			SAVE_GAME_VERSION								113	//111	//110	//109	//108	//107	//106	//105	//104	//103	//102	//101	//100 // 99

#define			CURRENT_SAVEGAME_DATATYPE_VERSION				113

#define			NAS_MERCS_PROFILES								113	// New Mercs profiles
#define			NAS_SAVEGAME_DATATYPE_CHANGE					112	// Before this, NAS settings (ON/OFF) was not saved to the savegame
#define			STOMP12_SAVEGAME_DATATYPE_CHANGE				111	// Before this, STOMP v1.2 was not included in the source
#define			BUGFIX_NPC_DATA_FOR_BIG_MAPS					110 // Before this, we had a bug in the NPC Data for Big Maps (this fix was introduced in the Closed Beta)
#define			STRATEGIC_MINES_DATATYPE_CHANGE					109 // Before this, we did not have strategic mines initialization via lua script
#define			HIDE_NPC_NAMES_FOR_UNKNOWN_PERSONS				108	// Before this, we did not have hiding of npc names for unknown persons included (by jazz)
#define			BIG_MAPS_PROJECT_SAVEGAME_DATATYPE_CHANGE		107	// Before this, we did not have big maps project 
#define			AIRPORT_SAVEGAME_DATATYPE_CHANGE				106	// Before this, we did not have airport externalized
#define			AP100_SAVEGAME_DATATYPE_CHANGE					105	// Before this, we didn't have the 100AP structure changes
#define			NIV_SAVEGAME_DATATYPE_CHANGE					102	// Before this, we used the old structure system


//#define RUSSIANGOLD
#ifdef __cplusplus
}
#endif


#endif
