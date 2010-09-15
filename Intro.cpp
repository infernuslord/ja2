#ifdef PRECOMPILEDHEADERS
	#include "JA2 All.h"
	#include "Intro.h"
	#include "Cinematics.h"
#else
	#include "sgp.h"
	#include "sys globals.h"
	#include "sysutil.h"
	#include "vobject_blitters.h"
	#include "wcheck.h"
	#include "cursors.h"
	#include "font control.h"
	#include "cursor control.h"
	#include "render dirty.h"
	#include "GameScreen.h"
	#include	"Text.h"
	#include	"Utilities.h"
	#include	"WordWrap.h"
	#include "Font Control.h"
	#include "text.h"
	#include "Multi Language Graphic Utils.h"
	#include "Line.h"
	#include "Intro.h"
	#include "Cinematics.h"
	#include "mainmenuscreen.h"
	#include "Music Control.h"
	#include "LibraryDataBase.h"
	#include "english.h"
	#include "Game Init.h"
	#include "Soldier Profile.h"
	#include "soldier profile type.h"
	#include "MessageBoxScreen.h"
#endif

#include <vfs/Core/vfs.h>

#ifdef JA2UB
#include "strategicmap.h"
#include "Map Screen Interface Map.h"
#include "Map Screen Interface.h"
#include "End Game.h"
#include "Cinematics Bink.h"
#endif

extern STR16	gzIntroScreen[];
extern HVSURFACE ghFrameBuffer;

enum
{
	INTRO_TXT__CANT_FIND_INTRO,
};

//ddd


//ggg
BOOLEAN		gfIntroScreenEntry;
BOOLEAN		gfIntroScreenExit;

UINT32		guiIntroExitScreen = INTRO_SCREEN;


extern	BOOLEAN	gfDoneWithSplashScreen;

#ifdef JA2UB
BINKFLIC *gpBinkFlic = NULL;
#else
SMKFLIC *gpSmackFlic = NULL;
#endif

#define		SMKINTRO_FIRST_VIDEO				255
#define		SMKINTRO_NO_VIDEO						-1

//enums for the various smacker files
enum
{
	SMKINTRO_REBEL_CRDT,
	SMKINTRO_OMERTA,
	SMKINTRO_PRAGUE_CRDT,
	SMKINTRO_PRAGUE,

	//there are no more videos shown for the begining


	SMKINTRO_END_END_SPEECH_MIGUEL,
	SMKINTRO_END_END_SPEECH_NO_MIGUEL,
	SMKINTRO_END_HELI_FLYBY,
	SMKINTRO_END_SKYRIDER_HELICOPTER,
	SMKINTRO_END_NOSKYRIDER_HELICOPTER,

	#ifdef JA2UB
	SMKINTRO_SPLASH_SCREEN,
	SMKINTRO_SPLASH_INTERPLAY,

	SMKINTRO_HELI_CRASH_SCENE_1,

	#else
	SMKINTRO_SPLASH_SCREEN,
	SMKINTRO_SPLASH_TALONSOFT,
	#endif
	//there are no more videos shown for the endgame
	SMKINTRO_LAST_END_GAME,
};

INT32	giCurrentIntroBeingPlayed = SMKINTRO_NO_VIDEO;

#ifdef JA2UB
CHAR		*gpzBinkFileNames[] = 
{
	//begining of the game
	"INTRO\\Rebel_cr.smk",
	"INTRO\\Omerta.smk",
	"INTRO\\Prague_cr.smk",
	"INTRO\\Prague.smk",


	//endgame
	"INTRO\\Throne_Mig.smk",
	"INTRO\\Throne_NoMig.smk",
	"INTRO\\Heli_FlyBy.smk",
	"INTRO\\Heli_Sky.smk",
	"INTRO\\Heli_NoSky.smk",

	"INTRO\\SplashScreen.bik",
	"INTRO\\IPLYLogo.bik",

	//Ja25: New vidoes
	"INTRO\\Intro.bik",

	"INTRO\\MissileEnding.bik"
};
#else
CHAR		*gpzSmackerFileNames[] = 
{
	//begining of the game
	"INTRO\\Rebel_cr.smk",
	"INTRO\\Omerta.smk",
	"INTRO\\Prague_cr.smk",
	"INTRO\\Prague.smk",


	//endgame
	"INTRO\\Throne_Mig.smk",
	"INTRO\\Throne_NoMig.smk",
	"INTRO\\Heli_FlyBy.smk",
	"INTRO\\Heli_Sky.smk",
	"INTRO\\Heli_NoSky.smk",

	"INTRO\\SplashScreen.smk",
	"INTRO\\TalonSoftid_endhold.smk",
};
#endif

//enums used for when the intro screen can come up, either begining game intro, or end game cinematic
INT8	gbIntroScreenMode=-1;


extern	void		CDromEjectionErrorMessageBoxCallBack( UINT8 bExitValue );

void	GetIntroScreenUserInput();
BOOLEAN	EnterIntroScreen();
void	RenderIntroScreen();
void	ExitIntroScreen();
void	HandleIntroScreen();
void	PrepareToExitIntroScreen();
INT32 GetNextIntroVideo( UINT32 uiCurrentVideo );
void	StartPlayingIntroFlic( INT32 iIndexOfFlicToPlay );
void	DisplaySirtechSplashScreen();


//ppp


UINT32	IntroScreenInit( void )
{
	//Set so next time we come in, we can set up
	gfIntroScreenEntry = TRUE;

	return( 1 );
}


UINT32	IntroScreenShutdown( void )
{
	return( 1 );
}


UINT32	IntroScreenHandle( void )
{
	if( gfIntroScreenEntry )
	{
		gfIntroScreenEntry = FALSE;
		gfIntroScreenExit = FALSE;

		EnterIntroScreen();
		
		InvalidateRegion( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	}

	RestoreBackgroundRects();


	GetIntroScreenUserInput();

	HandleIntroScreen();

	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

	ExecuteBaseDirtyRectQueue();
	EndFrameBufferRender();


	if( gfIntroScreenExit )
	{
		ExitIntroScreen();
		gfIntroScreenExit = FALSE;
		gfIntroScreenEntry = TRUE;
	}

	return( guiIntroExitScreen );
}


BOOLEAN EnterIntroScreen()
{
	INT32 iFirstVideoID = -1;

	// CLEAR THE FRAME BUFFER
	ClearMainMenu();


	SetCurrentCursorFromDatabase( VIDEO_NO_CURSOR );

	// Don't play music....
	SetMusicMode( MUSIC_NONE );

	// WANNE: No we have an INI option for the choise if the intro should be played
	if (!iPlayIntro)
	{
		PrepareToExitIntroScreen();
		return( TRUE );
	}

//#ifdef JA2BETAVERSION
//	if( FileExists( "..\\NoIntro.txt" ) )
//	{
//		PrepareToExitIntroScreen();
//		return( TRUE );
//	}
//#endif

	//if the library doesnt exist, exit
	if( !IsLibraryOpened( LIBRARY_INTRO ) )
	{
		PrepareToExitIntroScreen();
		return( TRUE );
	}

	//initialize smacker
	#ifdef JA2UB	
	BinkInitialize(  ghWindow, SCREEN_WIDTH, SCREEN_HEIGHT );
	#else
	SmkInitialize( ghWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
	#endif


	//get the index opf the first video to watch
	iFirstVideoID = GetNextIntroVideo( SMKINTRO_FIRST_VIDEO );

	if( iFirstVideoID != -1 )
	{
		StartPlayingIntroFlic( iFirstVideoID );

		guiIntroExitScreen = INTRO_SCREEN;
	}

	//Got no intro video, exit
	else
	{
		PrepareToExitIntroScreen();
	}
	

	return( TRUE );
}

void RenderIntroScreen()
{
}

void ExitIntroScreen()
{

	//shutdown smaker
	#ifdef JA2UB
	BinkShutdownVideo( );
	
	#else
	SmkShutdown();
	#endif
}

void HandleIntroScreen()
{
	BOOLEAN	fFlicStillPlaying = FALSE;

	//if we are exiting this screen, this frame, dont update the screen
	if( gfIntroScreenExit )
		return;


	//handle smaker each frame
	#ifdef JA2UB
	fFlicStillPlaying = BinkPollFlics();
	#else
	fFlicStillPlaying = SmkPollFlics();
	#endif

	//if the flic is not playing
	if( !fFlicStillPlaying )
	{
		INT32 iNextVideoToPlay = -1;

		iNextVideoToPlay = GetNextIntroVideo( giCurrentIntroBeingPlayed );

		if( iNextVideoToPlay != -1 )
		{
			StartPlayingIntroFlic( iNextVideoToPlay );
		}
		else
		{
			PrepareToExitIntroScreen();
			giCurrentIntroBeingPlayed = -1;
		}
	}

	InvalidateScreen();
}



void		GetIntroScreenUserInput()
{
	InputAtom Event;
	POINT  MousePos;


	GetCursorPos(&MousePos);
	ScreenToClient(ghWindow, &MousePos); // In window coords!

	while( DequeueEvent( &Event ) )
	{
		// HOOK INTO MOUSE HOOKS
		switch( Event.usEvent)
	{
			case LEFT_BUTTON_DOWN:
				MouseSystemHook(LEFT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case LEFT_BUTTON_UP:
				MouseSystemHook(LEFT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y ,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_DOWN:
				MouseSystemHook(RIGHT_BUTTON_DOWN, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_UP:
				MouseSystemHook(RIGHT_BUTTON_UP, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case RIGHT_BUTTON_REPEAT:
				MouseSystemHook(RIGHT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
			case LEFT_BUTTON_REPEAT:
				MouseSystemHook(LEFT_BUTTON_REPEAT, (INT16)MousePos.x, (INT16)MousePos.y,_LeftButtonDown, _RightButtonDown);
				break;
		}


		if( Event.usEvent == KEY_UP )
		{
			switch( Event.usParam )
			{
				case ESC:

					// ATE: if in splash, don't exit all!
					#ifdef JA2UB
					BinkCloseFlic( gpBinkFlic );
					if ( gbIntroScreenMode != INTRO_SPLASH )
					{
						PrepareToExitIntroScreen();
					}
					#else
					PrepareToExitIntroScreen();
					#endif
					break;
				case SPACE:
					#ifdef JA2UB
					BinkCloseFlic( gpBinkFlic );
					#else
					SmkCloseFlic( gpSmackFlic );
					#endif
					break;

#ifdef JA2TESTVERSION

				case 'r':
					break;

				case 'i':
					InvalidateRegion( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
					break;

#endif
			}
		}
	}

	// if the user presses either mouse button
	if( gfLeftButtonState || gfRightButtonState )
	{
		//advance to the next flic
		#ifdef JA2UB
		BinkCloseFlic( gpBinkFlic );
		#else
		SmkCloseFlic( gpSmackFlic );
		#endif

	}
}


void PrepareToExitIntroScreen()
{

//Ja25: no begining intro
#ifdef JA2UB
	//if its the heli crash intro 
	if( gbIntroScreenMode == INTRO_HELI_CRASH )
	{
		//go to the init screen
//Ja25: no longer going to initscreen ( cause this is now AFTER mapscreen )
//		guiIntroExitScreen = INIT_SCREEN;

		guiIntroExitScreen = GAME_SCREEN;
		SetCurrentWorldSector( sSelMapX, sSelMapY, ( UINT8 )iCurrentMapSectorZ );
	}
#else
	//if its the intro at the begining of the game
	if( gbIntroScreenMode == INTRO_BEGINING )
	{
		//go to the init screen
		guiIntroExitScreen = INIT_SCREEN;
	}
#endif
	else if( gbIntroScreenMode == INTRO_SPLASH )
	{
		//display a logo when exiting
		DisplaySirtechSplashScreen();

		gfDoneWithSplashScreen = TRUE;
		guiIntroExitScreen = INIT_SCREEN;
	}
#ifdef JA2UB
	else if( gbIntroScreenMode == INTRO_ENDING )
	{
		guiIntroExitScreen = GAME_SCREEN;
		SetCurrentWorldSector( 16, 11, 0 );

		EnterTacticalInFinalSector();

		//Dont leave tactical
		gfEnteringMapScreen = FALSE;
	}
#endif
	else
	{
		//We want to reinitialize the game
		ReStartingGame();

//		guiIntroExitScreen = MAINMENU_SCREEN;
		guiIntroExitScreen = CREDIT_SCREEN;
	}

	gfIntroScreenExit = TRUE;
}


INT32 GetNextIntroVideo( UINT32 uiCurrentVideo )
{
	INT32 iStringToUse = -1;
#ifdef JA2UB
	//switch on whether it is the beginging or the end game video
	switch( gbIntroScreenMode )
	{
		case INTRO_HELI_CRASH:
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_HELI_CRASH_SCENE_1;
					break;
			}
			break;

		//end game
		case INTRO_ENDING:
		{
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_LAST_END_GAME;
					break;
			}
		}
		break;

		case INTRO_SPLASH:
				switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
				iStringToUse = SMKINTRO_SPLASH_SCREEN;
				break;
			}				
		break;
	}
	
#else
	//switch on whether it is the beginging or the end game video
	switch( gbIntroScreenMode )
	{
		//the video at the begining of the game
		case INTRO_BEGINING:
		{
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_REBEL_CRDT;
					break;
				case SMKINTRO_REBEL_CRDT:
					iStringToUse = SMKINTRO_OMERTA;
					break;
				case SMKINTRO_OMERTA:
					iStringToUse = SMKINTRO_PRAGUE_CRDT;
					break;
				case SMKINTRO_PRAGUE_CRDT:
					iStringToUse = SMKINTRO_PRAGUE;
					break;
				case SMKINTRO_PRAGUE:
					iStringToUse = -1;
					break;
//				case SMKINTRO_LAST_INTRO:
//					iStringToUse = -1;
//					break;
			}
		}
		break;

		//end game
		case INTRO_ENDING:
		{
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					//if Miguel is dead, play the flic with out him in it
					if( gMercProfiles[ MIGUEL ].bMercStatus == MERC_IS_DEAD )
						iStringToUse = SMKINTRO_END_END_SPEECH_NO_MIGUEL;
					else
						iStringToUse = SMKINTRO_END_END_SPEECH_MIGUEL;
					break;

				case SMKINTRO_END_END_SPEECH_MIGUEL:
				case SMKINTRO_END_END_SPEECH_NO_MIGUEL:
					iStringToUse = SMKINTRO_END_HELI_FLYBY;
					break;

				//if SkyRider is dead, play the flic without him
				case SMKINTRO_END_HELI_FLYBY:
					if( gMercProfiles[ SKYRIDER ].bMercStatus == MERC_IS_DEAD )
						iStringToUse = SMKINTRO_END_NOSKYRIDER_HELICOPTER;
					else
						iStringToUse = SMKINTRO_END_SKYRIDER_HELICOPTER;
					break;
			}
		}
		break;

		case INTRO_SPLASH:
			switch( uiCurrentVideo )
			{
				case SMKINTRO_FIRST_VIDEO:
					iStringToUse = SMKINTRO_SPLASH_SCREEN;
					break;
				case SMKINTRO_SPLASH_SCREEN:
					//iStringToUse = SMKINTRO_SPLASH_TALONSOFT;
					break;
			}
			break;
	}
#endif

	return( iStringToUse );
}


void StartPlayingIntroFlic( INT32 iIndexOfFlicToPlay )
{


	if( iIndexOfFlicToPlay != -1 )
	{
		//start playing a flic
		#ifdef JA2UB
		gpBinkFlic = BinkPlayFlic( gpzBinkFileNames[ iIndexOfFlicToPlay ], (SCREEN_WIDTH-640)/2, (SCREEN_HEIGHT-480)/2, BINK_FLIC_AUTOCLOSE | BINK_FLIC_CENTER_VERTICAL );
		#else
		gpSmackFlic = SmkPlayFlic( gpzSmackerFileNames[ iIndexOfFlicToPlay ], (SCREEN_WIDTH-640)/2, (SCREEN_HEIGHT-480)/2, TRUE );
		#endif

		#ifdef JA2UB
		if( gpBinkFlic != NULL )
		#else
		if( gpSmackFlic != NULL )
		#endif
		{
			giCurrentIntroBeingPlayed = iIndexOfFlicToPlay;
		}
		else
		{
			//do a check
#ifdef JA2BETAVERSION
			PrepareToExitIntroScreen();
#else

			DoScreenIndependantMessageBox( gzIntroScreen[INTRO_TXT__CANT_FIND_INTRO], MSG_BOX_FLAG_OK, CDromEjectionErrorMessageBoxCallBack );
#endif
		}
	}
}


void SetIntroType( INT8 bIntroType )
{
#ifdef JA2UB
	if( bIntroType == INTRO_HELI_CRASH )
	{
		gbIntroScreenMode = INTRO_HELI_CRASH;
	}
#else
	if( bIntroType == INTRO_BEGINING )
	{
		gbIntroScreenMode = INTRO_BEGINING;
	}
#endif
	else if( bIntroType == INTRO_ENDING )
	{
		gbIntroScreenMode = INTRO_ENDING;
	}
	else if( bIntroType == INTRO_SPLASH )
	{
		gbIntroScreenMode = INTRO_SPLASH;
	}
}


void DisplaySirtechSplashScreen()
{
	HVOBJECT hPixHandle;
	VOBJECT_DESC	VObjectDesc;
	UINT32 uiLogoID;

	UINT32										uiDestPitchBYTES;
	UINT8											*pDestBuf;


	// CLEAR THE FRAME BUFFER
	pDestBuf = LockVideoSurface( FRAME_BUFFER, &uiDestPitchBYTES );
	memset(pDestBuf, 0, SCREEN_HEIGHT * uiDestPitchBYTES );
	UnLockVideoSurface( FRAME_BUFFER );


	memset( &VObjectDesc, 0, sizeof( VOBJECT_DESC ) );
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("INTERFACE\\SirtechSplash.sti", VObjectDesc.ImageFile);

//	FilenameForBPP("INTERFACE\\TShold.sti", VObjectDesc.ImageFile);
	if( !AddVideoObject(&VObjectDesc, &uiLogoID) )
	{
		FilenameForBPP("GERMAN\\SPLASH_GERMAN.sti", VObjectDesc.ImageFile);
	if( !AddVideoObject(&VObjectDesc, &uiLogoID) )
	{
		/*
		* This is the place, where most non english coders stranding.
		* Don't hesitate, don't give up!
		* I'll now tell You what You made wrong
		*								(2006-10-10, Sergeant_Kolja)
		*/
		#ifdef _DEBUG
		#	if defined(ENGLISH)
			AssertMsg( 0, String( "Wheter English nor German works. May be You built English - but have only German or other foreign Disk?" ) );
		#	elif defined(GERMAN)
			AssertMsg( 0, String( "Weder Englisch noch Deutsch geht. Deutsche Version kompiliert und mit englischer CDs gestartet? Das geht nicht!" ) );
		#	endif
		#endif
		AssertMsg( 0, String( "Failed to load %s", VObjectDesc.ImageFile ) );
		return;
	}
	}

	GetVideoObject(&hPixHandle, uiLogoID);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,(SCREEN_WIDTH-640)/2, (SCREEN_HEIGHT-480)/2, VO_BLT_SRCTRANSPARENCY,NULL);
	DeleteVideoObjectFromIndex(uiLogoID);


	InvalidateScreen();
	RefreshScreen( NULL );
}
