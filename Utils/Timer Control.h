#ifndef __TIMER_CONTROL_H
#define __TIMER_CONTROL_H

#ifndef CALLBACKTIMER
#define		CALLBACKTIMER
#endif

typedef INT32		TIMECOUNTER;

//typedef void (__stdcall *JA2_TIMERPROC)( UINT32 uiID, UINT32 uiMsg, UINT32 uiUser, UINT32 uiDw1, UINT32 uiDw2 );

typedef void (*CUSTOMIZABLE_TIMER_CALLBACK) ( void );

// CALLBACK TIMER DEFINES
enum
{
	ITEM_LOCATOR_CALLBACK,
	NUM_TIMER_CALLBACKS
};

#define	TILE_ANIM__NORMAL_SPEED				200
#define	TILE_ANIM__FAST_SPEED					30


// TIMER DEFINES
enum
{
	TOVERHEAD = 0,											// Overhead time slice
	NEXTSCROLL,													// Scroll Speed timer
	STARTSCROLL,												// Scroll Start timer
	ANIMATETILES,												// Animate tiles timer
	FPSCOUNTER,													// FPS value
	PATHFINDCOUNTER,										// PATH FIND COUNTER
	CURSORCOUNTER,											// ANIMATED CURSOR
	RMOUSECLICK_DELAY_COUNTER,					// RIGHT BUTTON CLICK DELAY
	LMOUSECLICK_DELAY_COUNTER,					// LEFT	BUTTON CLICK DELAY
	SLIDETEXT,													// DAMAGE DISPLAY				
	TARGETREFINE,												// TARGET REFINE
	CURSORFLASH,												// Cursor/AP flash
	FADE_GUY_OUT,												// FADE MERCS OUT
	PANELSLIDE_UNUSED,									// PANLE SLIDE
	TCLOCKUPDATE,												// CLOCK UPDATE
	PHYSICSUPDATE,											// PHYSICS UPDATE.
	GLOW_ENEMYS,
	STRATEGIC_OVERHEAD,									// STRATEGIC OVERHEAD
	CYCLERENDERITEMCOLOR,								// CYCLE COLORS
	NONGUNTARGETREFINE,									// TARGET REFINE
	CURSORFLASHUPDATE,									// 
	INVALID_AP_HOLD,										// TIME TO HOLD INVALID AP
	RADAR_MAP_BLINK,										// BLINK DELAY FOR RADAR MAP
	OVERHEAD_MAP_BLINK,									// OVERHEADMAP
	MUSICOVERHEAD,											// MUSIC TIMER
	RUBBER_BAND_START_DELAY,
	NUMTIMERS
};

// Base resultion of callback timer
#define		BASETIMESLICE												10				

// TIMER INTERVALS
extern INT32	giTimerIntervals[ NUMTIMERS ];
// TIMER COUNTERS
extern INT32	giTimerCounters[ NUMTIMERS ];

// GLOBAL SYNC TEMP TIME
extern INT32	giClockTimer;
extern INT32	giTimerDiag;
extern INT32	giTimerTeamTurnUpdate;


// Functions
BOOLEAN InitializeJA2Clock( void );
void	ShutdownJA2Clock( void );

#define GetJA2Clock()						guiBaseJA2Clock

UINT32	GetPauseJA2Clock( );

UINT32 InitializeJA2TimerID( UINT32 uiDelay, UINT32 uiCallbackID, UINT32 uiUser );
void	RemoveJA2TimerCallback( UINT32 uiTimer );

void PauseTime( BOOLEAN fPaused );

void SetCustomizableTimerCallbackAndDelay( INT32 iDelay, CUSTOMIZABLE_TIMER_CALLBACK pCallback, BOOLEAN fReplace );
void CheckCustomizableTimer( void );

//Don't modify this value
extern UINT32	guiBaseJA2Clock;
extern UINT32	guiBaseJA2NoPauseClock;
extern CUSTOMIZABLE_TIMER_CALLBACK gpCustomizableTimerCallback;

// MACROS
//																CHeck if new counter < 0														| set to 0 |										Decrement

#ifdef CALLBACKTIMER

#define	UPDATECOUNTER( c )						( ( giTimerCounters[ c ] - BASETIMESLICE ) < 0 ) ?	( giTimerCounters[ c ] = 0 ) : ( giTimerCounters[ c ] -= BASETIMESLICE )	
#define	RESETCOUNTER( c )							( giTimerCounters[ c ] = giTimerIntervals[ c ] )
#define	COUNTERDONE( c )							( giTimerCounters[ c ] == 0 ) ? TRUE : FALSE

#define	UPDATETIMECOUNTER( c )				( ( c - BASETIMESLICE ) < 0 ) ?	( c = 0 ) : ( c -= BASETIMESLICE )	
#define		RESETTIMECOUNTER( c, d )			( c = d )

#ifdef BOUNDS_CHECKER
	#define	TIMECOUNTERDONE( c, d )				( TRUE )
#else
	#define	TIMECOUNTERDONE( c, d )				( c == 0 ) ? TRUE : FALSE
#endif

#define		SYNCTIMECOUNTER( )
#define		ZEROTIMECOUNTER( c )			( c = 0 )

#else

#define	UPDATECOUNTER( c )				
#define	RESETCOUNTER( c )							( giTimerCounters[ c ] = giClockTimer )
#define	COUNTERDONE( c )							( ( ( giClockTimer = GetJA2Clock() ) - giTimerCounters[ c ] ) >	giTimerIntervals[ c ] ) ? TRUE : FALSE

#define	UPDATETIMECOUNTER( c )		
#define	RESETTIMECOUNTER( c, d )			( c = giClockTimer )
#define	TIMECOUNTERDONE( c, d )				( giClockTimer - c >	d ) ? TRUE : FALSE
#define		SYNCTIMECOUNTER( )						( giClockTimer = GetJA2Clock() )

#endif


void SetTileAnimCounter( INT32 iTime );


#endif