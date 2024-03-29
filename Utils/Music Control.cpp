#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
#else
	#include "types.h"
	#include "Music Control.h"
	#include "soundman.h"
	#include "Random.h"
	#include "gamescreen.h"
	#include "jascreens.h"
	#include "Creature Spreading.h"
	#include "overhead.h"
	#include "timer control.h"
	#include "strategicmap.h"
	#include "fade screen.h"
#endif

//extern int iScreenMode;

static UINT32 uiMusicHandle = NO_SAMPLE;
static BOOLEAN fMusicPlaying = FALSE;

static BOOLEAN fMusicFadingOut = FALSE;
static BOOLEAN fMusicFadingIn = FALSE;
static UINT32 uiMusicVolume = 50;

static BOOLEAN gfMusicEnded = FALSE;

static UINT8 gubMusicMode = 0;

static UINT8 gubOldMusicMode = 0;

static INT8 gbVictorySongCount = 0;
static INT8 gbDeathSongCount = 0;

static INT8 bNothingModeSong;
static INT8 bEnemyModeSong;
static INT8 bBattleModeSong;

static BOOLEAN gfUseCreatureMusic = FALSE;

static INT8 gbFadeSpeed = 1;

static BOOLEAN gfDontRestartSong = FALSE;
// unused
//BOOLEAN	gfForceMusicToTense = FALSE;


CHAR8 *szMusicList[NUM_MUSIC]=
{
	"MUSIC\\marimbad 2.wav",
	"MUSIC\\menumix1.wav",
	"MUSIC\\nothing A.wav",
	"MUSIC\\nothing B.wav",
	"MUSIC\\nothing C.wav",
	"MUSIC\\nothing D.wav",
	"MUSIC\\tensor A.wav",
	"MUSIC\\tensor B.wav",
	"MUSIC\\tensor C.wav",
	"MUSIC\\triumph.wav",
	"MUSIC\\death.wav",
	"MUSIC\\battle A.wav",
	"MUSIC\\tensor B.wav",
	"MUSIC\\creepy.wav",
	"MUSIC\\creature battle.wav",
};

BOOLEAN StartMusicBasedOnMode(void);
void DoneFadeOutDueToEndMusic(void);
void MusicStopCallback(void *pData);
BOOLEAN MusicStop(void);
BOOLEAN MusicFadeOut(void);
BOOLEAN MusicFadeIn(void);

//extern void HandleEndDemoInCreatureLevel( );

//BOOLEAN NoEnemiesInSight( )
//{
//	SOLDIERTYPE			 *pSoldier;
//	INT32										cnt;
//
//	// Loop through our guys
//	// End the turn of player charactors
//	cnt = gTacticalStatus.Team[ gbPlayerNum ].bFirstID;
//
//	// look for all mercs on the same team,
//	for ( pSoldier = MercPtrs[ cnt ]; cnt <= gTacticalStatus.Team[ gbPlayerNum ].bLastID; cnt++, pSoldier++ )
//	{
//		if ( pSoldier->bActive && pSoldier->stats.bLife >= OKLIFE )
//		{
//			if ( pSoldier->aiData.bOppCnt != 0 )
//			{
//				return( FALSE );
//			}
//		}
//	}
//
//	return( TRUE );
//}



//********************************************************************************
// MusicPlay
//
//		Starts up one of the tunes in the music list.
//
//	Returns:	TRUE if the music was started, FALSE if an error occurred
//
//********************************************************************************
BOOLEAN MusicPlay(UINT32 uiNum)
{
	// WANNE: We want music in windowed mode
	//if( 1==iScreenMode ) /* on Windowed mode, skip the music? was coded for WINDOWED_MODE that way...*/
	//return FALSE;

	SOUNDPARMS spParms;

	if(fMusicPlaying)
		MusicStop();

	memset(&spParms, 0xff, sizeof(SOUNDPARMS));
	spParms.uiPriority = PRIORITY_MAX;
	spParms.uiVolume = 0;
	spParms.uiLoop = 1;	// Lesh: only 1 line added

	spParms.EOSCallback = MusicStopCallback;

	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, "About to call SoundPlayStreamedFile" );

	uiMusicHandle = SoundPlayStreamedFile(szMusicList[uiNum], &spParms);

	if(uiMusicHandle != SOUND_ERROR)
	{
		//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music PLay %d %d", uiMusicHandle, gubMusicMode	) );

		gfMusicEnded = FALSE;
		fMusicPlaying = TRUE;
		MusicFadeIn();
		return TRUE;
	}

	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music PLay %d %d", uiMusicHandle, gubMusicMode	) );
	return FALSE;
}

//********************************************************************************
// MusicSetVolume
//
//		Sets the volume on the currently playing music.
//
//	Returns:	TRUE if the volume was set, FALSE if an error occurred
//
//********************************************************************************
BOOLEAN MusicSetVolume(UINT32 uiVolume)
{
	INT32 uiOldMusicVolume = uiMusicVolume;

	// WANNE: We want music in windowed mode
	//if( 1==iScreenMode ) /* on Windowed mode, skip the music? was coded for WINDOWED_MODE that way...*/
	//return FALSE;

	uiMusicVolume = __min(uiVolume, 127);

	if(uiMusicHandle != NO_SAMPLE)
	{
		// get volume and if 0 stop music!
		if (uiMusicVolume == 0)
		{
			gfDontRestartSong = TRUE;
			MusicStop();
			return TRUE;
		}

		SoundSetVolume(uiMusicHandle, uiMusicVolume);

		return TRUE;
	}

	// If here, check if we need to re-start music
	// Have we re-started?
	if (uiMusicVolume > 0 && uiOldMusicVolume == 0)
	{
		StartMusicBasedOnMode();
	}

	return FALSE;
}

//********************************************************************************
// MusicGetVolume
//
//		Gets the volume on the currently playing music.
//
//	Returns:	TRUE if the volume was set, FALSE if an error occurred
//
//********************************************************************************
UINT32 MusicGetVolume(void)
{
	return uiMusicVolume;
}

//********************************************************************************
// MusicStop
//
//		Stops the currently playing music.
//
//	Returns:	TRUE if the music was stopped, FALSE if an error occurred
//
//********************************************************************************
static BOOLEAN MusicStop(void)
{
	// WANNE: We want music in windowed mode
	//if( 1==iScreenMode ) /* on Windowed mode, skip the music? was coded for WINDOWED_MODE that way...*/
	//	return(FALSE);

	if(uiMusicHandle != NO_SAMPLE)
	{
		//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music Stop %d %d", uiMusicHandle, gubMusicMode ) );

		SoundStop(uiMusicHandle);
		fMusicPlaying = FALSE;
		uiMusicHandle = NO_SAMPLE;
		return TRUE;
	}

	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music Stop %d %d", uiMusicHandle, gubMusicMode ) );
	return FALSE;
}

//********************************************************************************
// MusicFadeOut
//
//		Fades out the current song.
//
//	Returns:	TRUE if the music has begun fading, FALSE if an error occurred
//
//********************************************************************************
static BOOLEAN MusicFadeOut(void)
{
	if(uiMusicHandle != NO_SAMPLE)
	{
		fMusicFadingOut = TRUE;
		return TRUE;
	}
	return FALSE;
}

//********************************************************************************
// MusicFadeIn
//
//		Fades in the current song.
//
//	Returns:	TRUE if the music has begun fading in, FALSE if an error occurred
//
//********************************************************************************
static BOOLEAN MusicFadeIn(void)
{
	if(uiMusicHandle != NO_SAMPLE)
	{
		fMusicFadingIn = TRUE;
		return TRUE;
	}
	return FALSE;
}

//********************************************************************************
// MusicPoll
//
//		Handles any maintenance the music system needs done. Should be polled from
//	the main loop, or somewhere with a high frequency of calls.
//
//	Returns:	TRUE always
//
//********************************************************************************
BOOLEAN MusicPoll(BOOLEAN /*fForce*/)
{
	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll");

	// WANNE: We want music in windowed mode
	//if( 1==iScreenMode ) /* on Windowed mode, skip the music? was coded for WINDOWED_MODE that way...*/
	//	return(TRUE);

	INT32 iVol;

	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: SoundServiceStreams ");
	SoundServiceStreams();
	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: SoundServiceRandom ");
	SoundServiceRandom();

	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: Handle Sound every sound overhead time");
	// Handle Sound every sound overhead time....
	if (COUNTERDONE(MUSICOVERHEAD))
	{
		//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: Reset counter");
		// Reset counter
		RESETCOUNTER(MUSICOVERHEAD);

		if (fMusicFadingIn)
		{
			//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: music fading in");
			if(uiMusicHandle != NO_SAMPLE)
			{
				iVol = SoundGetVolume(uiMusicHandle);
				iVol = __min( (INT32)uiMusicVolume, iVol+gbFadeSpeed );
				SoundSetVolume(uiMusicHandle, iVol);
				if(iVol == (INT32)uiMusicVolume)
				{
					fMusicFadingIn = FALSE;
					gbFadeSpeed = 1;
				}
			}
		}
		else if (fMusicFadingOut)
		{
			//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: music fading out");
			if(uiMusicHandle != NO_SAMPLE)
			{
				iVol = SoundGetVolume(uiMusicHandle);
				iVol = (iVol >=1)? iVol-gbFadeSpeed : 0;

				iVol = __max( (INT32)iVol, 0 );

				SoundSetVolume(uiMusicHandle, iVol);
				if(iVol == 0)
				{
					MusicStop();
					fMusicFadingOut = FALSE;
					gbFadeSpeed = 1;
				}
			}
		}

		if (gfMusicEnded)
		{
			//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: music ended");
			// OK, based on our music mode, play another!
			//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music End Loop %d %d", uiMusicHandle, gubMusicMode ) );

			// If we were in victory mode, change!
			if (gbVictorySongCount == 1 || gbDeathSongCount == 1)
			{
				if (gbDeathSongCount == 1 && guiCurrentScreen == GAME_SCREEN)
				{
					CheckAndHandleUnloadingOfCurrentWorld();
				}

				if (gbVictorySongCount == 1)
				{
					SetMusicMode(MUSIC_TACTICAL_NOTHING);
				}
			}
			else
			{
				if (!gfDontRestartSong)
				{
					//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll: don't restart song, StartMusicBasedOnMode");
					StartMusicBasedOnMode();
				}
			}

			gfMusicEnded = FALSE;
			gfDontRestartSong = FALSE;
		}
	}

	//DebugMsg (TOPIC_JA2,DBG_LEVEL_3,"MusicPoll done");
	return TRUE;
}


static BOOLEAN SetMusicMode(UINT8 ubMusicMode, BOOLEAN fForce)
{
	static INT8 bPreviousMode = 0;

	// OK, check if we want to restore
	if (ubMusicMode == MUSIC_RESTORE)
	{
		if (bPreviousMode == MUSIC_TACTICAL_VICTORY || bPreviousMode == MUSIC_TACTICAL_DEATH)
		{
			bPreviousMode = MUSIC_TACTICAL_NOTHING;
		}

		ubMusicMode = bPreviousMode;
	}
	else
	{
		// Save previous mode...
		bPreviousMode = gubOldMusicMode;
	}

	// if different, start a new music song
	if (fForce || gubOldMusicMode != ubMusicMode)
	{
		// Set mode....
		gubMusicMode = ubMusicMode;

		//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music New Mode %d %d", uiMusicHandle, gubMusicMode	) );

		gbVictorySongCount = 0;
		gbDeathSongCount = 0;

		if(uiMusicHandle != NO_SAMPLE)
		{
			// Fade out old music
			MusicFadeOut();
		}
		else
		{
			// Change music!
			StartMusicBasedOnMode();
		}
	}

	gubOldMusicMode = gubMusicMode;

	return TRUE;
}


static BOOLEAN StartMusicBasedOnMode(void)
{
	static BOOLEAN fFirstTime = TRUE;

	if (fFirstTime)
	{
		fFirstTime = FALSE;

		bNothingModeSong = (INT8) (NOTHING_A_MUSIC + Random(4));
		bEnemyModeSong = (INT8) (TENSOR_A_MUSIC + Random(3));
		bBattleModeSong = (INT8) (BATTLE_A_MUSIC + Random(2));
	}


	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "StartMusicBasedOnMode() %d %d", uiMusicHandle, gubMusicMode ) );

	// Setup a song based on mode we're in!
	switch(gubMusicMode)
	{
		case MUSIC_MAIN_MENU:
			// ATE: Don't fade in
			gbFadeSpeed = (INT8)uiMusicVolume;
			MusicPlay(MENUMIX_MUSIC);
			break;

		case MUSIC_LAPTOP:
			gbFadeSpeed = (INT8)uiMusicVolume;
			MusicPlay(MARIMBAD2_MUSIC);
			break;

		case MUSIC_TACTICAL_NOTHING:
			// ATE: Don't fade in
			gbFadeSpeed = (INT8)uiMusicVolume;
			if(gfUseCreatureMusic)
			{
				MusicPlay(CREEPY_MUSIC);
			}
			else
			{
				MusicPlay(bNothingModeSong);
				bNothingModeSong = (INT8) (NOTHING_A_MUSIC + Random(4));
			}
			break;

		case MUSIC_TACTICAL_ENEMYPRESENT:
			// ATE: Don't fade in EnemyPresent...
			gbFadeSpeed = (INT8)uiMusicVolume;
			if(gfUseCreatureMusic)
			{
				MusicPlay(CREEPY_MUSIC);
			}
			else
			{
				MusicPlay(bEnemyModeSong);
				bEnemyModeSong = (INT8) (TENSOR_A_MUSIC + Random(3));
			}
			break;

		case MUSIC_TACTICAL_BATTLE:
			// ATE: Don't fade in
			gbFadeSpeed = (INT8)uiMusicVolume;
			if(gfUseCreatureMusic)
			{
				MusicPlay(CREATURE_BATTLE_MUSIC);
			}
			else
			{
				MusicPlay(bBattleModeSong);
			}
			bBattleModeSong = (INT8) (BATTLE_A_MUSIC + Random(2));
			break;

		case MUSIC_TACTICAL_VICTORY:

			// ATE: Don't fade in EnemyPresent...
			gbFadeSpeed = (INT8)uiMusicVolume;
			MusicPlay(TRIUMPH_MUSIC);
			gbVictorySongCount++;

			if(gfUseCreatureMusic && !gbWorldSectorZ)
			{
				//We just killed all the creatures that just attacked the town.
				gfUseCreatureMusic = FALSE;
			}
			break;

		case MUSIC_TACTICAL_DEATH:

			// ATE: Don't fade in EnemyPresent...
			gbFadeSpeed = (INT8)uiMusicVolume;
			MusicPlay(DEATH_MUSIC);
			gbDeathSongCount++;
			break;

		default:
			MusicFadeOut();
			break;
	}

	return TRUE;
}

BOOLEAN SetMusicMode(UINT8 ubMusicMode)
{
	return SetMusicMode(ubMusicMode, FALSE);
}

static void MusicStopCallback(void *pData)
{
	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String( "Music EndCallback %d %d", uiMusicHandle, gubMusicMode	) );

	gfMusicEnded = TRUE;
	uiMusicHandle = NO_SAMPLE;

	//DebugMsg( TOPIC_JA2, DBG_LEVEL_3, "Music EndCallback completed" );
}


void SetMusicFadeSpeed(INT8 bFadeSpeed)
{
	gbFadeSpeed = bFadeSpeed;
}

UINT8 GetMusicMode(void)
{
	return gubMusicMode;
}

BOOLEAN UsingCreatureMusic(void)
{
	return gfUseCreatureMusic;
}

void UseCreatureMusic(BOOLEAN fUseCreatureMusic)
{
	if (gfUseCreatureMusic != fUseCreatureMusic)
	{
		// this means a change
		gfUseCreatureMusic = fUseCreatureMusic;
		SetMusicMode(gubMusicMode, TRUE);	// same as before
	}
}

BOOLEAN IsMusicPlaying(void)
{
	return fMusicPlaying;
}

UINT32 GetMusicHandle(void)
{
	return uiMusicHandle;
}

// unused
//void FadeMusicForXSeconds( UINT32 uiDelay )
//{
//	INT16 sNumTimeSteps, sNumVolumeSteps;
//
//	// get # time steps in delay....
//	sNumTimeSteps = (INT16)( uiDelay / 10 );
//
//	// Devide this by music volume...
//	sNumVolumeSteps = (INT16)( uiMusicVolume / sNumTimeSteps );
//
//	// Set fade delay...
//	SetMusicFadeSpeed( (INT8)sNumVolumeSteps );
//}

// unused
//void	DoneFadeOutDueToEndMusic( void )
//{
//	// Quit game....
//	InternalLeaveTacticalScreen( MAINMENU_SCREEN );
//	//SetPendingNewScreen( MAINMENU_SCREEN );
//}


