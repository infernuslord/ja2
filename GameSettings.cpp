#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "HelpScreen.h"
	#include "Campaign.h"
	#include "Cheats.h"
	#include "INIReader.h"
#else
	#include	"Types.h"
	#include	"GameSettings.h"
	#include	"FileMan.h"
	#include	"String.h"
	#include	"Sound Control.h"
	#include	"SaveLoadScreen.h"
	#include	"Music Control.h"
	#include	"Options Screen.h"
	#include	"Overhead.h"
	#include	"GameVersion.h"
	#include	"LibraryDataBase.h"
	#include	"Debug.h"
	#include	"Language Defines.h"
	#include "HelpScreen.h"
	#include "INIReader.h"
	#include "Shade Table Util.h"
	#include "soldier profile type.h"
	#include "Random.h"
	#include "SaveLoadGame.h"
	#include "sgp.h"
	#include "screenids.h"
	#include "Font Control.h"
	#include "message.h"
	#include "Campaign.h"
	#include "meanwhile.h"
	#include "strategicmap.h"
	#include "Queen Command.h"
	#include "Game Clock.h"
	#include "Init.h"
	#include "displaycover.h"
#endif

#include "Text.h"
#include "connect.h"
#include "sgp_logger.h"

#include "Map Information.h"

#include <vfs/Core/vfs.h>
#include <vfs/Core/vfs_file_raii.h>
#include <vfs/Core/File/vfs_file.h>

#define				GAME_SETTINGS_FILE				"Ja2_Settings.INI"

#define				GAME_INI_FILE					"..\\Ja2.ini"

#define				GAME_EXTERNAL_OPTIONS_FILE		"Ja2_Options.ini"

#define				AP_BP_CONSTANTS_FILE			"APBPConstants.ini"

#define				STOMP_SETTINGS_FILE				"Skills_Settings.ini" // SANDRO - file for STOMP

// HEADROCK HAM 4: This file contains all the settings required to tweak the new Shooting Mechanism. There's lots of them.
#define				CTH_COEFFICIENTS_FILE			"CTHConstants.ini"

#define				CD_ROOT_DIR						"DATA\\"

GAME_SETTINGS		gGameSettings;
GAME_OPTIONS		gGameOptions;
// Snap: Options read from an INI file in the default of custom Data directory
GAME_EXTERNAL_OPTIONS gGameExternalOptions;
SKILL_TRAIT_VALUES gSkillTraitValues;  // SANDRO - added this one
CTH_CONSTANTS gGameCTHConstants;	// HEADROCK HAM 4: CTH constants

extern	SGPFILENAME	gCheckFilenames[];
extern	CHAR8		gzErrorMsg[256];
extern INT16 APBPConstants[TOTAL_APBP_VALUES];

void		InitGameSettings();


BOOLEAN GetCdromLocationFromIniFile( STR pRootOfCdromDrive );

extern BOOLEAN DoJA2FilesExistsOnDrive( CHAR8 *zCdLocation );

BOOLEAN GetCDromDriveLetter( STR8	pString );
BOOLEAN	IsDriveLetterACDromDrive( STR pDriveLetter );
void		CDromEjectionErrorMessageBoxCallBack( UINT8 bExitValue );


bool UsingNewInventorySystem()
{
	return (gGameOptions.ubInventorySystem == INVENTORY_NEW);
}

bool UsingNewAttachmentSystem()
{
	return (gGameOptions.ubAttachmentSystem == ATTACHMENT_NEW);
}

bool UsingNewCTHSystem()
{
	return (gGameSettings.fOptions[TOPTION_USE_NCTH] == TRUE);
}

std::string StringToLower(std::string strToConvert)
{//change each element of the string to lower case
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = tolower(strToConvert[i]);
   }
   return strToConvert;//return the converted string
}

BOOLEAN IsNIVModeValid(bool checkRes)
{	
	bool isValid = FALSE;
	
	// WANNE: Playing with NIV needs the v1.13 profile, because the "data" folder does not contains any NIV items!
	// Check if the Profile with the NAME = "v1.13" is found in the specificed vfs_config.*.ini
	if(getVFS()->getProfileStack()->getProfile(L"v1.13") != NULL)
	{
		isValid = TRUE;
	}
	else
		isValid = FALSE;

	// Also check the resolution if needed.
	if(checkRes == true && iResolution == 0)
		isValid = FALSE;
	
	return isValid;
}


BOOLEAN LoadGameSettings()
{	
	try
	{
		CIniReader iniReader(GAME_SETTINGS_FILE, TRUE);	// force path even for non existing files	

		gGameSettings.bLastSavedGameSlot                                = iniReader.ReadInteger("JA2 Game Settings","bLastSavedGameSlot"                       ,  -1        , -1 , 255 );
		gGameSettings.ubMusicVolumeSetting                              = iniReader.ReadInteger("JA2 Game Settings","ubMusicVolumeSetting"                     ,  MIDVOLUME ,  0 , HIGHVOLUME );
		gGameSettings.ubSoundEffectsVolume                              = iniReader.ReadInteger("JA2 Game Settings","ubSoundEffectsVolume"                     ,  MIDVOLUME ,  0 , HIGHVOLUME );
		gGameSettings.ubSpeechVolume                                    = iniReader.ReadInteger("JA2 Game Settings","ubSpeechVolume"                           ,  MIDVOLUME ,  0 , HIGHVOLUME );
		gGameSettings.uiMeanwhileScenesSeenFlags                        = iniReader.ReadUINT32 ("JA2 Game Settings","uiMeanwhileScenesSeenFlags"               ,  0         ,  0 , UINT_MAX );
		gGameSettings.fHideHelpInAllScreens                             = iniReader.ReadBoolean("JA2 Game Settings","fHideHelpInAllScreens"                    ,  FALSE );	
		gGameSettings.fOptions[TOPTION_SPEECH]                          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SPEECH"                           ,  TRUE  );
		gGameSettings.fOptions[TOPTION_MUTE_CONFIRMATIONS]              = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_MUTE_CONFIRMATIONS"               ,  FALSE );
		gGameSettings.fOptions[TOPTION_SUBTITLES]                       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SUBTITLES"                        ,  TRUE  );
		gGameSettings.fOptions[TOPTION_KEY_ADVANCE_SPEECH]              = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_KEY_ADVANCE_SPEECH"               ,  FALSE );
		gGameSettings.fOptions[TOPTION_ANIMATE_SMOKE]                   = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ANIMATE_SMOKE"                    ,  TRUE  );
		gGameSettings.fOptions[TOPTION_BLOOD_N_GORE]                    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_BLOOD_N_GORE"                     ,  TRUE  );
		gGameSettings.fOptions[TOPTION_DONT_MOVE_MOUSE]                 = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_DONT_MOVE_MOUSE"                  ,  FALSE );
		gGameSettings.fOptions[TOPTION_OLD_SELECTION_METHOD]            = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_OLD_SELECTION_METHOD"             ,  FALSE );
		gGameSettings.fOptions[TOPTION_ALWAYS_SHOW_MOVEMENT_PATH]       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALWAYS_SHOW_MOVEMENT_PATH"        ,  FALSE );
		gGameSettings.fOptions[TOPTION_SHOW_MISSES]                     = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_MISSES"                      ,  FALSE );
		gGameSettings.fOptions[TOPTION_RTCONFIRM]                       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_RTCONFIRM"                        ,  FALSE );
		gGameSettings.fOptions[TOPTION_SLEEPWAKE_NOTIFICATION]          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SLEEPWAKE_NOTIFICATION"           ,  TRUE  );
		gGameSettings.fOptions[TOPTION_USE_METRIC_SYSTEM]               = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_USE_METRIC_SYSTEM"                ,  TRUE );
		gGameSettings.fOptions[TOPTION_MERC_ALWAYS_LIGHT_UP]            = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_MERC_ALWAYS_LIGHT_UP"             ,  FALSE );
		gGameSettings.fOptions[TOPTION_SMART_CURSOR]                    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SMART_CURSOR"                     ,  FALSE );
		gGameSettings.fOptions[TOPTION_SNAP_CURSOR_TO_DOOR]             = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SNAP_CURSOR_TO_DOOR"              ,  TRUE  );
		gGameSettings.fOptions[TOPTION_GLOW_ITEMS]                      = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_GLOW_ITEMS"                       ,  TRUE  );
		gGameSettings.fOptions[TOPTION_TOGGLE_TREE_TOPS]                = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_TOGGLE_TREE_TOPS"                 ,  TRUE  );
		gGameSettings.fOptions[TOPTION_TOGGLE_WIREFRAME]                = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_TOGGLE_WIREFRAME"                 ,  TRUE  );
		gGameSettings.fOptions[TOPTION_3D_CURSOR]                       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_3D_CURSOR"                        ,  FALSE );
		gGameSettings.fOptions[TOPTION_CTH_CURSOR]                      = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_CTH_CURSOR"                       ,  TRUE  );
		gGameSettings.fOptions[TOPTION_GL_BURST_CURSOR]                 = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_GL_BURST_CURSOR"                  ,  TRUE  );
		gGameSettings.fOptions[TOPTION_ALLOW_TAUNTS]					= iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALLOW_TAUNTS"					   ,  TRUE  ); // changed from drop all - SANDRO
		gGameSettings.fOptions[TOPTION_GL_HIGH_ANGLE]					= iniReader.ReadBoolean("JA2 Game Settings","TOPTION_GL_HIGH_ANGLE"                    ,  FALSE );
		gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK]			= iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALLOW_REAL_TIME_SNEAK"            ,  FALSE ); // Changed from aim levels restriction - SANDRO
		gGameSettings.fOptions[TOPTION_SPACE_SELECTS_NEXT_SQUAD]        = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SPACE_SELECTS_NEXT_SQUAD"         ,  TRUE  );
		gGameSettings.fOptions[TOPTION_SHOW_ITEM_SHADOW]                = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_ITEM_SHADOW"                 ,  TRUE  );
		gGameSettings.fOptions[TOPTION_SHOW_WEAPON_RANGE_IN_TILES]      = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_WEAPON_RANGE_IN_TILES"       ,  TRUE  );
		gGameSettings.fOptions[TOPTION_TRACERS_FOR_SINGLE_FIRE]         = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_TRACERS_FOR_SINGLE_FIRE"          ,  FALSE );
		gGameSettings.fOptions[TOPTION_RAIN_SOUND]                      = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_RAIN_SOUND"                       ,  TRUE  );
		gGameSettings.fOptions[TOPTION_ALLOW_CROWS]                     = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALLOW_CROWS"                      ,  TRUE  );
		gGameSettings.fOptions[TOPTION_ALLOW_SOLDIER_TOOLTIPS]          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALLOW_SOLDIER_TOOLTIPS"           ,  TRUE  );
		gGameSettings.fOptions[TOPTION_USE_AUTO_SAVE]                   = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_USE_AUTO_SAVE"                    ,  FALSE );
		gGameSettings.fOptions[TOPTION_SILENT_SKYRIDER]                 = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SILENT_SKYRIDER"                  ,  FALSE );
		//gGameSettings.fOptions[TOPTION_LOW_CPU_USAGE]                   = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_LOW_CPU_USAGE"                    ,  FALSE );
		gGameSettings.fOptions[TOPTION_ENHANCED_DESC_BOX]               = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ENHANCED_DESC_BOX"                ,  TRUE );
		gGameSettings.fOptions[TOPTION_TOGGLE_TURN_MODE]                = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_TOGGLE_TURN_MODE"                 ,  FALSE );
		gGameSettings.fOptions[TOPTION_STAT_PROGRESS_BARS]              = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_STAT_PROGRESS_BARS"               ,  TRUE ); // HEADROCK HAM 3.6: Progress Bars
		gGameSettings.fOptions[TOPTION_REPORT_MISS_MARGIN]				= iniReader.ReadBoolean("JA2 Game Settings","TOPTION_REPORT_MISS_MARGIN"			   ,  FALSE ); // HEADROCK HAM 4: Shot offset report
		gGameSettings.fOptions[TOPTION_ALT_MAP_COLOR]					= iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALT_MAP_COLOR"					   ,  FALSE ); // HEADROCK HAM 4: Strategic Map Colors
		gGameSettings.fOptions[TOPTION_ALTERNATE_BULLET_GRAPHICS]       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_ALTERNATE_BULLET_GRAPHICS"        ,  TRUE );
		gGameSettings.fOptions[TOPTION_USE_NCTH]					    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_USE_NCTH"						   ,  TRUE );
		gGameSettings.fOptions[TOPTION_SHOW_TACTICAL_FACE_GEAR]		    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_TACTICAL_FACE_GEAR"		   ,  TRUE );
		gGameSettings.fOptions[TOPTION_SHOW_TACTICAL_FACE_ICONS]	    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_TACTICAL_FACE_ICONS"		   ,  TRUE );
		gGameSettings.fOptions[TOPTION_CHEAT_MODE_OPTIONS_HEADER]       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_CHEAT_MODE_OPTIONS_HEADER"        ,  FALSE );
		gGameSettings.fOptions[TOPTION_FORCE_BOBBY_RAY_SHIPMENTS]       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_FORCE_BOBBY_RAY_SHIPMENTS"        ,  FALSE );
		gGameSettings.fOptions[TOPTION_CHEAT_MODE_OPTIONS_END]          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_CHEAT_MODE_OPTIONS_END"           ,  FALSE );
		gGameSettings.fOptions[TOPTION_DEBUG_MODE_OPTIONS_HEADER]       = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_DEBUG_MODE_OPTIONS_HEADER"        ,  FALSE );
		gGameSettings.fOptions[TOPTION_SHOW_RESET_ALL_OPTIONS]          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_SHOW_RESET_ALL_OPTIONS"           ,  FALSE );
		gGameSettings.fOptions[TOPTION_RESET_ALL_OPTIONS]               = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_RESET_ALL_OPTIONS"                ,  FALSE );
		gGameSettings.fOptions[TOPTION_RETAIN_DEBUG_OPTIONS_IN_RELEASE] = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_RETAIN_DEBUG_OPTIONS_IN_RELEASE"  ,  FALSE );
		gGameSettings.fOptions[TOPTION_DEBUG_MODE_RENDER_OPTIONS_GROUP] = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_DEBUG_MODE_RENDER_OPTIONS_GROUP"  ,  FALSE );
		gGameSettings.fOptions[TOPTION_RENDER_MOUSE_REGIONS]            = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_RENDER_MOUSE_REGIONS"             ,  FALSE );
		gGameSettings.fOptions[TOPTION_DEBUG_MODE_OPTIONS_END]          = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_DEBUG_MODE_OPTIONS_END"           ,  FALSE );
		gGameSettings.fOptions[TOPTION_LAST_OPTION]                     = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_LAST_OPTION"                      ,  FALSE );
		gGameSettings.fOptions[NUM_GAME_OPTIONS]                        = iniReader.ReadBoolean("JA2 Game Settings","NUM_GAME_OPTIONS"                         ,  FALSE );
		gGameSettings.fOptions[TOPTION_MERC_CASTS_LIGHT]                = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_MERC_CASTS_LIGHT"                 ,  TRUE  );
		gGameSettings.fOptions[TOPTION_HIDE_BULLETS]                    = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_HIDE_BULLETS"                     ,  FALSE );
		gGameSettings.fOptions[TOPTION_TRACKING_MODE]                   = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_TRACKING_MODE"                    ,  TRUE  );
		gGameSettings.fOptions[TOPTION_DISABLE_CURSOR_SWAP]             = iniReader.ReadBoolean("JA2 Game Settings","TOPTION_DISABLE_CURSOR_SWAP"              ,  FALSE );
		gGameSettings.fOptions[NUM_ALL_GAME_OPTIONS]                    = iniReader.ReadBoolean("JA2 Game Settings","NUM_ALL_GAME_OPTIONS"                     ,  FALSE );


		DeleteShadeTableDir();  // ary-05/05/2009 : Might be bad idea for it to be here. But its gotta happen for some reason every now and then.
								//		 : The call to DeleteShadeTableDir() used to coincided with reseting an older settings file.
								//		 : Shade Table Dir is rebuilt when ever LoadShadeTable() cant find it. Its only around ~1.5 MB. 

		//
		//Do checking to make sure the settings are valid
		//
		if( gGameSettings.bLastSavedGameSlot < 0 || gGameSettings.bLastSavedGameSlot >= NUM_SLOT )
			gGameSettings.bLastSavedGameSlot = -1;

		if( gGameSettings.ubMusicVolumeSetting > HIGHVOLUME )
			gGameSettings.ubMusicVolumeSetting = MIDVOLUME;

		if( gGameSettings.ubSoundEffectsVolume > HIGHVOLUME )
			gGameSettings.ubSoundEffectsVolume = MIDVOLUME;

		if( gGameSettings.ubSpeechVolume > HIGHVOLUME )
			gGameSettings.ubSpeechVolume = MIDVOLUME;


		//make sure that at least subtitles or speech is enabled
		if( !gGameSettings.fOptions[ TOPTION_SUBTITLES ] && !gGameSettings.fOptions[ TOPTION_SPEECH ] )
		{
			gGameSettings.fOptions[ TOPTION_SUBTITLES ]						= TRUE;
			gGameSettings.fOptions[ TOPTION_SPEECH ]						= TRUE;
		}


		//
		//	Set the settings
		//

		SetSoundEffectsVolume( gGameSettings.ubSoundEffectsVolume );
		SetSpeechVolume( gGameSettings.ubSpeechVolume );
		MusicSetVolume( gGameSettings.ubMusicVolumeSetting );

		//if the user doesnt want the help screens present
		if( gGameSettings.fHideHelpInAllScreens )
		{
			gHelpScreen.usHasPlayerSeenHelpScreenInCurrentScreen = 0;
		}
		else
		{
			//Set it so that every screens help will come up the first time ( the 'x' will be set )
			gHelpScreen.usHasPlayerSeenHelpScreenInCurrentScreen = 0xffff;
		}

		return( TRUE );
	}
	catch(vfs::Exception)
	{
		// file does not exist, InitGamesettings() and then return. 
		// InitGamesettings() will also call SaveGameSettings().
		InitGameSettings();
		return(FALSE);
	}		
}


BOOLEAN	SaveGameSettings()
{
	//Record the current settings into the game settins structure
	gGameSettings.ubSoundEffectsVolume = (UINT8)GetSoundEffectsVolume( );
	gGameSettings.ubSpeechVolume       = (UINT8)GetSpeechVolume( );
	gGameSettings.ubMusicVolumeSetting = (UINT8)MusicGetVolume( );

	std::stringstream settings;
	const char endl[] = "\r\n";
	settings << ";******************************************************************************************************************************" << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << ";    Jagged Alliance 2 --Settings File--                                                                                       " << endl;
	settings << ";                                                                                                                              " << endl;
	settings << ";    Please note that this file is automatically generated by the game.                                                        " << endl;
	settings << ";                                                                                                                              " << endl;
	settings << ";    While it is safe to change things from within this file, not all values are acceptable. Some may break the game,          " << endl;
	settings << ";      some may be ignored, but most likely they will be acceptable or reset to a default value.                               " << endl;
	settings << ";                                                                                                                              " << endl;
	settings << ";    Please note, This file and its contents are in a beta phase. Expect changes, however they should be minimal and automated." << endl;
	settings << ";                                                                                                                              " << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << endl;
	settings << ";    The Current Game Setting Struct is defined as : " << endl;
	settings << ";" << endl;
	settings << ";    typedef struct" << endl;
	settings << ";    {" << endl;
	settings << ";        INT8     bLastSavedGameSlot;                 // The last saved game number goes in here" << endl;
	settings << ";        UINT8    ubMusicVolumeSetting;               // Volume Setting" << endl;
	settings << ";        UINT8    ubSoundEffectsVolume;               // Volume Setting" << endl;
	settings << ";        UINT8    ubSpeechVolume;                     // Volume Setting" << endl;
	settings << ";        UINT8    fOptions[ NUM_ALL_GAME_OPTIONS ];   // Toggle Options (Speech, Subtitles, Show Tree Tops, etc.. )" << endl;
	settings << ";        UINT32   uiMeanwhileScenesSeenFlags;         // Bit Vector describing seen 'mean whiles..'" << endl;
	settings << ";        BOOLEAN  fHideHelpInAllScreens;              // Controls Help \"do not show help again\" checkbox" << endl;
	//settings << ";        UINT8    ubSizeOfDisplayCover;               // The number of grids the player designates thru [Delete + ( = or - )]" << endl;
	//settings << ";        UINT8    ubSizeOfLOS;                        // The number of grids the player designates thru [End    + ( = or - )]" << endl;
	settings << ";    } GAME_SETTINGS" << endl;
	settings << ";" << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << endl << endl;
	settings << "[JA2 Game Settings]" << endl;

	settings << "bLastSavedGameSlot                       = " << (int)gGameSettings.bLastSavedGameSlot << endl;
	settings << "ubMusicVolumeSetting                     = " << (int)gGameSettings.ubMusicVolumeSetting << endl;
	settings << "ubSoundEffectsVolume                     = " << (int)gGameSettings.ubSoundEffectsVolume << endl;
	settings << "ubSpeechVolume                           = " << (int)gGameSettings.ubSpeechVolume << endl;
	settings << "uiMeanwhileScenesSeenFlags               = " << gGameSettings.uiMeanwhileScenesSeenFlags << endl;
	settings << "fHideHelpInAllScreens                    = " << (gGameSettings.fHideHelpInAllScreens								?    "TRUE" : "FALSE" ) << endl;
	//settings << "ubSizeOfDisplayCover                     = " << (int)gGameSettings.ubSizeOfDisplayCover << endl;
	//settings << "ubSizeOfLOS                              = " << (int)gGameSettings.ubSizeOfLOS << endl;
	settings << "TOPTION_SPEECH                           = " << (gGameSettings.fOptions[TOPTION_SPEECH]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_MUTE_CONFIRMATIONS               = " << (gGameSettings.fOptions[TOPTION_MUTE_CONFIRMATIONS]				?	 "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SUBTITLES                        = " << (gGameSettings.fOptions[TOPTION_SUBTITLES]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_KEY_ADVANCE_SPEECH               = " << (gGameSettings.fOptions[TOPTION_KEY_ADVANCE_SPEECH]				?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ANIMATE_SMOKE                    = " << (gGameSettings.fOptions[TOPTION_ANIMATE_SMOKE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_BLOOD_N_GORE                     = " << (gGameSettings.fOptions[TOPTION_BLOOD_N_GORE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_DONT_MOVE_MOUSE                  = " << (gGameSettings.fOptions[TOPTION_DONT_MOVE_MOUSE]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_OLD_SELECTION_METHOD             = " << (gGameSettings.fOptions[TOPTION_OLD_SELECTION_METHOD]				?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ALWAYS_SHOW_MOVEMENT_PATH        = " << (gGameSettings.fOptions[TOPTION_ALWAYS_SHOW_MOVEMENT_PATH]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SHOW_MISSES                      = " << (gGameSettings.fOptions[TOPTION_SHOW_MISSES]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_RTCONFIRM                        = " << (gGameSettings.fOptions[TOPTION_RTCONFIRM]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SLEEPWAKE_NOTIFICATION           = " << (gGameSettings.fOptions[TOPTION_SLEEPWAKE_NOTIFICATION]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_USE_METRIC_SYSTEM                = " << (gGameSettings.fOptions[TOPTION_USE_METRIC_SYSTEM]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_MERC_ALWAYS_LIGHT_UP             = " << (gGameSettings.fOptions[TOPTION_MERC_ALWAYS_LIGHT_UP]				?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SMART_CURSOR                     = " << (gGameSettings.fOptions[TOPTION_SMART_CURSOR]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SNAP_CURSOR_TO_DOOR              = " << (gGameSettings.fOptions[TOPTION_SNAP_CURSOR_TO_DOOR]				?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_GLOW_ITEMS                       = " << (gGameSettings.fOptions[TOPTION_GLOW_ITEMS]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_TOGGLE_TREE_TOPS                 = " << (gGameSettings.fOptions[TOPTION_TOGGLE_TREE_TOPS]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_TOGGLE_WIREFRAME                 = " << (gGameSettings.fOptions[TOPTION_TOGGLE_WIREFRAME]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_3D_CURSOR                        = " << (gGameSettings.fOptions[TOPTION_3D_CURSOR]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_CTH_CURSOR                       = " << (gGameSettings.fOptions[TOPTION_CTH_CURSOR]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_GL_BURST_CURSOR                  = " << (gGameSettings.fOptions[TOPTION_GL_BURST_CURSOR]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ALLOW_TAUNTS                     = " << (gGameSettings.fOptions[TOPTION_ALLOW_TAUNTS]						?    "TRUE" : "FALSE" ) << endl; // changed from drop all - SANDRO
	settings << "TOPTION_GL_HIGH_ANGLE                    = " << (gGameSettings.fOptions[TOPTION_GL_HIGH_ANGLE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ALLOW_REAL_TIME_SNEAK            = " << (gGameSettings.fOptions[TOPTION_ALLOW_REAL_TIME_SNEAK]				?    "TRUE" : "FALSE" ) << endl; // changed from restrict aim levels - SANDRO
	settings << "TOPTION_SPACE_SELECTS_NEXT_SQUAD         = " << (gGameSettings.fOptions[TOPTION_SPACE_SELECTS_NEXT_SQUAD]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SHOW_ITEM_SHADOW                 = " << (gGameSettings.fOptions[TOPTION_SHOW_ITEM_SHADOW]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SHOW_WEAPON_RANGE_IN_TILES       = " << (gGameSettings.fOptions[TOPTION_SHOW_WEAPON_RANGE_IN_TILES]		?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_TRACERS_FOR_SINGLE_FIRE          = " << (gGameSettings.fOptions[TOPTION_TRACERS_FOR_SINGLE_FIRE]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_RAIN_SOUND                       = " << (gGameSettings.fOptions[TOPTION_RAIN_SOUND]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ALLOW_CROWS                      = " << (gGameSettings.fOptions[TOPTION_ALLOW_CROWS]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ALLOW_SOLDIER_TOOLTIPS           = " << (gGameSettings.fOptions[TOPTION_ALLOW_SOLDIER_TOOLTIPS]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_USE_AUTO_SAVE                    = " << (gGameSettings.fOptions[TOPTION_USE_AUTO_SAVE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SILENT_SKYRIDER                  = " << (gGameSettings.fOptions[TOPTION_SILENT_SKYRIDER]					?    "TRUE" : "FALSE" ) << endl;
	//settings << "TOPTION_LOW_CPU_USAGE                    = " << (gGameSettings.fOptions[TOPTION_LOW_CPU_USAGE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_ENHANCED_DESC_BOX                = " << (gGameSettings.fOptions[TOPTION_ENHANCED_DESC_BOX]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_TOGGLE_TURN_MODE                 = " << (gGameSettings.fOptions[TOPTION_TOGGLE_TURN_MODE]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_STAT_PROGRESS_BARS               = " << (gGameSettings.fOptions[TOPTION_STAT_PROGRESS_BARS]				?    "TRUE" : "FALSE" ) << endl; // HEADROCK HAM 3.6: Progress Bars
	settings << "TOPTION_ALT_MAP_COLOR					  = " << (gGameSettings.fOptions[TOPTION_ALT_MAP_COLOR]						?	 "TRUE" : "FALSE" ) << endl; // HEADROCK HAM 4: Alt Map Colors
	settings << "TOPTION_ALTERNATE_BULLET_GRAPHICS        = " << (gGameSettings.fOptions[TOPTION_ALTERNATE_BULLET_GRAPHICS]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_USE_NCTH                         = " << (gGameSettings.fOptions[TOPTION_USE_NCTH]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SHOW_TACTICAL_FACE_GEAR          = " << (gGameSettings.fOptions[TOPTION_SHOW_TACTICAL_FACE_GEAR]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_SHOW_TACTICAL_FACE_ICONS         = " << (gGameSettings.fOptions[TOPTION_SHOW_TACTICAL_FACE_ICONS]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_DISABLE_CURSOR_SWAP              = " << (gGameSettings.fOptions[TOPTION_DISABLE_CURSOR_SWAP]               ?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_CHEAT_MODE_OPTIONS_HEADER        = " << (gGameSettings.fOptions[TOPTION_CHEAT_MODE_OPTIONS_HEADER]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_FORCE_BOBBY_RAY_SHIPMENTS        = " << (gGameSettings.fOptions[TOPTION_FORCE_BOBBY_RAY_SHIPMENTS]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_CHEAT_MODE_OPTIONS_END           = " << (gGameSettings.fOptions[TOPTION_CHEAT_MODE_OPTIONS_END]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_DEBUG_MODE_OPTIONS_HEADER        = " << (gGameSettings.fOptions[TOPTION_DEBUG_MODE_OPTIONS_HEADER]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_REPORT_MISS_MARGIN				  = " << (gGameSettings.fOptions[TOPTION_REPORT_MISS_MARGIN]				?	 "TRUE" : "FALSE" ) << endl; // HEADROCK HAM 4: Shot offset report
	settings << "TOPTION_SHOW_RESET_ALL_OPTIONS           = " << (gGameSettings.fOptions[TOPTION_SHOW_RESET_ALL_OPTIONS]			?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_RESET_ALL_OPTIONS                = " << (gGameSettings.fOptions[TOPTION_RESET_ALL_OPTIONS]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_RETAIN_DEBUG_OPTIONS_IN_RELEASE  = " << (gGameSettings.fOptions[TOPTION_RETAIN_DEBUG_OPTIONS_IN_RELEASE]	?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_DEBUG_MODE_RENDER_OPTIONS_GROUP  = " << (gGameSettings.fOptions[TOPTION_DEBUG_MODE_RENDER_OPTIONS_GROUP]	?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_RENDER_MOUSE_REGIONS             = " << (gGameSettings.fOptions[TOPTION_RENDER_MOUSE_REGIONS]				?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_DEBUG_MODE_OPTIONS_END           = " << (gGameSettings.fOptions[TOPTION_DEBUG_MODE_OPTIONS_END]			?    "TRUE" : "FALSE" ) << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << ";  Options beyond this point are Code derived options, DO NOT CHANGE THESE UNLESS YOU KNOW WHAT YOUR ARE DOING." << endl;
	settings << ";  They are only included here for complete transparency for all GameSettings content.							" << endl;
	settings << ";******************************************************************************************************************************" << endl;
	settings << "TOPTION_LAST_OPTION                      = " << (gGameSettings.fOptions[TOPTION_LAST_OPTION]						?    "TRUE" : "FALSE" ) << endl;
	settings << "NUM_GAME_OPTIONS                         = " << (gGameSettings.fOptions[NUM_GAME_OPTIONS]							?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_MERC_CASTS_LIGHT                 = " << (gGameSettings.fOptions[TOPTION_MERC_CASTS_LIGHT]					?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_HIDE_BULLETS                     = " << (gGameSettings.fOptions[TOPTION_HIDE_BULLETS]						?    "TRUE" : "FALSE" ) << endl;
	settings << "TOPTION_TRACKING_MODE                    = " << (gGameSettings.fOptions[TOPTION_TRACKING_MODE]						?    "TRUE" : "FALSE" ) << endl;
	settings << "NUM_ALL_GAME_OPTIONS                     = " << (gGameSettings.fOptions[NUM_ALL_GAME_OPTIONS]						?    "TRUE" : "FALSE" ) << endl;

	try
	{
		vfs::COpenWriteFile wfile(GAME_SETTINGS_FILE,true,true);
		wfile->write(settings.str().c_str(), settings.str().length());
	}
	catch(vfs::Exception& ex)
	{
		SGP_WARNING(ex.what());
		vfs::CFile file(GAME_SETTINGS_FILE);
		if(file.openWrite(true,true))
		{
			vfs::COpenWriteFile wfile( vfs::tWritableFile::cast(&file));
			SGP_TRYCATCH_RETHROW(file.write(settings.str().c_str(), settings.str().length()),L"");
		}
	}

	return( TRUE );

}


void InitGameSettings()
{
	// completely blank out gGameSettings
	memset( &gGameSettings, 0, sizeof( GAME_SETTINGS ) );

	//Init the Game Settings
	gGameSettings.bLastSavedGameSlot	= -1;
	gGameSettings.ubMusicVolumeSetting	= 63;
	gGameSettings.ubSoundEffectsVolume	= 63;
	gGameSettings.ubSpeechVolume		= 63;

	//Set the settings
	SetSoundEffectsVolume( gGameSettings.ubSoundEffectsVolume );
	SetSpeechVolume( gGameSettings.ubSpeechVolume );
	MusicSetVolume( gGameSettings.ubMusicVolumeSetting );

	gGameSettings.fOptions[ TOPTION_SPEECH ]							= TRUE;
	gGameSettings.fOptions[ TOPTION_MUTE_CONFIRMATIONS ]				= FALSE;
	gGameSettings.fOptions[ TOPTION_SUBTITLES ]							= TRUE;
	gGameSettings.fOptions[ TOPTION_KEY_ADVANCE_SPEECH ]				= FALSE;
	gGameSettings.fOptions[ TOPTION_ANIMATE_SMOKE ]						= TRUE;
	gGameSettings.fOptions[ TOPTION_BLOOD_N_GORE ]						= TRUE;
	gGameSettings.fOptions[ TOPTION_DONT_MOVE_MOUSE ]					= FALSE;
	gGameSettings.fOptions[ TOPTION_OLD_SELECTION_METHOD ]				= FALSE;
	gGameSettings.fOptions[ TOPTION_ALWAYS_SHOW_MOVEMENT_PATH ]			= FALSE;
	gGameSettings.fOptions[	TOPTION_SHOW_MISSES ]						= FALSE;
	gGameSettings.fOptions[ TOPTION_RTCONFIRM ]							= FALSE;
	gGameSettings.fOptions[ TOPTION_SLEEPWAKE_NOTIFICATION ]			= TRUE;
	gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ]					= TRUE;
	gGameSettings.fOptions[ TOPTION_MERC_ALWAYS_LIGHT_UP ]				= FALSE;
	gGameSettings.fOptions[ TOPTION_SMART_CURSOR ]						= FALSE;
	gGameSettings.fOptions[ TOPTION_SNAP_CURSOR_TO_DOOR ]				= TRUE;
	gGameSettings.fOptions[ TOPTION_GLOW_ITEMS ]						= TRUE;
	gGameSettings.fOptions[ TOPTION_TOGGLE_TREE_TOPS ]					= TRUE;
	gGameSettings.fOptions[ TOPTION_TOGGLE_WIREFRAME ]					= TRUE;
	gGameSettings.fOptions[ TOPTION_3D_CURSOR ]							= FALSE;
	gGameSettings.fOptions[ TOPTION_CTH_CURSOR ]						= TRUE;

	//Madd:
	gGameSettings.fOptions[ TOPTION_GL_BURST_CURSOR ]					= TRUE;
	gGameSettings.fOptions[ TOPTION_ALLOW_TAUNTS ]						= TRUE;	// changed - SANDRO
	gGameSettings.fOptions[ TOPTION_GL_HIGH_ANGLE ]						= FALSE;
	gGameSettings.fOptions[	TOPTION_ALLOW_REAL_TIME_SNEAK ]				= FALSE;	// changed - SANDRO

	//lalien
	gGameSettings.fOptions[ TOPTION_SPACE_SELECTS_NEXT_SQUAD ]			= TRUE;
	gGameSettings.fOptions[ TOPTION_SHOW_ITEM_SHADOW ]					= TRUE;
	gGameSettings.fOptions[ TOPTION_SHOW_WEAPON_RANGE_IN_TILES ]		= TRUE;
	gGameSettings.fOptions[ TOPTION_TRACERS_FOR_SINGLE_FIRE ]			= FALSE;
	gGameSettings.fOptions[ TOPTION_RAIN_SOUND ]						= TRUE;
	gGameSettings.fOptions[ TOPTION_ALLOW_CROWS ]						= TRUE;
	gGameSettings.fOptions[ TOPTION_ALLOW_SOLDIER_TOOLTIPS ]			= TRUE;
	gGameSettings.fOptions[ TOPTION_USE_AUTO_SAVE ]						= FALSE;
	gGameSettings.fOptions[ TOPTION_SILENT_SKYRIDER ]					= FALSE;
	//gGameSettings.fOptions[ TOPTION_LOW_CPU_USAGE ]						= FALSE;
	gGameSettings.fOptions[ TOPTION_ENHANCED_DESC_BOX ]					= TRUE;

	// arynn 
	gGameSettings.fOptions[ TOPTION_TOGGLE_TURN_MODE ]					= FALSE;

	// HEADROCK HAM 3.6:
	gGameSettings.fOptions[ TOPTION_STAT_PROGRESS_BARS ]				= FALSE;

	// HEADROCK HAM 4:
	gGameSettings.fOptions[ TOPTION_ALT_MAP_COLOR ]						= FALSE;

	gGameSettings.fOptions[ TOPTION_ALTERNATE_BULLET_GRAPHICS ]			= TRUE;

	// CHRISL: HAM 4: Activate/Deactivate NCTH mode
	gGameSettings.fOptions[ TOPTION_USE_NCTH ]							= TRUE;

	// WANNE:
	gGameSettings.fOptions[ TOPTION_SHOW_TACTICAL_FACE_GEAR ]			= TRUE;
	gGameSettings.fOptions[ TOPTION_SHOW_TACTICAL_FACE_ICONS ]			= TRUE;

	gGameSettings.fOptions[ TOPTION_REPORT_MISS_MARGIN ]				= FALSE;

	gGameSettings.fOptions[ TOPTION_DISABLE_CURSOR_SWAP ]               = FALSE;

	// arynn: Cheat/Debug Menu
	gGameSettings.fOptions[ TOPTION_CHEAT_MODE_OPTIONS_HEADER ]			= FALSE;	
	gGameSettings.fOptions[ TOPTION_FORCE_BOBBY_RAY_SHIPMENTS ]			= FALSE;	// force all pending Bobby Ray shipments
	gGameSettings.fOptions[ TOPTION_CHEAT_MODE_OPTIONS_END ]			= FALSE;	
	gGameSettings.fOptions[ TOPTION_DEBUG_MODE_OPTIONS_HEADER ]			= FALSE;	// an example options screen options header (pure text)
	gGameSettings.fOptions[ TOPTION_SHOW_RESET_ALL_OPTIONS ]			= FALSE;	// failsafe show/hide option to reset all options
	gGameSettings.fOptions[ TOPTION_REPORT_MISS_MARGIN ]			    = FALSE;
	gGameSettings.fOptions[ TOPTION_RESET_ALL_OPTIONS ]					= FALSE;	// a do once and reset self option (button like effect)
	gGameSettings.fOptions[ TOPTION_RETAIN_DEBUG_OPTIONS_IN_RELEASE ]	= FALSE;	// allow debug options that were set in debug.exe to continue in a rel.exe (debugging release can be beneficial)
	gGameSettings.fOptions[	TOPTION_DEBUG_MODE_RENDER_OPTIONS_GROUP ]	= FALSE;	// an example option that will show/hide other options
	gGameSettings.fOptions[	TOPTION_RENDER_MOUSE_REGIONS ]				= FALSE;	// an example of a DEBUG build option
	gGameSettings.fOptions[	TOPTION_DEBUG_MODE_OPTIONS_END ]			= FALSE;	// an example options screen options divider (pure text)

	// enum control options (not real options but included here for the sake of complete control of values)

	//gGameSettings.ubSizeOfDisplayCover = 16;
	//gGameSettings.ubSizeOfLOS = 16;

	// ary-05/05/2009 : TOPTION_LAST_OPTION is THE LAST options screen toggle option that exists. (its still an option, and its < NUM_GAME_OPTIONS)
	//		 : intended for debugging options screen final page. test to avoid last page over or under extension. 
	//		 : might be useful in future of toggle option content developement.
	gGameSettings.fOptions[	TOPTION_LAST_OPTION ]						= FALSE; // doesnt do anything except exist
	gGameSettings.fOptions[	NUM_GAME_OPTIONS ]						    = FALSE; // Toggles prior to this will be able to be toggled by the player

	// JA2Gold
	gGameSettings.fOptions[ TOPTION_MERC_CASTS_LIGHT ]					= TRUE;

	gGameSettings.fOptions[ TOPTION_HIDE_BULLETS ]						= FALSE;
	gGameSettings.fOptions[ TOPTION_TRACKING_MODE ]						= TRUE;

	gGameSettings.fOptions[	NUM_ALL_GAME_OPTIONS ]						= FALSE; // Absolute final end of enum

	//Since we just set the settings, save them
	SaveGameSettings();

}

void InitGameOptions()
{
	memset( &gGameOptions, 0, sizeof( GAME_OPTIONS ) );

	gGameOptions.ubBobbyRay			= BR_GOOD;
	gGameOptions.fGunNut			= TRUE;
	gGameOptions.fAirStrikes		= FALSE;
	gGameOptions.ubGameStyle		= STYLE_SCIFI;
	gGameOptions.ubDifficultyLevel	= DIF_LEVEL_MEDIUM;

	//CHRISL: override default inventory mode when in low res
	if(IsNIVModeValid(true) == FALSE)
	{
		gGameOptions.ubInventorySystem	= INVENTORY_OLD;
		gGameOptions.ubAttachmentSystem = ATTACHMENT_OLD;
	}
	else
	{
		gGameOptions.ubInventorySystem	= INVENTORY_NEW;
		gGameOptions.ubAttachmentSystem = ATTACHMENT_OLD;
	}
	
	gGameOptions.fTurnTimeLimit	= FALSE;
	gGameOptions.fIronManMode		= FALSE;
	
	// following added by SANDRO
	gGameOptions.ubMaxIMPCharacters	= (gGameExternalOptions.iIMPMaleCharacterCount + gGameExternalOptions.iIMPFemaleCharacterCount); 

	if (gGameExternalOptions.fReadProfileDataFromXML)
		gGameOptions.fNewTraitSystem	= TRUE;
	else
		gGameOptions.fNewTraitSystem	= FALSE;

	gGameOptions.ubProgressSpeedOfItemsChoices  = ITEM_PROGRESS_NORMAL;
	gGameOptions.fEnableAllTerrorists = FALSE;
	gGameOptions.fEnemiesDropAllItems	= FALSE; 
	gGameOptions.fEnableAllWeaponCaches = FALSE;
}


// WDS: These HAVE to total 100% at all times!!!
//#define PROGRESS_PORTION_KILLS		25
//#define PROGRESS_PORTION_CONTROL	25
//#define PROGRESS_PORTION_INCOME		50


// The following are for fixing problems when reading the .ini file
#define COUNT_STANDARD_MALE_SLOTS 3
#define FIRST_STANDARD_MALE_SLOT 51
#define COUNT_STANDARD_FEMALE_SLOTS 3
#define FIRST_STANDARD_FEMALE_SLOT 54


extern INT32 CountFilledIMPSlots( INT8 iSex );
extern INT32 CountEmptyIMPSlots( INT8 iSex );

// Snap: Read options from an INI file in the default of custom Data directory
void LoadGameExternalOptions()
{

	//Kaiden: Setting Ja2_Options.ini file to be read
	CIniReader iniReader(GAME_EXTERNAL_OPTIONS_FILE);
	
	//################# System Limit Settings #################

	// WDS - make number of mercenaries, etc. be configurable. Note: Changing one of these can render savegames unloadable.
	gGameExternalOptions.ubGameMaximumNumberOfPlayerMercs			= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_PLAYER_MERCS", 24, 1, CODE_MAXIMUM_NUMBER_OF_PLAYER_MERCS);
	gGameExternalOptions.ubGameMaximumNumberOfPlayerVehicles		= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_PLAYER_VEHICLES", 2, 2, CODE_MAXIMUM_NUMBER_OF_PLAYER_VEHICLES);

	gGameExternalOptions.ubGameMaximumNumberOfEnemies				= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_ENEMIES_IN_TACTICAL", 32, 16, CODE_MAXIMUM_NUMBER_OF_ENEMIES);
	gGameExternalOptions.ubGameMaximumNumberOfCreatures				= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_CREATURES_IN_TACTICAL", 32, 0, CODE_MAXIMUM_NUMBER_OF_CREATURES);
	gGameExternalOptions.ubGameMaximumNumberOfRebels				= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_MILITIA_IN_TACTICAL", 32, 16, CODE_MAXIMUM_NUMBER_OF_REBELS);
	gGameExternalOptions.ubGameMaximumNumberOfCivilians				= iniReader.ReadInteger("System Limit Settings","MAX_NUMBER_CIVS_IN_TACTICAL", 32, 16, CODE_MAXIMUM_NUMBER_OF_CIVS);

	gGameExternalOptions.iMaxEnemyGroupSize							= iniReader.ReadInteger("System Limit Settings","MAX_STRATEGIC_ENEMY_GROUP_SIZE",20, 10, 100);

	//################# Data File Settings #################

	// WANNE: Always use prof.dat??
	gGameExternalOptions.fUseDifficultyBasedProfDat		= iniReader.ReadBoolean("Data File Settings", "USE_DIFFICULTY_BASED_PROF_DAT", TRUE);

	// HEADROCK PROFEX/3.6: Activate this to read Profile data from MercProfiles.XML and MercOpinions.XML
	gGameExternalOptions.fReadProfileDataFromXML		= iniReader.ReadBoolean("Data File Settings","READ_PROFILE_DATA_FROM_XML", TRUE);

	// HEADROCK PROFEX/3.6: Activate this to write Profile data to MercProfiles Out.XML and MercOpinions Out.XML. This can be used to convert PROF.DAT to XML format.
	gGameExternalOptions.fWriteProfileDataToXML			= iniReader.ReadBoolean("Data File Settings","WRITE_PROFILE_DATA_TO_XML", FALSE);

	// Use "EnemyWeaponDrop.XML" etc. for determining which items are dropped?
	gGameExternalOptions.ubEnemiesItemDrop				= iniReader.ReadInteger("Data File Settings","USE_EXTERNALIZED_ENEMY_ITEM_DROPS", 0, 0, 1);

	//################# Merc Recruitment Settings #################

	// WDS: Allow flexible numbers of IMPs of each sex
	// SANDRO - moved to the game itself
	//gGameExternalOptions.iMaxIMPCharacters		= iniReader.ReadInteger("Recruitment Settings","MAX_IMP_CHARACTERS",1, 1, NUM_PROFILES);

	gGameExternalOptions.iIMPMaleCharacterCount	= iniReader.ReadInteger("Recruitment Settings","IMP_MALE_CHARACTER_COUNT", COUNT_STANDARD_MALE_SLOTS, 1, NUM_PROFILES);
	gGameExternalOptions.iIMPFemaleCharacterCount = iniReader.ReadInteger("Recruitment Settings","IMP_FEMALE_CHARACTER_COUNT", COUNT_STANDARD_FEMALE_SLOTS, 1, NUM_PROFILES);
	if (gGameExternalOptions.iIMPMaleCharacterCount + gGameExternalOptions.iIMPFemaleCharacterCount > NUM_PROFILES)
	{
		gGameExternalOptions.iIMPMaleCharacterCount	= COUNT_STANDARD_MALE_SLOTS;
		gGameExternalOptions.iIMPFemaleCharacterCount = COUNT_STANDARD_FEMALE_SLOTS;
	}

	//
	// Note: put -1 between male/female slots and -1 at end.	This allows everything to be
	// counted dynamically quite easily.	Note that all the code assumes there is AT
	// LEAST ONE slot for each sex.	If that changes the code will have to be updated.
	//
	// Because errors in these values can really goof things up we will try to fix up bad
	// values and use the defaults instead.
	//
	int idx;
	char caMaleCountStr [] = "IMP_MALE_%d";
	char caFemaleCountStr [] = "IMP_FEMALE_%d";
	char caCountStr[20];

	gGameExternalOptions.iaIMPSlots = (INT32*)MemAlloc( (gGameExternalOptions.iIMPMaleCharacterCount + gGameExternalOptions.iIMPFemaleCharacterCount + 2) * sizeof( UINT32 ) );
	for (idx = 0; idx < gGameExternalOptions.iIMPMaleCharacterCount; ++idx)
	{
		sprintf( caCountStr, caMaleCountStr, idx+1);
		gGameExternalOptions.iaIMPSlots[idx] = iniReader.ReadInteger("Recruitment Settings",caCountStr, -1, -1, NUM_PROFILES-1);
		if (gGameExternalOptions.iaIMPSlots[idx] < 0)
		{
			if (idx < COUNT_STANDARD_MALE_SLOTS)
			{
				gGameExternalOptions.iaIMPSlots[idx] = FIRST_STANDARD_MALE_SLOT+idx;
			}
			else
			{
				// This is bad so just use the last standard slot #
				gGameExternalOptions.iaIMPSlots[idx] = FIRST_STANDARD_MALE_SLOT+COUNT_STANDARD_MALE_SLOTS-1;
			}
		}
	}
	gGameExternalOptions.iaIMPSlots[gGameExternalOptions.iIMPMaleCharacterCount] = -1;
	for (idx = 0; idx < gGameExternalOptions.iIMPFemaleCharacterCount; ++idx)
	{
		sprintf( caCountStr, caFemaleCountStr, idx+1);
		gGameExternalOptions.iaIMPSlots[idx+gGameExternalOptions.iIMPMaleCharacterCount+1] = iniReader.ReadInteger("Recruitment Settings",caCountStr, -1, -1, NUM_PROFILES-1);
		if (gGameExternalOptions.iaIMPSlots[idx+gGameExternalOptions.iIMPMaleCharacterCount+1] < 0)
		{
			if (idx < COUNT_STANDARD_FEMALE_SLOTS)
			{
				gGameExternalOptions.iaIMPSlots[idx+gGameExternalOptions.iIMPMaleCharacterCount+1] = FIRST_STANDARD_FEMALE_SLOT+idx;
			}
			else
			{
				// This is bad so just use the last standard slot #
				gGameExternalOptions.iaIMPSlots[idx+gGameExternalOptions.iIMPMaleCharacterCount+1] = FIRST_STANDARD_FEMALE_SLOT+COUNT_STANDARD_FEMALE_SLOTS-1;
			}
		}
	}
	gGameExternalOptions.iaIMPSlots[gGameExternalOptions.iIMPFemaleCharacterCount+gGameExternalOptions.iIMPMaleCharacterCount+1] = -1;

	// silversurfer: read early recruitment options 1=immediately (control Omerta), 2=early (control 1, 2, 3 towns including Omerta)
	// 3=normal (control 3, 4, 5 towns including Omerta), 4=after liberating Omerta and solving the "Deliver Food Quest" for Miguel
	gGameExternalOptions.ubEarlyRebelsRecruitment[0]	= iniReader.ReadInteger("Recruitment Settings","EARLY_REBELS_RECRUITMENT", 3, 1, 4);
	switch (gGameExternalOptions.ubEarlyRebelsRecruitment[0])
	{
		case 2:
			{
				gGameExternalOptions.ubEarlyRebelsRecruitment[1] = 1;	// FACT_PLAYER_OWNS_2_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[2] = 2;	// FACT_PLAYER_OWNS_3_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[3] = 3;	// FACT_PLAYER_OWNS_4_TOWNS_INCLUDING_OMERTA
				break;
			}
		case 3:
			{
				gGameExternalOptions.ubEarlyRebelsRecruitment[1] = 3;	// FACT_PLAYER_OWNS_2_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[2] = 4;	// FACT_PLAYER_OWNS_3_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[3] = 5;	// FACT_PLAYER_OWNS_4_TOWNS_INCLUDING_OMERTA
				break;
			}
		case 4:
			{
				gGameExternalOptions.ubEarlyRebelsRecruitment[1] = 3;	// FACT_PLAYER_OWNS_2_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[2] = 4;	// FACT_PLAYER_OWNS_3_TOWNS_INCLUDING_OMERTA
				gGameExternalOptions.ubEarlyRebelsRecruitment[3] = 5;	// FACT_PLAYER_OWNS_4_TOWNS_INCLUDING_OMERTA
				break;
			}
		default:
			break;
	}

	//I.M.P Character generation
	// SANDRO - some changes here
	gGameExternalOptions.iIMPProfileCost				 = iniReader.ReadInteger("Recruitment Settings","IMP_PROFILE_COST",3000, 0, 50000);
	gGameExternalOptions.fDynamicIMPProfileCost			 = iniReader.ReadBoolean("Recruitment Settings","DYNAMIC_IMP_PROFILE_COST",FALSE);
	gGameExternalOptions.iImpAttributePoints				= iniReader.ReadInteger("Recruitment Settings","IMP_INITIAL_POINTS",500, 1, 5000);
	gGameExternalOptions.iMinAttribute						= iniReader.ReadInteger("Recruitment Settings","IMP_MIN_ATTRIBUTE",35, 1, 99);
	gGameExternalOptions.iMaxZeroBonus						= iniReader.ReadInteger("Recruitment Settings","IMP_BONUS_POINTS_FOR_ZERO_ATTRIBUTE",15, 0, 100);
	// if attribute points set too low...
	if ( gGameExternalOptions.iImpAttributePoints < ((gGameExternalOptions.iMinAttribute * 5) + (gGameExternalOptions.iMaxZeroBonus * 5)) )
	{
		gGameExternalOptions.iImpAttributePoints = ((gGameExternalOptions.iMinAttribute * 5) + (gGameExternalOptions.iMaxZeroBonus * 5));
	}

	gGameExternalOptions.iMaxAttribute						= iniReader.ReadInteger("Recruitment Settings","IMP_MAX_ATTRIBUTE",90, gGameExternalOptions.iMinAttribute, 100);
	gGameExternalOptions.iIMPStartingLevelCostMultiplier	= iniReader.ReadInteger("Recruitment Settings","IMP_STARTING_LEVEL_COST_MULTIPLIER", 5, 0, 100);
	gGameExternalOptions.iBonusPointsForDisability			= iniReader.ReadInteger("Recruitment Settings","IMP_BONUS_POINTS_FOR_DISABILITY",20, 0, 500);
	gGameExternalOptions.iBonusPointsPerSkillNotTaken		= iniReader.ReadInteger("Recruitment Settings","IMP_BONUS_POINTS_PER_SKILL_NOT_TAKEN",25, 0, 500);
	// DBrot: Expert choices
	gGameExternalOptions.fExpertsGetDifferentChoices			 = iniReader.ReadBoolean("Recruitment Settings","EXPERTS_GET_DIFFERENT_CHOICES",FALSE);
	//Merc settings
	gGameExternalOptions.fMercDayOne						= iniReader.ReadBoolean("Recruitment Settings","MERC_WEBSITE_IMMEDIATELY_AVAILABLE",FALSE);
	gGameExternalOptions.fAllMercsAvailable					= iniReader.ReadBoolean("Recruitment Settings","MERC_WEBSITE_ALL_MERCS_AVAILABLE",FALSE);
	//tais: mercs can go on assignment; 0 = default behaviour, 1 = all mercs available at start, 2 = no mercs go on other assignments... period!
	gGameExternalOptions.fMercsOnAssignment			= iniReader.ReadInteger("Recruitment Settings","MERCS_CAN_BE_ON_ASSIGNMENT",0,0,2);



	//Merc Death Settings:
	gGameExternalOptions.gfMercsDieOnAssignment			= iniReader.ReadBoolean("Recruitment Settings","MERCS_CAN_DIE_ON_ASSIGNMENT",TRUE);
	gGameExternalOptions.giEasyMercDeaths				= iniReader.ReadInteger("Recruitment Settings","MAX_MERC_DEATHS_EASY",1, 0, 10);
	gGameExternalOptions.giExperiencedMercDeaths		= iniReader.ReadInteger("Recruitment Settings","MAX_MERC_DEATHS_EXPERIENCED",2, 0, 10);
	gGameExternalOptions.giExpertMercDeaths				= iniReader.ReadInteger("Recruitment Settings","MAX_MERC_DEATHS_EXPERT",3, 0, 10);
	gGameExternalOptions.giInsaneMercDeaths				= iniReader.ReadInteger("Recruitment Settings","MAX_MERC_DEATHS_INSANE",4, 0, 10);

	// CHRISL: New setting to allow Slay to remain as a hired PC
	gGameExternalOptions.fEnableSlayForever					= iniReader.ReadBoolean("Recruitment Settings", "SLAY_STAYS_FOREVER", FALSE);

	//################# Financial Settings #################

	gGameExternalOptions.iStartingCashNovice		= iniReader.ReadInteger("Financial Settings", "STARTING_CASH_NOVICE",45000, 2000, 0x0FFFFFFF);
	gGameExternalOptions.iStartingCashExperienced	= iniReader.ReadInteger("Financial Settings", "STARTING_CASH_EXPERIENCED",35000, 2000, 0x0FFFFFFF);
	gGameExternalOptions.iStartingCashExpert		= iniReader.ReadInteger("Financial Settings", "STARTING_CASH_EXPERT",30000, 2000, 0x0FFFFFFF);
	gGameExternalOptions.iStartingCashInsane		= iniReader.ReadInteger("Financial Settings", "STARTING_CASH_INSANE",15000, 2000, 0x0FFFFFFF);

	// HEADROCK HAM B1: Set % of mine income, where 100% = normal
	gGameExternalOptions.usMineIncomePercentage		= iniReader.ReadInteger("Financial Settings","MINE_INCOME_PERCENTAGE", 100, 1, 1000);

	// ALT+LMB item selling
	gGameExternalOptions.fSellAll					= iniReader.ReadBoolean("Financial Settings","SELL_ITEMS_WITH_ALT_LMB",FALSE);
	gGameExternalOptions.iPriceModifier				= iniReader.ReadInteger("Financial Settings","SELL_ITEMS_PRICE_MODIFIER",10, -1, 100);

	gGameExternalOptions.iMilitiaTrainingCost			= iniReader.ReadInteger("Financial Settings","MILITIA_BASE_TRAINING_COST",750, 10, 10000);
	gGameExternalOptions.iRegularCostModifier			= iniReader.ReadInteger("Financial Settings","MILITIA_COST_MULTIPLIER_REGULAR",1, 1, 10);
	gGameExternalOptions.iVeteranCostModifier			= iniReader.ReadInteger("Financial Settings","MILITIA_COST_MULTIPLIER_ELITE",2, 1, 10);
	gGameExternalOptions.iMilitiaCostModifier			= iniReader.ReadInteger("Financial Settings","MILITIA_COST_MULTIPLIER_MOBILE",3, 1, 10);

	// HEADROCK HAM 3.6: Daily upkeep costs for militia
	gGameExternalOptions.usDailyCostTownGreen			= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_TOWN_GREEN", 0, 0, 10000);
	gGameExternalOptions.usDailyCostTownRegular			= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_TOWN_REGULAR", 0, 0, 10000);
	gGameExternalOptions.usDailyCostTownElite			= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_TOWN_ELITE", 0, 0, 10000);
	gGameExternalOptions.usDailyCostMobileGreen			= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_MOBILE_GREEN", 0, 0, 10000);
	gGameExternalOptions.usDailyCostMobileRegular		= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_MOBILE_REGULAR", 0, 0, 10000);
	gGameExternalOptions.usDailyCostMobileElite			= iniReader.ReadInteger("Financial Settings","DAILY_MILITIA_UPKEEP_MOBILE_ELITE", 0, 0, 10000);

	// HEADROCK HAM 3.5: Helicopter - Base cost per sector. GREEN = Free airspace, RED = Enemy-controlled airspace.
	gGameExternalOptions.usHelicopterBaseCostPerGreenTile				= iniReader.ReadInteger("Financial Settings","HELICOPTER_BASE_COST_PER_GREEN_TILE", 100, 0, 60000);
	gGameExternalOptions.usHelicopterBaseCostPerRedTile					= iniReader.ReadInteger("Financial Settings","HELICOPTER_BASE_COST_PER_RED_TILE", 1000, 0, 60000);

	//tais: percentage that the merc's salary rises when he/she levels up
	gGameExternalOptions.gMercLevelUpSalaryIncreasePercentage		= (FLOAT)iniReader.ReadInteger("Financial Settings","MERC_LEVEL_UP_SALARY_INCREASE_PERCENTAGE",25, 0, 1000);
	
	//################# Troubleshooting Settings #################

	gGameExternalOptions.gubDeadLockDelay = (UINT8) iniReader.ReadInteger("Troubleshooting Settings","DEAD_LOCK_DELAY",15, 5, 50);
	gGameExternalOptions.gfEnableEmergencyButton_SkipStrategicEvents = iniReader.ReadBoolean("Troubleshooting Settings","ENABLE_EMERGENCY_BUTTON_NUMLOCK_TO_SKIP_STRATEGIC_EVENTS",0);

	// WDS - Automatically try to save when an assertion failure occurs
	gGameExternalOptions.autoSaveOnAssertionFailure		= iniReader.ReadBoolean("Troubleshooting Settings","AUTO_SAVE_ON_ASSERTION_FAILURE", FALSE);
	gGameExternalOptions.autoSaveTime 					= iniReader.ReadInteger("Troubleshooting Settings","AUTO_SAVE_EVERY_N_HOURS", 6, 0, 24);

	//################# Graphics Settings #################
	gGameExternalOptions.gfVSync = iniReader.ReadBoolean("Graphics Settings","VERTICAL_SYNC",0);

	gGameExternalOptions.giPlayerTurnSpeedUpFactor		= iniReader.ReadFloat("Graphics Settings","PLAYER_TURN_SPEED_UP_FACTOR",1.0, 0, 1.0);
	gGameExternalOptions.giEnemyTurnSpeedUpFactor		= iniReader.ReadFloat("Graphics Settings","ENEMY_TURN_SPEED_UP_FACTOR",1.0, 0, 1.0);
	gGameExternalOptions.giCreatureTurnSpeedUpFactor	= iniReader.ReadFloat("Graphics Settings","CREATURE_TURN_SPEED_UP_FACTOR",1.0, 0, 1.0);
	gGameExternalOptions.giMilitiaTurnSpeedUpFactor		= iniReader.ReadFloat("Graphics Settings","MILITIA_TURN_SPEED_UP_FACTOR",1.0, 0, 1.0);
	gGameExternalOptions.giCivilianTurnSpeedUpFactor	= iniReader.ReadFloat("Graphics Settings","CIVILIAN_TURN_SPEED_UP_FACTOR",1.0, 0, 1.0);

	gGameExternalOptions.gfUseExternalLoadscreens		= iniReader.ReadBoolean("Graphics Settings","USE_EXTERNALIZED_LOADSCREENS", FALSE);

	//tais: enable/disable New Starting Gear Interface (0 = disabled, classic style; 1 = enabled, new 21 item view and up to 5 gearkit selection)
	gGameExternalOptions.gfUseNewStartingGearInterface		= iniReader.ReadBoolean("Graphics Settings","USE_NEW_STARTING_GEAR_INTERFACE", FALSE);

	// WANNE: Moved to options screen
	//afp - use a different graphic for bullets?
	//gGameExternalOptions.gbBulletTracer					= iniReader.ReadBoolean("Graphics Settings","ALTERNATE_BULLET_GRAPHICS",FALSE);

	// Are enemy females restricted to Blackshirts only?
	gGameExternalOptions.fRestrictFemaleEnemiesExceptElite	= iniReader.ReadBoolean("Graphics Settings","RESTRICT_FEMALE_ENEMIES_EXCEPT_ELITE",FALSE);

	// *** ddd - BEGIN
	// New setting to allow thin progressbar
	gGameExternalOptions.fSmallSizeProgressbar				= iniReader.ReadBoolean("Graphics Settings", "SMALL_SIZE_PB", FALSE);
	// *** ddd - END
	
	//################# Sound Settings #################
	
	gGameExternalOptions.guiWeaponSoundEffectsVolume	= iniReader.ReadInteger("Sound Settings","WEAPON_SOUND_EFFECTS_VOLUME",0, 0, 1000 /*1000 = 10x?*/);



	//################# Tactical Interface Settings #################

	gGameExternalOptions.gfRevealItems						= iniReader.ReadBoolean("Tactical Interface Settings","REVEAL_DROPPED_ENEMY_ITEMS_AFTER_COMBAT",TRUE);

	// Unload weapons & remove attachments
	gGameExternalOptions.gfShiftFUnloadWeapons				= iniReader.ReadBoolean("Tactical Interface Settings","SHIFT_F_UNLOAD_WEAPONS",1);
	gGameExternalOptions.gfShiftFRemoveAttachments			= iniReader.ReadBoolean("Tactical Interface Settings","SHIFT_F_REMOVE_ATTACHMENTS",1);

	// WDS - Smart goggle switching
	gGameExternalOptions.smartGoggleSwitch					= iniReader.ReadBoolean("Tactical Interface Settings","SMART_GOGGLE_SWAP", FALSE);

	// HEADROCK HAM 3.5: When enabled, goggle-switching affects every merc in the sector, not just those belonging to the current squad.
	gGameExternalOptions.fGoggleSwapAffectsAllMercsInSector	= iniReader.ReadBoolean("Tactical Interface Settings","GOGGLE_SWAP_AFFECTS_ALL_MERCS_IN_SECTOR", FALSE);

	// WDS - Automatically flag mines
	gGameExternalOptions.automaticallyFlagMines				= iniReader.ReadBoolean("Tactical Interface Settings","AUTOMATICALLY_FLAG_MINES_WHEN_SPOTTED", FALSE);

	// silversurfer: don't play quote when mine spotted?
	gGameExternalOptions.fMineSpottedNoTalk					= iniReader.ReadBoolean("Tactical Interface Settings","MINES_SPOTTED_NO_TALK", FALSE);
	
	//DBrot: Stand up after battle? 
	gGameExternalOptions.fStandUpAfterBattle				= iniReader.ReadBoolean("Tactical Interface Settings","STAND_UP_AFTER_BATTLE", TRUE);
	// Tactical militia command	
	gGameExternalOptions.fAllowTacticalMilitiaCommand		= iniReader.ReadBoolean("Tactical Interface Settings","ALLOW_TACTICAL_MILITIA_COMMAND",0);

	// Determines where to use the Enhanced Description Box. Turn on/off via in-game options menu.
	gGameExternalOptions.iEnhancedDescriptionBox			= iniReader.ReadInteger("Tactical Interface Settings","USE_ENHANCED_DESCRIPTION_BOX",0, 0, 2);

	// HEADROCK HAM B2.6/2/1: Toggle new Burst/Auto Targeting Cursors: 0=neither, 1=both, 2=Burst, 3=Auto
	gGameExternalOptions.ubNewCTHBars						= iniReader.ReadInteger("Tactical Interface Settings","USE_NEW_BURST-AUTO_TARGETING_CURSORS", 0, 0, 3);

	// HEADROCK HAM B2.7: When turned on, this will give a CTH approximation instead of an exact value, on CTH Bars and "F" key feedback.
	gGameExternalOptions.fApproximateCTH					= iniReader.ReadBoolean("Tactical Interface Settings","INACCURATE_CTH_READOUT", FALSE);

	// HEADROCK HAM 3.4: This controls the intensity of Hiding the Bullet Count during combat. The higher it is, the more intense the effect. Negative values reduce the effect.
	gGameExternalOptions.usBulletHideIntensity				= iniReader.ReadInteger("Tactical Interface Settings","HIDE_BULLET_COUNT_INTENSITY", 100, 0, 1000);

	// HEADROCK HAM 3.6: Maximum number of messages displayed in Tactical view
	gGameExternalOptions.ubMaxMessagesTactical				= iniReader.ReadInteger("Tactical Interface Settings","MAXIMUM_MESSAGES_IN_TACTICAL", 6, 1, 36);
	// Apply a resolution-based limit.
	switch (iResolution)
	{
		case 0:
			// Max 20 lines in 640x480
			gGameExternalOptions.ubMaxMessagesTactical = __max(20, gGameExternalOptions.ubMaxMessagesTactical);
			break;
		case 1:
			// Max 26 lines in 800x600
			gGameExternalOptions.ubMaxMessagesTactical = __max(26, gGameExternalOptions.ubMaxMessagesTactical);
			break;
	}

	// WANNE: Moved to options screen
	//legion by Jazz
	/*gGameExternalOptions.fShowTacticalFaceGear				= iniReader.ReadBoolean("Tactical Interface Settings","SHOW_TACTICAL_FACE_GEAR",FALSE);
	gGameExternalOptions.fShowTacticalFaceIcons				= iniReader.ReadBoolean("Tactical Interface Settings","SHOW_TACTICAL_FACE_ICONS",FALSE);*/

	gGameExternalOptions.bTacticalFaceIconStyle 			= iniReader.ReadInteger("Tactical Interface Settings","TACTICAL_FACE_ICON_STYLE", 0, 0, 3);

	// Camo portraits by Jazz
	gGameExternalOptions.fShowCamouflageFaces				= iniReader.ReadBoolean("Tactical Interface Settings","SHOW_CAMOUFLAGE_FACES", FALSE);

	//################# Tactical Difficulty Settings #################

	// Enemy AP settings
	gGameExternalOptions.iEasyAPBonus					= (INT8) iniReader.ReadInteger("Tactical Difficulty Settings","ENEMY_AP_BONUS_NOVICE",0,__max(-APBPConstants[AP_MINIMUM],-128),127);
	gGameExternalOptions.iExperiencedAPBonus			= (INT8) iniReader.ReadInteger("Tactical Difficulty Settings","ENEMY_AP_BONUS_EXPERIENCED",0,__max(-APBPConstants[AP_MINIMUM],-128),127);
	gGameExternalOptions.iExpertAPBonus					= (INT8) iniReader.ReadInteger("Tactical Difficulty Settings","ENEMY_AP_BONUS_EXPERT",0,__max(-APBPConstants[AP_MINIMUM],-128),127);
	gGameExternalOptions.iInsaneAPBonus					= (INT8) iniReader.ReadInteger("Tactical Difficulty Settings","ENEMY_AP_BONUS_INSANE",0,__max(-APBPConstants[AP_MINIMUM],-128),127);

	gGameExternalOptions.iPlayerAPBonus					= (INT8) iniReader.ReadInteger("Tactical Difficulty Settings","PLAYER_AP_BONUS",0,__max(-APBPConstants[AP_MINIMUM],-128),127);

	// Percentage bonus to total enemy CtH on every hit - applies during tactical combat only
	gGameExternalOptions.sEnemyAdminCtHBonusPercent	 = iniReader.ReadInteger("Tactical Difficulty Settings", "ADMIN_CTH_BONUS_PERCENT", 0, -100, 500);
	gGameExternalOptions.sEnemyRegularCtHBonusPercent = iniReader.ReadInteger("Tactical Difficulty Settings", "REGULAR_CTH_BONUS_PERCENT", 0, -100, 500);
	gGameExternalOptions.sEnemyEliteCtHBonusPercent = iniReader.ReadInteger("Tactical Difficulty Settings", "ELITE_CTH_BONUS_PERCENT", 10, -100, 500);

	// Damage the enemz suffer is reduced by this percentage - applies during tactical combat only
	gGameExternalOptions.sEnemyAdminDamageResistance	 = iniReader.ReadInteger("Tactical Difficulty Settings", "ADMIN_DAMAGE_RESISTANCE", 0, -50, 95);
	gGameExternalOptions.sEnemyRegularDamageResistance = iniReader.ReadInteger("Tactical Difficulty Settings", "REGULAR_DAMAGE_RESISTANCE", 0, -50, 95);
	gGameExternalOptions.sEnemyEliteDamageResistance = iniReader.ReadInteger("Tactical Difficulty Settings", "ELITE_DAMAGE_RESISTANCE", 0, -50, 95);

	// SANDRO - Function to assign traits to enemy soldiers or militia
	gGameExternalOptions.fAssignTraitsToEnemy	= iniReader.ReadBoolean("Tactical Difficulty Settings", "ASSIGN_SKILL_TRAITS_TO_ENEMY", FALSE);
	gGameExternalOptions.fAssignTraitsToMilitia	= iniReader.ReadBoolean("Tactical Difficulty Settings", "ASSIGN_SKILL_TRAITS_TO_MILITIA", FALSE);
	gGameExternalOptions.bAssignedTraitsRarity = iniReader.ReadInteger("Tactical Difficulty Settings", "ASSIGNED_SKILL_TRAITS_RARITY ", 0, -100, 100);

	// HEADROCK HAM B2.8: At "1", Militia will drop their equipment similar to enemies, IF killed by non-player character. At "2" they drop whenever killed.
	gGameExternalOptions.ubMilitiaDropEquipment			= iniReader.ReadInteger("Tactical Difficulty Settings","MILITIA_DROP_EQUIPMENT", 0, 0, 2 );

	// HEADROCK HAM B2.7: Change the speed of skill progression. (defaults set to JA2 normal)
	gGameExternalOptions.usHealthSubpointsToImprove			= iniReader.ReadInteger("Tactical Difficulty Settings","HEALTH_SUBPOINTS_TO_IMPROVE", 50, 1, 1000 );
	gGameExternalOptions.usStrengthSubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","STRENGTH_SUBPOINTS_TO_IMPROVE", 50, 1, 1000 );
	gGameExternalOptions.usDexteritySubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","DEXTERITY_SUBPOINTS_TO_IMPROVE", 50, 1, 1000 );
	gGameExternalOptions.usAgilitySubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","AGILITY_SUBPOINTS_TO_IMPROVE", 50, 1, 1000 );
	gGameExternalOptions.usWisdomSubpointsToImprove			= iniReader.ReadInteger("Tactical Difficulty Settings","WISDOM_SUBPOINTS_TO_IMPROVE", 50, 1, 1000 );
	gGameExternalOptions.usMarksmanshipSubpointsToImprove	= iniReader.ReadInteger("Tactical Difficulty Settings","MARKSMANSHIP_SUBPOINTS_TO_IMPROVE", 25, 1, 1000 );
	gGameExternalOptions.usMedicalSubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","MEDICAL_SUBPOINTS_TO_IMPROVE", 25, 1, 1000 );
	gGameExternalOptions.usMechanicalSubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","MECHANICAL_SUBPOINTS_TO_IMPROVE", 25, 1, 1000 );
	gGameExternalOptions.usExplosivesSubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","EXPLOSIVES_SUBPOINTS_TO_IMPROVE", 25, 1, 1000 );
	gGameExternalOptions.usLeadershipSubpointsToImprove		= iniReader.ReadInteger("Tactical Difficulty Settings","LEADERSHIP_SUBPOINTS_TO_IMPROVE", 25, 1, 1000 );
	gGameExternalOptions.usLevelSubpointsToImprove			= iniReader.ReadInteger("Tactical Difficulty Settings","LEVEL_SUBPOINTS_TO_IMPROVE", 350, 1, 6500);

	// Alternate algorithm for choosing equipment level. Mostly disregards soldier's class and puts less emphasis on distance from Sector P3.
	// SANDRO - moved into the game
	//gGameExternalOptions.fSlowProgressForEnemyItemsChoice	= iniReader.ReadBoolean("Tactical Difficulty Settings", "SLOW_PROGRESS_FOR_ENEMY_ITEMS_CHOICE", TRUE);

	// The_Bob - real time sneaking code 01/06/09
	// Suport disabling real time sneaking via external .ini file
	// SANDRO - revisited and moved to preferences
	// gGameExternalOptions.fAllowRealTimeSneak				= iniReader.ReadBoolean("Tactical Difficulty Settings","ALLOW_REAL_TIME_SNEAK", FALSE);
	// Silence the RT sneaking messages
	gGameExternalOptions.fQuietRealTimeSneak				= iniReader.ReadBoolean("Tactical Difficulty Settings","QUIET_REAL_TIME_SNEAK", FALSE);
	// HEADROCK HAM 3.6: If activated, the game does not switch focus to a merc who spots an enemy in real-time mode. This fixes issues with Real-Time Sneak.
	gGameExternalOptions.fNoAutoFocusChangeInRealtimeSneak		= iniReader.ReadBoolean("Tactical Difficulty Settings","NO_AUTO_FOCUS_CHANGE_IN_REALTIME_SNEAK", FALSE);

	// HEADROCK HAM 3.2: If activated, reinforcements (militia/enemy) arrive in the battle with 0 APs. This makes them less of a diablo-ex-machina. 0 = Diabled. 2 = Enemies. 3 = Militia. 1 = both
	gGameExternalOptions.ubReinforcementsFirstTurnFreeze	= iniReader.ReadInteger("Tactical Difficulty Settings","REINFORCEMENTS_ARRIVE_WITH_ZERO_AP", 0, 0, 3);

	// HEADROCK HAM 3.6: Militia can now place blue flags when they spot a landmine.
	gGameExternalOptions.fMilitiaPlaceBlueFlags				= iniReader.ReadBoolean("Tactical Difficulty Settings","MILITIA_CAN_PLACE_FLAGS_ON_MINES", FALSE);

	// HEADROCK HAM 3.6: Non-Combat Bodytypes shouldn't become hostile
	gGameExternalOptions.fCanTrueCiviliansBecomeHostile		= iniReader.ReadBoolean("Tactical Difficulty Settings","CAN_TRUE_CIVILIANS_BECOME_HOSTILE", TRUE);

	// HEADROCK HAM 3.6: Militia become hostile when attacked. 0 = No. 1 = If killed. 2 = If attacked (JA2 Default)
	gGameExternalOptions.ubCanMilitiaBecomeHostile			= iniReader.ReadInteger("Tactical Difficulty Settings","CAN_MILITIA_BECOME_HOSTILE", 2, 0, 2);

	// SANDRO - Mercs stronger during autoresolve setting
	gGameExternalOptions.sMercsAutoresolveOffenseBonus = iniReader.ReadInteger("Tactical Difficulty Settings", "MERCS_OFFENSE_IN_AUTORESOLVE_BATTLES_BONUS",15, -100, 500);
	gGameExternalOptions.sMercsAutoresolveDeffenseBonus = iniReader.ReadInteger("Tactical Difficulty Settings", "MERCS_DEFFENSE_IN_AUTORESOLVE_BATTLES_BONUS",30, -100, 500);

	// WANNE: Added INI file Option for enemy ambushes, so we also have the option to play vanilla ja2 ambush settings
	// SANDRO - changed this so on any difficulty there is a chance to beambushed. Hoever this chance is calculated differently to not lead to instant load game like before
	gGameExternalOptions.fEnableChanceOfEnemyAmbushes = iniReader.ReadBoolean("Tactical Difficulty Settings", "ENABLE_CHANCE_OF_ENEMY_AMBUSHES", TRUE);
	gGameExternalOptions.bChanceModifierEnemyAmbushes = iniReader.ReadInteger("Tactical Difficulty Settings","ENEMY_AMBUSHES_CHANCE_MODIFIER ", 0, -100, 100);
	
	// SANDRO - Special NPCs strength increased by percent
	gGameExternalOptions.usSpecialNPCStronger = iniReader.ReadInteger("Tactical Difficulty Settings", "SPECIAL_NPCS_STRONGER",0, 0, 200);


	//################# Tactical Vision Settings #################

	// Sight range
	gGameExternalOptions.ubStraightSightRange				= iniReader.ReadInteger("Tactical Vision Settings","BASE_SIGHT_RANGE",13, 5, 100);

	// Tunnel Vision
	gGameExternalOptions.gfAllowLimitedVision				= iniReader.ReadBoolean("Tactical Vision Settings","ALLOW_TUNNEL_VISION",0);


	//################# Tactical Tooltip Settings #################

	// ShadoWarrior: Tooltip changes (start)
	gGameExternalOptions.ubSoldierTooltipDetailLevel		= (UINT8) iniReader.ReadInteger("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DETAIL_LEVEL", 1, 0, 4);

	gGameExternalOptions.fEnableDynamicSoldierTooltips		= iniReader.ReadBoolean("Tactical Tooltip Settings", "DYNAMIC_SOLDIER_TOOLTIPS", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipLocation		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_LOCATION", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBrightness	= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BRIGHTNESS", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipRangeToTarget	= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_RANGE_TO_TARGET", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipID			= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_ID", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipOrders		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_ORDERS", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipAttitude		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_ATTITUDE", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipActionPoints	= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_ACTIONPOINTS", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipHealth		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_HEALTH", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipTraits		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_TRAITS", TRUE); // added by SANDRO
	gGameExternalOptions.fEnableSoldierTooltipHelmet		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_HELMET", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipVest			= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_VEST", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipLeggings		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_LEGGINGS", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipHeadItem1		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_HEAD_SLOT_1", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipHeadItem2		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_HEAD_SLOT_2", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipWeapon		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_WEAPON", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipSecondHand	= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_OFF_HAND", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot1		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_1", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot2		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_2", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot3		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_3", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot4		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_4", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot5		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_5", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot6		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_6", TRUE);
	gGameExternalOptions.fEnableSoldierTooltipBigSlot7		= iniReader.ReadBoolean("Tactical Tooltip Settings", "SOLDIER_TOOLTIP_DISPLAY_BIG_SLOT_7", TRUE);
	// ShadoWarrior: Tooltip changes (end)

	//SCORE: Settings for UDT
	gGameExternalOptions.gfAllowUDTRange					= iniReader.ReadBoolean("Tactical Tooltip Settings","ALLOW_DYNAMIC_TOOLTIP_RANGE",0);
	gGameExternalOptions.ubUDTModifier						= (UINT8) iniReader.ReadInteger("Tactical Tooltip Settings", "DYNAMIC_TOOLTIP_RANGE_MODIFIER", 50);
	gGameExternalOptions.gfAllowUDTDetail					= iniReader.ReadBoolean("Tactical Tooltip Settings","ALLOW_DYNAMIC_TOOLTIP_DETAIL_LEVEL",0);


	//################# Tactical Gameplay Settings ##################

	gGameExternalOptions.fAllowWalkingWithWeaponRaised		= iniReader.ReadBoolean("Tactical Gameplay Settings","ALLOW_WALKING_WITH_WEAPON_RAISED", TRUE);

	// WANNE: Externalized grid number of new merc when they arrive with the helicopter (by Jazz)
	gGameExternalOptions.iInitialMercArrivalLocation		= iniReader.ReadInteger("Tactical Gameplay Settings","INITIAL_MERC_ARRIVAL_LOCATION", 4870 );

	// HEADROCK HAM B1: Set minimum and maximum CTH
	gGameExternalOptions.ubMaximumCTH						= iniReader.ReadInteger("Tactical Gameplay Settings","MAXIMUM_POSSIBLE_CTH", 99, 1, 100);

	gGameExternalOptions.ubMinimumCTH						= iniReader.ReadInteger("Tactical Gameplay Settings","MINIMUM_POSSIBLE_CTH", 1, 0, 99);

	// HEADROCK HAM B1: Set minimum CTH at fraction between 0 and 1 ( MINCTH = 1/(100*divisor) ) Note Minimum above must be 0.
	gGameExternalOptions.usMinimumCTHDivisor				= iniReader.ReadInteger("Tactical Gameplay Settings","MINIMUM_CTH_DIVISOR", 100, 1, 250);

	// HEADROCK HAM B2.5: Turn on Realistic Tracers. 0 = off (regular tracers). 1 = Fully realistic tracers. 2 = Tracer Bump + 1.13 Autofire Penalty Reduction
	gGameExternalOptions.ubRealisticTracers					= iniReader.ReadInteger("Tactical Gameplay Settings","REALISTIC_TRACERS", 0, 0, 2);

	// HEADROCK HAM B2.5: Realistic tracers - one of every X bullets in a tracer magazines will be a tracer bullet. 0 = off (JA2 normal)
	gGameExternalOptions.ubNumBulletsPerTracer				= __max(iniReader.ReadInteger("Tactical Gameplay Settings","NUM_BULLETS_PER_TRACER", 5, 1, 255),1);

	// HEADROCK HAM B2.5: Realistic tracers - CTH increased by this amount whenever a tracer is fired. 0 = off.
	gGameExternalOptions.ubCTHBumpPerTracer					= iniReader.ReadInteger("Tactical Gameplay Settings","CTH_BUMP_PER_TRACER", 30, 0, 100 );

	// CHRISL: Exeternalize the minimum range at which tracers can improve autofire hit chance
	gGameExternalOptions.ubMinRangeTracerEffect				= iniReader.ReadInteger("Tactical Gameplay Settings","MIN_RANGE_FOR_TRACER", 10);

	// HEADROCK HAM 3.5: Limit bonus from tracers based on range to target. This is a multiplier factor - higher means harder to aim with tracers.
	gGameExternalOptions.ubRangeDifficultyAimingWithTracers	= iniReader.ReadInteger("Tactical Gameplay Settings","RANGE_EFFECT_ON_MAX_TRACER_CTH_BONUS", 3, 1, 10);

	// HEADROCK HAM B2.6: Increased aiming costs?
	gGameExternalOptions.fIncreasedAimingCost				= iniReader.ReadBoolean("Tactical Gameplay Settings","INCREASE_AIMING_COSTS", FALSE);

	// CHRISL: Converts the AutoFireToHitBonus value to a percentage for CTH calculations
	gGameExternalOptions.ubFlatAFTHBtoPrecentMultiplier		= iniReader.ReadInteger("Tactical Gameplay Settings","AUTOFIRE_TOHIT_BONUS_MULTIPLIER", 0, 0, 10);

	// HEADROCK HAM 3.1: Divisor for the AP-to-Ready cost charge on first aiming click, when extra aiming costs are enabled. 0 = No ready-time-based charge.
	gGameExternalOptions.ubFirstAimReadyCostDivisor			= iniReader.ReadInteger("Tactical Gameplay Settings","FIRST_AIM_READY_COST_DIVISOR", 0, 0, 255);

	// SANDRO - moved this here from preferences and renamed to actually match its effect
	gGameExternalOptions.fAimLevelRestriction		= iniReader.ReadBoolean("Tactical Gameplay Settings","ALLOW_EXTRA_AIM_LEVELS", TRUE);

	// HEADROCK HAM B2.6: Dynamically determine Max-Aiming based also on weapon, bipod, etc?
	gGameExternalOptions.fDynamicAimingTime					= iniReader.ReadBoolean("Tactical Gameplay Settings","DYNAMIC_AIMING_LIMITS", FALSE);

	// allow old behaviour
	gGameExternalOptions.fAimLevelsDependOnDistance			= iniReader.ReadBoolean("Tactical Gameplay Settings", "AIM_LEVELS_DEPEND_ON_DISTANCE", TRUE);
	gGameExternalOptions.iAimLevelsCompatibilityOption		= iniReader.ReadInteger("Tactical Gameplay Settings", "AIM_LEVELS_COMPATIBILITY_OPTION", 0, -10000, 10000);

	//WarmSteel - These determine in which group each scope belongs. Needed for dynamic aiming limits.
	gGameExternalOptions.sVeryHighPowerScope				= iniReader.ReadInteger("Tactical Gameplay Settings","VERY_HIGH_POWER_SCOPE_AIM_THRESHOLD", 18, 0, 255);
	gGameExternalOptions.sHighPowerScope					= iniReader.ReadInteger("Tactical Gameplay Settings","HIGH_POWER_SCOPE_AIM_THRESHOLD", 13, 0, 255);
	gGameExternalOptions.sMediumPowerScope					= iniReader.ReadInteger("Tactical Gameplay Settings","MEDIUM_POWER_SCOPE_AIM_THRESHOLD", 8, 0, 255);

	//CHRISL: AI Sniper fields
	gGameExternalOptions.fAISniperElite						= iniReader.ReadBoolean("Tactical Gameplay Settings", "AI_SNIPER_RESTRICT_TO_ELITE", TRUE);
	gGameExternalOptions.fAISniperRange						= iniReader.ReadInteger("Tactical Gameplay Settings","AI_SNIPER_MIN_RANGE ", 40, 0, 1000);
	gGameExternalOptions.fAISniperChance					= iniReader.ReadInteger("Tactical Gameplay Settings","AI_SNIPER_CHANCE ", 30, 0, 100);
	gGameExternalOptions.fAISniperChanceWithSR				= iniReader.ReadInteger("Tactical Gameplay Settings","AI_SNIPER_CHANCE_WITH_SR ", 80, 0, 100);

	// HEADROCK HAM B2.6: Controls how much effect target movement has on aiming
	gGameExternalOptions.iMovementEffectOnAiming			= (float)iniReader.ReadDouble("Tactical Gameplay Settings","CTH_PENALTY_FOR_TARGET_MOVEMENT", 1.5, 0.0, 255.0);

	// HEADROCK HAM 3.3: Externalized maximum possible penalty for hitting a moving target. JA2 Default = 30.
	gGameExternalOptions.usMaxCTHPenaltyForMovingTarget		= iniReader.ReadInteger("Tactical Gameplay Settings","MAX_CTH_PENALTY_FOR_TARGET_MOVEMENT", 30, 0, 300);

	// HEADROCK HAM 3.2: Critical Headshots may cause blindness. Rolls 1 to X change of being blinded. 0 = disabled.
	gGameExternalOptions.ubChanceBlindedByHeadshot			= iniReader.ReadInteger("Tactical Gameplay Settings","CHANCE_BLINDED_BY_HEADSHOT", 0, 0, 100);

	// HEADROCK HAM 3.2: Critical Legshots cause additional AP loss
	gGameExternalOptions.fCriticalLegshotCausesAPLoss		= iniReader.ReadBoolean("Tactical Gameplay Settings","CRITICAL_LEGSHOT_CAUSES_AP_LOSS", FALSE);

	//legion by Jazz
	gGameExternalOptions.fCanJumpThroughWindows	 			= iniReader.ReadBoolean("Tactical Gameplay Settings","CAN_JUMP_THROUGH_WINDOWS", FALSE);
	gGameExternalOptions.fCanClimbOnWalls					= iniReader.ReadBoolean("Tactical Gameplay Settings","CAN_CLIMB_ON_WALLS", FALSE);
	
	//legion by Jazz
	gGameExternalOptions.fIndividualHiddenPersonNames		= iniReader.ReadBoolean("Tactical Gameplay Settings","INDIVIDUAL_HIDDEN_PERSON_NAMES", FALSE);

	//Enemy Names by Jazz
	gGameExternalOptions.fEnemyNames						= iniReader.ReadBoolean("Tactical Gameplay Settings","INDIVIDUAL_ENEMY_NAMES",FALSE);	
	
	//Civ Names by Jazz
	gGameExternalOptions.fCivGroupName						= iniReader.ReadBoolean("Tactical Gameplay Settings","INDIVIDUAL_CIVILIAN_NAMES",FALSE);		

	//Enemy Rank by Jazz
	gGameExternalOptions.fEnemyRank							= iniReader.ReadBoolean("Tactical Gameplay Settings","INDIVIDUAL_ENEMY_RANK",FALSE);

	// *** ddd - BEGIN
	gGameExternalOptions.fExtMouseKeyEnabled				= iniReader.ReadBoolean("Tactical Interface Settings", "ENABLE_EXT_MOUSE_KEYS", FALSE);

	// New setting to change stamina
	gGameExternalOptions.uStaminaHit						= iniReader.ReadInteger("Tactical Interface Settings", "STAMINA_HIT", 10000);
	
	// Alternative system for aiming - progressive method depending on marksmash of Merc
	gGameExternalOptions.bAltAimEnabled						= iniReader.ReadBoolean("Tactical Interface Settings","ALT_AIMING_ENABLED",FALSE);
	
	// Use aimed burst
	gGameExternalOptions.bAimedBurstEnabled				= iniReader.ReadBoolean("Tactical Interface Settings","USE_AIMED_BURST",FALSE);
			
	// Penalcy for aimed burst
	gGameExternalOptions.uAimedBurstPenalty				= iniReader.ReadInteger("Tactical Interface Settings","AIMING_BURST_PENALTY",2);
	
	// We could see all what can see militia
	gGameExternalOptions.bWeSeeWhatMilitiaSeesAndViceVersa = iniReader.ReadBoolean("Tactical Interface Settings","WE_SEE_WHAT_MILITIA_SEES_AND_VICE_VERSA",TRUE);
	
	// Gun supressor can deterioration
	gGameExternalOptions.bAllowWearSuppressor				= iniReader.ReadBoolean("Tactical Interface Settings","ALLOW_WEAR_SUPPRESSOR",FALSE);	
	
	// Civils don't make too much actions (for faster civils turn)
	gGameExternalOptions.bLazyCivilians						= iniReader.ReadBoolean("Tactical Interface Settings","ALLOW_LAZY_CIVILIANS",FALSE);	
	
	// Chance to Say Annoying Phrase (you can just turn of it by button in game)
	gGameExternalOptions.iChanceSayAnnoyingPhrase			= iniReader.ReadInteger("Tactical Interface Settings","CHANCE_SAY_ANNOYING_PHRASE",100);	
	 
	// New enemy AI for night battles
	gGameExternalOptions.bNewTacticalAIBehavior				= iniReader.ReadBoolean("Tactical Interface Settings","NEW_AI_TACTICAL",FALSE);	
	
	// Heahshot penalty
	gGameExternalOptions.uShotHeadPenalty					= iniReader.ReadFloat("Tactical Interface Settings","SHOT_HEAD_PENALTY",3,0,100);	
	
	// Modifer of damage for HEADSHOT
	gGameExternalOptions.fShotHeadDivisor					= iniReader.ReadFloat("Tactical Interface Settings","SHOT_HEAD_DIVISOR",1.5,1,10);	

	// Penalty for fire when you don't see enemy (when you see enemy because his see militya or ather merc)
	gGameExternalOptions.iPenaltyShootUnSeen				= iniReader.ReadInteger("Tactical Interface Settings","SHOOT_UNSEEN_PENALTY",0,0,255);		
	
	// CtH/2 if the target are out of gun range or invisible for this merc
	gGameExternalOptions.fOutOfGunRangeOrSight				= iniReader.ReadFloat("Tactical Interface Settings","OUT_OF_SIGHT_OR_GUN_RANGE",2,1,100);	
	// *** ddd - END

	// SANDRO - Improved camo applying and camo can be removed
	gGameExternalOptions.fCamoRemoving						= iniReader.ReadBoolean("Tactical Gameplay Settings", "CAMO_REMOVING", TRUE);

	// SANDRO - Enhanced close combat system
	gGameExternalOptions.fEnhancedCloseCombatSystem			= iniReader.ReadBoolean("Tactical Gameplay Settings", "ENHANCED_CLOSE_COMBAT_SYSTEM", TRUE);

	// SANDRO - give special Exp for completing quests
	gGameExternalOptions.usAwardSpecialExpForQuests			= iniReader.ReadInteger("Tactical Gameplay Settings", "AWARD_SPECIAL_EXP_POINTS_FOR_COMPLETING_QUESTS", 100, 0, 5000);

	//tais: soldiers always wear any armour..
	gGameExternalOptions.fSoldiersWearAnyArmour				= iniReader.ReadBoolean("Tactical Gameplay Settings", "SOLDIERS_ALWAYS_WEAR_ANY_ARMOR", FALSE);

	// improved Interrupt System (info: multiplayer game ALWAYS use the old interrupt system, because the new one causes crashes, no problem so far)
	gGameExternalOptions.fImprovedInterruptSystem			= iniReader.ReadBoolean("Tactical Gameplay Settings", "IMPROVED_INTERRUPT_SYSTEM", TRUE);
	gGameExternalOptions.ubBasicPercentRegisterValueIIS		= iniReader.ReadInteger("Tactical Gameplay Settings", "BASIC_PERCENTAGE_APS_REGISTERED", 60, 0, 250);
	gGameExternalOptions.ubPercentRegisterValuePerLevelIIS	= iniReader.ReadInteger("Tactical Gameplay Settings", "PERCENTAGE_APS_REGISTERED_PER_EXP_LEVEL", 4, 0, 100);
	gGameExternalOptions.ubBasicReactionTimeLengthIIS		= iniReader.ReadInteger("Tactical Gameplay Settings", "BASIC_REACTION_TIME_LENGTH", 25, 5, 100);
	gGameExternalOptions.fAllowCollectiveInterrupts			= iniReader.ReadBoolean("Tactical Gameplay Settings", "ALLOW_COLLECTIVE_INTERRUPTS", TRUE);
	gGameExternalOptions.fAllowInstantInterruptsOnSight		= iniReader.ReadBoolean("Tactical Gameplay Settings", "ALLOW_INSTANT_INTERRUPTS_ON_SPOTTING", FALSE);

	//################# Tactical Cover System Settings ##################

	// CPT: Cover System Settings
	gGameExternalOptions.ubStealthTraitCoverValue	= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_STEALTH_TRAIT_VALUE", 15, 0, 100);
	gGameExternalOptions.ubStealthEffectiveness		= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_STEALTH_EFFECTIVENESS", 50, 0, 100);
	gGameExternalOptions.ubCamouflageEffectiveness	= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_CAMOUFLAGE_EFFECTIVENESS", 50, 0, 100);
	gGameExternalOptions.ubStanceEffectiveness		= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_STANCE_EFFECTIVENESS", 10, 0, 100);
	gGameExternalOptions.ubLBEEffectiveness			= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_LBE_EFFECTIVENESS", 20, 0, 100);
	gGameExternalOptions.ubMovementEffectiveness	= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_MOVEMENT_EFFECTIVENESS", 20, 0, 100);
	gGameExternalOptions.ubTreeCoverEffectiveness	= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_TREE_EFFECTIVENESS", 20, 0, 100);
	gGameExternalOptions.ubCoverDisplayUpdateWait	= iniReader.ReadInteger("Tactical Cover System Settings", "COVER_SYSTEM_UPDATE_DELAY", 500, -1, 10000);

	//################# Tactical Suppression Fire Settings ##################
	// These settings control the behavior of Suppression Fire, its severity, and its side-effects.

	// HEADROCK HAM B2.1: This controls how effective suppression is, by increasing the number of ubSuppressionPoints accumulated by combatants (percentage);
	gGameExternalOptions.sSuppressionEffectiveness				= iniReader.ReadInteger("Tactical Suppression Fire Settings","SUPPRESSION_EFFECTIVENESS", 0, 0, 1000);

	// Min/max Suppression Tolerance values. Maximum system limit is 24!
	gGameExternalOptions.ubSuppressionToleranceMax				= iniReader.ReadInteger("Tactical Suppression Fire Settings","SUPPRESSION_TOLERANCE_MAX", 18, 1, 24);
	gGameExternalOptions.ubSuppressionToleranceMin				= iniReader.ReadInteger("Tactical Suppression Fire Settings","SUPPRESSION_TOLERANCE_MIN", 1, 0, 24);

	// HEADROCK HAM 3.2: This feature allows the status, leadership and experience of nearby friendlies help/hinder a character's tolerance, based on their distance from him.
	gGameExternalOptions.fFriendliesAffectTolerance				= iniReader.ReadBoolean("Tactical Suppression Fire Settings","NEARBY_FRIENDLIES_AFFECT_TOLERANCE", FALSE);

	// HEADROCK HAM 3.3: Increases tolerance while moving.
	gGameExternalOptions.ubTilesMovedPerBonusTolerancePoint		= iniReader.ReadInteger("Tactical Suppression Fire Settings","TILES_MOVED_PER_BONUS_TOLERANCE_POINT", 5, 0, 20);

	// HEADROCK HAM B2: Suppression Shock effectiveness (percentage, 100 = "normal", 0 = deactivated. Range 0-65535)
	gGameExternalOptions.usSuppressionShockEffect				= iniReader.ReadInteger("Tactical Suppression Fire Settings","SUPPRESSION_SHOCK_INTENSITY", 100, 0, 1000);

	// HEADROCK HAM B2.6: Adjustable maximum for Suppression Shock effect. This has the added effect of reducing overall susceptibility to shock and may render some enemies unshockable.
	gGameExternalOptions.ubMaxSuppressionShock					= iniReader.ReadInteger("Tactical Suppression Fire Settings","MAX_SUPPRESSION_SHOCK", 30, 0, 200 );

	// HEADROCK HAM B2.1: CTH penalty given by a "Cowering" target to any enemy shooter.
	gGameExternalOptions.ubAimPenaltyPerTargetShock				= iniReader.ReadInteger("Tactical Suppression Fire Settings","CTH_PENALTY_PER_TARGET_SHOCK", 5, 0, 100 );

	// HEADROCK HAM B2.8: Absolute maximum CTH penalty from target's shock value.
	gGameExternalOptions.usMaxShooterCoweringPenalty			= iniReader.ReadInteger("Tactical Suppression Fire Settings","MAX_CTH_PENALTY_FOR_TARGET_SHOCK", 0, 0, 250 );

	// HEADROCK HAM B2.8: These are new cowering penalty divisors that help us determine how effective cowering is in different stances and when the shooter is targetting different bodyparts
	gGameExternalOptions.ubCoweringPenaltyDivisorProne			= iniReader.ReadInteger("Tactical Suppression Fire Settings","CTH_PENALTY_DIVISOR_FOR_PRONE_SHOCKED_TARGET", 1, 1, 100 );
	gGameExternalOptions.ubCoweringPenaltyDivisorCrouchedHead	= iniReader.ReadInteger("Tactical Suppression Fire Settings","CTH_PENALTY_DIVISOR_FOR_CROUCHED_SHOCKED_TARGET_HEAD", 3, 1, 100);
	gGameExternalOptions.ubCoweringPenaltyDivisorCrouchedTorso	= iniReader.ReadInteger("Tactical Suppression Fire Settings","CTH_PENALTY_DIVISOR_FOR_CROUCHED_SHOCKED_TARGET_TORSO", 4, 1, 100);
	gGameExternalOptions.ubCoweringPenaltyDivisorCrouchedLegs	= iniReader.ReadInteger("Tactical Suppression Fire Settings","CTH_PENALTY_DIVISOR_FOR_CROUCHED_SHOCKED_TARGET_LEGS_DIVISOR", 5, 1, 100);

	// HEADROCK HAM B2.8: This is the maximum range at which a target gives out the full CTH penalty for cowering. At lower range, it'll give proportionally less penalty.
	gGameExternalOptions.usMinRangeForFullCoweringPenalty		= iniReader.ReadInteger("Tactical Suppression Fire Settings","MIN_RANGE_FOR_FULL_TARGET_SHOCK_PENALTY", 300, 10, 10000 );

	gGameExternalOptions.usMaxTargetCoweringPenalty				= iniReader.ReadInteger("Tactical Suppression Fire Settings","MAX_CTH_PENALTY_FROM_SHOCK", 0, 0, 250 );

	// HEADROCK HAM 3.2: This enabled reduced sight for cowering characters. 0 = disabled. 2 = Reduced Sightrange. 3 = Tunnel-vision. 1 = Both.
	gGameExternalOptions.ubCoweringReducesSightRange			= iniReader.ReadInteger("Tactical Suppression Fire Settings","SHOCK_REDUCES_SIGHTRANGE", 0, 0, 3); 

	// HEADROCK HAM B2.3: A "cowering" soldier is twice as susceptible to suppression.
	gGameExternalOptions.ubCowerEffectOnSuppression				= iniReader.ReadInteger("Tactical Suppression Fire Settings","COWERING_PENALTY_TO_SUPPRESSION_TOLERANCE", 4, 0, 24 );

	// CHRISL: Changed from a simple flag to two externalized values for more modder control over AI suppression
	gGameExternalOptions.ubAISuppressionMinimumMagSize			= iniReader.ReadInteger("Tactical Suppression Fire Settings","AI_SUPPRESS_MIN_MAG_SIZE", 30, 0, 1000);
	gGameExternalOptions.ubAISuppressionMinimumAmmo				= iniReader.ReadInteger("Tactical Suppression Fire Settings","AI_SUPPRESS_MIN_AMMO_REMAINING", 20, 0, 1000);

	// HEADROCK HAM 3.5: Explosive Suppression Effectiveness alters the amount of Suppression Points you get from nearby blasts.
	gGameExternalOptions.usExplosionSuppressionEffect			= iniReader.ReadInteger("Tactical Suppression Fire Settings","EXPLOSIVE_SUPPRESSION_EFFECTIVENESS", 100, 0, 1000);

	// HEADROCK HAM 3.1: This is a suppression tool that not everyone will like. It gives an on-screen message when any character has been suppressed so much he's lost his next turn completely!
	gGameExternalOptions.fShowSuppressionShutdown				= iniReader.ReadBoolean("Tactical Suppression Fire Settings","NOTIFY_WHEN_PINNED_DOWN", FALSE);

	// HEADROCK HAM 3.3: Minimum distance (in METERS) at which character suffer from friendly suppression.
	gGameExternalOptions.usMinDistanceFriendlySuppression		= iniReader.ReadInteger("Tactical Suppression Fire Settings","MIN_DISTANCE_FRIENDLY_SUPPRESSION", 30, 0, 65000);


	//################# Tactical Weather Settings ##################

	gGameExternalOptions.ubVisDistDecreasePerRainIntensity				= iniReader.ReadInteger("Tactical Weather Settings","VISUAL_DISTANCE_DECREASE_PER_RAIN_INTENSITY",30, 0, 100);

	// Rain settings
	gGameExternalOptions.gfAllowRain									= iniReader.ReadBoolean("Tactical Weather Settings","ALLOW_RAIN",0);
	gGameExternalOptions.gusRainChancePerDay							= iniReader.ReadInteger("Tactical Weather Settings","RAIN_CHANCE_PER_DAY",100, 0, 100);
	gGameExternalOptions.gusRainMinLength								= iniReader.ReadInteger("Tactical Weather Settings","RAIN_MIN_LENGTH_IN_MINUTES",60, 1, 1438 /* 24 hrs - 2 minutes */);
	gGameExternalOptions.gusRainMaxLength								= iniReader.ReadInteger("Tactical Weather Settings","RAIN_MAX_LENGTH_IN_MINUTES",300, gGameExternalOptions.gusRainMinLength+1, 1439);
	gGameExternalOptions.guiMaxRainDrops								= iniReader.ReadInteger("Tactical Weather Settings","MAX_RAIN_DROPS",80, 1, 800);
	gGameExternalOptions.ubWeaponReliabilityReductionPerRainIntensity	= iniReader.ReadInteger("Tactical Weather Settings","WEAPON_RELIABILITY_REDUCTION_PER_RAIN_INTENSITY",0, 0, 10);
	gGameExternalOptions.ubBreathGainReductionPerRainIntensity			= iniReader.ReadDouble("Tactical Weather Settings","BREATH_GAIN_REDUCTION_PER_RAIN_INTENSITY",25, 1, 100);

	// Thunder settings
	gGameExternalOptions.gfAllowLightning								= iniReader.ReadBoolean("Tactical Weather Settings","ALLOW_LIGHTNING",TRUE);
	gGameExternalOptions.guiMinLightningInterval						= iniReader.ReadInteger("Tactical Weather Settings","MIN_INTERVAL_BETWEEN_LIGHTNINGS_IN_REAL_TIME_SECONDS",5, 1, 100);
	gGameExternalOptions.guiMaxLightningInterval						= iniReader.ReadInteger("Tactical Weather Settings","MAX_INTERVAL_BETWEEN_LIGHTNINGS_IN_REAL_TIME_SECONDS",15, 2, 600);
	gGameExternalOptions.guiMinDLInterval								= iniReader.ReadInteger("Tactical Weather Settings","MIN_INTERVAL_BETWEEN_LIGHTNING_AND_THUNDERCLAPS_IN_SECONDS",1, 1, 100);
	gGameExternalOptions.guiMaxDLInterval								= iniReader.ReadInteger("Tactical Weather Settings","MAX_INTERVAL_BETWEEN_LIGHTNING_AND_THUNDERCLAPS_IN_SECONDS",5, 2, 600);
	gGameExternalOptions.guiProlongLightningIfSeenSomeone				= iniReader.ReadInteger("Tactical Weather Settings","DELAY_IN_SECONDS_IF_SEEN_SOMEONE_DURING_LIGHTNING_IN_TURNBASED",5, 1, 60);
	gGameExternalOptions.guiChanceToDoLightningBetweenTurns				= iniReader.ReadInteger("Tactical Weather Settings","CHANCE_TO_DO_LIGHTNING_BETWEEN_TURNS",35, 0, 100);




	//################# Strategic Gamestart Settings ##################

	//Lalien: Game starting time
	gGameExternalOptions.iGameStartingTime			= iniReader.ReadInteger("Strategic Gamestart Settings", "GAME_STARTING_TIME", NUM_SEC_IN_HOUR, 0, NUM_SEC_IN_DAY-1);
	gGameExternalOptions.iGameStartingTime += NUM_SEC_IN_DAY;
	
	gGameExternalOptions.iFirstArrivalDelay			= iniReader.ReadInteger("Strategic Gamestart Settings", "FIRST_ARRIVAL_DELAY", 6 * NUM_SEC_IN_HOUR, 0, NUM_SEC_IN_DAY);

	// HEADROCK HAM 3.5: Arrival sectorX/Y.
	gGameExternalOptions.ubDefaultArrivalSectorX	= iniReader.ReadInteger("Strategic Gamestart Settings","DEFAULT_ARRIVAL_SECTOR_X", 9, 1, 16);
	gGameExternalOptions.ubDefaultArrivalSectorY	= iniReader.ReadInteger("Strategic Gamestart Settings","DEFAULT_ARRIVAL_SECTOR_Y", 1, 1, 16);


	//################# Strategic Interface Settings ##################

	// CHRISL: Setting to turn off the description and stack popup options from the sector inventory panel
	gGameExternalOptions.fSectorDesc							= iniReader.ReadBoolean("Strategic Interface Settings","ALLOW_DESCRIPTION_BOX_FOR_ITEMS_IN_SECTOR_INVENTORY",TRUE);

	// HEADROCK HAM 3.6: Progress bars for each stat, displayed behind the stat value on the merc panel. INI settings give RGB color, Menu setting toggles on/off.
	gGameExternalOptions.ubStatProgressBarsRed					= iniReader.ReadInteger("Strategic Interface Settings","STAT_PROGRESS_BARS_RED", 200, 0, 255);
	gGameExternalOptions.ubStatProgressBarsGreen				= iniReader.ReadInteger("Strategic Interface Settings","STAT_PROGRESS_BARS_GREEN", 0, 0, 255);
	gGameExternalOptions.ubStatProgressBarsBlue					= iniReader.ReadInteger("Strategic Interface Settings","STAT_PROGRESS_BARS_BLUE", 0, 0, 255);

	// HEADROCK HAM 3.6: Determines whether the extrapolated daily costs of mercs are figured into the "Daily Expenses" display. 0 = No, just facility costs. 1 = Only mercs with a fixed daily rate. 2 = All mercs, including AIM contracts.
	gGameExternalOptions.ubIncludeContractsInExpenses			= iniReader.ReadInteger("Strategic Interface Settings","INCLUDE_CONTRACTS_IN_PROJECTED_EXPENSES_WINDOW", 1, 0, 2);


	//################# Strategic Progress Settings ##################

	// WDS: Game progress 
	gGameExternalOptions.ubGameProgressPortionKills				= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MAX_POINTS_FROM_KILLS", 25, 0, 100);
	gGameExternalOptions.ubGameProgressPortionControl			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MAX_POINTS_FROM_SECTOR_CONTROL", 25, 0, 100);
	gGameExternalOptions.ubGameProgressPortionIncome			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MAX_POINTS_FROM_MINE_INCOME", 50, 0, 100);
	gGameExternalOptions.ubGameProgressPortionVisited			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MAX_POINTS_FROM_EXPLORED_SECTORS", 0, 0, 100);

	// Any way to warn on this?
	if (gGameExternalOptions.ubGameProgressPortionKills + 
		gGameExternalOptions.ubGameProgressPortionControl + 
		gGameExternalOptions.ubGameProgressPortionIncome + 
		gGameExternalOptions.ubGameProgressPortionVisited != 100) 
	{
		gGameExternalOptions.ubGameProgressPortionKills		= 25;
		gGameExternalOptions.ubGameProgressPortionControl	= 25;
		gGameExternalOptions.ubGameProgressPortionIncome	= 50;
		gGameExternalOptions.ubGameProgressPortionVisited	= 0;

		// Yes, there is!
		std::stringstream errMessage;
		errMessage << "The values of the four ''MAX_PROGRESS_POINTS'' INI settings do not add up to 100! Using default values instead...";
		iniErrorMessages.push(errMessage.str());
	}

	// HEADROCK HAM 3: If enabled, changes the way the game calculates progress. It will look at each progress control separately (Kills/Income/Control/Visited) and set the progress to the HIGHEST scoring control.
	gGameExternalOptions.fAlternateProgressCalculation			= iniReader.ReadBoolean("Strategic Progress Settings","ALTERNATE_PROGRESS_CALCULATION", FALSE);

	// Minimum progress value.
	gGameExternalOptions.ubGameProgressMinimum					= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MINIMUM", 0, 0, 100);
	// Flat modifier to Current Progress.
	gGameExternalOptions.bGameProgressModifier					= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MODIFIER", 0, -100, 100);

	// HEADROCK HAM 3: Four INI settings to control the number of kills you must accumulate to win one progress point, one setting per difficulty level
	gGameExternalOptions.usNumKillsPerProgressPointNovice		= iniReader.ReadInteger("Strategic Progress Settings","NUM_KILLS_PER_PROGRESS_POINT_NOVICE", 7, 1, 1000);
	gGameExternalOptions.usNumKillsPerProgressPointExperienced	= iniReader.ReadInteger("Strategic Progress Settings","NUM_KILLS_PER_PROGRESS_POINT_EXPERIENCED", 10, 1, 1000);
	gGameExternalOptions.usNumKillsPerProgressPointExpert		= iniReader.ReadInteger("Strategic Progress Settings","NUM_KILLS_PER_PROGRESS_POINT_EXPERT", 15, 1, 1000);
	gGameExternalOptions.usNumKillsPerProgressPointInsane		= iniReader.ReadInteger("Strategic Progress Settings","NUM_KILLS_PER_PROGRESS_POINT_INSANE", 60, 1, 1000);

	//Global game events 
	gGameExternalOptions.ubGameProgressStartMadlabQuest			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_START_MADLAB_QUEST",35, 0, 100);
	gGameExternalOptions.ubGameProgressMikeAvailable			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_MIKE_AVAILABLE",50, 0, 100);
	gGameExternalOptions.ubGameProgressIggyAvaliable			= iniReader.ReadInteger("Strategic Progress Settings","GAME_PROGRESS_IGGY_AVAILABLE",70, 0, 100);


	//################# Strategic Event Settings ##################

	// Drassen counterattack
	gGameExternalOptions.ubSendTroopsToDrassen			= iniReader.ReadBoolean("Strategic Event Settings","TRIGGER_MASSIVE_ENEMY_COUNTERATTACK_AT_DRASSEN",TRUE);

	// Enable/Disable crepitus completely in SCI-FI mode.
	gGameExternalOptions.fEnableCrepitus				= iniReader.ReadBoolean("Strategic Event Settings", "ENABLE_CREPITUS", TRUE);

	// HEADROCK HAM 3.1: Select which mine will run out. 0 = no mine. 1 = San Mona (unused), 2 = Drassen, 3 = Alma, 4 = Cambria, 5 = Chitzena, 6 = Grumm.
	gGameExternalOptions.bWhichMineRunsOut				= iniReader.ReadInteger("Strategic Event Settings","WHICH_MINE_SHUTS_DOWN", -1, -1, 256);


	//################# Strategic Gameplay Settings ##################

	// Allow enemy and militia Strategic Groups to reinforce one another for battles?
	gGameExternalOptions.gfAllowReinforcements				= iniReader.ReadBoolean("Strategic Gameplay Settings","ALLOW_REINFORCEMENTS",FALSE);
	// Allow reinforcements only between City sectors?
	gGameExternalOptions.gfAllowReinforcementsOnlyInCity	= iniReader.ReadBoolean("Strategic Gameplay Settings","ALLOW_REINFORCEMENTS_ONLY_IN_CITIES",FALSE);

	// SANDRO - moved into the game start screen
	//gGameExternalOptions.fEnableAllTerrorists				= iniReader.ReadBoolean("Strategic Gameplay Settings", "ENABLE_ALL_TERRORISTS", FALSE);
	//gGameExternalOptions.fEnableAllWeaponCaches				= iniReader.ReadBoolean("Strategic Gameplay Settings", "ENABLE_ALL_WEAPON_CACHES", FALSE);

	// Kaiden: Vehicle Inventory change - Added INI file Option VEHICLE_INVENTORY
	gGameExternalOptions.fVehicleInventory					= iniReader.ReadBoolean("Strategic Gameplay Settings", "VEHICLE_INVENTORY", TRUE);

	// HEADROCK HAM 3.1: Can the Humvee go off-road?
	gGameExternalOptions.fHumveeOffroad						= iniReader.ReadBoolean("Strategic Gameplay Settings","HUMVEE_OFFROAD", FALSE);

	// HEADROCK HAM B2.6/B1: Adjustable "luck" factor in Auto-Resolve
	gGameExternalOptions.iAutoResolveLuckFactor				= (float)(__max(iniReader.ReadDouble("Strategic Gameplay Settings","AUTORESOLVE_LUCK_FACTOR", 2.0, 0.0, 255.0),1.0));

	// HEADROCK HAM 3.2: When enabled, this setting removes the player's omniscience inside his own sectors. The player will no longer see the movement of enemy groups unless someone is nearby to scout them.
	gGameExternalOptions.fNoEnemyDetectionWithoutRecon		= iniReader.ReadBoolean("Strategic Gameplay Settings","NO_ENEMY_DETECTION_WITHOUT_RECON", FALSE);

	// HEADROCK HAM 3.6: Determines how likely a character is, every hour, to trigger a facility event. The actual chance is X in every Y attempts, where X is facility-specific, and Y is the value adjusted here.
	gGameExternalOptions.usFacilityEventRarity				= iniReader.ReadInteger("Strategic Gameplay Settings","FACILITY_EVENT_RARITY", 1000, 0, 50000);
	// HEADROCK HAM 3.6: Controls how important the character's stats are, in insuring he/she gets better results (or smaller damage) from using facilities. The higher this is, the more dangerous all facilities are.
	gGameExternalOptions.ubFacilityDangerRate				= iniReader.ReadInteger("Strategic Gameplay Settings","FACILITY_DANGER_RATE", 50, 0, 100);

	// 2Points: Use new repair algorithm (Items are priorized based on type and damage to item, starting from equipped weapons, going to armor, then inventory)
	gGameExternalOptions.fAdditionalRepairMode				= iniReader.ReadBoolean("Strategic Gameplay Settings", "ADDITIONAL_REPAIR_MODE", FALSE);	

	// CHRISL: Determine how Skyrider should handle landing in enemy occupied sectors
	gGameExternalOptions.ubSkyriderHotLZ					= iniReader.ReadInteger("Strategic Gameplay Settings", "ALLOW_SKYRIDER_HOT_LZ", 0);


	//################# Laptop Settings ##################

	gGameExternalOptions.gBriefingRoom						= iniReader.ReadBoolean("Laptop Settings", "BRIEFING_ROOM", FALSE);
	gGameExternalOptions.gEncyclopedia						= iniReader.ReadBoolean("Laptop Settings", "ENCYCLOPEDIA", FALSE);


	//################# Bobby Ray Settings ##################


	// HEADROCK HAM 3: If enabled, tooltipping over Bobby Ray's weapons will show a list of possible attachments to those weapons.
	gGameExternalOptions.fBobbyRayTooltipsShowAttachments	= iniReader.ReadBoolean("Bobby Ray Settings","BOBBY_RAY_TOOLTIPS_SHOW_POSSIBLE_ATTACHMENTS", FALSE);

	// WDS - Option to turn off stealing
	gGameExternalOptions.fStealingDisabled					= iniReader.ReadBoolean("Bobby Ray Settings","STEALING_FROM_SHIPMENTS_DISABLED",FALSE);

	// WANNE - Chance of shipment lost
	gGameExternalOptions.gubChanceOfShipmentLost			= iniReader.ReadInteger("Bobby Ray Settings","CHANCE_OF_SHIPMENT_LOSS", 10);


	//################# Item Property Settings ##################

	//Weapons modification
	gGameExternalOptions.iExplosivesDamageModifier			= iniReader.ReadInteger("Item Property Settings","EXPLOSIVES_DAMAGE_MODIFIER",100, 0, 1000);
	gGameExternalOptions.iMeleeDamageModifier				= iniReader.ReadInteger("Item Property Settings","MELEE_DAMAGE_MODIFIER",100, 0, 1000);
	gGameExternalOptions.iGunDamageModifier					= iniReader.ReadInteger("Item Property Settings","GUN_DAMAGE_MODIFIER",100, 0, 1000);
	gGameExternalOptions.iGunRangeModifier					= iniReader.ReadInteger("Item Property Settings","GUN_RANGE_MODIFIER",100, 0, 1000);

	// Enables the "Coverage" value of armor items.
	gGameExternalOptions.fEnableArmorCoverage				= iniReader.ReadBoolean("Item Property Settings", "ENABLE_ARMOR_COVERAGE", FALSE); // ShadoWarrior for Captain J's armor coverage
	
	gGameExternalOptions.fAmmoDynamicWeight					= iniReader.ReadBoolean("Item Property Settings", "DYNAMIC_AMMO_WEIGHT", TRUE); //Pulmu

	// HEADROCK HAM B2.6: Autofire Bullets/5AP modifier
	gGameExternalOptions.bAutofireBulletsPer5APModifier		= iniReader.ReadInteger("Item Property Settings","AUTOFIRE_BULLETS_PER_5AP_MODIFIER", 0, -100, 100 );

	// HEADROCK HAM 3: Externalized ratio between Weight and Strength. This value determines how many strength points we need to lift 0.5kg with no encumberance.
	gGameExternalOptions.iStrengthToLiftHalfKilo			= (float)iniReader.ReadDouble("Item Property Settings","STRENGTH_TO_LIFT_HALF_KILO", 1.0, 0.1, 100.0);

	// HEADROCK HAM 3.2: Set a divisor for the CtH of Mortar weapons.
	gGameExternalOptions.ubMortarCTHDivisor					= iniReader.ReadInteger("Item Property Settings","MORTAR_CTH_DIVISOR", 1, 1, 255);

	// WarmSteel: NAS
	gGameExternalOptions.fUseDefaultSlots					= iniReader.ReadBoolean("Item Property Settings","USE_DEFAULT_SLOTS_WHEN_MISSING",FALSE);
	gGameExternalOptions.usAttachmentDropRate				= iniReader.ReadInteger("Item Property Settings","ATTACHMENT_DROP_RATE",10, 0, 100);
	gGameExternalOptions.iMaxEnemyAttachments				= iniReader.ReadInteger("Item Property Settings","MAX_ENEMY_ATTACHMENTS",6, 2, MAX_ATTACHMENTS);

	//################# Strategic Enemy AI Settings ##################

	// WDS - New AI
	gGameExternalOptions.useNewAI							= iniReader.ReadBoolean("Strategic Enemy AI Settings","NEW_AGGRESSIVE_AI",FALSE);

	gGameExternalOptions.iForcePercentageNovice				= iniReader.ReadInteger("Strategic Enemy AI Settings","INITIAL_GARRISON_PERCENTAGES_NOVICE",70, 1, 200);
	gGameExternalOptions.iForcePercentageExperienced		= iniReader.ReadInteger("Strategic Enemy AI Settings","INITIAL_GARRISON_PERCENTAGES_EXPERIENCED",100, 1, 300);
	gGameExternalOptions.iForcePercentageExpert				= iniReader.ReadInteger("Strategic Enemy AI Settings","INITIAL_GARRISON_PERCENTAGES_EXPERT",150, 1, 400);
	gGameExternalOptions.iForcePercentageInsane				= iniReader.ReadInteger("Strategic Enemy AI Settings","INITIAL_GARRISON_PERCENTAGES_INSANE",200, 1, 600);

	gGameExternalOptions.ubMinEnemyGroupSizeNovice			= (UINT8) iniReader.ReadInteger("Strategic Enemy AI Settings","MIN_ENEMY_GROUP_SIZE_NOVICE",3, 1, CODE_MAXIMUM_NUMBER_OF_ENEMIES);
	gGameExternalOptions.ubMinEnemyGroupSizeExperienced		= (UINT8) iniReader.ReadInteger("Strategic Enemy AI Settings","MIN_ENEMY_GROUP_SIZE_EXPERIENCED",4, 1, CODE_MAXIMUM_NUMBER_OF_ENEMIES);
	gGameExternalOptions.ubMinEnemyGroupSizeExpert			= (UINT8) iniReader.ReadInteger("Strategic Enemy AI Settings","MIN_ENEMY_GROUP_SIZE_EXPERT",6, 1, CODE_MAXIMUM_NUMBER_OF_ENEMIES);
	gGameExternalOptions.ubMinEnemyGroupSizeInsane			= (UINT8) iniReader.ReadInteger("Strategic Enemy AI Settings","MIN_ENEMY_GROUP_SIZE_INSANE",12, 1, CODE_MAXIMUM_NUMBER_OF_ENEMIES);

	gGameExternalOptions.iPercentElitesBonusExperienced		= iniReader.ReadInteger("Strategic Enemy AI Settings","PERCENT_EXTRA_ELITES_EXPERIENCED",0, 0, 100);
	gGameExternalOptions.iPercentElitesBonusExpert			= iniReader.ReadInteger("Strategic Enemy AI Settings","PERCENT_EXTRA_ELITES_EXPERT",25, 0, 100);
	gGameExternalOptions.iPercentElitesBonusInsane			= iniReader.ReadInteger("Strategic Enemy AI Settings","PERCENT_EXTRA_ELITES_INSANE",50, 0, 100);

	gGameExternalOptions.gfEasyUnlimitedTroops				= iniReader.ReadBoolean("Strategic Enemy AI Settings","UNLIMITED_POOL_OF_TROOPS_NOVICE",FALSE);
	gGameExternalOptions.gfNormalUnlimitedTroops			= iniReader.ReadBoolean("Strategic Enemy AI Settings","UNLIMITED_POOL_OF_TROOPS_EXPERIENCED",FALSE);
	gGameExternalOptions.gfHardUnlimitedTroops				= iniReader.ReadBoolean("Strategic Enemy AI Settings","UNLIMITED_POOL_OF_TROOPS_EXPERT",FALSE);
	gGameExternalOptions.gfInsaneUnlimitedTroops			= iniReader.ReadBoolean("Strategic Enemy AI Settings","UNLIMITED_POOL_OF_TROOPS_INSANE",TRUE);

	gGameExternalOptions.iReinforcementPoolNovice			= iniReader.ReadInteger("Strategic Enemy AI Settings","QUEENS_INITIAL_POOL_OF_TROOPS_NOVICE",150, 25, 1000000);
	gGameExternalOptions.iReinforcementPoolExperienced		= iniReader.ReadInteger("Strategic Enemy AI Settings","QUEENS_INITIAL_POOL_OF_TROOPS_EXPERIENCED",200, 25, 1000000);
	gGameExternalOptions.iReinforcementPoolExpert			= iniReader.ReadInteger("Strategic Enemy AI Settings","QUEENS_INITIAL_POOL_OF_TROOPS_EXPERT",400, 25, 1000000);
	gGameExternalOptions.iReinforcementPoolInsane			= iniReader.ReadInteger("Strategic Enemy AI Settings","QUEENS_INITIAL_POOL_OF_TROOPS_INSANE",8000, 25, 1000000);

	gGameExternalOptions.guiBaseQueenPoolIncrement			= iniReader.ReadInteger("Strategic Enemy AI Settings","QUEEN_POOL_INCREMENT_PER_DIFFICULTY_LEVEL",60, 1, 100);

	gGameExternalOptions.ubEasyEnemyStartingAlertLevel		= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_STARTING_ALERT_LEVEL_NOVICE", 5, 1, 100);
	gGameExternalOptions.ubNormalEnemyStartingAlertLevel	= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_STARTING_ALERT_LEVEL_EXPERIENCED", 20, 1, 100);
	gGameExternalOptions.ubHardEnemyStartingAlertLevel		= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_STARTING_ALERT_LEVEL_EXPERT", 60, 1, 100);
	gGameExternalOptions.ubInsaneEnemyStartingAlertLevel	= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_STARTING_ALERT_LEVEL_INSANE", 80, 1, 100);

	gGameExternalOptions.ubEasyEnemyStartingAlertDecay		= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_ALERT_DECAY_NOVICE", 75, 1, 100);
	gGameExternalOptions.ubNormalEnemyStartingAlertDecay	= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_ALERT_DECAY_EXPERIENCED", 50, 1, 100);
	gGameExternalOptions.ubHardEnemyStartingAlertDecay		= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_ALERT_DECAY_EXPERT", 25, 1, 100);
	gGameExternalOptions.ubInsaneEnemyStartingAlertDecay	= iniReader.ReadInteger("Strategic Enemy AI Settings","ENEMY_ALERT_DECAY_INSANE", 10, 1, 100);

	gGameExternalOptions.ubEasyNumAwareBattles				= iniReader.ReadInteger("Strategic Enemy AI Settings","NUM_AWARE_BATTLES_NOVICE", 1, 1, 10);
	gGameExternalOptions.ubNormalNumAwareBattles			= iniReader.ReadInteger("Strategic Enemy AI Settings","NUM_AWARE_BATTLES_EXPERIENCED", 2, 1, 10);
	gGameExternalOptions.ubHardNumAwareBattles				= iniReader.ReadInteger("Strategic Enemy AI Settings","NUM_AWARE_BATTLES_EXPERT", 3, 1, 10);
	gGameExternalOptions.ubInsaneNumAwareBattles			= iniReader.ReadInteger("Strategic Enemy AI Settings","NUM_AWARE_BATTLES_INSANE", 4, 1, 10);

	gGameExternalOptions.ubEasyTimeEvaluateInMinutes		= iniReader.ReadInteger("Strategic Enemy AI Settings","BASE_DELAY_IN_MINUTES_BETWEEN_EVALUATIONS_NOVICE", 480, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubNormalTimeEvaluateInMinutes		= iniReader.ReadInteger("Strategic Enemy AI Settings","BASE_DELAY_IN_MINUTES_BETWEEN_EVALUATIONS_EXPERIENCED", 360, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubHardTimeEvaluateInMinutes		= iniReader.ReadInteger("Strategic Enemy AI Settings","BASE_DELAY_IN_MINUTES_BETWEEN_EVALUATIONS_EXPERT", 180, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubInsaneTimeEvaluateInMinutes		= iniReader.ReadInteger("Strategic Enemy AI Settings","BASE_DELAY_IN_MINUTES_BETWEEN_EVALUATIONS_INSANE", 90, 10, NUM_MIN_IN_DAY);

	gGameExternalOptions.ubEasyTimeEvaluateVariance			= iniReader.ReadInteger("Strategic Enemy AI Settings","EVALUATION_DELAY_VARIANCE_NOVICE", 240, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubNormalTimeEvaluateVariance		= iniReader.ReadInteger("Strategic Enemy AI Settings","EXPERIENCED_TIME_EVALUATE_VARIANCE", 180, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubHardTimeEvaluateVariance			= iniReader.ReadInteger("Strategic Enemy AI Settings","EXPERT_TIME_EVALUATE_VARIANCE", 120, 10, NUM_MIN_IN_DAY);
	gGameExternalOptions.ubInsaneTimeEvaluateVariance		= iniReader.ReadInteger("Strategic Enemy AI Settings","INSANE_TIME_EVALUATE_VARIANCE", 60, 10, NUM_MIN_IN_DAY);

	gGameExternalOptions.ubEasyGracePeriodInHours			= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_HOURS_AFTER_SECTOR_LIBERATION_NOVICE", 144, 1, 288);
	gGameExternalOptions.ubNormalGracePeriodInHours			= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_HOURS_AFTER_SECTOR_LIBERATION_EXPERIENCED", 96, 1, 288);
	gGameExternalOptions.ubHardGracePeriodInHours			= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_HOURS_AFTER_SECTOR_LIBERATION_EXPERT", 48, 1, 288);
	gGameExternalOptions.ubInsaneGracePeriodInHours			= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_HOURS_AFTER_SECTOR_LIBERATION_INSANE", 6, 1, 288);

	gGameExternalOptions.ubEasyPatrolGracePeriodInDays		= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_DAYS_AFTER_PATROL_DESTROYED_NOVICE", 16, 1, 100);
	gGameExternalOptions.ubNormalPatrolGracePeriodInDays	= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_DAYS_AFTER_PATROL_DESTROYED_EXPERIENCED", 12, 1, 100);
	gGameExternalOptions.ubHardPatrolGracePeriodInDays		= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_DAYS_AFTER_PATROL_DESTROYED_EXPERT", 8, 1, 100);
	gGameExternalOptions.ubInsanePatrolGracePeriodInDays	= iniReader.ReadInteger("Strategic Enemy AI Settings","GRACE_PERIOD_IN_DAYS_AFTER_PATROL_DESTROYED_INSANE", 2, 1, 100);

	gGameExternalOptions.gfEasyAggressiveQueen				= iniReader.ReadBoolean("Strategic Enemy AI Settings","AGGRESSIVE_QUEEN_AI_NOVICE",FALSE);
	gGameExternalOptions.gfNormalAggressiveQueen			= iniReader.ReadBoolean("Strategic Enemy AI Settings","AGGRESSIVE_QUEEN_AI_EXPERIENCED",FALSE);
	gGameExternalOptions.gfHardAggressiveQueen				= iniReader.ReadBoolean("Strategic Enemy AI Settings","AGGRESSIVE_QUEEN_AI_EXPERT",FALSE);
	gGameExternalOptions.gfInsaneAggressiveQueen			= iniReader.ReadBoolean("Strategic Enemy AI Settings","AGGRESSIVE_QUEEN_AI_INSANE",TRUE);

	gGameExternalOptions.gfInvestigateSector				= iniReader.ReadBoolean("Strategic Enemy AI Settings","ENEMY_INVESTIGATE_SECTOR",FALSE);
	gGameExternalOptions.gfReassignPendingReinforcements	= iniReader.ReadBoolean("Strategic Enemy AI Settings","REASSIGN_PENDING_REINFORCEMENTS",TRUE);

	
	//################# Militia Training Settings ##################

	gGameExternalOptions.iMaxMilitiaPerSector				= iniReader.ReadInteger("Militia Training Settings","MAX_MILITIA_PER_SECTOR",20, 1, CODE_MAXIMUM_NUMBER_OF_REBELS);

	gGameExternalOptions.iTrainingSquadSize					= iniReader.ReadInteger("Militia Training Settings","NUM_MILITIA_TRAINED_PER_SESSION",10, 1, CODE_MAXIMUM_NUMBER_OF_REBELS);

	gGameExternalOptions.iMinLoyaltyToTrain					= iniReader.ReadInteger("Militia Training Settings","MIN_LOYALTY_TO_TRAIN_MILITIA",20, 0, 100);

	gGameExternalOptions.ubTownMilitiaTrainingRate			= iniReader.ReadInteger("Militia Training Settings","MILITIA_TRAINING_RATE",4, 1, 10);

	gGameExternalOptions.gfTrainVeteranMilitia				= iniReader.ReadBoolean("Militia Training Settings","ALLOW_TRAINING_ELITE_MILITIA",FALSE);
	gGameExternalOptions.guiTrainVeteranMilitiaDelay		= iniReader.ReadInteger("Militia Training Settings","ELITE_MILITIA_TRAINING_DELAY",1, 0, 30);

	gGameExternalOptions.ubRpcBonusToTrainMilitia			= iniReader.ReadInteger("Militia Training Settings","RPC_BONUS_TO_MILITIA_TRAINING_RATE",10, 0, 100);

	// HEADROCK HAM 3: Define minimum leadership required for training militia. Set to 0 for "no limit".
	gGameExternalOptions.ubMinimumLeadershipToTrainMilitia	= iniReader.ReadInteger("Militia Training Settings","MINIMUM_LEADERSHIP_TO_TRAIN_MILITIA", 0, 0, 99);

	// HEADROCK HAM 3: If enabled, the trainer's "effective" leadership skill determines HOW MANY militia he/she creates per session.
	gGameExternalOptions.fLeadershipAffectsMilitiaQuantity	= iniReader.ReadBoolean("Militia Training Settings","LEADERSHIP_AFFECTS_MILITIA_QUANTITY", FALSE);

	// HEADROCK HAM 3: If "LEADERSHIP_AFFECTS_MILITIA_QUANTITY" is true, this value determines the lowest leadership required to train a full (default size 10) squad of town militia in one training session.
	gGameExternalOptions.ubReqLeadershipForFullTraining		= iniReader.ReadInteger("Militia Training Settings","REQ_LEADERSHIP_FOR_MAX_MILITIA", 100, 1, 100);

	// HEADROCK HAM 3: Define effect of "TEACHER" trait in increasing effective leadership, for purposes of eligibility for training militia. This is a percentage value. HAM Default would be 200 = double effective leadership for each TEACHING level.
	gGameExternalOptions.usTeacherTraitEffectOnLeadership	= iniReader.ReadInteger("Militia Training Settings","TEACHER_TRAIT_EFFECT_ON_LEADERSHIP", 100, 1, 10000);


	//################# Mobile Militia Training Settings ##################

	gGameExternalOptions.gfAllowMilitiaGroups						= iniReader.ReadBoolean("Mobile Militia Training Settings","ALLOW_MOBILE_MILITIA",FALSE);
	gGameExternalOptions.guiAllowMilitiaGroupsDelay					= iniReader.ReadInteger("Mobile Militia Training Settings","MOBILE_MILITIA_TRAINING_DELAY",1, 0, 30);

	gGameExternalOptions.guiNumMobileMilitiaTrained					= iniReader.ReadInteger("Mobile Militia Training Settings","NUM_MOBILE_MILITIA_TRAINED_PER_SESSION",4, 1, 100);

	gGameExternalOptions.gfmusttrainroaming							= iniReader.ReadBoolean("Mobile Militia Training Settings","MUST_TRAIN_MOBILE_MILITIA",FALSE);

	gGameExternalOptions.guiCreateEachNHours						= iniReader.ReadInteger("Mobile Militia Training Settings","CREATE_MOBILE_MILITIA_SQUAD_EACH_N_HOURS",24, 1, 96);

	// HEADROCK HAM 3.3: New militia feature, Minimum Leadership required to train Roaming Militia
	gGameExternalOptions.ubMinimumLeadershipToTrainMobileMilitia	= iniReader.ReadInteger("Mobile Militia Training Settings","MIN_LEADERSHIP_TO_TRAIN_MOBILE_MILITIA", 0, 0, 100);

	// HEADROCK HAM 3.3: If enabled, the trainer's "effective" leadership skill determines HOW MANY Mobile Militia he/she creates per session.
	gGameExternalOptions.fLeadershipAffectsMobileMilitiaQuantity	= iniReader.ReadBoolean("Mobile Militia Training Settings","LEADERSHIP_AFFECTS_MOBILE_MILITIA_QUANTITY", FALSE);

	// HEADROCK HAM 3.3: If "LEADERSHIP_AFFECTS_MILITIA_QUANTITY" is true, this value determines the lowest leadership required to train a full (default size 5) squad of Mobile Militia in one training session.
	gGameExternalOptions.ubReqLeadershipForFullMobileTraining		= iniReader.ReadInteger("Mobile Militia Training Settings","REQ_LEADERSHIP_FOR_MAX_MOBILE_MILITIA", 1, 1, 100);

	// HEADROCK HAM 3.5: Does leadership affect the Quality of new Mobile Militia groups?
	gGameExternalOptions.fLeadershipAffectsMobileMilitiaQuality		= iniReader.ReadBoolean("Mobile Militia Training Settings","LEADERSHIP_AFFECTS_MOBILE_MILITIA_QUALITY", FALSE);

	// HEADROCK HAM 3.4: What percentage of a new Mobile Militia group will be made of Elites? If >0, then at least one of every new group will be an Elite. 100 = All Elites.
	gGameExternalOptions.ubPercentRoamingMilitiaElites				= iniReader.ReadInteger("Mobile Militia Training Settings","PERCENT_MOBILE_MILITIA_ELITES", 100, 0, 100);

	// HEADROCK HAM 3.4: What percentage of a new Mobile Militia group will be made of Regulars? If >0, then at least one of every new group will be a Regular. 100 = All Regulars.
	gGameExternalOptions.ubPercentRoamingMilitiaRegulars			= iniReader.ReadInteger("Mobile Militia Training Settings","PERCENT_MOBILE_MILITIA_REGULARS", 0, 0, 100);


	//################# Mobile Militia Movement Settings ##################

	gGameExternalOptions.gflimitedRoaming						= iniReader.ReadBoolean("Mobile Militia Movement Settings","RESTRICT_ROAMING",FALSE);

	// HEADROCK HAM B1: Allow restricted militia to move through visited sectors?
	gGameExternalOptions.fUnrestrictVisited						= iniReader.ReadBoolean("Mobile Militia Movement Settings","ALLOW_MILITIA_MOVEMENT_THROUGH_EXPLORED_SECTORS", FALSE);

	// HEADROCK HAM B1: Allow dynamic restrictions?
	gGameExternalOptions.fDynamicRestrictRoaming				= iniReader.ReadBoolean("Mobile Militia Movement Settings","ALLOW_DYNAMIC_RESTRICTED_ROAMING", TRUE);

	// HEADROCK HAM B2.7: Augmented Roaming Militia code - turn this to TRUE to allow militia free travel through San Mona, Tixa, Orta, Omerta, and Estoni.
	gGameExternalOptions.fAllowMilitiaMoveThroughMinorCities	= iniReader.ReadBoolean("Mobile Militia Movement Settings","ALLOW_MILITIA_MOVEMENT_THROUGH_MINOR_CITIES", FALSE);	

	// HEADROCK HAM 3.3: If enabled, Roaming Militia can automatically reinforce city garrisons. 
	gGameExternalOptions.fAllowMobileReinforceCities			= iniReader.ReadBoolean("Mobile Militia Movement Settings","ALLOW_MOBILE_MILITIA_REINFORCE_TOWN_GARRISONS", FALSE);

	// HEADROCK HAM 3.3: If enabled, Roaming Militia can automatically reinforce city garrisons. 
	gGameExternalOptions.fAllowMobileReinforceSAM				= iniReader.ReadBoolean("Mobile Militia Movement Settings","ALLOW_MOBILE_MILITIA_REINFORCE_SAM_GARRISONS", FALSE);

	
	// SANDRO - added several bonuses for militia 
	//################# Militia Strength Settings ##################

	// These applies for autoresolve only
	gGameExternalOptions.sGreenMilitiaAutoresolveStrength	 = iniReader.ReadInteger("Militia Strength Settings", "GREEN_MILITIA_AUTORESOLVE_STRENGTH_BONUS", 0, -100, 500);
	gGameExternalOptions.sRegularMilitiaAutoresolveStrength = iniReader.ReadInteger("Militia Strength Settings", "REGULAR_MILITIA_AUTORESOLVE_STRENGTH_BONUS", 0, -100, 500);
	gGameExternalOptions.sVeteranMilitiaAutoresolveStrength = iniReader.ReadInteger("Militia Strength Settings", "VETERAN_MILITIA_AUTORESOLVE_STRENGTH_BONUS", 10, -100, 500);

	// Flat bonus to militia APs - applies during tactical combat only
	gGameExternalOptions.bGreenMilitiaAPsBonus	 = iniReader.ReadInteger("Militia Strength Settings", "GREEN_MILITIA_APS_BONUS", 0, -75, 75);
	gGameExternalOptions.bRegularMilitiaAPsBonus = iniReader.ReadInteger("Militia Strength Settings", "REGULAR_MILITIA_APS_BONUS", 0, -75, 75);
	gGameExternalOptions.bVeteranMilitiaAPsBonus = iniReader.ReadInteger("Militia Strength Settings", "VETERAN_MILITIA_APS_BONUS", 5, -75, 75);

	// Percentage bonus to total militia CtH on every hit - applies during tactical combat only
	gGameExternalOptions.sGreenMilitiaCtHBonusPercent	 = iniReader.ReadInteger("Militia Strength Settings", "GREEN_MILITIA_CTH_BONUS_PERCENT", 0, -100, 500);
	gGameExternalOptions.sRegularMilitiaCtHBonusPercent = iniReader.ReadInteger("Militia Strength Settings", "REGULAR_MILITIA_CTH_BONUS_PERCENT", 0, -100, 500);
	gGameExternalOptions.sVeteranMilitiaCtHBonusPercent = iniReader.ReadInteger("Militia Strength Settings", "VETERAN_MILITIA_CTH_BONUS_PERCENT", 10, -100, 500);

	// Damage the militia suffer is reduced by this percentage - applies during tactical combat only
	gGameExternalOptions.bGreenMilitiaDamageResistance	 = iniReader.ReadInteger("Militia Strength Settings", "GREEN_MILITIA_DAMAGE_RESISTANCE", 0, -50, 95);
	gGameExternalOptions.bRegularMilitiaDamageResistance = iniReader.ReadInteger("Militia Strength Settings", "REGULAR_MILITIA_DAMAGE_RESISTANCE", 0, -50, 95);
	gGameExternalOptions.bVeteranMilitiaDamageResistance = iniReader.ReadInteger("Militia Strength Settings", "VETERAN_MILITIA_DAMAGE_RESISTANCE", 0, -50, 95);

	// Modifier increasing militia equipment quality on creation - applies during tactical combat only
	gGameExternalOptions.bGreenMilitiaEquipmentQualityModifier	 = iniReader.ReadInteger("Militia Strength Settings", "GREEN_MILITIA_EQUIPMENT_QUALITY_MODIFIER", 0, -5, 10);
	gGameExternalOptions.bRegularMilitiaEquipmentQualityModifier = iniReader.ReadInteger("Militia Strength Settings", "REGULAR_MILITIA_EQUIPMENT_QUALITY_MODIFIER", 0, -5, 10);
	gGameExternalOptions.bVeteranMilitiaEquipmentQualityModifier = iniReader.ReadInteger("Militia Strength Settings", "VETERAN_MILITIA_EQUIPMENT_QUALITY_MODIFIER", 1, -5, 10);


	//################# Shopkeeper Inventory Settings ##################

	// WDS - Improve Tony's and Devin's inventory like BR's
	gGameExternalOptions.tonyUsesBRSetting		= iniReader.ReadBoolean("Shopkeeper Inventory Settings","TONY_USES_BOBBY_RAYS_SETTING", FALSE);
	gGameExternalOptions.devinUsesBRSetting		= iniReader.ReadBoolean("Shopkeeper Inventory Settings","DEVIN_USES_BOBBY_RAYS_SETTING", FALSE);

	// chance that Tony will be in his office - silversurfer/SANDRO
	gGameExternalOptions.ubChanceTonyAvailable		= iniReader.ReadInteger("Shopkeeper Inventory Settings","CHANCE_TONY_AVAILABLE", 80, 0, 100);

	//################# Strategic Assignment Settings ##################

	////////// ALL ASSIGNMENTS //////////

	gGameExternalOptions.ubMinutesForAssignmentToCount		= iniReader.ReadInteger("Strategic Assignment Settings","MINUTES_FOR_ASSIGNMENT_TO_COUNT",45, 1, NUM_MIN_IN_DAY);

	////////// PRACTICE/TRAIN/STUDY //////////

	gGameExternalOptions.ubTrainingSkillMin					= iniReader.ReadInteger("Strategic Assignment Settings","MIN_REQUIRED_SKILL_TO_BEGIN_TRAINING",0, 0, 100);
	gGameExternalOptions.ubTrainingSkillMax					= iniReader.ReadInteger("Strategic Assignment Settings","MAX_SKILL_ACHIEVABLE_BY_TRAINING",100, 0, 100);
	gGameExternalOptions.ubSelfTrainingDivisor				= iniReader.ReadInteger("Strategic Assignment Settings","TRAINING_RATE_DIVISOR",1000, 1, 10000);
	gGameExternalOptions.ubInstructedTrainingDivisor		= iniReader.ReadInteger("Strategic Assignment Settings","INSTRUCTED_TRAINING_DIVISOR",3000, 1, 10000);

	gGameExternalOptions.ubTeachBonusToTrain				= iniReader.ReadInteger("Strategic Assignment Settings","TEACHER_TRAIT_BONUS_TO_TRAINING_EFFICIENCY",30, 0, 100);
	gGameExternalOptions.ubMinSkillToTeach					= iniReader.ReadInteger("Strategic Assignment Settings","MIN_SKILL_REQUIRED_TO_TEACH_OTHER",25, 0, 100);

	// HEADROCK HAM B2.8: New Trainer Relations: 2 = Trainees will go to sleep when their trainer goes to sleep. 3 = Trainer will go to sleep if all trainees are asleep. 1 = Both. 0 = Neither.
	gGameExternalOptions.ubSmartTrainingSleep				= iniReader.ReadInteger("Strategic Assignment Settings","SYNCHRONIZED_SLEEPING_HOURS_WHEN_TRAINING_TOGETHER", 0, 0, 3);

	// HEADROCK HAM B2.8: New Trainer Relations: 2 = Trainees will wake up when their trainer wakes up. 3 = Trainer will wake up if all trainees wake up. 1 = Both. 0 = Neither.
	gGameExternalOptions.ubSmartTrainingWake				= iniReader.ReadInteger("Strategic Assignment Settings","SYNCHRONIZED_WAKING_HOURS_WHEN_TRAINING_TOGETHER", 0, 0, 3);

	// HEADROCK HAM B2.8: New Trainer Relations: 2 = Trainers will rest if no trainees available. 3 = Trainees will rest if no trainers available (not recommended). 1 = Both. 0 = Neither.
	gGameExternalOptions.ubSmartTrainingRest				= iniReader.ReadInteger("Strategic Assignment Settings","REST_IF_NO_TRAINING_PARTNER_AVAILABLE", 0, 0, 3);

	////////// DOCTOR //////////

	gGameExternalOptions.ubLowActivityLevel					= iniReader.ReadInteger("Strategic Assignment Settings","NATURAL_HEALING_SPEED_DIVISOR_AT_LOW_ACTIVITY_LEVEL",1, 1, 100);
	gGameExternalOptions.ubMediumActivityLevel				= iniReader.ReadInteger("Strategic Assignment Settings","NATURAL_HEALING_SPEED_DIVISOR_AT_MEDIUM_ACTIVITY_LEVEL",4, 1, 100);
	gGameExternalOptions.ubHighActivityLevel				= iniReader.ReadInteger("Strategic Assignment Settings","NATURAL_HEALING_SPEED_DIVISOR_AT_HIGH_ACTIVITY_LEVEL",12, 1, 100);

	gGameExternalOptions.ubDoctoringRateDivisor				= iniReader.ReadInteger("Strategic Assignment Settings","DOCTORING_RATE_DIVISOR",2400, 1200, 24000);
	gGameExternalOptions.ubHospitalHealingRate				= iniReader.ReadInteger("Strategic Assignment Settings","HOSPITAL_HEALING_RATE",5, 1, 12);
	gGameExternalOptions.ubBaseMedicalSkillToDealWithEmergency				= iniReader.ReadInteger("Strategic Assignment Settings","BASE_MEDICAL_SKILL_TO_DEAL_WITH_EMERGENCY",20, 0, 100);
	gGameExternalOptions.ubMultiplierForDifferenceInLifeValueForEmergency	= iniReader.ReadInteger("Strategic Assignment Settings","MULTIPLIER_FOR_DIFFERENCE_IN_LIFE_VALUE_FOR_EMERGENCY",4, 1, 10);
	gGameExternalOptions.ubPointCostPerHealthBelowOkLife	= iniReader.ReadInteger("Strategic Assignment Settings","POINT_COST_PER_HEALTH_BELOW_OKLIFE",2, 1, 5);//OKLIFE = 15

	////////// REPAIR //////////

	gGameExternalOptions.ubRepairCostPerJam					= iniReader.ReadInteger("Strategic Assignment Settings","REPAIR_POINT_COST_TO_FIX_WEAPON_JAM",2, 1, 10);
	gGameExternalOptions.ubRepairRateDivisor				= iniReader.ReadInteger("Strategic Assignment Settings","REPAIR_RATE_DIVISOR",2500, 500, 25000);
	gGameExternalOptions.ubAssignmentUnitsPerDay			= iniReader.ReadInteger("Strategic Assignment Settings","REPAIR_SESSIONS_PER_DAY",24, 1, 96);
	
	//SaveGame slot by Jazz		
	// WANNE: No need to make it external to switch between old/new. We always use the new save/load screen with more save slots
	//gGameExternalOptions.fSaveGameSlot					= iniReader.ReadBoolean("Extension","SAVE_GAMES_SLOT",FALSE);
	gGameExternalOptions.fSaveGameSlot						= TRUE;				

	
	// WANNE: This is just a debug setting. Only in debug version we set that property to TRUE.
	// In Release version this should always be set to FALSE
	// dnl ch51 081009 JA2 Debug Settings
#ifdef _DEBUG
	gGameExternalOptions.fEnableInventoryPoolQ				= TRUE;
#else
	gGameExternalOptions.fEnableInventoryPoolQ = FALSE;
#endif		
}


// SANDRO - externalization of all skill trait values and STOMP settings into separate file
void LoadSkillTraitsExternalSettings()
{
	CIniReader iniReader(STOMP_SETTINGS_FILE);

	gSkillTraitValues.ubMaxNumberOfTraits = iniReader.ReadInteger("Generic Traits Settings","MAX_NUMBER_OF_TRAITS", 3, 2, 30);
	gSkillTraitValues.ubNumberOfMajorTraitsAllowed = iniReader.ReadInteger("Generic Traits Settings","NUMBER_OF_MAJOR_TRAITS_ALLOWED", 2, 2, 20);

	// GENERIC SETTINGS
	gSkillTraitValues.bCtHModifierAssaultRifles = iniReader.ReadInteger("Generic Traits Settings","ASSAULT_RIFLES_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierSniperRifles = iniReader.ReadInteger("Generic Traits Settings","SNIPER_RIFLES_CTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCtHModifierRifles = iniReader.ReadInteger("Generic Traits Settings","RIFLES_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierSMGs = iniReader.ReadInteger("Generic Traits Settings","SMGS_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierLMGs = iniReader.ReadInteger("Generic Traits Settings","LMGS_CTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCtHModifierShotguns = iniReader.ReadInteger("Generic Traits Settings","SHOTGUNS_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierPistols = iniReader.ReadInteger("Generic Traits Settings","PISTOLS_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierMachinePistols = iniReader.ReadInteger("Generic Traits Settings","MACHINE_PISTOLS_CTH_MODIFIER", -5, -100, 100);
	gSkillTraitValues.bCtHModifierRocketLaunchers = iniReader.ReadInteger("Generic Traits Settings","ROCKET_LAUNCHERS_CTH_MODIFIER", -25, -100, 100);
	gSkillTraitValues.bCtHModifierGrenadeLaunchers = iniReader.ReadInteger("Generic Traits Settings","GRENADE_LAUNCHERS_CTH_MODIFIER", -25, -100, 100);
	gSkillTraitValues.sCtHModifierMortar = iniReader.ReadInteger("Generic Traits Settings","MORTAR_CTH_MODIFIER", -60, -500, 500);
	gSkillTraitValues.bCtHModifierThrowingKnives = iniReader.ReadInteger("Generic Traits Settings","THROWING_KNIVES_CTH_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCtHModifierThrowingGrenades = iniReader.ReadInteger("Generic Traits Settings","THROWING_GRENADES_CTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCtHModifierHtHAttack = iniReader.ReadInteger("Generic Traits Settings","HTH_ATTACK_CTH_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bModifierDodgeHtHChance = iniReader.ReadInteger("Generic Traits Settings","CHANCE_TO_DODGE_HTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCtHModifierKnifeAttack = iniReader.ReadInteger("Generic Traits Settings","KNIFE_ATTACK_CTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bModifierDodgeKnifeChance = iniReader.ReadInteger("Generic Traits Settings","CHANCE_TO_DODGE_KNIFE_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCtHModifierRobot = iniReader.ReadInteger("Generic Traits Settings","ROBOT_CTH_MODIFIER", -10, -100, 100);
	gSkillTraitValues.ubCtHPenaltyDualShot = iniReader.ReadInteger("Generic Traits Settings","DUAL_SHOT_CTH_PENALTY", 25, 0, 100);
	gSkillTraitValues.bPercentModifierHtHBreathLoss = iniReader.ReadInteger("Generic Traits Settings","PERCENT_BREATH_LOSS_ON_HTH_ATTACK_MODIFIER", -25, -100, 100);
	gSkillTraitValues.bPercentModifierBladesBreathLoss = iniReader.ReadInteger("Generic Traits Settings","PERCENT_BREATH_LOSS_ON_KNIFE_ATTACK_MODIFIER", -25, -100, 100);
	gSkillTraitValues.bPercentModifierBluntBreathLoss = iniReader.ReadInteger("Generic Traits Settings","PERCENT_BREATH_LOSS_ON_BLUNT_MELEE_ATTACK_MODIFIER", -40, -100, 100);
	gSkillTraitValues.ubModifierForAPsAddedOnAimedPunches = iniReader.ReadInteger("Generic Traits Settings","MODIFIER_FOR_APS_ADDED_ON_AIMED_HTH_ATTACKS", 3, 1, 10);
	gSkillTraitValues.ubModifierForAPsAddedOnAimedBladedAttackes = iniReader.ReadInteger("Generic Traits Settings","MODIFIER_FOR_APS_ADDED_ON_AIMED_BLADE_ATTACKS", 3, 1, 10);
	gSkillTraitValues.bSpeedModifierDoctoring = iniReader.ReadInteger("Generic Traits Settings","DOCTORING_SPEED_MODIFIER", -40, -100, 100);
	gSkillTraitValues.bSpeedModifierBandaging = iniReader.ReadInteger("Generic Traits Settings","BANDAGING_SPEED_MODIFIER", -30, -100, 100);
	gSkillTraitValues.bSpeedModifierRepairing = iniReader.ReadInteger("Generic Traits Settings","REPAIRING_SPEED_MODIFIER", -20, -100, 100);
	gSkillTraitValues.bSpeedModifierTrainingMilitia = iniReader.ReadInteger("Generic Traits Settings","TRAIN_MILITIA_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bSpeedModifierTeachingOthers = iniReader.ReadInteger("Generic Traits Settings","TEACHING_OTHERS_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCheckModifierLockpicking = iniReader.ReadInteger("Generic Traits Settings","LOCKPICKING_CHECK_MODIFIER", -10, -100, 100);
	gSkillTraitValues.bCheckModifierAttachDetonators = iniReader.ReadInteger("Generic Traits Settings","ATTACHING_DETONATORS_CHECK_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCheckModifierSetExplosives = iniReader.ReadInteger("Generic Traits Settings","SET_EXPLOSIVES_CHECK_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCheckModifierDisarmExplosiveTraps = iniReader.ReadInteger("Generic Traits Settings","DISARM_EXPLOSIVE_TRAPS_CHECK_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCheckModifierDisarmElectronicTraps = iniReader.ReadInteger("Generic Traits Settings","DISARM_ELECTRONIC_TRAPS_CHECK_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bCheckModifierAttachSpecialItems = iniReader.ReadInteger("Generic Traits Settings","ATTACH_SPECIAL_ITEMS_CHECK_MODIFIER", -15, -100, 100);
	gSkillTraitValues.bTanksDamageResistanceModifier = iniReader.ReadInteger("Generic Traits Settings","TANKS_DAMAGE_RESISTANCE_MODIFIER", 40, -100, 95);
	gSkillTraitValues.ubDamageNeededToLoseStats = iniReader.ReadInteger("Generic Traits Settings","DAMAGE_NEEDED_TO_LOSE_STATS", 15, 0, 100);

	// AUTO WEAPONS
	gSkillTraitValues.ubAWBonusCtHAssaultRifles = iniReader.ReadInteger("Auto Weapons","BONUS_CTH_ASSAULT_RIFLES", 5, 0, 100);
	gSkillTraitValues.ubAWBonusCtHSMGs = iniReader.ReadInteger("Auto Weapons","BONUS_CTH_SMGS", 5, 0, 100);
	gSkillTraitValues.ubAWBonusCtHLMGs = iniReader.ReadInteger("Auto Weapons","BONUS_CTH_LMGS", 5, 0, 100);
	gSkillTraitValues.ubAWAutoFirePenaltyReduction = iniReader.ReadInteger("Auto Weapons","AUTOFIRE_PENALTY_REDUCTION", 40, 0, 100);
	gSkillTraitValues.ubAWUnwantedBulletsReduction = iniReader.ReadInteger("Auto Weapons","UNWANTED_BULLETS_REDUCTION", 4, 0, 40);
	gSkillTraitValues.ubAWFiringSpeedBonusLMGs = iniReader.ReadInteger("Auto Weapons","FIRING_SPEED_BONUS_LMGS", 10, 0, 45);
	gSkillTraitValues.ubAWPercentReadyLMGReduction = iniReader.ReadInteger("Auto Weapons","PERCENT_AP_READY_LMG_REDUCTION", 10, 0, 45);

	// HEAVY WEAPONS
	gSkillTraitValues.ubHWGrenadeLaunchersAPsReduction = iniReader.ReadInteger("Heavy Weapons","GRENADE_LAUNCHERS_FIRE_AP_REDUCTION", 20, 0, 45);
	gSkillTraitValues.ubHWRocketLaunchersAPsReduction = iniReader.ReadInteger("Heavy Weapons","ROCKET_LAUNCHERS_FIRE_AP_REDUCTION", 20, 0, 45);
	gSkillTraitValues.ubHWBonusCtHGrenadeLaunchers = iniReader.ReadInteger("Heavy Weapons","BONUS_CTH_GRENADE_LAUNCHERS", 25, 0, 100);
	gSkillTraitValues.ubHWBonusCtHRocketLaunchers = iniReader.ReadInteger("Heavy Weapons","BONUS_CTH_ROCKET_LAUNCHERS", 25, 0, 100);
	gSkillTraitValues.ubHWMortarAPsReduction = iniReader.ReadInteger("Heavy Weapons","MORTAR_FIRE_AP_REDUCTION", 10, 0, 45);
	gSkillTraitValues.ubHWMortarCtHPenaltyReduction = iniReader.ReadInteger("Heavy Weapons","MORTAR_CTH_PENALTY_REDUCTION", 50, 0, 100);
	gSkillTraitValues.ubHWDamageTanksBonusPercent = iniReader.ReadInteger("Heavy Weapons","DAMAGE_TO_TANKS_PERCENT_BONUS", 30, 0, 200);
	gSkillTraitValues.ubHWDamageBonusPercentForHW = iniReader.ReadInteger("Heavy Weapons","HW_DAMAGE_PERCENT_BONUS", 15, 0, 100);

	// SNIPER
	gSkillTraitValues.ubSNBonusCtHRifles = iniReader.ReadInteger("Sniper","BONUS_CTH_RIFLES", 5, 0, 100);
	gSkillTraitValues.ubSNBonusCtHSniperRifles = iniReader.ReadInteger("Sniper","BONUS_CTH_SNIPER_RIFLES", 10, 0, 100);
	gSkillTraitValues.ubSNEffRangeToTargetReduction = iniReader.ReadInteger("Sniper","EFFECTIVE_RANGE_TO_TARGET_REDUCTION", 5, 0, 45);
	gSkillTraitValues.ubSNAimingBonusPerClick = iniReader.ReadInteger("Sniper","AIMING_BONUS_PER_CLICK_RIFLES", 10, 0, 50);
	gSkillTraitValues.ubSNDamageBonusPerClick = iniReader.ReadInteger("Sniper","GUN_DAMAGE_BONUS_PER_CLICK", 5, 0, 50);
	gSkillTraitValues.ubSNDamageBonusFromNumClicks = iniReader.ReadInteger("Sniper","GUN_DAMAGE_BONUS_FROM_NUM_CLICKS", 4, 0, 8);
	gSkillTraitValues.ubSNChamberRoundAPsReduction = iniReader.ReadInteger("Sniper","CHAMBER_ROUND_APS_REDUCTION", 25, 0, 45);
	gSkillTraitValues.ubSNAimClicksAdded = iniReader.ReadInteger("Sniper","POSSIBLE_AIM_CLICK_ADDED_RIFLES", 1, 0, 3);

	// RANGER
	gSkillTraitValues.ubRABonusCtHRifles = iniReader.ReadInteger("Ranger","BONUS_CTH_RIFLES", 5, 0, 100);
	gSkillTraitValues.ubRABonusCtHShotguns = iniReader.ReadInteger("Ranger","BONUS_CTH_SHOTGUNS", 10, 0, 100);
	gSkillTraitValues.ubRAPumpShotgunsAPsReduction = iniReader.ReadInteger("Ranger","PUMP_SHOTGUNS_APS_REDUCTION", 25, 0, 45);
	gSkillTraitValues.ubRAGroupTimeSpentForTravellingFoot = iniReader.ReadInteger("Ranger","GROUP_TIME_SPENT_FOR_TRAVELLING_BY_FOOT_REDUCTION", 20, 0, 100);
	gSkillTraitValues.ubRAGroupTimeSpentForTravellingVehicle = iniReader.ReadInteger("Ranger","GROUP_TIME_SPENT_FOR_TRAVELLING_IN_VEHICLE_REDUCTION", 10, 0, 100);
	gSkillTraitValues.ubRAMaxBonusesToTravelSpeed = iniReader.ReadInteger("Ranger","MAX_STACKABLE_LESS_TRAVEL_TIME_BONUSES", 2, 0, 20);
	gSkillTraitValues.ubRABreathForTravellingReduction = iniReader.ReadInteger("Ranger","ENERGY_SPENT_TRAVEL_REDUCTION", 30, 0, 100);
	gSkillTraitValues.ubRAWeatherPenaltiesReduction = iniReader.ReadInteger("Ranger","WEATHER_PENALTIES_REDUCTION", 50, 0, 100);
	//gSkillTraitValues.ubRACamoEffectivenessBonus = iniReader.ReadInteger("Ranger","CAMO_EFFECTIVENESS_BONUS_PERCENT", 10, 0, 100);
	gSkillTraitValues.ubRACamoWornountSpeedReduction = iniReader.ReadInteger("Ranger","CAMO_WORNOUT_SPEED_REDUCTION", 50, 0, 100);

	// GUNSLINGER
	gSkillTraitValues.ubGSFiringSpeedBonusPistols = iniReader.ReadInteger("Gunslinger","FIRING_SPEED_BONUS_PISTOLS", 15, 0, 45);
	gSkillTraitValues.ubGSEffectiveRangeBonusPistols = iniReader.ReadInteger("Gunslinger","FEFFECTIVE_RANGE_BONUS_PISTOLS", 10, 0, 100);
	gSkillTraitValues.ubGSBonusCtHPistols = iniReader.ReadInteger("Gunslinger","BONUS_CTH_PISTOLS", 10, 0, 100);
	gSkillTraitValues.ubGSBonusCtHMachinePistols = iniReader.ReadInteger("Gunslinger","BONUS_CTH_MACHINE_PISTOLS", 5, 0, 100);
	gSkillTraitValues.ubGSCtHMPExcludeAuto = iniReader.ReadBoolean("Gunslinger","CTH_MP_EXCLUDE_AUTOFIRE", TRUE);
	gSkillTraitValues.ubGSAimingBonusPerClick = iniReader.ReadInteger("Gunslinger","AIMING_BONUS_PER_CLICK_HANDGUNS", 5, 0, 100);
	gSkillTraitValues.ubGSPercentReadyPistolsReduction = iniReader.ReadInteger("Gunslinger","PERCENT_AP_READY_PISTOLS_REDUCTION", 15, 0, 50);
	gSkillTraitValues.ubGSRealoadSpeedHandgunsBonus = iniReader.ReadInteger("Gunslinger","RELOAD_SPEED_HANDGUNS_BONUS", 25, 0, 45);
	gSkillTraitValues.ubGSAimClicksAdded = iniReader.ReadInteger("Gunslinger","POSSIBLE_AIM_CLICK_ADDED_HANDGUNS", 1, 0, 3);

	// MARTIAL ARTS
	gSkillTraitValues.ubMAPunchAPsReduction = iniReader.ReadInteger("Martial Arts","PUNCH_APS_REDUCTION", 15, 0, 50);
	gSkillTraitValues.ubMABonusCtHBareHands = iniReader.ReadInteger("Martial Arts","BONUS_CTH_BARE_HANDS", 30, 0, 100);	
	gSkillTraitValues.ubMABonusCtHBrassKnuckles = iniReader.ReadInteger("Martial Arts","BONUS_CTH_KNUCKLES", 25, 0, 100);
	gSkillTraitValues.ubMABonusDamageHandToHand = iniReader.ReadInteger("Martial Arts","BONUS_HTH_DAMAGE", 30, 0, 250);
	gSkillTraitValues.ubMABonusBreathDamageHandToHand = iniReader.ReadInteger("Martial Arts","BONUS_HTH_BREATH_DAMAGE", 30, 0, 250);
	gSkillTraitValues.usMALostBreathRegainPenalty = iniReader.ReadInteger("Martial Arts","LOST_BREATH_REGAIN_PENALTY", 50, 0, 10000);
	gSkillTraitValues.usMAAimedPunchDamageBonus = iniReader.ReadInteger("Martial Arts","AIMED_PUNCH_DAMAGE_BONUS", 75, 0, 3000);
	gSkillTraitValues.bMAAimedPunchCtHModifier = iniReader.ReadInteger("Martial Arts","AIMED_PUNCH_CTH_MODIFIER", 0, -100, 100);
	gSkillTraitValues.ubMAChanceToDodgeHtH = iniReader.ReadInteger("Martial Arts","BONUS_CHANCE_TO_DODGE_HTH", 35, 0, 250);
	gSkillTraitValues.ubMAOnTopCTDHtHBareHanded = iniReader.ReadInteger("Martial Arts","ONTOP_BONUS_CTD_HTH_WITH_BARE_HANDS", 5, 0, 250);
	gSkillTraitValues.ubMAOnTopCTDHtHBrassKnuckles = iniReader.ReadInteger("Martial Arts","ONTOP_BONUS_CTD_HTH_WITH_KNUCKLES", 0, 0, 250);
	gSkillTraitValues.ubMAChanceToDodgeMelee = iniReader.ReadInteger("Martial Arts","BONUS_CHANCE_TO_DODGE_MELEE", 20, 0, 250);
	gSkillTraitValues.ubMAReducedAPsToSteal = iniReader.ReadInteger("Martial Arts","APS_TO_STEAL_WEAPON_REDUCTION", 25, 0, 50);
	gSkillTraitValues.ubMAAPsChangeStanceReduction = iniReader.ReadInteger("Martial Arts","APS_CHANGE_STANCE_REDUCTION", 25, 0, 100);
	gSkillTraitValues.ubMAApsTurnAroundReduction = iniReader.ReadInteger("Martial Arts","APS_TURN_AROUND_REDUCTION", 25, 0, 100);
	gSkillTraitValues.ubMAAPsClimbOrJumpReduction = iniReader.ReadInteger("Martial Arts","APS_CLIMB_OR_JUMP_REDUCTION", 25, 0, 100);
	gSkillTraitValues.ubMAChanceToCkickDoors = iniReader.ReadInteger("Martial Arts","CHANCE_KICK_DOORS_BONUS", 25, 0, 250);
	gSkillTraitValues.fPermitExtraAnimationsOnlyToMA = iniReader.ReadBoolean("Martial Arts","PERMIT_EXTRA_ANIMATIONS_TO_EXPERT_MARTIAL_ARTS_ONLY", TRUE);

	// SQUADLEADER
	gSkillTraitValues.usSLRadiusNormal = iniReader.ReadInteger("Squadleader","BONUSES_RADIUS_NORMAL", 10, 2, 1000);
	gSkillTraitValues.usSLRadiusExtendedEar = iniReader.ReadInteger("Squadleader","BONUSES_RADIUS_EXTENDED_EAR", 20, 2, 1000);
	if( gSkillTraitValues.usSLRadiusExtendedEar < gSkillTraitValues.usSLRadiusNormal ) { gSkillTraitValues.usSLRadiusExtendedEar = gSkillTraitValues.usSLRadiusNormal; }
	gSkillTraitValues.ubSLMaxBonuses = iniReader.ReadInteger("Squadleader","MAX_STACKABLE_BONUSES", 3, 1, 30);
	gSkillTraitValues.ubSLBonusAPsPercent = iniReader.ReadInteger("Squadleader","BONUS_APS_PERCENT_IN_RADIUS", 5, 0, 100);	
	gSkillTraitValues.ubSLEffectiveLevelInRadius = iniReader.ReadInteger("Squadleader","EFFECTIVE_LEVEL_OF_OTHERS_IN_RADIUS", 1, 0, 10);	
	gSkillTraitValues.ubSLEffectiveLevelAsStandby = iniReader.ReadInteger("Squadleader","EFFECTIVE_LEVEL_AS_STANDBY", 1, 0, 10);	
	gSkillTraitValues.ubSLOverallSuppresionBonusPercent = iniReader.ReadInteger("Squadleader","OVERALL_SUPRESSION_BONUS_PERCENT", 20, 0, 100);	
	gSkillTraitValues.ubSLMoraleGainBonus = iniReader.ReadInteger("Squadleader","MORALE_GAIN_BONUS", 1, 0, 20);	
	gSkillTraitValues.ubSLMoraleLossReduction = iniReader.ReadInteger("Squadleader","MORALE_LOSS_REDUCTION", 1, 0, 20);	
	gSkillTraitValues.ubSLFearResistance = iniReader.ReadInteger("Squadleader","SL_FEAR_RESISTANCE", 50, 0, 100);	
	gSkillTraitValues.ubSLDeathMoralelossMultiplier = iniReader.ReadInteger("Squadleader","SL_DEATH_MORALE_LOSS_MULTIPLIER", 1, 0, 10);	

	// TECHNICIAN
	gSkillTraitValues.usTERepairSpeedBonus = iniReader.ReadInteger("Technician","REPAIR_SPEED_BONUS_PERCENT", 25, 0, 1000);
	gSkillTraitValues.usTELockpickingBonus = iniReader.ReadInteger("Technician","LOCKPICKING_BONUS", 30, 0, 1000);
	gSkillTraitValues.usTEDisarmElTrapBonus = iniReader.ReadInteger("Technician","DISARMING_ELECTRONIC_TRAPS_BONUS", 40, 0, 1000);
	gSkillTraitValues.usTEAttachingItemsBonus = iniReader.ReadInteger("Technician","COMBINING_ITEMS_BONUS", 40, 0, 1000);
	gSkillTraitValues.ubTEUnjamGunBonus = iniReader.ReadInteger("Technician","UNJAMMING_GUN_BONUS", 20, 0, 250);
	gSkillTraitValues.ubTERepairElectronicsPenaltyReduction = iniReader.ReadInteger("Technician","REPAIR_ELECTRONICS_PENALTY_REDUCTION", 50, 0, 100);
	gSkillTraitValues.ubTEChanceToDetectTrapsBonus = iniReader.ReadInteger("Technician","EFFECTIVE_LEVEL_TO_FIND_TRAPS_BONUS", 2, 0, 10);
	gSkillTraitValues.ubTECtHControlledRobotBonus = iniReader.ReadInteger("Technician","ROBOT_CTH_BONUS", 10, 0, 100);
	gSkillTraitValues.ubTETraitsNumToRepairRobot = iniReader.ReadInteger("Technician","NUMBER_TRAITS_TO_BE_ABLE_TO_REPAIR_THE_ROBOT", 1, 0, 2);
	gSkillTraitValues.ubTERepairRobotPenaltyReduction = iniReader.ReadInteger("Technician","REPAIR_SPEED_ROBOT_PENALTY_REDUCTION", 30, 0, 100);
	if (gSkillTraitValues.ubTETraitsNumToRepairRobot == 2) {gSkillTraitValues.ubTERepairRobotPenaltyReduction /= 2; }

	// DOCTOR
	gSkillTraitValues.ubDONumberTraitsNeededForSurgery = iniReader.ReadInteger("Doctor","NUMBER_OF_TRAITS_NEEDED_FOR_SURGERY", 1, 0, 2);
	gSkillTraitValues.ubDOSurgeryHealPercentBase = iniReader.ReadInteger("Doctor","BASE_PERCENT_SURGERY_HEAL", 10, 0, 100);
	gSkillTraitValues.ubDOSurgeryHealPercentOnTop = iniReader.ReadInteger("Doctor","ONTOP_PERCENT_SURGERY_HEAL_PER_TRAIT", 20, 0, 100);
	gSkillTraitValues.usDOSurgeryMedBagConsumption = iniReader.ReadInteger("Doctor","MEDICAL_BAG_CONSUMPTION_BY_SURGERY", 100, 0, 1000);
	gSkillTraitValues.usDOSurgeryMaxBreathLoss = iniReader.ReadInteger("Doctor","MAX_ENERGY_LOSS_FOR_LIFE_HEALED", 100, 0, 500);
	gSkillTraitValues.usDORepairStatsRateBasic = iniReader.ReadInteger("Doctor","REPAIR_STATS_RATE_BASIC", 20, 0, 1000);
	gSkillTraitValues.usDORepairStatsRateOnTop = iniReader.ReadInteger("Doctor","REPAIR_STATS_RATE_ONTOP", 40, 0, 1000);
	gSkillTraitValues.ubDORepStPenaltyIfAlsoHealing = iniReader.ReadInteger("Doctor","REPAIR_STATS_RATE_REDUCTION_IF_ALSO_HEALING", 50, 0, 100);
	gSkillTraitValues.ubDOHealingPenaltyIfAlsoStatRepair = iniReader.ReadInteger("Doctor","HEALING_RATE_REDUCTION_IF_ALSO_REPAIRING_STATS", 50, 0, 100);
	gSkillTraitValues.fDORepStShouldThrowMessage = iniReader.ReadBoolean("Doctor","SHOW_MESSAGE_ABOUT_STATS_REGAINED", TRUE );
	gSkillTraitValues.usDODoctorAssignmentBonus = iniReader.ReadInteger("Doctor","DOCTOR_ASSIGNMENT_BONUS_PERCENT", 25, 0, 500);
	gSkillTraitValues.ubDOBandagingSpeedPercent = iniReader.ReadInteger("Doctor","BANDAGING_SPEED_PERCENT", 30, 0, 250);
	gSkillTraitValues.ubDONaturalRegenBonus = iniReader.ReadInteger("Doctor","NATURAL_REGENERATION_IN_SECTOR_BONUS", 10, 0, 250);
	gSkillTraitValues.ubDOMaxRegenBonuses = iniReader.ReadInteger("Doctor","MAX_NATURAL_REGEN_BONUSES", 4, 1, 50);

	// AMBIDEXTROUS
	gSkillTraitValues.ubAMPenaltyDoubleReduction = iniReader.ReadInteger("Ambidextrous","PENALTY_TO_SHOOT_DOUBLE_GUNS_REDUCTION", 100, 0, 100);
	gSkillTraitValues.ubAMReloadSpeedMagazines = iniReader.ReadInteger("Ambidextrous","RELOAD_SPEED_WITH_MAGAZINE_BONUS", 20, 0, 90);
	gSkillTraitValues.ubAMReloadSpeedLoose = iniReader.ReadInteger("Ambidextrous","RELOAD_SPEED_WITH_LOOSE_ROUNDS_BONUS", 33, 0, 90);
	gSkillTraitValues.ubAMPickItemsAPsReduction = iniReader.ReadInteger("Ambidextrous","PICK_ITEM_AP_REDUCTION", 33, 0, 90);
	gSkillTraitValues.ubAMWorkBackpackAPsReduction = iniReader.ReadInteger("Ambidextrous","WORK_BACKPACK_AP_REDUCTION", 33, 0, 90);
	gSkillTraitValues.ubAMHandleDoorsAPsReduction = iniReader.ReadInteger("Ambidextrous","HANDLE_DOORS_AP_REDUCTION", 33, 0, 90);
	gSkillTraitValues.ubAMHandleBombsAPsReduction = iniReader.ReadInteger("Ambidextrous","HANDLE_BOMBS_AP_REDUCTION", 33, 0, 90);
	gSkillTraitValues.ubAMAttachingItemsAPsReduction = iniReader.ReadInteger("Ambidextrous","ATTACH_ITEMS_AP_REDUCTION", 33, 0, 90);

	// MELEE
	gSkillTraitValues.ubMEBladesAPsReduction = iniReader.ReadInteger("Melee","BLADE_ATTACK_APS_REDUCTION", 20, 0, 100);
	gSkillTraitValues.ubMECtHBladesBonus = iniReader.ReadInteger("Melee","CTH_BLADES_BONUS", 40, 0, 100);
	gSkillTraitValues.ubMECtHBluntBonus = iniReader.ReadInteger("Melee","CTH_BLUNT_WEAPONS_BONUS", 30, 0, 200);
	gSkillTraitValues.ubMEDamageBonusBlades = iniReader.ReadInteger("Melee","DAMAGE_BONUS_BLADES", 30, 0, 250);
	gSkillTraitValues.ubMEDamageBonusBlunt = iniReader.ReadInteger("Melee","DAMAGE_BONUS_BLUNT_WEAPONS", 30, 0, 250);
	gSkillTraitValues.usMEAimedMeleeAttackDamageBonus = iniReader.ReadInteger("Melee","AIMED_MELEE_ATTACK_DAMAGE_BONUS", 50, 0, 1000);
	gSkillTraitValues.ubMEDodgeBladesBonus = iniReader.ReadInteger("Melee","BONUS_CHANCE_TO_DODGE_BLADES", 30, 0, 200);
	gSkillTraitValues.ubMECtDBladesOnTopWithBladeInHands = iniReader.ReadInteger("Melee","ONTOP_CHANCE_TO_DODGE_BLADES_WITH_BLADE", 20, 0, 200);
	gSkillTraitValues.ubMEDodgeBluntBonus = iniReader.ReadInteger("Melee","BONUS_CHANCE_TO_DODGE_BLUNT_WEAPONS", 20, 0, 200);
	gSkillTraitValues.ubMECtDBluntOnTopWithBladeInHands = iniReader.ReadInteger("Melee","ONTOP_CHANCE_TO_DODGE_BLUNT_WITH_BLADE", 10, 0, 200);

	// THROWING
	gSkillTraitValues.ubTHBladesAPsReduction = iniReader.ReadInteger("Throwing","THROW_BLADE_APS_REDUCTION", 20, 0, 90);
	gSkillTraitValues.ubTHBladesMaxRange = iniReader.ReadInteger("Throwing","TH_BLADES_RANGE_BONUS", 15, 0, 200);
	gSkillTraitValues.ubTHBladesCtHBonus = iniReader.ReadInteger("Throwing","TH_BLADES_CTH_BONUS", 25, 0, 100);
	gSkillTraitValues.ubTHBladesCtHBonusPerClick = iniReader.ReadInteger("Throwing","TH_BLADES_CTH_BONUS_PER_AIM_CLICK", 5, 0, 100);
	gSkillTraitValues.ubTHBladesDamageBonus = iniReader.ReadInteger("Throwing","TH_BLADES_DAMAGE_BONUS", 20, 0, 250);
	gSkillTraitValues.ubTHBladesDamageBonusPerClick = iniReader.ReadInteger("Throwing","TH_BLADES_DAMAGE_BONUS_PER_AIM_CLICK", 10, 0, 100);
	gSkillTraitValues.ubTHBladesSilentCriticalHitChance = iniReader.ReadInteger("Throwing","TH_BLADES_SILENT_CRITICAL_HIT_CHANCE", 20, 0, 100);
	gSkillTraitValues.ubTHBladesCriticalHitMultiplierBonus = iniReader.ReadInteger("Throwing","SILENT_CRITICAL_HIT_MULTIPLIER_BONUS", 1, 0, 50);
	gSkillTraitValues.ubTHBladesAimClicksAdded = iniReader.ReadInteger("Throwing","POSSIBLE_AIM_CLICK_ADDED_TH_KNIVES", 1, 0, 5);

	// NIGHT OPS
	gSkillTraitValues.ubNOeSightRangeBonusInDark = iniReader.ReadInteger("Night Ops","SIGHT_RANGE_BONUS_IN_DARK", 1, 0, 100);
	gSkillTraitValues.ubNOHearingRangeBonus = iniReader.ReadInteger("Night Ops","BASIC_HEARING_RANGE_BONUS", 1, 0, 100);
	gSkillTraitValues.ubNOHearingRangeBonusInDark = iniReader.ReadInteger("Night Ops","ONTOP_HEARING_RANGE_BONUS_IN_DARK", 2, 0, 100);
	gSkillTraitValues.ubNOIterruptsBonusInDark = iniReader.ReadInteger("Night Ops","INTERRUPTS_BONUS_IN_DARK", 2, 0, 10);
	gSkillTraitValues.ubNONeedForSleepReduction = iniReader.ReadInteger("Night Ops","NEED_FOR_SLEEP_REDUCTION", 3, 0, 10);

	// STEALTHY
	gSkillTraitValues.ubSTStealthModeSpeedBonus = iniReader.ReadInteger("Stealthy","STEALTH_MODE_SPEED_BONUS", 50, 0, 100);
	gSkillTraitValues.ubSTBonusToMoveQuietly = iniReader.ReadInteger("Stealthy","BONUS_TO_MOVE_STEALTHILY", 40, 0, 250);
	gSkillTraitValues.ubSTStealthBonus = iniReader.ReadInteger("Stealthy","STEALTH_BONUS", 25, 0, 200);
	gSkillTraitValues.ubSTStealthPenaltyForMovingReduction = iniReader.ReadInteger("Stealthy","CHANCE_TO_BE_SPOTTED_FOR_MOVING_REDUCTION", 25, 0, 100);

	// ATHLETICS
	gSkillTraitValues.ubATAPsMovementReduction = iniReader.ReadInteger("Athletics","APS_NEED_FOR_MOVEMENT_REDUCTION", 33, 0, 90);
	gSkillTraitValues.ubATBPsMovementReduction = iniReader.ReadInteger("Athletics","BPS_SPENT_FOR_MOVEMENT_REDUCTION", 33, 0, 90);

	// BODYBUILDING
	gSkillTraitValues.ubBBDamageResistance = iniReader.ReadInteger("Bodybuilding","DAMAGE_RESISTANCE", 20, 0, 90);
	gSkillTraitValues.ubBBCarryWeightBonus = iniReader.ReadInteger("Bodybuilding","CARRY_WEIGHT_BONUS", 30, 0, 250);
	gSkillTraitValues.ubBBBreathLossForHtHImpactReduction = iniReader.ReadInteger("Bodybuilding","BREATH_LOSS_FOR_HTH_HIT_REDUCTION", 50, 0, 100);
	gSkillTraitValues.usBBIncreasedNeededDamageToFallDown = iniReader.ReadInteger("Bodybuilding","INCREASE_DAMAGE_NEEDED_TO_FALL_DOWN_IF_HIT_TO_LEGS", 100, 0, 500);

	// DEMOLITIONS
	gSkillTraitValues.ubDEAPsNeededToThrowGrenadesReduction = iniReader.ReadInteger("Demolitions","APS_NEEDED_TO_THROW_GRENADES_REDUCTION", 25, 0, 90);
	gSkillTraitValues.ubDEMaxRangeToThrowGrenades = iniReader.ReadInteger("Demolitions","MAX_RANGE_TO_THROW_GRENADES", 20, 0, 250);
	gSkillTraitValues.ubDECtHWhenThrowingGrenades = iniReader.ReadInteger("Demolitions","CTH_WHEN_THROWING_GRENADES", 30, 0, 100);
	gSkillTraitValues.ubDEDamageOfBombsAndMines = iniReader.ReadInteger("Demolitions","DAMAGE_OF_PLACED_BOMBS_AND_MINES", 25, 0, 250);
	gSkillTraitValues.ubDEAttachDetonatorCheckBonus = iniReader.ReadInteger("Demolitions","ATTACH_DETONATOR_CHECK_BONUS", 50, 0, 250);
	gSkillTraitValues.ubDEPlantAndRemoveBombCheckBonus = iniReader.ReadInteger("Demolitions","PLANT_AND_REMOVE_BOMBS_AND_MINES_BONUS", 50, 0, 250);
	gSkillTraitValues.ubDEPlacedBombLevelBonus = iniReader.ReadInteger("Demolitions","PLACED_BOMBS_AND_MINES_DETECTION_DIFFICULTY_BONUS", 5, 0, 15);
	gSkillTraitValues.ubDEShapedChargeDamageMultiplier = iniReader.ReadInteger("Demolitions","SHAPED_CHARGE_DAMAGE_MULTIPLIER", 3, 1, 50);

	// TEACHING
	gSkillTraitValues.ubTGBonusToTrainMilitia = iniReader.ReadInteger("Teaching","BONUS_TO_TRAIN_MILITIA", 40, 0, 250);
	gSkillTraitValues.ubTGEffectiveLDRToTrainMilitia = iniReader.ReadInteger("Teaching","EFFECTIVE_LEADERSHIP_FOR_MILITIA_TRAINING", 40, 0, 250);
	gSkillTraitValues.ubTGBonusToTeachOtherMercs = iniReader.ReadInteger("Teaching","BONUS_TO_TEACH_OTHER_MERCS", 40, 0, 250);
	gSkillTraitValues.ubTGEffectiveSkillValueForTeaching = iniReader.ReadInteger("Teaching","EFFECTIVE_SKILL_VALUE_TO_TEACH_OTHERS_BONUS", 25, 0, 100);
	gSkillTraitValues.ubTGBonusOnPractising = iniReader.ReadInteger("Teaching","BONUS_ON_PRACTISING", 25, 0, 250);

	// SCOUTING
	gSkillTraitValues.ubSCSightRangebonusWithScopes = iniReader.ReadInteger("Scouting","SIGHT_RANGE_INCREASED_WITH_SCOPES", 10, 0, 250);
	gSkillTraitValues.usSCSightRangebonusWithBinoculars = iniReader.ReadInteger("Scouting","SIGHT_RANGE_INCREASED_WITH_BINOCULARS", 40, 0, 1000);
	gSkillTraitValues.ubSCTunnelVisionReducedWithBinoculars = iniReader.ReadInteger("Scouting","TUNNEL_VISION_REDUCED_WITH_BINOCULARS", 20, 0, 250);
	gSkillTraitValues.fSCCanDetectEnemyPresenseAround = iniReader.ReadBoolean("Scouting","CAN_DETECT_ENEMY_PRESENSE_IN_SECTORS_AROUND", TRUE);
	gSkillTraitValues.fSCCanDetermineEnemyNumbersAround = iniReader.ReadBoolean("Scouting","CAN_DETERMINE_ENEMY_NUMBERS_IN_SECTORS_AROUND", TRUE);
	gSkillTraitValues.fSCDetectionInDiagonalSectors = iniReader.ReadBoolean("Scouting","ALLOW_DETECTION_IN_DIAGONAL_SECTORS", TRUE);
	gSkillTraitValues.fSCPreventsTheEnemyToAmbushMercs = iniReader.ReadBoolean("Scouting","PREVENTS_ENEMY_AMBUSHES", TRUE);
	gSkillTraitValues.fSCPreventsBloodcatsAmbushes = iniReader.ReadBoolean("Scouting","PREVENTS_BLOODCATS_AMBUSHES", TRUE);
	gSkillTraitValues.fSCThrowMessageIfAmbushPrevented = iniReader.ReadBoolean("Scouting","SHOW_MESSAGE_IF_AMBUSH_PREVENTED", TRUE);

}


INT16 DynamicAdjustAPConstants(INT16 iniReadValue, INT16 iniDefaultValue, BOOLEAN reverse)
{
	//CHRISL: This function will dynamically adjust all the APBPConstant values based on the AP_MAXIMUM value.  This way
	//	if you want to use a 50AP system instead of the default, you only need to alter one value in the INI file and all
	//	the other values will automatically be updated to reflect the new max value.  The way I've coded this, however, if
	//	you set your own value, you'll override this dynamic system.
	if(iniReadValue == iniDefaultValue)
	{
		if(!reverse)
			iniReadValue = (INT16)(((FLOAT)iniReadValue*(FLOAT)APBPConstants[AP_MAXIMUM]/100)+(iniReadValue<0?-.5:.5));
		else
			iniReadValue = (INT16)(((FLOAT)iniReadValue/(FLOAT)APBPConstants[AP_MAXIMUM]*100)+(iniReadValue<0?-.5:.5));
	}

	return iniReadValue;
}

void LoadGameAPBPConstants()
{
	// WDS - Chris you should fix up the ReadIntegers below to have valid min/max values.

	CIniReader iniReader(AP_BP_CONSTANTS_FILE);
	//CHRISL: To allow for dynamic settings, we need to switch AP_MAXIMUM and AP_MINIMUM so that only the max value needs
	//	to be changed to effect the entire system.  This will require a change in the ENUM so that we can use a loop to
	//	modify the remaining values.
	APBPConstants[AP_MAXIMUM] = iniReader.ReadInteger("APConstants","AP_MAXIMUM",100, 25, 250);
 
	//CHRISL: Once we've loaded the AP_MAXIMUM value, we can use it to modifiy all the remaining values
	APBPConstants[AP_MINIMUM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MINIMUM",40, 10, 100),40);
	
	// WANNE: Externalized minimum APs to get an interrupt
	APBPConstants[MIN_APS_TO_INTERRUPT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","MIN_APS_TO_INTERRUPT",16),16);
	
	APBPConstants[AP_MONSTER_MAXIMUM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MONSTER_MAXIMUM",160),160);
	APBPConstants[AP_VEHICLE_MAXIMUM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_VEHICLE_MAXIMUM",200),200);
	APBPConstants[MAX_AP_CARRIED] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","MAX_AP_CARRIED",20),20);

	//CHRISL: The following five values are actually used as percentile adjustments so we don't want to dynamically alter
	//	them.  I.E. 9 actually means 90% of the calculated APs.  15 = 150%.  etc.
	APBPConstants[AP_YOUNG_MONST_FACTOR] = iniReader.ReadInteger("APConstants","AP_YOUNG_MONST_FACTOR",15);
	APBPConstants[AP_MONST_FRENZY_FACTOR] = iniReader.ReadInteger("APConstants","AP_MONST_FRENZY_FACTOR",13);
	APBPConstants[AP_CLAUSTROPHOBE] = iniReader.ReadInteger("APConstants","AP_CLAUSTROPHOBE",9);
	APBPConstants[AP_AFRAID_OF_INSECTS] = iniReader.ReadInteger("APConstants","AP_AFRAID_OF_INSECTS",8);
	APBPConstants[AP_WRONG_MAG] = iniReader.ReadInteger("APConstants","AP_WRONG_MAG",15);

	APBPConstants[AP_EXCHANGE_PLACES] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_EXCHANGE_PLACES",20),20);
	APBPConstants[AP_REVERSE_MODIFIER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_REVERSE_MODIFIER",4),4);
	APBPConstants[AP_STEALTH_MODIFIER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_STEALTH_MODIFIER",8),8);
	APBPConstants[AP_STEAL_ITEM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_STEAL_ITEM",56),56);
	APBPConstants[AP_TAKE_BLOOD] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_TAKE_BLOOD",40),40);
	APBPConstants[AP_TALK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_TALK",24),24);
	APBPConstants[AP_MOVEMENT_FLAT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_FLAT",12),12);
	APBPConstants[AP_MOVEMENT_GRASS] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_GRASS",14),14);
	APBPConstants[AP_MOVEMENT_BUSH] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_BUSH",18),18);
	APBPConstants[AP_MOVEMENT_RUBBLE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_RUBBLE",24),24);
	APBPConstants[AP_MOVEMENT_SHORE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_SHORE",28),28);
	APBPConstants[AP_MOVEMENT_LAKE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_LAKE",36),36);
	APBPConstants[AP_MOVEMENT_OCEAN] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MOVEMENT_OCEAN",32),32);
	APBPConstants[AP_MODIFIER_RUN] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_RUN",-8),-8);
	APBPConstants[AP_MODIFIER_WALK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_WALK",-4),-4);
	APBPConstants[AP_MODIFIER_SWAT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_SWAT",0),0);
	APBPConstants[AP_MODIFIER_CRAWL] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_CRAWL",4),4);
	APBPConstants[AP_MODIFIER_PACK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_PACK",4),4);
	APBPConstants[AP_MODIFIER_READY] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MODIFIER_WEAPON_READY",1),4);
	APBPConstants[AP_CHANGE_FACING] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CHANGE_FACING",4),4);
	APBPConstants[AP_CHANGE_TARGET] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CHANGE_TARGET",2),2);
	APBPConstants[AP_TOSS_ITEM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_TOSS_ITEM",32),32);
	APBPConstants[AP_REFUEL_VEHICLE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_REFUEL_VEHICLE",40),40);
	APBPConstants[AP_RADIO] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_RADIO",20),20);
	APBPConstants[AP_CROUCH] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CROUCH",6),6);
	APBPConstants[AP_PRONE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_PRONE",8),8);
	APBPConstants[AP_LOOK_STANDING] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOOK_STANDING",4),4);
	APBPConstants[AP_LOOK_CROUCHED] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOOK_CROUCHED",6),6);
	APBPConstants[AP_LOOK_PRONE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOOK_PRONE",8),8);
	APBPConstants[AP_READY_KNIFE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_READY_KNIFE",0),0);
	APBPConstants[AP_READY_DUAL] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_READY_DUAL",4),4);
	APBPConstants[AP_MIN_AIM_ATTACK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MIN_AIM_ATTACK",0),0);
	APBPConstants[AP_DROP_BOMB] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_DROP_BOMB",12),12);
	APBPConstants[AP_RELOAD_GUN] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_RELOAD_GUN",20),20);
	APBPConstants[AP_START_FIRST_AID] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_START_FIRST_AID",20),20);
	APBPConstants[AP_START_REPAIR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_START_REPAIR",20),20);

	//CHRISL: This value is a divisor which should not be dynamically altered based on maxAP
	APBPConstants[AP_GET_WOUNDED_DIVISOR] = iniReader.ReadInteger("APConstants","AP_GET_WOUNDED_DIVISOR",1);

	APBPConstants[AP_FALL_DOWN] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_FALL_DOWN",16),16);
	APBPConstants[AP_OPEN_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_OPEN_DOOR",12),12);
	APBPConstants[AP_PICKLOCK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_PICKLOCK",40),40);
	APBPConstants[AP_EXAMINE_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_EXAMINE_DOOR",20),20);
	APBPConstants[AP_BOOT_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_BOOT_DOOR",32),32);
	APBPConstants[AP_USE_CROWBAR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_USE_CROWBAR",40),40);
	APBPConstants[AP_UNLOCK_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_UNLOCK_DOOR",24),24);
	APBPConstants[AP_LOCK_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOCK_DOOR",24),24);
	APBPConstants[AP_EXPLODE_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_EXPLODE_DOOR",40),40);
	APBPConstants[AP_UNTRAP_DOOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_UNTRAP_DOOR",40),40);
	APBPConstants[AP_USEWIRECUTTERS] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_USEWIRECUTTERS",40),40);
	APBPConstants[AP_CLIMBROOF] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CLIMBROOF",40),40);
	APBPConstants[AP_CLIMBOFFROOF] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CLIMBOFFROOF",24),24);
	APBPConstants[AP_JUMPFENCE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMPFENCE",24),24);
	APBPConstants[AP_JUMPFENCEBPACK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMPFENCEBPACK",32),32);
	APBPConstants[AP_USE_REMOTE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_USE_REMOTE",8),8);
	APBPConstants[AP_PULL_TRIGGER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_PULL_TRIGGER",8),8);
	APBPConstants[AP_PUNCH] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_PUNCH",16),16);
	APBPConstants[AP_PICKUP_ITEM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_PICKUP_ITEM",12),12);
	APBPConstants[AP_GIVE_ITEM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_GIVE_ITEM",4),4);
	APBPConstants[AP_BURY_MINE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_BURY_MINE",30),30);
	APBPConstants[AP_DISARM_MINE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_DISARM_MINE",40),40);
	APBPConstants[AP_DRINK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_DRINK",20),20);
	APBPConstants[AP_CAMOFLAGE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CAMOFLAGE",40),40);
	APBPConstants[AP_START_RUN_COST] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_START_RUN_COST",4),4);
	APBPConstants[AP_ATTACH_CAN] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_ATTACH_CAN",20),20);
	APBPConstants[AP_JUMP_OVER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMP_OVER",20),20);
	APBPConstants[AP_BACK_PACK] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_BACK_PACK",12),12);
	APBPConstants[AP_OPEN_ZIPPER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_OPEN_ZIPPER",24),24);
	APBPConstants[AP_CLOSE_ZIPPER] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CLOSE_ZIPPER",28),28);
	APBPConstants[AP_CLICK_AIM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_CLICK_AIM",4),4);
	// HEADROCK HAM 3.1: Separate costs for each aiming click (when using a scope):
	APBPConstants[AP_FIRST_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_FIRST_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_SECOND_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_SECOND_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_THIRD_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_THIRD_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_FOURTH_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_FOURTH_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_FIFTH_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_FIFTH_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_SIXTH_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_SIXTH_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_SEVENTH_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_SEVENTH_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AP_EIGHTH_CLICK_AIM_SCOPE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_EIGHTH_CLICK_AIM_SCOPE",4),4);
	APBPConstants[AUTOFIRE_SHOTS_AP_VALUE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AUTOFIRE_SHOTS_AP_VALUE",20),20);
	APBPConstants[BAD_AP_COST] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","BAD_AP_COST",36),36);
	APBPConstants[AP_RELOAD_LOOSE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_RELOAD_LOOSE",8),8);
	APBPConstants[AP_UNJAM] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_UNJAM",2),2);
	
	// WANNE: APs needed when you jump through a window
	APBPConstants[AP_JUMPWINDOW] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMPWINDOW",40),40);
	
	APBPConstants[AP_MAX_SUPPRESSED] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MAX_SUPPRESSED",64),64);
	APBPConstants[AP_MAX_TURN_SUPPRESSED] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MAX_TURN_SUPPRESSED",200),200);
	APBPConstants[AP_MIN_LIMIT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_MIN_LIMIT",-100),-100);
	APBPConstants[AP_LOST_PER_MORALE_DROP] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOST_PER_MORALE_DROP",12),12);
	APBPConstants[AP_SUPPRESSION_MOD] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_SUPPRESSION_MOD",24),24);
	// HEADROCK HAM 3.5: Determines divisor for AP/Shock ratio. 100AP will have this set at 4, 25AP will have this set at 1.
	APBPConstants[AP_SUPPRESSION_SHOCK_DIVISOR] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_SUPPRESSION_SHOCK_DIVISOR",4),4);
	// HEADROCK HAM 3.2: Modifier for legshot AP loss based on damage
	APBPConstants[AP_LOSS_PER_LEGSHOT_DAMAGE] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_LOSS_PER_LEGSHOT_DAMAGE",4),4);

	APBPConstants[DEFAULT_APS] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","DEFAULT_APS",80),80);
	APBPConstants[DEFAULT_AIMSKILL] = iniReader.ReadInteger("APConstants","DEFAULT_AIMSKILL",80);

	APBPConstants[BP_RATIO_RED_PTS_TO_NORMAL] = iniReader.ReadInteger("BPConstants","BP_RATIO_RED_PTS_TO_NORMAL",100);
	APBPConstants[BP_RUN_ENERGYCOSTFACTOR] = iniReader.ReadInteger("BPConstants","BP_RUN_ENERGYCOSTFACTOR",3);
	APBPConstants[BP_WALK_ENERGYCOSTFACTOR] = iniReader.ReadInteger("BPConstants","BP_WALK_ENERGYCOSTFACTOR",1);
	APBPConstants[BP_SWAT_ENERGYCOSTFACTOR] = iniReader.ReadInteger("BPConstants","BP_SWAT_ENERGYCOSTFACTOR",2);
	APBPConstants[BP_CRAWL_ENERGYCOSTFACTOR] = iniReader.ReadInteger("BPConstants","BP_CRAWL_ENERGYCOSTFACTOR",4);
	APBPConstants[BP_RADIO] = iniReader.ReadInteger("BPConstants","BP_RADIO",0);
	APBPConstants[BP_USE_DETONATOR] = iniReader.ReadInteger("BPConstants","BP_USE_DETONATOR",0);
	APBPConstants[BP_PER_AP_NO_EFFORT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","BP_PER_AP_NO_EFFORT",-50),-50, TRUE);
	APBPConstants[BP_PER_AP_MIN_EFFORT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","BP_PER_AP_MIN_EFFORT",-25),-25, TRUE);
	APBPConstants[BP_PER_AP_LT_EFFORT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","BP_PER_AP_LT_EFFORT",-12),-12, TRUE);
	APBPConstants[BP_PER_AP_MOD_EFFORT] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","BP_PER_AP_MOD_EFFORT",0),0, TRUE);
	APBPConstants[BP_MOVEMENT_FLAT] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_FLAT",5);
	APBPConstants[BP_MOVEMENT_GRASS] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_GRASS",10);
	APBPConstants[BP_MOVEMENT_BUSH] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_BUSH",20);
	APBPConstants[BP_MOVEMENT_RUBBLE] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_RUBBLE",35);
	APBPConstants[BP_MOVEMENT_SHORE] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_SHORE",50);
	APBPConstants[BP_MOVEMENT_LAKE] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_LAKE",75);
	APBPConstants[BP_MOVEMENT_OCEAN] = iniReader.ReadInteger("BPConstants","BP_MOVEMENT_OCEAN",100);
	APBPConstants[BP_MOVEMENT_READY] = iniReader.ReadInteger("BPConstants","BP_MODIFIER_WEAPON_READY",30);
	APBPConstants[BP_CROUCH] = iniReader.ReadInteger("BPConstants","BP_CROUCH",10);
	APBPConstants[BP_PRONE] = iniReader.ReadInteger("BPConstants","BP_PRONE",10);
	APBPConstants[BP_CLIMBROOF] = iniReader.ReadInteger("BPConstants","BP_CLIMBROOF",500);
	APBPConstants[BP_CLIMBOFFROOF] = iniReader.ReadInteger("BPConstants","BP_CLIMBOFFROOF",250);
	APBPConstants[BP_JUMPFENCE] = iniReader.ReadInteger("BPConstants","BP_JUMPFENCE",200);
	APBPConstants[BP_JUMPFENCEBPACK] = iniReader.ReadInteger("BPConstants","BP_JUMPFENCEBPACK",500);
	APBPConstants[BP_STEAL_ITEM] = iniReader.ReadInteger("BPConstants","BP_STEAL_ITEM",50);
	APBPConstants[BP_START_FIRST_AID] = iniReader.ReadInteger("BPConstants","BP_START_FIRST_AID",0);
	APBPConstants[BP_GET_HIT] = iniReader.ReadInteger("BPConstants","BP_GET_HIT",200);
	APBPConstants[BP_GET_WOUNDED] = iniReader.ReadInteger("BPConstants","BP_GET_WOUNDED",50);
	APBPConstants[BP_FALL_DOWN] = iniReader.ReadInteger("BPConstants","BP_FALL_DOWN",250);
	APBPConstants[BP_OPEN_DOOR] = iniReader.ReadInteger("BPConstants","BP_OPEN_DOOR",30);
	APBPConstants[BP_PICKLOCK] = iniReader.ReadInteger("BPConstants","BP_PICKLOCK",50);
	APBPConstants[BP_EXAMINE_DOOR] = iniReader.ReadInteger("BPConstants","BP_EXAMINE_DOOR",20);
	APBPConstants[BP_BOOT_DOOR] = iniReader.ReadInteger("BPConstants","BP_BOOT_DOOR",200);
	APBPConstants[BP_USE_CROWBAR] = iniReader.ReadInteger("BPConstants","BP_USE_CROWBAR",350);
	APBPConstants[BP_UNLOCK_DOOR] = iniReader.ReadInteger("BPConstants","BP_UNLOCK_DOOR",50);
	APBPConstants[BP_EXPLODE_DOOR] = iniReader.ReadInteger("BPConstants","BP_EXPLODE_DOOR",40);
	APBPConstants[BP_UNTRAP_DOOR] = iniReader.ReadInteger("BPConstants","BP_UNTRAP_DOOR",150);
	APBPConstants[BP_LOCK_DOOR] = iniReader.ReadInteger("BPConstants","BP_LOCK_DOOR",50);
	APBPConstants[BP_USEWIRECUTTERS] = iniReader.ReadInteger("BPConstants","BP_USEWIRECUTTERS",200);
	APBPConstants[BP_DROP_BOMB] = iniReader.ReadInteger("BPConstants","BP_DROP_BOMB",0);
	APBPConstants[BP_BURY_MINE] = iniReader.ReadInteger("BPConstants","BP_BURY_MINE",250);
	APBPConstants[BP_DISARM_MINE] = iniReader.ReadInteger("BPConstants","BP_DISARM_MINE",0);
	APBPConstants[BP_JUMP_OVER] = iniReader.ReadInteger("BPConstants","BP_JUMP_OVER",250);
	APBPConstants[BP_BACK_PACK] = iniReader.ReadInteger("APConstants","BP_JUMP_OVER",50);
	APBPConstants[BP_WORK_ZIPPER] = iniReader.ReadInteger("APConstants","BP_WORK_ZIPPER",250);
	APBPConstants[BP_UNJAM] = iniReader.ReadInteger("APConstants","BP_WORK_ZIPPER",0);
	
	APBPConstants[BP_JUMPOFFWALL] = iniReader.ReadInteger("BPConstants","BP_JUMPOFFWALL",250);
	APBPConstants[BP_JUMPWALL] = iniReader.ReadInteger("BPConstants","BP_JUMPWALL",500);
	
	APBPConstants[AP_JUMPWALL] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMPOFFWALL",40),40);
	APBPConstants[AP_JUMPOFFWALL] = DynamicAdjustAPConstants(iniReader.ReadInteger("APConstants","AP_JUMPWALL",24),24);

	SetupMaxActionPointsAnimation();
#undef ReadInteger
}

// HEADROCK HAM 4: Read the various coefficients for the new CTH and Shooting systems from an INI file.
void LoadCTHConstants()
{

	//Kaiden: Setting Ja2_Options.ini file to be read
	CIniReader iniReader(CTH_COEFFICIENTS_FILE);

	gGameCTHConstants.NORMAL_SHOOTING_DISTANCE			= iniReader.ReadInteger("General","NORMAL_SHOOTING_DISTANCE",100, 10, 10000);
	gGameCTHConstants.DEGREES_MAXIMUM_APERTURE			= iniReader.ReadFloat("General", "DEGREES_MAXIMUM_APERTURE", 15.0, 0.0, 22.5);
	gGameCTHConstants.RANGE_COEFFICIENT					= iniReader.ReadFloat("General", "RANGE_COEFFICIENT", 2.0, 0.001f, 100.0);
	gGameCTHConstants.GRAVITY_COEFFICIENT				= iniReader.ReadFloat("General", "GRAVITY_COEFFICIENT", 1.0, 0.001f, 100.0);
	gGameCTHConstants.VERTICAL_BIAS						= iniReader.ReadFloat("General", "VERTICAL_BIAS", 1.0f, 0.01f, 2.0f);
	gGameCTHConstants.SCOPE_RANGE_MULTIPLIER			= iniReader.ReadFloat("General", "SCOPE_RANGE_MULTIPLIER", 0.7f, 0.5f, 1.5f);
	gGameCTHConstants.SIDE_FACING_DIVISOR				= iniReader.ReadFloat("General", "SIDE_FACING_DIVISOR", 2.0, 1.0f, 10.0f);

	////////////////////////////////////////////////////////////
	// Coefficients for factors affecting Base CTH
	////////////////////////////////////////////////////////////

	gGameCTHConstants.BASE_EXP				= iniReader.ReadFloat("Base CTH","BASE_EXP",3.0, 0.0, 100.0);
	gGameCTHConstants.BASE_MARKS			= iniReader.ReadFloat("Base CTH","BASE_MARKS",1.0, 0.0, 100.0);
	gGameCTHConstants.BASE_WIS				= iniReader.ReadFloat("Base CTH","BASE_WIS",1.0, 0.0, 100.0);
	gGameCTHConstants.BASE_DEX				= iniReader.ReadFloat("Base CTH","BASE_DEX",1.0, 0.0, 100.0);

	gGameCTHConstants.BASE_LOW_MORALE		= iniReader.ReadFloat("Base CTH","BASE_LOW_MORALE",-1.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_HIGH_MORALE		= iniReader.ReadFloat("Base CTH","BASE_HIGH_MORALE",2.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_PSYCHO			= iniReader.ReadFloat("Base CTH","BASE_PSYCHO",-3.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_SHOOTING_UPWARDS	= iniReader.ReadFloat("Base CTH","BASE_SHOOTING_UPWARDS",-15.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_INJURY			= iniReader.ReadFloat("Base CTH","BASE_INJURY",-30.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DRUNK[0]			= iniReader.ReadFloat("Base CTH","BASE_DRUNK_TIPSY",-5.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DRUNK[1]			= iniReader.ReadFloat("Base CTH","BASE_DRUNK",-20.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DRUNK[2]			= iniReader.ReadFloat("Base CTH","BASE_DRUNK_WASTED",-50.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DRUNK[3]			= iniReader.ReadFloat("Base CTH","BASE_DRUNK_HUNGOVER",-10.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_FATIGUE			= iniReader.ReadFloat("Base CTH","BASE_FATIGUE",-15.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_SAME_TARGET		= iniReader.ReadFloat("Base CTH","BASE_SAME_TARGET",5.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_GASSED			= iniReader.ReadFloat("Base CTH","BASE_GASSED",-15.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_BEING_BANDAGED	= iniReader.ReadFloat("Base CTH","BASE_BEING_BANDAGED",-5.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_SHOCK			= iniReader.ReadFloat("Base CTH","BASE_SHOCK",-150.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_AGILE_TARGET		= iniReader.ReadFloat("Base CTH","BASE_AGILE_TARGET",-5.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_TARGET_INVISIBLE	= iniReader.ReadFloat("Base CTH","BASE_TARGET_INVISIBLE",-100.0, -1000.0, 1000.0);

	gGameCTHConstants.BASE_DRAW_COST		= iniReader.ReadFloat("Base CTH","BASE_DRAW_COST",2.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_TWO_GUNS			= iniReader.ReadFloat("Base CTH","BASE_TWO_GUNS",5.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_ONE_HANDED		= iniReader.ReadFloat("Base CTH","BASE_ONE_HANDED",2.5, -1000.0, 1000.0);
	gGameCTHConstants.BASE_STANDING_STANCE	= iniReader.ReadFloat("Base CTH","BASE_STANDING_STANCE",2.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_CROUCHING_STANCE	= iniReader.ReadFloat("Base CTH","BASE_CROUCHING_STANCE",3.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_PRONE_STANCE		= iniReader.ReadFloat("Base CTH","BASE_PRONE_STANCE",4.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_HEAVY_WEAPON		= iniReader.ReadFloat("Base CTH","BASE_HEAVY_WEAPON",2.0, -1000.0, 1000.0);

	gGameCTHConstants.BASE_DIFFICULTY[0]	= -100.0;
	gGameCTHConstants.BASE_DIFFICULTY[1]	= iniReader.ReadFloat("Base CTH","BASE_DIFFICULTY_NOVICE",-30.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DIFFICULTY[2]	= iniReader.ReadFloat("Base CTH","BASE_DIFFICULTY_EXPERIENCED",0.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DIFFICULTY[3]	= iniReader.ReadFloat("Base CTH","BASE_DIFFICULTY_EXPERT",20.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DIFFICULTY[4]	= iniReader.ReadFloat("Base CTH","BASE_DIFFICULTY_INSANE",50.0, -1000.0, 1000.0);
	gGameCTHConstants.BASE_DIFFICULTY[5]	= 100.0;

	////////////////////////////////////////////////////////////
	// Coefficients for factors affecting Aiming CTH
	////////////////////////////////////////////////////////////

	gGameCTHConstants.AIM_EXP 		= iniReader.ReadFloat("Aiming CTH","AIM_EXP",1.0, 0.0, 100.0);
	gGameCTHConstants.AIM_MARKS 	= iniReader.ReadFloat("Aiming CTH","AIM_MARKS",3.0, 0.0, 100.0);
	gGameCTHConstants.AIM_WIS 		= iniReader.ReadFloat("Aiming CTH","AIM_WIS",1.0, 0.0, 100.0);
	gGameCTHConstants.AIM_DEX 		= iniReader.ReadFloat("Aiming CTH","AIM_DEX",2.0, 0.0, 100.0);

	gGameCTHConstants.AIM_TOO_CLOSE_SCOPE	= iniReader.ReadFloat("Aiming CTH","AIM_TOO_CLOSE_SCOPE",-4.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_GUN_CONDITION  	= iniReader.ReadFloat("Aiming CTH","AIM_GUN_CONDITION",-2.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_LOW_MORALE  		= iniReader.ReadFloat("Aiming CTH","AIM_LOW_MORALE",-2.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_HIGH_MORALE  		= iniReader.ReadFloat("Aiming CTH","AIM_HIGH_MORALE",1.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_PSYCHO  			= iniReader.ReadFloat("Aiming CTH","AIM_PSYCHO",-5.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_VISIBILITY  		= iniReader.ReadFloat("Aiming CTH","AIM_VISIBILITY",-1.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_SHOOTING_UPWARDS  = iniReader.ReadFloat("Aiming CTH","AIM_SHOOTING_UPWARDS",-20.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_INJURY  			= iniReader.ReadFloat("Aiming CTH","AIM_INJURY",-60.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DRUNK[0]	  		= iniReader.ReadFloat("Aiming CTH","AIM_DRUNK_TIPSY",-10.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DRUNK[1]			= iniReader.ReadFloat("Aiming CTH","AIM_DRUNK",-40.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DRUNK[2]	 		= iniReader.ReadFloat("Aiming CTH","AIM_DRUNK_WASTED",-90.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DRUNK[3]			= iniReader.ReadFloat("Aiming CTH","AIM_DRUNK_HUNGOVER",-15.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_FATIGUE  			= iniReader.ReadFloat("Aiming CTH","AIM_FATIGUE",-40.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_GASSED  			= iniReader.ReadFloat("Aiming CTH","AIM_GASSED",-80.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_BEING_BANDAGED	= iniReader.ReadFloat("Aiming CTH","AIM_BEING_BANDAGED",-20.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_SHOCK  			= iniReader.ReadFloat("Aiming CTH","AIM_SHOCK",-150.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_TARGET_INVISIBLE  = iniReader.ReadFloat("Aiming CTH","AIM_TARGET_INVISIBLE",-50.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_SNIPER_SKILL		= iniReader.ReadFloat("Aiming CTH","AIM_SNIPER_SKILL",25.0, -100.0, 100.0);

	gGameCTHConstants.AIM_DRAW_COST  		= iniReader.ReadFloat("Aiming CTH","AIM_DRAW_COST",0.5, -1000.0, 1000.0);
	gGameCTHConstants.AIM_STANDING_STANCE  	= iniReader.ReadFloat("Aiming CTH","AIM_STANDING_STANCE",1.5, -1000.0, 1000.0);
	gGameCTHConstants.AIM_CROUCHING_STANCE  = iniReader.ReadFloat("Aiming CTH","AIM_CROUCHING_STANCE",1.25, -1000.0, 1000.0);
	gGameCTHConstants.AIM_PRONE_STANCE  	= iniReader.ReadFloat("Aiming CTH","AIM_PRONE_STANCE",1.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_TWO_GUNS  		= iniReader.ReadFloat("Aiming CTH","AIM_TWO_GUNS",4.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_ONE_HANDED  		= iniReader.ReadFloat("Aiming CTH","AIM_ONE_HANDED",2.5, -1000.0, 1000.0);
	gGameCTHConstants.AIM_HEAVY_WEAPON  	= iniReader.ReadFloat("Aiming CTH","AIM_HEAVY_WEAPON",2.0, -1000.0, 1000.0);

	gGameCTHConstants.AIM_DIFFICULTY[0]		= -100.0;
	gGameCTHConstants.AIM_DIFFICULTY[1]	  	= iniReader.ReadFloat("Aiming CTH","AIM_DIFFICULTY_NOVICE",-30.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DIFFICULTY[2]	  	= iniReader.ReadFloat("Aiming CTH","AIM_DIFFICULTY_EXPERIENCED",0.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DIFFICULTY[3]	  	= iniReader.ReadFloat("Aiming CTH","AIM_DIFFICULTY_EXPERT",20.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DIFFICULTY[4]	  	= iniReader.ReadFloat("Aiming CTH","AIM_DIFFICULTY_INSANE",50.0, -1000.0, 1000.0);
	gGameCTHConstants.AIM_DIFFICULTY[5]		= 100.0;

	////////////////////////////////////////////////////////////
	// Coefficients for factors affecting the Shooting Mechanism
	////////////////////////////////////////////////////////////

	gGameCTHConstants.MOVEMENT_MRK										= iniReader.ReadFloat("Shooting Mechanism","MOVEMENT_MRK",3.0, 0.0, 100.0);
	gGameCTHConstants.MOVEMENT_WIS										= iniReader.ReadFloat("Shooting Mechanism","MOVEMENT_WIS",2.0, 0.0, 100.0);
	gGameCTHConstants.MOVEMENT_DEX										= iniReader.ReadFloat("Shooting Mechanism","MOVEMENT_DEX",1.0, 0.0, 100.0);
	gGameCTHConstants.MOVEMENT_EXP_LEVEL								= iniReader.ReadFloat("Shooting Mechanism","MOVEMENT_EXP_LEVEL",2.0, 0.0, 100.0);
	gGameCTHConstants.MOVEMENT_TRACKING_DIFFICULTY						= iniReader.ReadInteger("Shooting Mechanism","MOVEMENT_TRACKING_DIFFICULTY",20, 0, 1000);
	gGameCTHConstants.MOVEMENT_PENALTY_PER_TILE							= iniReader.ReadFloat("Shooting Mechanism","MOVEMENT_PENALTY_PER_TILE",1.0, 0.0, 10.0);

	gGameCTHConstants.PRE_RECOIL_WIS									= iniReader.ReadFloat("Shooting Mechanism","PRE_RECOIL_WIS",2.0, 0.0, 100.0);
	gGameCTHConstants.PRE_RECOIL_EXP_LEVEL								= iniReader.ReadFloat("Shooting Mechanism","PRE_RECOIL_EXP_LEVEL",3.0, 0.0, 100.0);
	gGameCTHConstants.PRE_RECOIL_AUTO_WEAPONS_SKILL						= iniReader.ReadFloat("Shooting Mechanism","PRE_RECOIL_AUTO_WEAPONS_SKILL",2.0, 1.0, 100.0);

	gGameCTHConstants.RECOIL_MAX_COUNTER_STR							= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_STR",3.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_MAX_COUNTER_AGI							= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_AGI",1.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_MAX_COUNTER_EXP_LEVEL						= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_EXP_LEVEL",1.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_MAX_COUNTER_FORCE							= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_FORCE",5.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_MAX_COUNTER_CROUCH							= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_CROUCH",10.0, -100.0, 100.0);
	gGameCTHConstants.RECOIL_MAX_COUNTER_PRONE							= iniReader.ReadFloat("Shooting Mechanism","RECOIL_MAX_COUNTER_PRONE",25.0, -100.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_MIN_ERROR					= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_MIN",0.2f, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_DEX						= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_DEX",3.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_WIS						= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_WIS",1.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_AGI						= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_AGI",1.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_EXP_LEVEL					= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_EXP_LEVEL",2.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_AUTO_WEAPONS_DIVISOR		= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_AUTO_WEAPONS_DIVISOR",2.0, 1.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_TRACER_BONUS				= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_TRACER_BONUS",10.0, -1000.0, 1000.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_ANTICIPATION				= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_ANTICIPATION",25.0, -1000.0, 1000.0);
	gGameCTHConstants.RECOIL_COUNTER_ACCURACY_COMPENSATION				= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_ACCURACY_COMPENSATION",2.0, 0.0, 5.0);
	gGameCTHConstants.RECOIL_COUNTER_FREQUENCY_AGI						= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_FREQUENCY_AGI",3.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_FREQUENCY_EXP_LEVEL				= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_FREQUENCY_EXP_LEVEL",2.0, 0.0, 100.0);
	gGameCTHConstants.RECOIL_COUNTER_FREQUENCY_AUTO_WEAPONS_DIVISOR		= iniReader.ReadFloat("Shooting Mechanism","RECOIL_COUNTER_FREQUENCY_AUTO_WEAPONS_DIVISOR",2.0, -1000.0, 1000.0);

	gGameCTHConstants.RECOIL_COUNTER_INCREMENT							= iniReader.ReadInteger("Shooting Mechanism","RECOIL_COUNTER_INCREMENT",20, 0, 100);
	gGameCTHConstants.RECOIL_COUNTER_INCREMENT_TRACER					= iniReader.ReadInteger("Shooting Mechanism","RECOIL_COUNTER_INCREMENT_TRACER",25, 0, 100);
	gGameCTHConstants.NORMAL_RECOIL_DISTANCE							= iniReader.ReadInteger("Shooting Mechanism","NORMAL_RECOIL_DISTANCE",140, 10, 10000);
	gGameCTHConstants.MAX_BULLET_DEV					 				= iniReader.ReadFloat("Shooting Mechanism","MAX_BULLET_DEV ",10.0, -1000.0, 1000.0);
	gGameCTHConstants.RANGE_EFFECTS_DEV					 				= iniReader.ReadBoolean("Shooting Mechanism","RANGE_EFFECTS_DEV",  TRUE  );
	gGameCTHConstants.MAX_EFFECTIVE_RANGE_MULTIPLIER	 				= iniReader.ReadFloat("Shooting Mechanism","MAX_EFFECTIVE_RANGE_MULTIPLIER",1.1f, 0.5f, 10.0f);
	gGameCTHConstants.MAX_EFFECTIVE_RANGE_REDUCTION	 					= iniReader.ReadFloat("Shooting Mechanism","MAX_EFFECTIVE_RANGE_REDUCTION",0.5f, 0.0f, 1.0f);
	gGameCTHConstants.MAX_EFFECTIVE_USE_GRADIENT						= iniReader.ReadBoolean("Shooting Mechanism","MAX_EFFECTIVE_USE_GRADIENT",  FALSE );
}

void FreeGameExternalOptions()
{
	if (gGameExternalOptions.iaIMPSlots != NULL) // OJW - 20081129 - Fix memory leak when calling LoadGameExternalOptions twice
	MemFree( gGameExternalOptions.iaIMPSlots);
}

BOOLEAN GetCDLocation( )
{
	UINT32	uiStrngLength = 0;
	CHAR8		zCdLocation[ SGPFILENAME_LEN ];
	UINT32	uiRetVal=0;

	//Do a crude check to make sure the Ja2.ini file is the right on

	uiRetVal = GetPrivateProfileString( "Ja2 Settings","CD", "", zCdLocation, SGPFILENAME_LEN, GAME_INI_FILE );
	if( uiRetVal == 0 || !IsDriveLetterACDromDrive( zCdLocation ) )
	{
		// the user most likely doesnt have the file, or the user has messed with the file
		// build a new one

		//First delete the old file
		// Snap: don't clobber the INI file!
		//FileDelete( GAME_INI_FILE );

		//Get the location of the cdrom drive
		if( GetCDromDriveLetter( zCdLocation ) )
		{
			CHAR8		*pTemp;

			//if it succeeded
			pTemp = strrchr( zCdLocation, ':' );
			pTemp[0] = '\0';
		}
		else
		{
			//put in a default location
			sprintf( zCdLocation, "c" );
		}

		//Now create a new file
		WritePrivateProfileString( "Ja2 Settings", "CD", zCdLocation, GAME_INI_FILE );

		GetPrivateProfileString( "Ja2 Settings","CD", "", zCdLocation, SGPFILENAME_LEN, GAME_INI_FILE );
	}

	uiStrngLength = strlen( zCdLocation );

	//if the string length is less the 1 character, it is a drive letter
	if( uiStrngLength == 1 )
	{
		sprintf( gzCdDirectory, "%s:\\%s", zCdLocation, CD_ROOT_DIR );
	}

	//else it is most likely a network location
	else if( uiStrngLength > 1 )
	{
		sprintf( gzCdDirectory, "%s\\%s", zCdLocation, CD_ROOT_DIR );
	}
	else
	{
		//no path was entered
		gzCdDirectory[ 0 ] = '.';
	}

	return( TRUE );
}



BOOLEAN GetCDromDriveLetter( STR8	pString )
{
	UINT32	uiSize=0;
	UINT8		ubCnt=0;
	CHAR8		zDriveLetters[512];
	CHAR8		zDriveLetter[16];
	UINT32	uiDriveType;

	uiSize = GetLogicalDriveStrings( 512, zDriveLetters );

	for( ubCnt=0;ubCnt<uiSize;ubCnt++ )
	{
		//if the current char is not null
		if( zDriveLetters[ ubCnt ] != '\0' )
		{
			//get the string
			zDriveLetter[ 0 ] = zDriveLetters[ ubCnt ];
			ubCnt++;
			zDriveLetter[ 1 ] = zDriveLetters[ ubCnt ];
			ubCnt++;
			zDriveLetter[ 2 ] = zDriveLetters[ ubCnt ];

			zDriveLetter[ 3 ] = '\0';

			//Get the drive type
			uiDriveType = GetDriveType( zDriveLetter );
			switch( uiDriveType )
			{
				// The drive is a CD-ROM drive. 
				case DRIVE_CDROM:
					strcpy( pString, zDriveLetter );

					if ( DoJA2FilesExistsOnDrive( pString ) )
					{
						return( TRUE );
					}
					break;

				default:
					break;
			}
		}
	}

	return( FALSE );
}


/*


	//Determine the type of drive the CDrom is on
	uiDriveType = GetDriveType( zCdLocation );
	switch( uiDriveType )
	{
		// The root directory does not exist. 
		case DRIVE_NO_ROOT_DIR:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The root directory does not exist." ) );
			break;


		// The disk can be removed from the drive. 
		case DRIVE_REMOVABLE:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The disk can be removed from the drive." ) );
			break;


		// The disk cannot be removed from the drive. 
		case DRIVE_FIXED:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The disk cannot be removed from the drive." ) );
			break;


		// The drive is a remote (network) drive. 
		case DRIVE_REMOTE: 
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The drive is a remote (network) drive." ) );
			break;


		// The drive is a CD-ROM drive. 
		case DRIVE_CDROM:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The drive is a CD-ROM drive." ) );
			break;


		// The drive is a RAM disk. 
		case DRIVE_RAMDISK:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The drive is a RAM disk." ) );
			break;

	
		// The drive type cannot be determined. 
		case DRIVE_UNKNOWN:
		default:
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("CDrom Info '%s': %s", zCdLocation, "The drive type cannot be determined." ) );
			break;
	}


*/

BOOLEAN CheckIfGameCdromIsInCDromDrive()
{
	CHAR8		zVolumeNameBuffer[512];
	UINT32	uiVolumeSerialNumber=0;
	UINT32	uiMaxComponentLength=0;
	UINT32	uiFileSystemFlags=0;
	CHAR8		zFileSystemNameBuffer[512];
	CHAR8		zCdLocation[ SGPFILENAME_LEN ];
	CHAR8		zCdFile[ SGPFILENAME_LEN ];

	CHAR8		zCdromRootDrive[512];
	UINT32	uiVolumeReturnValue;
	UINT32	uiLastError = ERROR_SUCCESS;

	if( !GetCdromLocationFromIniFile( zCdromRootDrive ) )
		return( FALSE );

	uiVolumeReturnValue = GetVolumeInformation( zCdromRootDrive, zVolumeNameBuffer, 512, (LPDWORD) &uiVolumeSerialNumber, (LPDWORD) &uiMaxComponentLength, (LPDWORD) &uiFileSystemFlags, zFileSystemNameBuffer, 512 );

	if( !uiVolumeReturnValue )
	{
		uiLastError = GetLastError();
	}

	// OK, build filename
	sprintf( zCdFile, "%s%s", zCdLocation, gCheckFilenames[ Random( 2 ) ] );

		//If the cdrom drive is no longer in the drive
	if( uiLastError == ERROR_NOT_READY || ( !FileExists( zCdFile ) ) )
	{
			CHAR8 sString[512];

			//if a game has been started, add the msg about saving the game to a different entry
			if( gTacticalStatus.fHasAGameBeenStarted )
			{
				sprintf( sString, "%S	%S", pMessageStrings[ MSG_INTEGRITY_WARNING ], pMessageStrings[ MSG_CDROM_SAVE_GAME ] );

				SaveGame( SAVE__ERROR_NUM, pMessageStrings[ MSG_CDROM_SAVE ] );
			}
			else
			{
				sprintf( sString, "%S", pMessageStrings[ MSG_INTEGRITY_WARNING ] );
			}

		// ATE: These are ness. due to reference counting
		// in showcursor(). I'm not about to go digging in low level stuff at this
		// point in the game development, so keep these here, as this works...
//		ShowCursor(TRUE);
//		ShowCursor(TRUE);
		ShutdownWithErrorBox( sString );

		//DoTester( );
		//MessageBox(NULL, sString, "Error", MB_OK | MB_ICONERROR	);

			return( FALSE );
	}

	return( TRUE );
}


BOOLEAN GetCdromLocationFromIniFile( STR pRootOfCdromDrive )
{
	UINT32	uiRetVal=0;

	//Do a crude check to make sure the Ja2.ini file is the right on

	uiRetVal = GetPrivateProfileString( "Ja2 Settings","CD", "", pRootOfCdromDrive, SGPFILENAME_LEN, GAME_INI_FILE );
	if( uiRetVal == 0 )
	{
		pRootOfCdromDrive[0] = '\0';
		return( FALSE);
	}
	else
	{
		//add the :\ to the dir
		strcat( pRootOfCdromDrive, ":\\" );
		return( TRUE );
	}
}


void CDromEjectionErrorMessageBoxCallBack( UINT8 bExitValue )
{
	if( bExitValue == MSG_BOX_RETURN_OK )
	{
		guiPreviousOptionScreen = GAME_SCREEN;

		//if we are in a game, save the game
		if( gTacticalStatus.fHasAGameBeenStarted )
		{
			SaveGame( SAVE__ERROR_NUM, pMessageStrings[ MSG_CDROM_SAVE ] );
		}

 		//quit the game
		gfProgramIsRunning = FALSE;
	}
}


BOOLEAN IsDriveLetterACDromDrive( STR pDriveLetter )
{
	UINT32	uiDriveType;
	CHAR8		zRootName[512];

	sprintf( zRootName, "%s:\\", pDriveLetter );

	//Get the drive type
	uiDriveType = GetDriveType( zRootName );
	switch( uiDriveType )
	{
		// The drive is a CD-ROM drive. 
#ifdef JA2BETAVERSION
		case DRIVE_NO_ROOT_DIR:
		case DRIVE_REMOTE:
#endif
		case DRIVE_CDROM:
			return( TRUE );
			break;
	}

	return( FALSE );
}

void DisplayGameSettings( )
{
	//Display the version number
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s (%S)", pMessageStrings[ MSG_VERSION ], zVersionLabel, czVersionNumber );

	//Display the difficulty level
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_DIF_LEVEL_TEXT ], gzGIOScreenText[ gGameOptions.ubDifficultyLevel + GIO_EASY_TEXT - 1 ] );

	//Bobby Ray option
	switch ( gGameOptions.ubBobbyRay )
	{
		case BR_GOOD:
			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_BR_QUALITY_TEXT ], gzGIOScreenText[ GIO_BR_GOOD_TEXT ] );
			break;
		case BR_GREAT:
			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_BR_QUALITY_TEXT ], gzGIOScreenText[ GIO_BR_GREAT_TEXT ] );
			break;
		case BR_EXCELLENT:
			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_BR_QUALITY_TEXT ], gzGIOScreenText[ GIO_BR_EXCELLENT_TEXT ] );
			break;
		case BR_AWESOME:
			ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_BR_QUALITY_TEXT ], gzGIOScreenText[ GIO_BR_AWESOME_TEXT ] );
			break;
	}

		// Kaiden: Following Line was commented out (Extra Bobby Rays Setting always displays Normal.
	//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_BR_QUALITY_TEXT ], gzGIOScreenText[ GIO_BR_GOOD_TEXT ] );
//	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_GAME_SAVE_STYLE_TEXT ], gzGIOScreenText[ GIO_SAVE_ANYWHERE_TEXT + gGameOptions.fIronManMode ] );

	// Tons of Guns Option
	if( gGameOptions.fGunNut )
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_GUN_OPTIONS_TEXT ], gzGIOScreenText[ GIO_GUN_NUT_TEXT ] );
	else
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_GUN_OPTIONS_TEXT ], gzGIOScreenText[ GIO_REDUCED_GUNS_TEXT ] );

	//Sci fi option
	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_GAME_STYLE_TEXT ], gzGIOScreenText[ GIO_REALISTIC_TEXT + gGameOptions.ubGameStyle ] );

	////Timed Turns option
	//// JA2Gold: no timed turns
	//ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, L"%s: %s", gzGIOScreenText[ GIO_TIMED_TURN_TITLE_TEXT ], gzGIOScreenText[ GIO_NO_TIMED_TURNS_TEXT + gGameOptions.fTurnTimeLimit ] );

	if (!is_networked)
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, gzLateLocalizedString[58], CurrentPlayerProgressPercentage(), HighestPlayerProgressPercentage() );

//#ifdef _DEBUG
//	// WDS - Add debug output here
//	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, gzLateLocalizedString[58], CurrentPlayerProgressPercentage(), HighestPlayerProgressPercentage() );
//#endif

	////if( CHEATER_CHEAT_LEVEL() )
	//{
	//	ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, gzLateLocalizedString[58], CurrentPlayerProgressPercentage(), HighestPlayerProgressPercentage() );
	//}
}

BOOLEAN MeanwhileSceneSeen( UINT8 ubMeanwhile )
{
	UINT32	uiCheckFlag;

	if ( ubMeanwhile > 32 || ubMeanwhile > NUM_MEANWHILES )
	{
		return( FALSE );
	}

	uiCheckFlag = 0x1 << ubMeanwhile;

	if ( gGameSettings.uiMeanwhileScenesSeenFlags & uiCheckFlag )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}

BOOLEAN SetMeanwhileSceneSeen( UINT8 ubMeanwhile )
{
	UINT32	uiCheckFlag;

	if ( ubMeanwhile > 32 || ubMeanwhile > NUM_MEANWHILES )
	{
		// can't set such a flag!
		return( FALSE );
	}
	uiCheckFlag = 0x1 << ubMeanwhile;
	gGameSettings.uiMeanwhileScenesSeenFlags |= uiCheckFlag;
	return( TRUE );
}

BOOLEAN	CanGameBeSaved()
{
	//if the iron man mode is on
	if( gGameOptions.fIronManMode )
	{
		//if we are in turn based combat
		if( (gTacticalStatus.uiFlags & TURNBASED) && (gTacticalStatus.uiFlags & INCOMBAT) )
		{
			//no save for you
			return( FALSE );
		}

		//if there are enemies in the current sector
		if( gWorldSectorX != -1 && gWorldSectorY != -1 &&
				gWorldSectorX != 0 && gWorldSectorY != 0 &&
				NumEnemiesInAnySector( gWorldSectorX, gWorldSectorY, gbWorldSectorZ ) > 0 )
		{
			//no save for you
			return( FALSE );
		}

		//All checks failed, so we can save
		return( TRUE );
	}
	else
	{
		return( TRUE );
	}
}
