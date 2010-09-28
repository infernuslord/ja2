#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "HelpScreen.h"
	#include "Multilingual Text Code Generator.h"
	#include "INIReader.h"

#else
	#include "builddefines.h"
	#include <stdio.h>
	#include "sgp.h"
	#include "Gameloop.h"
	#include "Screens.h"
	#include "Wcheck.h"
	#include "INIReader.h"
	#include "vobject_blitters.h"
	#include "renderworld.h"
	#include "mousesystem.h"
	#include "sysutil.h"
	#include "worlddef.h"
	#include "Animation Data.h"
	#include "overhead.h"
	#include "Font Control.h"
	#include "Button System.h"
	#include "Timer Control.h"
	#include "Utilities.h"
	#include "Radar Screen.h"
	#include "Render Dirty.h"
	#include "cursors.h"
	#include "Sound Control.h"
	#include "Event Pump.h"
	#include "lighting.h"
	#include "Cursor Control.h"
	#include "music control.h"
	#include "video.h"
	#include "sys globals.h"
	#include "mapscreen.h"
	#include "interface items.h"
	#include "Maputility.h"
	#include "strategic.h"
	#include "dialogue control.h"
	#include "Text.h"
	#include "laptop.h"
	#include "NPC.h"
	#include "MercTextBox.h"
	#include "tile cache.h"
	#include "strategicmap.h"
	#include "Map Information.h"
	#include "laptop.h"
	#include "Shade Table Util.h"
	#include "Exit Grids.h"
	#include "Summary Info.h"
	#include "GameSettings.h"
	#include "Game Init.h"
	#include "Init.h"
	#include "jascreens.h"
	#include "XML.h"
	#include "SaveLoadGame.h"
	#include "weapons.h"
	#include "Strategic Movement.h"
	#include "Vehicles.h"
	#include "Multilingual Text Code Generator.h"
	#include "editscreen.h"
	#include "Arms Dealer Init.h"
#endif
#include "MPXmlTeams.hpp"
#include "Strategic Mines LUA.h"

#include "Interface.h"
#include "Strategic Town Loyalty.h"

#ifdef JA2UB
#include "Ja25_Tactical.h"
#endif

#include "legion cfg.h"


#include "Civ Quotes.h"
#include "Sector Summary.h"
extern INT16 APBPConstants[TOTAL_APBP_VALUES] = {0};
extern INT16 gubMaxActionPoints[28];//MAXBODYTYPES = 28... JUST GETTING IT TO WORK NOW.  GOTTHARD 7/2/08
extern BOOLEAN GetCDromDriveLetter( STR8	pString );

#include "PostalService.h"
extern CPostalService gPostalService;

// The InitializeGame function is responsible for setting up all data and Gaming Engine
// tasks which will run the game

#ifdef JA2EDITOR
#define BUILD_AS_EDITOR_ONLY
#else
#undef BUILD_AS_EDITOR_ONLY
#endif

#ifdef JA2BETAVERSION
extern	BOOLEAN	gfUseConsecutiveQuickSaveSlots;
#endif

#if defined( GERMAN ) && !defined( _DEBUG )
	//#define LASERLOCK_ENABLED
#endif


#ifdef LASERLOCK_ENABLED
	int	LASERLOK_Init( HINSTANCE hInstance );
	int	LASERLOK_Run();
	int	LASERLOK_Check();

	BOOLEAN	PrepareLaserLockSystem();
	void HandleLaserLockResult( BOOLEAN fSuccess );
//	int	TestCall( int n);
#endif

extern	HINSTANCE					ghInstance;

extern OBJECTTYPE GLOCK_17_ForUseWithLOS;

// Prepends the language prefix to the file name in a proposed path.
static void AddLanguagePrefix(STR fileName, const STR language)
{
	char *fileComponent;

	fileComponent = strrchr( fileName, '\\');
	if (fileComponent)
	{
		fileComponent++;
	}
	else
	{
		fileComponent = fileName;
	}

	// Make sure to use the overlap-safe version of memory copy
	memmove( fileComponent + strlen( language), fileComponent, strlen( fileComponent) + 1);
	memmove( fileComponent, language, strlen( language) );
}

static void AddLanguagePrefix(STR fileName)
{
#ifdef GERMAN 
	AddLanguagePrefix( fileName, GERMAN_PREFIX);
#endif
#ifdef RUSSIAN 
	AddLanguagePrefix( fileName, RUSSIAN_PREFIX);
#endif
#ifdef DUTCH 
	AddLanguagePrefix( fileName, DUTCH_PREFIX);
#endif
#ifdef POLISH 
	AddLanguagePrefix( fileName, POLISH_PREFIX);
#endif
#ifdef FRENCH 
	AddLanguagePrefix( fileName, FRENCH_PREFIX);
#endif
#ifdef ITALIAN 
	AddLanguagePrefix( fileName, ITALIAN_PREFIX);
#endif
#ifdef TAIWANESE 
	AddLanguagePrefix( fileName, TAIWANESE_PREFIX);
#endif
#ifdef CHINESE
	AddLanguagePrefix( fileName, CHINESE_PREFIX);
#endif
}

BOOLEAN LoadExternalGameplayData(STR directoryName)
{
	char fileName[MAX_PATH];

	//zilpin: pellet spread patterns externalized in XML
	//If file not found, or error, then the old hard-coded defaults are used by LOS.cpp
	//This needs to be loaded before AmmoTypes and Items because SpreadPatterns can be referenced by name or index.
	strcpy(fileName, directoryName);
	strcat(fileName, SPREADPATTERNSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSpreadPatterns(fileName), SPREADPATTERNSFILENAME);

	// WANNE: Enemy drops - begin
	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYMISCDROPSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInEnemyMiscDropsStats(gEnemyMiscDrops, fileName), ENEMYMISCDROPSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYEXPLOSIVEDROPSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInEnemyExplosiveDropsStats(gEnemyExplosiveDrops, fileName),ENEMYEXPLOSIVEDROPSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYWEAPONDROPSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInEnemyWeaponDropsStats(gEnemyWeaponDrops, fileName),ENEMYWEAPONDROPSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYAMMODROPSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInEnemyAmmoDropsStats(gEnemyAmmoDrops, fileName),ENEMYAMMODROPSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYARMOURDROPSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInEnemyArmourDropsStats(gEnemyArmourDrops, fileName),ENEMYARMOURDROPSFILENAME);
	// WANNE: Enemy drops - end

	// WANNE: Sector Loadscreens [2007-05-18]
	strcpy(fileName, directoryName);
	strcat(fileName, SECTORLOADSCREENSFILENAME);

	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInSectorLoadscreensStats(gSectorLoadscreens, fileName),SECTORLOADSCREENSFILENAME);
	}
	else
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("File does not exist, fileName = %s", fileName));
		// Reset ini-option
		gGameExternalOptions.gfUseExternalLoadscreens = FALSE;
	}

	strcpy(fileName, directoryName);
	strcat(fileName, AMMOTYPESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInAmmoTypeStats(fileName),AMMOTYPESFILENAME);

//Madd: Simple Localization
//Read in the correct ammostring file for the given language
	strcpy(fileName, directoryName);
#ifdef GERMAN
	strcat(fileName, GERMAN_PREFIX); // add German. prefix to filename
#endif
#ifdef RUSSIAN
	strcat(fileName, RUSSIAN_PREFIX); // add Russian. prefix to filename
#endif
#ifdef DUTCH
	strcat(fileName, DUTCH_PREFIX); // add Dutch. prefix to filename
#endif
#ifdef POLISH
	strcat(fileName, POLISH_PREFIX); // add Polish. prefix to filename
#endif
#ifdef FRENCH
	strcat(fileName, FRENCH_PREFIX); // add French. prefix to filename
#endif
#ifdef ITALIAN
	strcat(fileName, ITALIAN_PREFIX); // add Italian. prefix to filename
#endif
#ifdef TAIWANESE
	strcat(fileName, TAIWANESE_PREFIX); // add Taiwanese. prefix to filename
#endif
#ifdef CHINESE
	strcat(fileName, CHINESE_PREFIX); // add Chinese. prefix to filename
#endif
	strcat(fileName, AMMOFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	if(!ReadInAmmoStats(fileName))
	{
		//CHRISL: If we fail to load, try loading just the default english
		strcpy(fileName, directoryName);
		strcat(fileName, AMMOFILENAME);
		SGP_THROW_IFFALSE(!ReadInAmmoStats(fileName),AMMOFILENAME);
	}


	// Lesh: added this, begin
	strcpy(fileName, directoryName);
	strcat(fileName, BURSTSOUNDSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInBurstSoundArray(fileName),BURSTSOUNDSFILENAME);
	// Lesh: end

	strcpy(fileName, directoryName);
	strcat(fileName, ITEMSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInItemStats(fileName,FALSE),ITEMSFILENAME);

//Madd: Simple localization
// The idea here is that we can have a separate xml file that's named differently
// but only contains the relevant tags that need to be localized
// then when the file is read in using the same xml reader code, it will only overwrite
// the tags that are contained in the localized file.	This only works for items.xml 
// since I tweaked the xml_items.cpp to make it work :p
// So for instance, the german file would be called German.Items.xml and would only contain
// the uiIndex (for reference), szItemName, szLongItemName, szItemDesc, szBRName, and szBRDesc tags


#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInItemStats(fileName,TRUE))
			return FALSE;
	}
#endif

	//if(!WriteItemStats())
	//	return FALSE;

	strcpy(fileName, directoryName);
	strcat(fileName, SOUNDSFILENAME);
	SGP_THROW_IFFALSE(ReadInSoundArray(fileName),SOUNDSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, MAGAZINESFILENAME);
	SGP_THROW_IFFALSE(ReadInMagazineStats(fileName),MAGAZINESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ATTACHMENTSFILENAME);
	SGP_THROW_IFFALSE(ReadInAttachmentStats(fileName),ATTACHMENTSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ATTACHMENTINFOFILENAME);
	SGP_THROW_IFFALSE(ReadInAttachmentInfoStats(fileName),ATTACHMENTINFOFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, LAUNCHABLESFILENAME);
	SGP_THROW_IFFALSE(ReadInLaunchableStats(fileName),LAUNCHABLESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, COMPATIBLEFACEITEMSFILENAME);
	SGP_THROW_IFFALSE(ReadInCompatibleFaceItemStats(fileName),COMPATIBLEFACEITEMSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, MERGESFILENAME);
	SGP_THROW_IFFALSE(ReadInMergeStats(fileName),MERGESFILENAME);

	//if(!WriteMergeStats())
	//	return FALSE;

	strcpy(fileName, directoryName);
	strcat(fileName, ATTACHMENTCOMBOMERGESFILENAME);
	SGP_THROW_IFFALSE(ReadInAttachmentComboMergeStats(fileName),ATTACHMENTCOMBOMERGESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, EXPLOSIVESFILENAME);
	SGP_THROW_IFFALSE(ReadInExplosiveStats(fileName),EXPLOSIVESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ARMOURSFILENAME);
	SGP_THROW_IFFALSE(ReadInArmourStats(fileName),ARMOURSFILENAME);

	// CHRISL:
	strcpy(fileName, directoryName);
	strcat(fileName, LOADBEARINGEQUIPMENTFILENAME);
	SGP_THROW_IFFALSE(ReadInlbeStats(fileName),LOADBEARINGEQUIPMENTFILENAME);

	// CHRISL:
	LBEPocketType.clear();
	strcpy(fileName, directoryName);
	strcat(fileName, LBEPOCKETFILENAME);
	SGP_THROW_IFFALSE(ReadInLBEPocketStats(fileName,FALSE),LBEPOCKETFILENAME);

//CHRISL: Simple localization
// Same setup as what Madd used for items.xml

#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInLBEPocketStats(fileName,TRUE))
			return FALSE;
	}
#endif

#ifdef JA2UB
	//JA25 UB
	if ( gGameLegionOptions.MercStartingGear25XML == TRUE )
	{
	strcpy(fileName, directoryName);
	strcat(fileName, MERCSTARTINGGEAR25FILENAME);
	if ( FileExists(fileName) )
	{
	SGP_THROW_IFFALSE(ReadInMercStartingGearStats(fileName),MERCSTARTINGGEAR25FILENAME);
	}
	else
	{
#endif

	// CHRISL:
	strcpy(fileName, directoryName);
	strcat(fileName, MERCSTARTINGGEARFILENAME);
	SGP_THROW_IFFALSE(ReadInMercStartingGearStats(fileName),MERCSTARTINGGEARFILENAME);

#ifdef JA2UB
	}
	}
#endif

	strcpy(fileName, directoryName);
	strcat(fileName, WEAPONSFILENAME);
	SGP_THROW_IFFALSE(ReadInWeaponStats(fileName),WEAPONSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, INCOMPATIBLEATTACHMENTSFILENAME);
	SGP_THROW_IFFALSE(ReadInIncompatibleAttachmentStats(fileName),INCOMPATIBLEATTACHMENTSFILENAME);

	//WarmSteel - Attachment slots related xml's
	strcpy(fileName, directoryName);
	strcat(fileName, ATTACHMENTSLOTSFILENAME);
	SGP_THROW_IFFALSE(ReadInAttachmentSlotsStats(fileName),ATTACHMENTSLOTSFILENAME);

	//This one *always* after ReadInAttachmentSlotAssignStats and ReadInAttachmentSlotsStats.
	strcpy(fileName, directoryName);
	strcat(fileName, ITEMSLOTASSIGNFILENAME);
	SGP_THROW_IFFALSE(ReadInItemSlotAssignStats(fileName),ITEMSLOTASSIGNFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, NASINCOMPATIBLEATTACHMENTS);
	SGP_THROW_IFFALSE(ReadInNASIncompatibleAttachmentsStats(fileName),NASINCOMPATIBLEATTACHMENTS);

	strcpy(fileName, directoryName);
	strcat(fileName, ALTERINGATTACHMENTSFILENAME);
	SGP_THROW_IFFALSE(ReadInAlteringAttachmentsStats(fileName),ALTERINGATTACHMENTSFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYGUNCHOICESFILENAME);
	SGP_THROW_IFFALSE(ReadInExtendedArmyGunChoicesStats (fileName),ENEMYGUNCHOICESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ENEMYITEMCHOICESFILENAME);
	SGP_THROW_IFFALSE(ReadInArmyItemChoicesStats(fileName),ENEMYITEMCHOICESFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, IMPITEMCHOICESFILENAME);
	SGP_THROW_IFFALSE(ReadInIMPItemChoicesStats(fileName),IMPITEMCHOICESFILENAME);

	std::copy(DefaultarmsDealerInfo, 
			  DefaultarmsDealerInfo + sizeof(DefaultarmsDealerInfo)/sizeof(*DefaultarmsDealerInfo), 
			  armsDealerInfo.begin());

	strcpy(fileName, directoryName);
	strcat(fileName, TONYINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gTonyInventory,fileName),TONYINVENTORYFILENAME);

#ifdef JA2UB
//ja25 ub Biggins

	strcpy(fileName, directoryName);
	strcat(fileName, BETTYINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gBettyInventory,fileName),BETTYINVENTORYFILENAME);

	//UB
	strcpy(fileName, directoryName);
	strcat(fileName, RAULINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gRaulInventory,fileName),RAULINVENTORYFILENAME);

#else
	strcpy(fileName, directoryName);
	strcat(fileName, DEVININVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gDevinInventory,fileName),DEVININVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, PERKOINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gPerkoInventory,fileName),PERKOINVENTORYFILENAME);

#endif

	strcpy(fileName, directoryName);
	strcat(fileName, FRANZINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gFranzInventory,fileName),FRANZINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, KEITHINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gKeithInventory,fileName),KEITHINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, SAMINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gSamInventory,fileName),SAMINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, JAKEINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gJakeInventory,fileName),JAKEINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, HOWARDINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gHowardInventory,fileName),HOWARDINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, GABBYINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gGabbyInventory,fileName),GABBYINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, FRANKINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gFrankInventory,fileName),FRANKINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ELGININVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gElginInventory,fileName),ELGININVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, MANNYINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gMannyInventory,fileName),MANNYINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, HERVEINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gHerveInventory,fileName),HERVEINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, PETERINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gPeterInventory,fileName),PETERINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ALBERTOINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gAlbertoInventory,fileName),ALBERTOINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, CARLOINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gCarloInventory,fileName),CARLOINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, MICKEYINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gMickyInventory,fileName),MICKEYINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, ARNIEINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gArnieInventory,fileName),ARNIEINVENTORYFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, FREDOINVENTORYFILENAME);
	SGP_THROW_IFFALSE(ReadInInventoryStats(gFredoInventory,fileName),FREDOINVENTORYFILENAME);
	
	strcpy(fileName, directoryName);
	strcat(fileName, CITYTABLEFILENAME);
	SGP_THROW_IFFALSE(ReadInMapStructure(fileName, FALSE),CITYTABLEFILENAME);

#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInStrategicMapSectorTownNames(fileName, TRUE))
			return FALSE;
	}
#endif

	// Lesh: Strategic movement costs will be read in Strategic\Strategic Movement Costs.cpp,
	//		function BOOLEAN InitStrategicMovementCosts();
	//		It is called several times from various places and acts after clearing SectorInfo array

	// Lesh: load altsectors list
	strcpy(fileName, directoryName);
	strcat(fileName, ALTSECTORSFILENAME);
	SGP_THROW_IFFALSE(ReadInAltSectors(fileName),ALTSECTORSFILENAME);

	// Lesh: load samsites - must be after cities.xml
	strcpy(fileName, directoryName);
	strcat(fileName, SAMSITESFILENAME);
	SGP_THROW_IFFALSE(ReadInSAMInfo(fileName),SAMSITESFILENAME);

#ifdef JA2UB
	if ( gGameLegionOptions.EnemyXML == TRUE ) 
	{
#endif
	// Lesh: army externalization
	strcpy(fileName, directoryName);
	strcat(fileName, GARRISONFILENAME);
	SGP_THROW_IFFALSE(ReadInGarrisonInfo(fileName),GARRISONFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, PATROLFILENAME);
	SGP_THROW_IFFALSE(ReadInPatrolInfo(fileName),PATROLFILENAME);
#ifdef JA2UB
	}
#endif

	strcpy(fileName, directoryName);
	strcat(fileName, COMPOSITIONFILENAME);
	SGP_THROW_IFFALSE(ReadInArmyCompositionInfo(fileName),COMPOSITIONFILENAME);

	strcpy(fileName, directoryName);
	strcat(fileName, EXPLOSIONDATAFILENAME);
	SGP_THROW_IFFALSE(ReadInExplosionDataStats(fileName),EXPLOSIONDATAFILENAME);

	// Kaiden: Read in Restricted Sectors for Mobile Militia
	strcpy(fileName, directoryName);
	strcat(fileName, ROAMINGMILITIAFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInRoamingInfo(fileName),ROAMINGMILITIAFILENAME);

	// Dealtar: Read in shipping destinations and delivery methods
	gPostalService.Clear();
	strcpy(fileName, directoryName);
	strcat(fileName, SHIPPINGDESTINATIONSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInShippingDestinations(fileName, FALSE),SHIPPINGDESTINATIONSFILENAME);

#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInShippingDestinations(fileName, TRUE),SHIPPINGDESTINATIONSFILENAME);
	}
#endif
	
	strcpy(fileName, directoryName);
	strcat(fileName, DELIVERYMETHODSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInDeliveryMethods(fileName),DELIVERYMETHODSFILENAME);

	// HEADROCK HAM 3.5: Read in facility types
	strcpy(fileName, directoryName);
	strcat(fileName, FACILITYTYPESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInFacilityTypes(fileName,FALSE), FACILITYTYPESFILENAME);
	
#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInFacilityTypes(fileName,TRUE))
			return FALSE;
	}
#endif

	// HEADROCK HAM 3.4: Read in facility locations
	strcpy(fileName, directoryName);
	strcat(fileName, SECTORFACILITIESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSectorFacilities(fileName), SECTORFACILITIESFILENAME);

	// HEADROCK HAM 3.4: Read in dynamic roaming restrictions
	strcpy(fileName, directoryName);
	strcat(fileName, DYNAMICROAMINGFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInDynamicRoamingRestrictions(fileName), DYNAMICROAMINGFILENAME);
	
	// HEADROCK HAM 3.6: Read in customized sector names
	strcpy(fileName, directoryName);
	strcat(fileName, SECTORNAMESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSectorNames(fileName,FALSE,0), SECTORNAMESFILENAME);
#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInSectorNames(fileName,TRUE,0))
			return FALSE;
	}
#endif

	strcpy(fileName, directoryName);
	strcat(fileName, SECTORLEVEL1NAMESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSectorNames(fileName,FALSE,1), SECTORLEVEL1NAMESFILENAME);
	
#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInSectorNames(fileName,TRUE,1))
			return FALSE;
	}
#endif

	strcpy(fileName, directoryName);
	strcat(fileName, SECTORLEVEL2NAMESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSectorNames(fileName,FALSE,2), SECTORLEVEL2NAMESFILENAME);
	
#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInSectorNames(fileName,TRUE,2))
			return FALSE;
	}
#endif

	strcpy(fileName, directoryName);
	strcat(fileName, SECTORLEVEL3NAMESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSectorNames(fileName,FALSE,3), SECTORLEVEL3NAMESFILENAME);
	
#ifndef ENGLISH
	AddLanguagePrefix(fileName);
	if ( FileExists(fileName) )
	{
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		if(!ReadInSectorNames(fileName,TRUE,3))
			return FALSE;
	}
#endif

	// SANDRO - always initialize those files, we need it on game start
	//if (gGameExternalOptions.fReadProfileDataFromXML)
	//{
		// HEADROCK PROFEX: Read in Merc Profile data to replace PROF.DAT data
		strcpy(fileName, directoryName);
		strcat(fileName, MERCPROFILESFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInMercProfiles(fileName, FALSE), MERCPROFILESFILENAME);

		#ifndef ENGLISH
			AddLanguagePrefix(fileName);
				if ( FileExists(fileName) )
					{
					DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
					if(!ReadInMercProfiles(fileName,TRUE))
					return FALSE;
					}
		#endif

		// HEADROCK PROFEX: Read in Merc Opinion data to replace PROF.DAT data
		strcpy(fileName, directoryName);
		strcat(fileName, MERCOPINIONSFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));	
		SGP_THROW_IFFALSE(ReadInMercOpinions(fileName), MERCOPINIONSFILENAME);
		
		
#ifdef JA2UB		
		// UB25
		strcpy(fileName, directoryName);
		strcat(fileName, MERCPROFILESFILENAME25); 
		
		if ( FileExists(fileName) )
		{	
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));		
		SGP_THROW_IFFALSE(ReadInMercProfiles(fileName, FALSE), MERCPROFILESFILENAME25);
		
		#ifndef ENGLISH
			AddLanguagePrefix(fileName);
				if ( FileExists(fileName) )
					{
					DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
					if(!ReadInMercProfiles(fileName,TRUE))
					return FALSE;
					}
		#endif

		}

		strcpy(fileName, directoryName);
		strcat(fileName, MERCOPINIONSFILENAME25);
		if ( FileExists(fileName) )
		{		
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInMercOpinions(fileName), MERCOPINIONSFILENAME25);
		}
#endif

	// HEADROCK HAM 3.6: Read in customized Bloodcat Placements
	strcpy(fileName, directoryName);
	strcat(fileName, BLOODCATPLACEMENTSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInBloodcatPlacements(fileName), BLOODCATPLACEMENTSFILENAME);

	// HEADROCK HAM 3.6: Read in customized Uniform Colors
	strcpy(fileName, directoryName);
	strcat(fileName, UNIFORMCOLORSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInUniforms(fileName), UNIFORMCOLORSFILENAME);

    strcpy(fileName, directoryName);
	strcat(fileName, MULTIPLAYERTEAMSFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	mpTeams.ReadInMPTeams(fileName);

	//legion by jazz (load small faces from rpcs)
	strcpy(fileName, directoryName);
	strcat(fileName, RPCFACESSMALLFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSmallFacesStats(gRPCSmallFaceValues,fileName), RPCFACESSMALLFILENAME);
	
	//Hidden Names by Jazz 
	strcpy(fileName, directoryName);
	strcat(fileName, HIDDENNAMESFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInHiddenNamesStats(zHiddenNames,fileName), HIDDENNAMESFILENAME);	

	
	
	if (gGameExternalOptions.fEnemyNames == TRUE && gGameExternalOptions.fEnemyRank == FALSE)
    {
		// Enemy Names Group by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, ENEMYNAMESFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInEnemyNames(fileName,FALSE), ENEMYNAMESFILENAME);		

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInEnemyNames(fileName,TRUE))
				return FALSE;
		}
#endif
	}
	
	
	if (gGameExternalOptions.fCivGroupName == TRUE)
    {
		// Civ Names Group by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, CIVGROUPNAMESFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInCivGroupNamesStats(fileName,FALSE), CIVGROUPNAMESFILENAME);

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInCivGroupNamesStats(fileName,TRUE))
				return FALSE;
		}
#endif
	}
	
	
		// Sender Name List by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, SENDERNAMELISTFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInSenderNameList(fileName,FALSE), SENDERNAMELISTFILENAME);

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInSenderNameList(fileName,TRUE))
				return FALSE;
		}
#endif
	
	if (gGameExternalOptions.fEnemyNames == FALSE && gGameExternalOptions.fEnemyRank == TRUE)
    {
		// Enemy Rank by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, ENEMYRANKFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInEnemyRank(fileName,FALSE), ENEMYRANKFILENAME);		

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInEnemyRank(fileName,TRUE))
				return FALSE;
		}
#endif
	}

		// IMP Portraits List by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, IMPPORTRAITS);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInIMPPortraits(fileName,FALSE), IMPPORTRAITS);

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInIMPPortraits(fileName,TRUE))
				return FALSE;
		}
#endif


/*
	strcpy(fileName, directoryName);
	strcat(fileName, SOUNDPROFILE);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(WriteSoundProfile(gSoundProfileValue,fileName), SOUNDPROFILE);
*/

	//legion by jazz 
	strcpy(fileName, directoryName);
	strcat(fileName, SOUNDPROFILE);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInSoundProfile(fileName), SOUNDPROFILE);

	//legion by jazz 
	strcpy(fileName, directoryName);
	strcat(fileName, RANDOMSTATS);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInRandomStats(fileName), RANDOMSTATS);
	
	/*
	strcpy(fileName, directoryName);
	strcat(fileName, RANDOMSTATS);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(WriteRandomStats(fileName), RANDOMSTATS);
	*/

	//quote array by Jazz
	strcpy(fileName, directoryName);
	strcat(fileName, QUOTEARRAYFILENAME);
	DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
	SGP_THROW_IFFALSE(ReadInQarray(QuoteExp,fileName),QUOTEARRAYFILENAME);
	
		// Files Name List by Jazz
		strcpy(fileName, directoryName);
		strcat(fileName, FILESSENDERLISTFILENAME);
		DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
		SGP_THROW_IFFALSE(ReadInFilesSenderList(fileName,FALSE), FILESSENDERLISTFILENAME);

#ifndef ENGLISH
		AddLanguagePrefix(fileName);
		if ( FileExists(fileName) )
		{
			DebugMsg (TOPIC_JA2,DBG_LEVEL_3,String("LoadExternalGameplayData, fileName = %s", fileName));
			if(!ReadInFilesSenderList(fileName,TRUE))
				return FALSE;
		}
#endif

	
	LoadIMPPortraitsTEMP();

#ifdef JA2UB	
	//if ( OldNew == TRUE )
	//	Old_UB_Inventory ();
	//else
	//	New_UB_Inventory ();
#endif

	// load Lua for Strategic Mines initialization
	g_luaMines.LoadScript();

	return TRUE;
}


UINT32 InitializeJA2(void)
{

#ifdef LASERLOCK_ENABLED
	HandleLaserLockResult( PrepareLaserLockSystem() );
#endif

	HandleJA2CDCheck( );

	gfWorldLoaded = FALSE;

	//Load external game mechanic data
	//if ( !LoadExternalGameplayData(TABLEDATA_DIRECTORY))
	//{
	//	return( ERROR_SCREEN );
	//}
	SGP_TRYCATCH_RETHROW(LoadExternalGameplayData(TABLEDATA_DIRECTORY),L"Loading external data failed");

	// Load external text
	LoadAllExternalText();

	// Init JA2 sounds
	InitJA2Sound( );

	//dnl ch54 111009
	//gsRenderCenterX = 805;
	//gsRenderCenterY = 805;
	
	// Init data
	InitializeSystemVideoObjects( );

	// Init animation system
	if ( !InitAnimationSystem( ) )
	{
		return( ERROR_SCREEN );
	}

	// Init lighting system
	InitLightingSystem();

	// Init dialog queue system
	InitalizeDialogueControl();

	if ( !InitStrategicEngine( ) )
	{
		return( ERROR_SCREEN );
	}

	//needs to be called here to init the SectorInfo struct
	if ( !InitStrategicMovementCosts( ) )
	{
		return( ERROR_SCREEN );
	}

	// Init tactical engine
	if ( !InitTacticalEngine( ) )
	{
		return( ERROR_SCREEN );
	}

	// Init timer system
	//Moved to the splash screen code.
	//InitializeJA2Clock( );

	// INit shade tables
	BuildShadeTable( );

	// INit intensity tables
	BuildIntensityTable( );

	// Init Event Manager
	if ( !InitializeEventManager( ) )
	{
		return( ERROR_SCREEN );
	}

	// Initailize World
	if ( !InitializeWorld( ) )
	{
		return( ERROR_SCREEN );
	}

	InitTileCache( );

	InitMercPopupBox( );

	// Set global volume
	MusicSetVolume( gGameSettings.ubMusicVolumeSetting );

	DetermineRGBDistributionSettings();

	// Snap: Init save game directory
	if ( !InitSaveDir() )
	{
		return( ERROR_SCREEN );
	}

	//ADB When a merc calcs CTGT for a thrown item he uses a GLOCK temp item
	//but we don't want to recreate it every single time CTGT is called, so init the GLOCK here
	CreateItem(GLOCK_17, 100, &GLOCK_17_ForUseWithLOS);
	

#ifdef JA2BETAVERSION
	#ifdef JA2EDITOR

	//UNCOMMENT NEXT LINE TO ALLOW FORCE UPDATES...
	//LoadGlobalSummary();
	if( gfMustForceUpdateAllMaps )
	{
		ApologizeOverrideAndForceUpdateEverything();
	}
	#endif
#endif

#ifdef JA2BETAVERSION
	if( ProcessIfMultilingualCmdLineArgDetected( gzCommandLine ) )
	{ //If the multilingual text code generator has activated, quit now.
		gfProgramIsRunning = FALSE;
		return( INIT_SCREEN );
	}
#endif

#ifdef JA2BETAVERSION
#ifdef JA2EDITOR
	// CHECK COMMANDLINE FOR SPECIAL UTILITY
	if ( strcmp( gzCommandLine, "-DOMAPS" ) == 0 )
	{
		GenerateAllMapsInit();//dnl ch49 061009
		return( MAPUTILITY_SCREEN );
	}
#endif
#endif

#ifdef JA2BETAVERSION
	//This allows the QuickSave Slots to be autoincremented, ie everytime the user saves, there will be a new quick save file
	if ( _stricmp( gzCommandLine, "-quicksave" ) == 0 )
	{
		gfUseConsecutiveQuickSaveSlots = TRUE;
	}
#endif

#ifdef JA2UB
		// run old UB inventory Data-UB\Addons\Data-Old-UB-Inventory
	//	if( !strcmp( gzCommandLine, "-OLDUBINVENTORY" ) )
	//	{
	//		OldNew = TRUE; 
	//	}
#endif

#ifdef JA2BETAVERSION
	#ifdef JA2EDITOR
		#ifdef JA2UB
			// CHECK COMMANDLINE FOR SPECIAL UTILITY
		if( !strcmp( gzCommandLine, "-OLDUBINVENTORYEDITORAUTO" ) )
		{
			OutputDebugString( "Beginning JA2 using -EDITORAUTO commandline argument...\n" );
			//For editor purposes, need to know the default map file.
			sprintf( gubFilename, "none");
			//also set the sector
			gWorldSectorX = 0;
			gWorldSectorY = 0;
			gfAutoLoadA9 = FALSE;
			gfIntendOnEnteringEditor = TRUE;
			gGameOptions.fGunNut = TRUE;
			gGameOptions.fAirStrikes = FALSE;
			return( GAME_SCREEN );
		}
		#endif
	
		// CHECK COMMANDLINE FOR SPECIAL UTILITY
		if( !strcmp( gzCommandLine, "-EDITORAUTO" ) )
		{
			OutputDebugString( "Beginning JA2 using -EDITORAUTO commandline argument...\n" );
			//For editor purposes, need to know the default map file.
			sprintf( gubFilename, "none");
			//also set the sector
			gWorldSectorX = 0;
			gWorldSectorY = 0;
			gfAutoLoadA9 = FALSE;
			gfIntendOnEnteringEditor = TRUE;
			gGameOptions.fGunNut = TRUE;
			gGameOptions.fAirStrikes = FALSE;
			return( GAME_SCREEN );
		}
		if ( strcmp( gzCommandLine, "-EDITOR" ) == 0 )
		{
			OutputDebugString( "Beginning JA2 using -EDITOR commandline argument...\n" );
			//For editor purposes, need to know the default map file.
			sprintf( gubFilename, "none");
			//also set the sector
			gWorldSectorX = 0;
			gWorldSectorY = 0;
			gfAutoLoadA9 = FALSE;
			gfIntendOnEnteringEditor = TRUE;
			gGameOptions.fGunNut = TRUE;
			gGameOptions.fAirStrikes = FALSE;
			return( GAME_SCREEN );
		}

		#ifdef BUILD_AS_EDITOR_ONLY
			//ADB We are building with JA2EDITOR, why force a commandline arguement???
			//build once, rename, change the define and build again
			//no pesky shortcuts
			OutputDebugString( "Beginning JA2EDITOR without using a commandline argument...\n" );
			//For editor purposes, need to know the default map file.
			sprintf( gubFilename, "none");
			//also set the sector
			gWorldSectorX = 0;
			gWorldSectorY = 0;
			gfAutoLoadA9 = TRUE;
			gfIntendOnEnteringEditor = TRUE;
			gGameOptions.fGunNut = TRUE;
			gGameOptions.fAirStrikes = FALSE;
			return( GAME_SCREEN );
		#endif
	#endif
#endif

	return( INIT_SCREEN );
}


void ShutdownJA2(void)
{
	UINT32 uiIndex;

	// Clear screen....
	ColorFillVideoSurfaceArea( FRAME_BUFFER, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Get16BPPColor( FROMRGB( 0, 0, 0 ) ) );
	InvalidateScreen( );
	// Remove cursor....
	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

	RefreshScreen( NULL );

	ShutdownStrategicLayer();

	// remove temp files built by laptop
	ClearOutTempLaptopFiles( );

	// Shutdown queue system
	ShutdownDialogueControl();

	// Shutdown Screens
	for (uiIndex = 0; uiIndex < MAX_SCREENS; uiIndex++)
	{
	(*(GameScreens[uiIndex].ShutdownScreen))();
	}


	// Shutdown animation system
	DeInitAnimationSystem( );

	ShutdownLightingSystem();

	CursorDatabaseClear();

	ShutdownTacticalEngine( );

	// Shutdown Overhead
	ShutdownOverhead( );

	DeinitializeWorld( );

	DeleteTileCache( );

	ShutdownJA2Clock( );

	ShutdownFonts();

	ShutdownJA2Sound( );

	ShutdownEventManager( );

	ShutdownBaseDirtyRectQueue( );

	// Unload any text box images!
	RemoveTextMercPopupImages( );

	ClearOutVehicleList();
}


#ifdef LASERLOCK_ENABLED

BOOLEAN PrepareLaserLockSystem()
{
	INT32	iInitRetVal=0;
	INT32	iRunRetVal=0;
	INT32	iCheckRetVal=0;
	CHAR8 zDirectory[512];

	CHAR8		zCdLocation[ SGPFILENAME_LEN ];
	CHAR8		zCdFile[ SGPFILENAME_LEN ];

	//Get the "current" file directory
	GetFileManCurrentDirectory( zDirectory );

	if( GetCDromDriveLetter( zCdLocation ) )
	{
		// OK, build filename
		sprintf( zCdFile, "%s%s", zCdLocation, "Data" );
	}
	else
	{
		goto FAILED_LASERLOK;
	}

	//Go back to the root directory
	SetFileManCurrentDirectory( zCdFile );
	//Init the laser lock system
	iInitRetVal = LASERLOK_Init( ghInstance );
	if( iInitRetVal != 0 )
		goto FAILED_LASERLOK;

	//makes the verification of the laserlok system
	iRunRetVal = LASERLOK_Run();
	if( iRunRetVal != 0 )
		goto FAILED_LASERLOK;

	//checks the result of the laserlok run function
	iCheckRetVal = LASERLOK_Check();
	if( iCheckRetVal != 0 )
		goto FAILED_LASERLOK;

	//Restore back to the proper directory
	SetFileManCurrentDirectory( zDirectory );
	return( TRUE );

FAILED_LASERLOK:
	//Restore back to the proper directory
	SetFileManCurrentDirectory( zDirectory );
	return( FALSE );
}

void HandleLaserLockResult( BOOLEAN fSuccess )
{
	if( !fSuccess )
	{
		CHAR8	zString[512];

		sprintf( zString, "%S", gzLateLocalizedString[56] );

//		ShowCursor(TRUE);
//		ShowCursor(TRUE);
		ShutdownWithErrorBox( zString );
	}
}

#endif

void SetupMaxActionPointsAnimation()
{
	gubMaxActionPoints[0] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[1] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[2] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[3] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[4] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[5] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[6] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[7] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[8] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[9] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[10] = APBPConstants[AP_MONSTER_MAXIMUM];
	gubMaxActionPoints[11] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[12] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[13] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[14] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[15] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[16] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[17] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[18] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[19] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[20] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[21] = APBPConstants[AP_MAXIMUM];
	gubMaxActionPoints[22] = APBPConstants[AP_VEHICLE_MAXIMUM];
	gubMaxActionPoints[23] = APBPConstants[AP_VEHICLE_MAXIMUM];
	gubMaxActionPoints[24] = APBPConstants[AP_VEHICLE_MAXIMUM];
	gubMaxActionPoints[25] = APBPConstants[AP_VEHICLE_MAXIMUM];
	gubMaxActionPoints[26] = APBPConstants[AP_VEHICLE_MAXIMUM];
	gubMaxActionPoints[27] = APBPConstants[AP_VEHICLE_MAXIMUM];
}
