#ifdef PRECOMPILEDHEADERS
	#include "Laptop All.h"
	#include "GameSettings.h"

#ifdef JA2UB
	#include "Ja25 Strategic Ai.h"
#endif

#else
	#include "laptop.h"
	#include "mercs.h"
	#include "Utilities.h"
	#include "WCheck.h"
	#include "WordWrap.h"
	#include "Cursors.h"
	#include "Overhead.h"
	#include "Soldier Add.h"
	#include "Email.h"
	#include "Game Clock.h"
	#include "Faces.h"
	#include "dialogue control.h"
	#include "MercTextBox.h"
	#include "Merc Hiring.h"
	#include "Random.h"
	#include "LaptopSave.h"
	#include "GameSettings.h"
	#include "Text.h"
	#include "Speck Quotes.h"
	#include "mercs Account.h"
	#include "Soldier Profile.h"
	#include "Game Event Hook.h"
	#include "Quests.h"
#endif

#ifdef JA2UB
#include "Ja25_Tactical.h"
#include "Ja25 Strategic Ai.h"
#include "Speck Quotes.h"
#endif

#include "connect.h"

UINT8	NUMBER_OF_MERCS = 0;
UINT8	LAST_MERC_ID = -1;
UINT8 NUMBER_OF_BAD_MERCS = -1;

#define		MERC_TEXT_FONT									FONT12ARIAL
#define		MERC_TEXT_COLOR									FONT_MCOLOR_WHITE

#define		MERC_VIDEO_TITLE_FONT						FONT10ARIAL
#define		MERC_VIDEO_TITLE_COLOR					FONT_MCOLOR_LTYELLOW

#define		MERC_BACKGROUND_WIDTH						125
#define		MERC_BACKGROUND_HEIGHT					100

#define		MERC_TITLE_X										LAPTOP_SCREEN_UL_X + 135
#define		MERC_TITLE_Y										LAPTOP_SCREEN_WEB_UL_Y + 20

#define		MERC_PORTRAIT_X									LAPTOP_SCREEN_UL_X + 198
#define		MERC_PORTRAIT_Y									LAPTOP_SCREEN_WEB_UL_Y + 96
#define		MERC_PORTRAIT_TEXT_X						MERC_PORTRAIT_X
#define		MERC_PORTRAIT_TEXT_Y						MERC_PORTRAIT_Y + 109
#define		MERC_PORTRAIT_TEXT_WIDTH				115

#define		MERC_ACCOUNT_BOX_X							LAPTOP_SCREEN_UL_X + 138
#define		MERC_ACCOUNT_BOX_Y							LAPTOP_SCREEN_WEB_UL_Y + 251

#define		MERC_ACCOUNT_BOX_TEXT_X					MERC_ACCOUNT_BOX_X
#define		MERC_ACCOUNT_BOX_TEXT_Y					MERC_ACCOUNT_BOX_Y + 20
#define		MERC_ACCOUNT_BOX_TEXT_WIDTH			110

#define		MERC_ACCOUNT_ARROW_X						MERC_ACCOUNT_BOX_X + 125
#define		MERC_ACCOUNT_ARROW_Y						MERC_ACCOUNT_BOX_Y + 18

#define		MERC_ACCOUNT_BUTTON_X						MERC_ACCOUNT_BOX_X + 133
#define		MERC_ACCOUNT_BUTTON_Y						MERC_ACCOUNT_BOX_Y + 8

#define		MERC_FILE_BOX_X									MERC_ACCOUNT_BOX_X
#define		MERC_FILE_BOX_Y									LAPTOP_SCREEN_WEB_UL_Y + 321

#define		MERC_FILE_BOX_TEXT_X						MERC_FILE_BOX_X
#define		MERC_FILE_BOX_TEXT_Y						MERC_FILE_BOX_Y + 20
#define		MERC_FILE_BOX_TEXT_WIDTH				MERC_ACCOUNT_BOX_TEXT_WIDTH

#define		MERC_FILE_ARROW_X								MERC_FILE_BOX_X + 125
#define		MERC_FILE_ARROW_Y								MERC_FILE_BOX_Y + 18

#define		MERC_FILE_BUTTON_X							MERC_ACCOUNT_BUTTON_X
#define		MERC_FILE_BUTTON_Y							MERC_FILE_BOX_Y + 8



// Video Conference Defines
#define		MERC_VIDEO_BACKGROUND_X					MERC_PORTRAIT_X
#define		MERC_VIDEO_BACKGROUND_Y					MERC_PORTRAIT_Y
#define		MERC_VIDEO_BACKGROUND_WIDTH			116
#define		MERC_VIDEO_BACKGROUND_HEIGHT		108

#define		MERC_VIDEO_FACE_X								MERC_VIDEO_BACKGROUND_X + 10
#define		MERC_VIDEO_FACE_Y								MERC_VIDEO_BACKGROUND_Y + 17
#define		MERC_VIDEO_FACE_WIDTH						96
#define		MERC_VIDEO_FACE_HEIGHT					86
#define		MERC_X_TO_CLOSE_VIDEO_X					MERC_VIDEO_BACKGROUND_X + 104
#define		MERC_X_TO_CLOSE_VIDEO_Y					MERC_VIDEO_BACKGROUND_Y + 3
#define		MERC_X_VIDEO_TITLE_X						MERC_VIDEO_BACKGROUND_X + 5
#define		MERC_X_VIDEO_TITLE_Y						MERC_VIDEO_BACKGROUND_Y + 3

#define		MERC_INTRO_TIME									1000
#define		MERC_EXIT_TIME									500
#define		MERC_VIDEO_MERC_ID_FOR_SPECKS		159//255

#define		MERC_TEXT_BOX_POS_Y							iScreenHeightOffset + 255

#define		SPECK_IDLE_CHAT_DELAY						10000

#ifdef JA2UB
#define		MERC_NUMBER_OF_RANDOM_QUOTES		20//19//14
#else
#define		MERC_NUMBER_OF_RANDOM_QUOTES		19//14
#endif


#define		MERC_FIRST_MERC									BIFF
#define		MERC_LAST_MERC									BUBBA


//number of payment days ( # of merc days paid ) to get next set of mercs
#define		MERC_NUM_DAYS_TILL_FIRST_MERC_AVAILABLE				10
#define		MERC_NUM_DAYS_TILL_SECOND_MERC_AVAILABLE			16
#define		MERC_NUM_DAYS_TILL_THIRD_MERC_AVAILABLE				24
#define		MERC_NUM_DAYS_TILL_FOURTH_MERC_AVAILABLE			30

#define		MERC__AMOUNT_OF_MONEY_FOR_BUBBA								6000
#define		MERC__DAY_WHEN_BUBBA_CAN_BECOME_AVAILABLE			10

CONTITION_FOR_MERC_AVAILABLE_TEMP gConditionsForMercAvailabilityTemp[ NUM_PROFILES ];
CONTITION_FOR_MERC_AVAILABLE gConditionsForMercAvailability[ NUM_PROFILES ]; //NUM_MERC_ARRIVALS ]; //=
/*
{
	5000, 8,	6,	//BUBBA
	10000, 15, 7,	//Larry
	15000, 20, 9,	//Numb
	16000, 21, 10,	//Tex
	18000, 23, 11,	//Biggens
	20000, 25, 12,	//Cougar
	25000, 30, 13,	//Gaston
	26000, 31, 14,	//Stogie

};
*/

enum
{
	MERC_DISTORTION_NO_DISTORTION,
	MERC_DISTORTION_PIXELATE_UP,
	MERC_DISTORTION_PIXELATE_DOWN,
	MERC_DISRTORTION_DISTORT_IMAGE,
};


enum
{
	MERC_SITE_NEVER_VISITED,
	MERC_SITE_FIRST_VISIT,
	MERC_SITE_SECOND_VISIT,
	MERC_SITE_THIRD_OR_MORE_VISITS,
};


// Image Indetifiers

UINT32		guiAccountBox;
UINT32		guiArrow;
UINT32		guiFilesBox;
UINT32		guiMercSymbol;
UINT32		guiSpecPortrait;
UINT32		guiMercBackGround;
UINT32		guiMercVideoFaceBackground;
UINT32		guiMercVideoPopupBackground;

UINT8			gubMercArray[ NUM_PROFILES ]; //MAX_NUMBER_OF_MERCS
UINT8			gubCurMercIndex;

INT32			iMercPopUpBox = -1;

UINT16		gusPositionOfSpecksDialogBox_X;
CHAR16		gsSpeckDialogueTextPopUp[ 900 ];
UINT16		gusSpeckDialogueX;
UINT16		gusSpeckDialogueActualWidth;

BOOLEAN		gfInMercSite=FALSE;		//this flag is set when inide of the merc site

//Merc Video Conferencing Mode
enum
{
	MERC_VIDEO_NO_VIDEO_MODE,
	MERC_VIDEO_INIT_VIDEO_MODE,
	MERC_VIDEO_VIDEO_MODE,
	MERC_VIDEO_EXIT_VIDEO_MODE,
};

UINT8			gubCurrentMercVideoMode;
BOOLEAN		gfMercVideoIsBeingDisplayed;
INT32			giVideoSpeckFaceIndex;
UINT16		gusMercVideoSpeckSpeech;

BOOLEAN		gfDisplaySpeckTextBox=FALSE;

BOOLEAN		gfJustEnteredMercSite=FALSE;
UINT8			gubArrivedFromMercSubSite=MERC_CAME_FROM_OTHER_PAGE;		//the merc is arriving from one of the merc sub pages
BOOLEAN		gfDoneIntroSpeech=TRUE;

BOOLEAN		gfMercSiteScreenIsReDrawn=FALSE;

BOOLEAN		gfJustHiredAMercMerc=FALSE;

BOOLEAN		gfRedrawMercSite=FALSE;

BOOLEAN		gfFirstTimeIntoMERCSiteSinceEnteringLaptop=FALSE;

//used for the random quotes to try to balance the ones that are said
typedef struct
{
	UINT8		ubQuoteID;
	UINT32	uiNumberOfTimesQuoteSaid;

} NUMBER_TIMES_QUOTE_SAID;
NUMBER_TIMES_QUOTE_SAID			gNumberOfTimesQuoteSaid[ MERC_NUMBER_OF_RANDOM_QUOTES ] =
{
#ifdef JA2UB
		{ SPECK_QUOTE_BIFF_DEAD_WHEN_IMPORTING, 0 },
#endif
		{ SPECK_QUOTE_RANDOM_CHIT_CHAT_1, 0 },
		{ SPECK_QUOTE_RANDOM_CHIT_CHAT_2, 0 },

#ifdef JA2UB
		{ SPECK_QUOTE_RANDOM_CHIT_CHAT_3, 0 },
#endif

		{ SPECK_QUOTE_ADVERTISE_GASTON, 0 },
		{ SPECK_QUOTE_ADVERTISE_STOGIE, 0 },

		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_BIFF, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_HAYWIRE, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_GASKET, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_RAZOR, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_FLO, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_GUMPY, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_LARRY, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_COUGER, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_NUMB, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_BUBBA, 0 },

		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_AIM_SLANDER_1, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_AIM_SLANDER_2, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_AIM_SLANDER_3, 0 },
		{ SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_AIM_SLANDER_4, 0 },
};


//
// Buttons
//

// The Account Box button
void BtnAccountBoxButtonCallback(GUI_BUTTON *btn,INT32 reason);
UINT32	guiAccountBoxButton;
INT32		guiAccountBoxButtonImage;

//File Box
UINT32	guiFileBoxButton;
void BtnFileBoxButtonCallback(GUI_BUTTON *btn,INT32 reason);

// The 'X' to close the video conf window button
void BtnXToCloseMercVideoButtonCallback(GUI_BUTTON *btn,INT32 reason);
UINT32	guiXToCloseMercVideoButton;
INT32		guiXToCloseMercVideoButtonImage;


//Mouse region for the subtitles region when the merc is talking
MOUSE_REGION		gMercSiteSubTitleMouseRegion;
void MercSiteSubTitleRegionCallBack(MOUSE_REGION * pRegion, INT32 iReason );


BOOLEAN LoadNewMercsFromLoadGameFile( HWFILE hFile );
BOOLEAN SaveNewMercsToSaveGameFile( HWFILE hFile );


//*******************************
//
//	Function Prototypes
//
//*******************************

BOOLEAN		StartSpeckTalking(UINT16 usQuoteNum);
void			InitMercVideoFace();
BOOLEAN		HandleSpeckTalking( BOOLEAN fReset );
//BOOLEAN	PixelateVideoMercImage();
BOOLEAN		PixelateVideoMercImage( BOOLEAN fUp, UINT16 usPosX, UINT16 usPosY, UINT16 usWidth, UINT16 usHeight);
BOOLEAN		InitDestroyXToCloseVideoWindow( BOOLEAN fCreate );
BOOLEAN		DisplayMercVideoIntro( UINT16 usTimeTillFinish );
void			HandleCurrentMercDistortion();
void			HandleTalkingSpeck();
//BOOLEAN DistortVideoMercImage();
BOOLEAN		DistortVideoMercImage( UINT16 usPosX, UINT16 usPosY, UINT16 usWidth, UINT16 usHeight );
BOOLEAN		IsAnyMercMercsHired( );
BOOLEAN		IsAnyMercMercsDead();
UINT8			CountNumberOfMercMercsHired();
UINT8			CountNumberOfMercMercsWhoAreDead();
BOOLEAN		GetSpeckConditionalOpening( BOOLEAN fJustEnteredScreen );
void			RemoveSpeckPopupTextBox();
BOOLEAN		ShouldSpeckStartTalkingDueToActionOnSubPage();
BOOLEAN		ShouldSpeckSayAQuote();
void			HandleSpeckIdleConversation( BOOLEAN fReset );
INT16			GetRandomQuoteThatHasBeenSaidTheLeast( );
void			StopSpeckFromTalking( );
BOOLEAN		HasLarryRelapsed();
void			IncreaseMercRandomQuoteValue( UINT8 ubQuoteID, UINT8 ubValue );
BOOLEAN		ShouldTheMercSiteServerGoDown();
void			DrawMercVideoBackGround();
BOOLEAN		CanMercQuoteBeSaid( UINT32 uiQuoteID );
UINT8			NumberOfMercMercsDead();
void			MakeBiffAwayForCoupleOfDays();
BOOLEAN		AreAnyOfTheNewMercsAvailable();
void			ShouldAnyNewMercMercBecomeAvailable();
BOOLEAN		CanMercBeAvailableYet( UINT8 ubMercToCheck );
UINT32		CalcMercDaysServed();
#ifdef JA2UB
void			MarkSpeckImportantQuoteUsed( UINT32 uiQuoteNum );
BOOLEAN		HasImportantSpeckQuoteBeingSaid( UINT32 uiQuoteNum );
INT8			IsSpeckQuoteImportantQuote( UINT32 uiQuoteNum );
#endif
//ppp

BOOLEAN SaveNewMercsToSaveGameFile( HWFILE hFile )
{
	UINT32	uiNumBytesWritten;

	FileWrite( hFile, &gConditionsForMercAvailability, sizeof( gConditionsForMercAvailability), &uiNumBytesWritten );
	if( uiNumBytesWritten != sizeof( gConditionsForMercAvailability ) )
	{
		return( FALSE );
	}

	return( TRUE );
}

BOOLEAN LoadNewMercsFromLoadGameFile( HWFILE hFile )
{
	UINT32	uiNumBytesRead;

	FileRead( hFile, &gConditionsForMercAvailability, sizeof( gConditionsForMercAvailability ), &uiNumBytesRead );
	if( uiNumBytesRead != sizeof( gConditionsForMercAvailability ) )
	{
		return( FALSE );
	}

	return( TRUE );
}


void GameInitMercs()
{
	UINT8 i;

	NUMBER_OF_MERCS = 0;
	LAST_MERC_ID = -1;
	NUMBER_OF_BAD_MERCS = -1;
	
	for(i=0; i<NUM_PROFILES; i++)
	{
		if ( gConditionsForMercAvailability[i].ProfilId != 0 )
		{
			NUMBER_OF_MERCS = NUMBER_OF_MERCS + 1;
			LAST_MERC_ID = LAST_MERC_ID + 1;
			gubMercArray[ i ] = gConditionsForMercAvailability[i].ProfilId;
		}
	}
	
	for(i=0; i<NUM_PROFILES; i++)
	{
		if ( gConditionsForMercAvailability[i].StartMercsAvailable == TRUE && gConditionsForMercAvailability[i].NewMercsAvailable == FALSE )
			NUMBER_OF_BAD_MERCS = NUMBER_OF_BAD_MERCS + 1;
	}
	
	LaptopSaveInfo.gubPlayersMercAccountStatus = MERC_NO_ACCOUNT;
	gubCurMercIndex = 0;

	if(!gGameExternalOptions.fAllMercsAvailable)
	{
		LaptopSaveInfo.gubLastMercIndex = NUMBER_OF_BAD_MERCS; // LAST_MERC_ID;
	}
	else
	{
		LaptopSaveInfo.gubLastMercIndex =	LAST_MERC_ID; //NUMBER_OF_BAD_MERCS;
	}
	
#ifdef JA2UB	
	//Ja25.  create an account immediately
	{
		//open an account
		LaptopSaveInfo.gubPlayersMercAccountStatus = MERC_ACCOUNT_VALID;

		//Get an account number
		LaptopSaveInfo.guiPlayersMercAccountNumber = Random( 99999 );
	}
#endif

	gubCurrentMercVideoMode = MERC_VIDEO_NO_VIDEO_MODE;
	gfMercVideoIsBeingDisplayed = FALSE;

	LaptopSaveInfo.guiNumberOfMercPaymentsInDays = 0;

	gusMercVideoSpeckSpeech = 0;

/*
	for( i=0; i<MERC_NUMBER_OF_RANDOM_QUOTES; i++ )
	{
		gNumberOfTimesQuoteSaid[i] = 0;
	}
*/
}


BOOLEAN EnterMercs()
{
	VOBJECT_DESC	VObjectDesc;
	VSURFACE_DESC		vs_desc;

	SetBookMark( MERC_BOOKMARK );

	//Reset a static variable
	HandleSpeckTalking( TRUE );

	InitMercBackGround();

	// load the Account box graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\AccountBox.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiAccountBox));

	// load the files Box graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\FilesBox.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiFilesBox));

	// load the MercSymbol graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\MERCSymbol.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiMercSymbol));

	// load the SpecPortrait graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\SpecPortrait.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiSpecPortrait));

	// load the Arrow graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\Arrow.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiArrow));

	// load the Merc video conf background graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\SpeckComWindow.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiMercVideoPopupBackground));


	// Account Box button
	guiAccountBoxButtonImage	= LoadButtonImage("LAPTOP\\SmallButtons.sti", -1,0,-1,1,-1 );
#ifdef JA2UB
// no UB
#else
	guiAccountBoxButton = QuickCreateButton(guiAccountBoxButtonImage, MERC_ACCOUNT_BUTTON_X, MERC_ACCOUNT_BUTTON_Y,
																BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
																DEFAULT_MOVE_CALLBACK, BtnAccountBoxButtonCallback);
	SetButtonCursor(guiAccountBoxButton, CURSOR_LAPTOP_SCREEN);
	SpecifyDisabledButtonStyle( guiAccountBoxButton, DISABLED_STYLE_SHADED);

#endif
	guiFileBoxButton = QuickCreateButton(guiAccountBoxButtonImage, MERC_FILE_BUTTON_X, MERC_FILE_BUTTON_Y,
																BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
																DEFAULT_MOVE_CALLBACK, BtnFileBoxButtonCallback);
	SetButtonCursor(guiFileBoxButton, CURSOR_LAPTOP_SCREEN);
	SpecifyDisabledButtonStyle( guiFileBoxButton, DISABLED_STYLE_SHADED);

	//if the player doesnt have an account disable it
	if( LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_NO_ACCOUNT )
	{
		DisableButton( guiFileBoxButton );
	}


	//
	//	Video Conferencing stuff
	//

	// Create a background video surface to blt the face onto
	vs_desc.fCreateFlags = VSURFACE_CREATE_DEFAULT | VSURFACE_SYSTEM_MEM_USAGE;
	vs_desc.usWidth = MERC_VIDEO_FACE_WIDTH;
	vs_desc.usHeight = MERC_VIDEO_FACE_HEIGHT;
	vs_desc.ubBitDepth = 16;
	CHECKF( AddVideoSurface( &vs_desc, &guiMercVideoFaceBackground) );


	RenderMercs();

	//init the face

	gfJustEnteredMercSite = TRUE;

	//if NOT entering from a subsite
	if( gubArrivedFromMercSubSite == MERC_CAME_FROM_OTHER_PAGE )
	{
		//Set that we have been here before
		if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_NEVER_VISITED )
			LaptopSaveInfo.ubPlayerBeenToMercSiteStatus = MERC_SITE_FIRST_VISIT;
		else if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_FIRST_VISIT )
			LaptopSaveInfo.ubPlayerBeenToMercSiteStatus = MERC_SITE_SECOND_VISIT;
		else
			LaptopSaveInfo.ubPlayerBeenToMercSiteStatus = MERC_SITE_THIRD_OR_MORE_VISITS;

		//Reset the speech variable
		gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;
	}


	GetSpeckConditionalOpening( TRUE );
//	gubArrivedFromMercSubSite = MERC_CAME_FROM_OTHER_PAGE;

	//if Speck should start talking
	if( ShouldSpeckSayAQuote() )
	{
		gubCurrentMercVideoMode = MERC_VIDEO_INIT_VIDEO_MODE;
	}

	//Reset the some variables
	HandleSpeckIdleConversation( TRUE );

	//Since we are in the site, set the flag
	gfInMercSite = TRUE;

	return(TRUE);
}


void ExitMercs()
{
	StopSpeckFromTalking( );

	if( gfMercVideoIsBeingDisplayed )
	{
		gfMercVideoIsBeingDisplayed = FALSE;
		DeleteFace( giVideoSpeckFaceIndex	);
		InitDestroyXToCloseVideoWindow( FALSE );
		gubCurrentMercVideoMode = MERC_VIDEO_NO_VIDEO_MODE;
	}

	DeleteVideoObjectFromIndex(guiAccountBox);
	DeleteVideoObjectFromIndex(guiFilesBox);
	DeleteVideoObjectFromIndex(guiMercSymbol);
	DeleteVideoObjectFromIndex(guiSpecPortrait);
	DeleteVideoObjectFromIndex(guiArrow);
	DeleteVideoObjectFromIndex(guiMercVideoPopupBackground);

	UnloadButtonImage( guiAccountBoxButtonImage );
	RemoveButton( guiFileBoxButton );
#ifdef JA2UB
//JA25: removed		RemoveButton( guiAccountBoxButton );
#else
	RemoveButton( guiAccountBoxButton );
#endif
	RemoveMercBackGround();

	DeleteVideoSurfaceFromIndex( guiMercVideoFaceBackground );

/*
	//Set that we have been here before
	if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_FIRST_VISIT )
		LaptopSaveInfo.ubPlayerBeenToMercSiteStatus = MERC_SITE_SECOND_VISIT;
	else
		LaptopSaveInfo.ubPlayerBeenToMercSiteStatus = MERC_SITE_THIRD_OR_MORE_VISITS;
*/

	gfJustEnteredMercSite = TRUE;
	gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;

	//Remove the merc text box if one is available
	RemoveSpeckPopupTextBox();

	//Set up so next time we come in, we know we came from a differnt page
	gubArrivedFromMercSubSite = MERC_CAME_FROM_OTHER_PAGE;

	gfJustHiredAMercMerc = FALSE;

	//Since we are leaving the site, set the flag
	gfInMercSite = TRUE;

	//Empty the Queue cause Speck could still have a quote in waiting
	EmptyDialogueQueue( );
}

void HandleMercs()
{
	if( gfRedrawMercSite )
	{
		RenderMercs();
		gfRedrawMercSite = FALSE;
		gfMercSiteScreenIsReDrawn = TRUE;
	}

	//if Speck has something to say, say it
	if( gusMercVideoSpeckSpeech != MERC_VIDEO_SPECK_SPEECH_NOT_TALKING )// && !gfDoneIntroSpeech )
	{
		//if the face isnt active, make it so
		if( !gfMercVideoIsBeingDisplayed )
		{
			// Blt the video window background
			DrawMercVideoBackGround();

			InitDestroyXToCloseVideoWindow( TRUE );

			InitMercVideoFace();
			gubCurrentMercVideoMode = MERC_VIDEO_INIT_VIDEO_MODE;

//			gfMercSiteScreenIsReDrawn = TRUE;
		}
	}

	//if the page is redrawn, and we are in video conferencing, redraw the VC backgrund graphic
	if( gfMercVideoIsBeingDisplayed && gfMercSiteScreenIsReDrawn )
	{
		// Blt the video window background
		DrawMercVideoBackGround();

		gfMercSiteScreenIsReDrawn = FALSE;
	}


	//if Specks should be video conferencing...
	if( gubCurrentMercVideoMode != MERC_VIDEO_NO_VIDEO_MODE )
	{
		HandleTalkingSpeck();
	}

	//Reset the some variables
	HandleSpeckIdleConversation( FALSE );

	if( fCurrentlyInLaptop == FALSE )
	{
		//if we are exiting the laptop screen, shut up the speck
		StopSpeckFromTalking( );
	}
}

void RenderMercs()
{
	HVOBJECT hPixHandle;

	DrawMecBackGround();

	// Title
	GetVideoObject(&hPixHandle, guiMercSymbol);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,MERC_TITLE_X, MERC_TITLE_Y, VO_BLT_SRCTRANSPARENCY,NULL);

	// Speck Portrait
	GetVideoObject(&hPixHandle, guiSpecPortrait);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,MERC_PORTRAIT_X, MERC_PORTRAIT_Y, VO_BLT_SRCTRANSPARENCY,NULL);

	// Account Box
	GetVideoObject(&hPixHandle, guiAccountBox);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,MERC_ACCOUNT_BOX_X, MERC_ACCOUNT_BOX_Y, VO_BLT_SRCTRANSPARENCY,NULL);

	// Files Box
	GetVideoObject(&hPixHandle, guiFilesBox);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0, MERC_FILE_BOX_X, MERC_FILE_BOX_Y, VO_BLT_SRCTRANSPARENCY,NULL);

	//Text on the Speck Portrait
	DisplayWrappedString(MERC_PORTRAIT_TEXT_X, MERC_PORTRAIT_TEXT_Y, MERC_PORTRAIT_TEXT_WIDTH, 2, MERC_TEXT_FONT, MERC_TEXT_COLOR, MercHomePageText[MERC_SPECK_OWNER], FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED);

#ifdef JA2UB
	//Display the "ask about or special offer
	DisplayWrappedString(MERC_ACCOUNT_BOX_TEXT_X, MERC_ACCOUNT_BOX_TEXT_Y, 230, 2, MERC_TEXT_FONT, MERC_TEXT_COLOR, gzNewLaptopMessages[ LPTP_MSG__MERC_SPECIAL_OFFER ], FONT_MCOLOR_BLACK, FALSE, CENTER_JUSTIFIED);
#else
/* ja25:*/
	//Text on the Account Box
	if( LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_NO_ACCOUNT )
		DisplayWrappedString(MERC_ACCOUNT_BOX_TEXT_X, MERC_ACCOUNT_BOX_TEXT_Y, MERC_ACCOUNT_BOX_TEXT_WIDTH, 2, MERC_TEXT_FONT, MERC_TEXT_COLOR, MercHomePageText[MERC_OPEN_ACCOUNT], FONT_MCOLOR_BLACK, FALSE, RIGHT_JUSTIFIED);
	else
		DisplayWrappedString(MERC_ACCOUNT_BOX_TEXT_X, MERC_ACCOUNT_BOX_TEXT_Y, MERC_ACCOUNT_BOX_TEXT_WIDTH, 2, MERC_TEXT_FONT, MERC_TEXT_COLOR, MercHomePageText[MERC_VIEW_ACCOUNT], FONT_MCOLOR_BLACK, FALSE, RIGHT_JUSTIFIED);
#endif
	//Text on the Files Box
	DisplayWrappedString(MERC_FILE_BOX_TEXT_X, MERC_FILE_BOX_TEXT_Y, MERC_FILE_BOX_TEXT_WIDTH, 2, MERC_TEXT_FONT, MERC_TEXT_COLOR, MercHomePageText[MERC_VIEW_FILES], FONT_MCOLOR_BLACK, FALSE, RIGHT_JUSTIFIED);

	//If the Specks popup dioalogue box is active, display it.
	if( iMercPopUpBox != -1 )
	{

#ifdef JA2UB
//JA25: removed			DrawButton( guiAccountBoxButton );
//		ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#else
		DrawButton( guiAccountBoxButton );
		ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#endif
		RenderMercPopUpBoxFromIndex( iMercPopUpBox, gusSpeckDialogueX, MERC_TEXT_BOX_POS_Y, FRAME_BUFFER);
	}

	MarkButtonsDirty( );
	RenderWWWProgramTitleBar( );

	//if the page is redrawn, and we are in video conferencing, redraw the VC backgrund graphic
	gfMercSiteScreenIsReDrawn = TRUE;
#ifdef JA2UB
//JA25: removed	ButtonList[ guiAccountBoxButton ]->uiFlags &= ~BUTTON_FORCE_UNDIRTY;
#else
	ButtonList[ guiAccountBoxButton ]->uiFlags &= ~BUTTON_FORCE_UNDIRTY;
#endif
	InvalidateRegion(LAPTOP_SCREEN_UL_X,LAPTOP_SCREEN_WEB_UL_Y,LAPTOP_SCREEN_LR_X,LAPTOP_SCREEN_WEB_LR_Y);
}


BOOLEAN InitMercBackGround()
{
	VOBJECT_DESC	VObjectDesc;

	// load the Merc background graphic and add it
	VObjectDesc.fCreateFlags=VOBJECT_CREATE_FROMFILE;
	FilenameForBPP("LAPTOP\\MERCBackGround.sti", VObjectDesc.ImageFile);
	CHECKF(AddVideoObject(&VObjectDesc, &guiMercBackGround));

	return(TRUE);
}


BOOLEAN DrawMecBackGround()
{
	WebPageTileBackground(4, 4, MERC_BACKGROUND_WIDTH, MERC_BACKGROUND_HEIGHT, guiMercBackGround);
	return(TRUE);
}


BOOLEAN RemoveMercBackGround()
{
	DeleteVideoObjectFromIndex(guiMercBackGround);

	return(TRUE);
}


#ifdef JA2UB
//no UB
#else
void BtnAccountBoxButtonCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if (btn->uiFlags & BUTTON_CLICKED_ON)
		{
			btn->uiFlags &= (~BUTTON_CLICKED_ON );

			if( LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_NO_ACCOUNT )
				guiCurrentLaptopMode = LAPTOP_MODE_MERC_NO_ACCOUNT;
			else
				guiCurrentLaptopMode = LAPTOP_MODE_MERC_ACCOUNT;

			if( iMercPopUpBox != -1 )
			{
				ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;

				RenderMercPopUpBoxFromIndex( iMercPopUpBox, gusSpeckDialogueX, MERC_TEXT_BOX_POS_Y, FRAME_BUFFER);
			}

			InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
		}
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}
#endif

void BtnFileBoxButtonCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if (btn->uiFlags & BUTTON_CLICKED_ON)
		{
			btn->uiFlags &= (~BUTTON_CLICKED_ON );

			guiCurrentLaptopMode = LAPTOP_MODE_MERC_FILES;

			InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
		}
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}


void DailyUpdateOfMercSite( UINT16 usDate)
{
	SOLDIERTYPE *pSoldier;
	INT16		sSoldierID, i;
	UINT8		ubMercID;
	INT32		iNumDays;

	//if its the first day, leave
	if( usDate == 1 )
		return;

	iNumDays = 0;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( (UINT8) i );
		if( IsMercOnTeam( ubMercID ) )
		{
			// WANNE: If we have drunken merc, then skip otherwise is will exist 2 times!
			if (gConditionsForMercAvailability[ i ].Drunk)
				continue;

			//// WANNE.LARRY
			////if it larry Roach burn advance.	( cause larry is in twice, a sober larry and a stoned larry )
			//if( i == MERC_LARRY_ROACHBURN )
			//	continue;

			sSoldierID = GetSoldierIDFromMercID( ubMercID );
			pSoldier = MercPtrs[ sSoldierID ];

			//if the merc is dead, dont advance the contract length
			if( !IsMercDead( pSoldier->ubProfile ) )
			{
				gMercProfiles[ pSoldier->ubProfile ].iMercMercContractLength += 1;
//				pSoldier->iTotalContractLength++;
			}

#ifdef JA2UB
//JA25:  MERC does a 1 time fee, no longer pay as you go 
#else

			//Get the longest time
			if( gMercProfiles[ pSoldier->ubProfile ].iMercMercContractLength > iNumDays )
				iNumDays = gMercProfiles[ pSoldier->ubProfile ].iMercMercContractLength;
#endif
		}
	}

#ifdef JA2UB
//JA25:  No longer pay as you go, now pay up front
#else
	//if the players hasnt paid for a while, get email him to tell him to pay
	//iTotalContractLength
	if( iNumDays > MERC_NUM_DAYS_TILL_ACCOUNT_INVALID )
	{
		if( LaptopSaveInfo.gubPlayersMercAccountStatus != MERC_ACCOUNT_INVALID )
		{
			LaptopSaveInfo.gubPlayersMercAccountStatus = MERC_ACCOUNT_INVALID;
//			AddEmail( MERC_INVALID, MERC_INVALID_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), -1, -1, TYPE_EMAIL_EMAIL_EDT);
		}
	}
	else if( iNumDays > MERC_NUM_DAYS_TILL_ACCOUNT_SUSPENDED )
	{
		if( LaptopSaveInfo.gubPlayersMercAccountStatus != MERC_ACCOUNT_SUSPENDED )
		{
			LaptopSaveInfo.gubPlayersMercAccountStatus = MERC_ACCOUNT_SUSPENDED;
//			AddEmail( MERC_WARNING, MERC_WARNING_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), -1, -1, TYPE_EMAIL_EMAIL_EDT);

			// Have speck complain next time player come to site
			LaptopSaveInfo.uiSpeckQuoteFlags |= SPECK_QUOTE__SENT_EMAIL_ABOUT_LACK_OF_PAYMENT;
		}
	}
	else if( iNumDays > MERC_NUM_DAYS_TILL_FIRST_WARNING)
	{
		if( LaptopSaveInfo.gubPlayersMercAccountStatus != MERC_ACCOUNT_VALID_FIRST_WARNING )
		{
			LaptopSaveInfo.gubPlayersMercAccountStatus = MERC_ACCOUNT_VALID_FIRST_WARNING;
//			AddEmail( MERC_FIRST_WARNING, MERC_FIRST_WARNING_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), -1, -1, TYPE_EMAIL_EMAIL_EDT);

			// Have speck complain next time player come to site
			LaptopSaveInfo.uiSpeckQuoteFlags |= SPECK_QUOTE__SENT_EMAIL_ABOUT_LACK_OF_PAYMENT;
		}
	}
#endif

	//Check and act if any new Merc Mercs should become available
	ShouldAnyNewMercMercBecomeAvailable();

/*
	//If we should advacne the number of days that the good mercs arrive
//	if( LaptopSaveInfo.guiNumberOfMercPaymentsInDays > 4 )
	{
		UINT8 ubNumDays;

//		ubNumDays = (UINT8) LaptopSaveInfo.guiNumberOfMercPaymentsInDays / 4;
		ubNumDays = (UINT8) LaptopSaveInfo.guiNumberOfMercPaymentsInDays;

//		LaptopSaveInfo.guiNumberOfMercPaymentsInDays = LaptopSaveInfo.guiNumberOfMercPaymentsInDays % 4;
		LaptopSaveInfo.guiNumberOfMercPaymentsInDays = 0;

		//for the first merc
		//if the merc is not already here
		if( LaptopSaveInfo.gbNumDaysTillFirstMercArrives != -1 )
		{
			//We advance the day the merc arrives on
			if( LaptopSaveInfo.gbNumDaysTillFirstMercArrives > ubNumDays )
			{
				LaptopSaveInfo.gbNumDaysTillFirstMercArrives -= ubNumDays;
			}
			else
			{
				//its time to add the new mercs
				LaptopSaveInfo.gubLastMercIndex = NUMBER_MERCS_AFTER_FIRST_MERC_ARRIVES;

				//Set the fact that there are new mercs available
				LaptopSaveInfo.fNewMercsAvailableAtMercSite = TRUE;

				//if we havent already sent an email this turn
				if( !fAlreadySentEmailToPlayerThisTurn )
				{
//					AddEmail( NEW_MERCS_AT_MERC, NEW_MERCS_AT_MERC_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), TYPE_EMAIL_EMAIL_EDT);
					fAlreadySentEmailToPlayerThisTurn = TRUE;
				}
				LaptopSaveInfo.gbNumDaysTillFirstMercArrives = -1;
			}
		}


		//for the Second merc
		//if the merc is not already here
		if( LaptopSaveInfo.gbNumDaysTillSecondMercArrives != -1 )
		{
			//We advance the day the merc arrives on
			if( LaptopSaveInfo.gbNumDaysTillSecondMercArrives > ubNumDays )
			{
				LaptopSaveInfo.gbNumDaysTillSecondMercArrives -= ubNumDays;
			}
			else
			{
				//its time to add the new mercs
				LaptopSaveInfo.gubLastMercIndex = NUMBER_MERCS_AFTER_SECOND_MERC_ARRIVES;

				//Set the fact that there are new mercs available
				LaptopSaveInfo.fNewMercsAvailableAtMercSite = TRUE;

				//if we havent already sent an email this turn
				if( !fAlreadySentEmailToPlayerThisTurn )
				{
					AddEmail( NEW_MERCS_AT_MERC, NEW_MERCS_AT_MERC_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin());
					fAlreadySentEmailToPlayerThisTurn = TRUE;
				}
				LaptopSaveInfo.gbNumDaysTillSecondMercArrives = -1;
			}
		}

		//for the Third merc
		//if the merc is not already here
		if( LaptopSaveInfo.gbNumDaysTillThirdMercArrives != -1 )
		{
			//We advance the day the merc arrives on
			if( LaptopSaveInfo.gbNumDaysTillThirdMercArrives > ubNumDays )
			{
				LaptopSaveInfo.gbNumDaysTillThirdMercArrives -= ubNumDays;
			}
			else
			{
				//its time to add the new mercs
				LaptopSaveInfo.gubLastMercIndex = NUMBER_MERCS_AFTER_THIRD_MERC_ARRIVES;

				//Set the fact that there are new mercs available
				LaptopSaveInfo.fNewMercsAvailableAtMercSite = TRUE;

				//if we havent already sent an email this turn
				if( !fAlreadySentEmailToPlayerThisTurn )
				{
					AddEmail( NEW_MERCS_AT_MERC, NEW_MERCS_AT_MERC_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin());
					fAlreadySentEmailToPlayerThisTurn = TRUE;
				}
				LaptopSaveInfo.gbNumDaysTillThirdMercArrives = -1;
			}
		}

		//for the Fourth merc
		//if the merc is not already here
		if( LaptopSaveInfo.gbNumDaysTillFourthMercArrives != -1 )
		{
			//We advance the day the merc arrives on
			if( LaptopSaveInfo.gbNumDaysTillFourthMercArrives > ubNumDays )
			{
				LaptopSaveInfo.gbNumDaysTillFourthMercArrives -= ubNumDays;
			}
			else
			{
				//its time to add the new mercs
				LaptopSaveInfo.gubLastMercIndex = NUMBER_MERCS_AFTER_FOURTH_MERC_ARRIVES;

				//Set the fact that there are new mercs available
				LaptopSaveInfo.fNewMercsAvailableAtMercSite = TRUE;

				//if we havent already sent an email this turn
				if( !fAlreadySentEmailToPlayerThisTurn )
				{
					AddEmail( NEW_MERCS_AT_MERC, NEW_MERCS_AT_MERC_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin());
					fAlreadySentEmailToPlayerThisTurn = TRUE;
				}
				LaptopSaveInfo.gbNumDaysTillFourthMercArrives = -1;
			}
		}
	}
*/

	// If the merc site has never gone down, the number of MERC payment days is above 'X',
	// and the players account status is ok ( cant have the merc site going down when the player owes him money, player may lose account that way )
#ifdef JA2UB
// no UB
#else
	if( ShouldTheMercSiteServerGoDown() )
	{
		UINT32	uiTimeInMinutes=0;


		//Set the fact the site has gone down
		LaptopSaveInfo.fMercSiteHasGoneDownYet = TRUE;

//No lnger removing the bookmark, leave it up, and the user will go to the broken link page
		//Remove the book mark
//		RemoveBookMark( MERC_BOOKMARK );

		//Get the site up the next day at 6:00 pm
		uiTimeInMinutes = GetMidnightOfFutureDayInMinutes( 1 ) + 18 * 60;

		//Add an event that will get the site back up and running
		AddStrategicEvent( EVENT_MERC_SITE_BACK_ONLINE, uiTimeInMinutes, 0 );
	}
#endif
}


//Gets the actual merc id from the array
UINT8 GetMercIDFromMERCArray(UINT8 ubMercID)
{
	// Is this a drunken merc (e.g Larry) and has an additional drunken profile
	if( gConditionsForMercAvailability[ ubMercID ].Drunk == TRUE && gConditionsForMercAvailability[ ubMercID ].uiAlternateIndex != 255)
	{
		if ( HasLarryRelapsed() )
		{
			// Drunken Larry
			if (gConditionsForMercAvailability[ ubMercID ].uiIndex <= NUM_PROFILES)
			{
				return( gubMercArray[ gConditionsForMercAvailability[ ubMercID ].uiIndex ] );
			}
			else
			{
				Assert(0);
				return( TRUE );
			}
		}
		else
		{
			// Normal Larry (Normal Profile is one 
			return( gubMercArray[ gConditionsForMercAvailability[ ubMercID ].uiAlternateIndex ] );
		}
	}
	// Merc is not drunken
	else if( ubMercID <= NUM_PROFILES )
	{
		return( gubMercArray[ ubMercID ] );
	}
	//else its an error
	else
	{
		Assert(0);
		return( TRUE );
	}
}


/*
BOOLEAN InitDeleteMercVideoConferenceMode()
{
	static BOOLEAN	fVideoConfModeCreated = FALSE;

	if( !fVideoConfModeCreated && gubCurrentMercVideoMode == MERC_VIDEO_INIT_VIDEO_MODE )
	{
//		InitMercVideoFace();
	}

	if( fVideoConfModeCreated && gubCurrentMercVideoMode == MERC_VIDEO_EXIT_VIDEO_MODE )
	{
		//If merc is talking, stop him from talking
		ShutupaYoFace( giVideoSpeckFaceIndex );

		//Delete the face
		DeleteFace( giVideoSpeckFaceIndex	);

		gfMercVideoIsBeingDisplayed = FALSE;
	}


	return(TRUE);
}
*/

void InitMercVideoFace()
{
	//Alocates space, and loads the sti for SPECK
//	giVideoSpeckFaceIndex = InternalInitFace( NO_PROFILE, NOBODY, 0, MERC_VIDEO_MERC_ID_FOR_SPECKS, 3000, 2000 );
		giVideoSpeckFaceIndex = InitFace( MERC_VIDEO_MERC_ID_FOR_SPECKS, NOBODY, 0 );

	// Sets up the eyes blinking and the mouth moving
//	InternalSetAutoFaceActive( guiMercVideoFaceBackground, FACE_AUTO_RESTORE_BUFFER , giVideoSpeckFaceIndex, 0, 0, 8, 9, 7, 25 );
		SetAutoFaceActive( guiMercVideoFaceBackground, FACE_AUTO_RESTORE_BUFFER , giVideoSpeckFaceIndex, 0, 0);


	//Renders the face to the background
	RenderAutoFace( giVideoSpeckFaceIndex );

	//enables the global flag indicating the the video is being displayed
	gfMercVideoIsBeingDisplayed = TRUE;

}


BOOLEAN	StartSpeckTalking(UINT16 usQuoteNum)
{

	if(is_networked)
		return( FALSE );

	if( usQuoteNum == MERC_VIDEO_SPECK_SPEECH_NOT_TALKING || usQuoteNum == MERC_VIDEO_SPECK_HAS_TO_TALK_BUT_QUOTE_NOT_CHOSEN_YET )
		return( FALSE );

	//Reset the time for when speck starts to do the random quotes
	HandleSpeckIdleConversation( TRUE );

	//Start Speck talking
	if(!CharacterDialogue( MERC_VIDEO_MERC_ID_FOR_SPECKS, usQuoteNum, giVideoSpeckFaceIndex, DIALOGUE_SPECK_CONTACT_PAGE_UI, FALSE, FALSE ) )
	{
		Assert(0);
		return(FALSE);
	}

	gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;

	return(TRUE);
}

// Performs the frame by frame update
BOOLEAN HandleSpeckTalking( BOOLEAN fReset )
{
	static BOOLEAN fWasTheMercTalking=FALSE;
	BOOLEAN		fIsTheMercTalking;
	SGPRect		SrcRect;
	SGPRect		DestRect;

	if( fReset )
	{
		fWasTheMercTalking = FALSE;
		return( TRUE );
	}

	SrcRect.iLeft = 0;
	SrcRect.iTop = 0;
	SrcRect.iRight = 48;
	SrcRect.iBottom = 43;

	DestRect.iLeft = MERC_VIDEO_FACE_X;
	DestRect.iTop = MERC_VIDEO_FACE_Y;
	DestRect.iRight = DestRect.iLeft + MERC_VIDEO_FACE_WIDTH;
	DestRect.iBottom = DestRect.iTop + MERC_VIDEO_FACE_HEIGHT;

	HandleDialogue();
	HandleAutoFaces( );
	HandleTalkingAutoFaces( );

	//Blt the face surface to the video background surface
	if(	!BltStretchVideoSurface(FRAME_BUFFER, guiMercVideoFaceBackground, 0, 0, VO_BLT_SRCTRANSPARENCY, &SrcRect, &DestRect ) )
		return(FALSE);

	//HandleCurrentMercDistortion();

	InvalidateRegion(MERC_VIDEO_BACKGROUND_X, MERC_VIDEO_BACKGROUND_Y, (MERC_VIDEO_BACKGROUND_X + MERC_VIDEO_BACKGROUND_WIDTH), (MERC_VIDEO_BACKGROUND_Y + MERC_VIDEO_BACKGROUND_HEIGHT) );

	//find out if the merc just stopped talking
	fIsTheMercTalking = gFacesData[ giVideoSpeckFaceIndex ].fTalking;

	//if the merc just stopped talking
	if(fWasTheMercTalking && !fIsTheMercTalking)
	{
		fWasTheMercTalking = FALSE;

		if( DialogueQueueIsEmpty( ) )
		{
			RemoveSpeckPopupTextBox();

			gfDisplaySpeckTextBox = FALSE;

			gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;

			//Reset the time for when speck starts to do the random quotes
			HandleSpeckIdleConversation( TRUE );
		}
		else
			fIsTheMercTalking = TRUE;
	}

	fWasTheMercTalking = fIsTheMercTalking;

	return(fIsTheMercTalking);
}


void HandleCurrentMercDistortion()
{
	static UINT8 ubCurrentMercDistortionMode = MERC_DISTORTION_NO_DISTORTION;
	BOOLEAN fReturnStatus;

	//if there is no current distortion mode, randomly choose one
	if( ubCurrentMercDistortionMode == MERC_DISTORTION_NO_DISTORTION )
	{
		UINT8 ubRandom;

		ubRandom = (UINT8)Random(200);

		if( ubRandom < 40 )
		{
			ubRandom = (UINT8)Random(100);
			if( ubRandom < 10 )
				ubCurrentMercDistortionMode = MERC_DISRTORTION_DISTORT_IMAGE;
			else if( ubRandom < 30 )
				ubCurrentMercDistortionMode = MERC_DISTORTION_PIXELATE_UP;
		}
	}

	// Perform whichever video distortion mode is current
	switch( ubCurrentMercDistortionMode )
	{
		case MERC_DISTORTION_NO_DISTORTION:
			break;

		case MERC_DISTORTION_PIXELATE_UP:
//			fReturnStatus = PixelateVideoMercImage( TRUE );
			fReturnStatus = PixelateVideoMercImage( TRUE, MERC_VIDEO_FACE_X, MERC_VIDEO_FACE_Y, MERC_VIDEO_FACE_WIDTH, MERC_VIDEO_FACE_HEIGHT );
			if( fReturnStatus )
				ubCurrentMercDistortionMode = MERC_DISTORTION_PIXELATE_DOWN;
			break;

		case MERC_DISTORTION_PIXELATE_DOWN:
//			fReturnStatus = PixelateVideoMercImage( FALSE );
			fReturnStatus = PixelateVideoMercImage( FALSE, MERC_VIDEO_FACE_X, MERC_VIDEO_FACE_Y, MERC_VIDEO_FACE_WIDTH, MERC_VIDEO_FACE_HEIGHT );
			if( fReturnStatus )
				ubCurrentMercDistortionMode = MERC_DISTORTION_NO_DISTORTION;
			break;

		case MERC_DISRTORTION_DISTORT_IMAGE:
//			fReturnStatus = DistortVideoMercImage();
			fReturnStatus = DistortVideoMercImage( MERC_VIDEO_FACE_X, MERC_VIDEO_FACE_Y, MERC_VIDEO_FACE_WIDTH, MERC_VIDEO_FACE_HEIGHT );

			if( fReturnStatus )
				ubCurrentMercDistortionMode = MERC_DISTORTION_NO_DISTORTION;
			break;
	}
}


BOOLEAN PixelateVideoMercImage( BOOLEAN fUp, UINT16 usPosX, UINT16 usPosY, UINT16 usWidth, UINT16 usHeight)
{
	static UINT32	uiLastTime;
	UINT32	uiCurTime = GetJA2Clock();
	UINT16 *pBuffer=NULL, DestColor;
	UINT32 uiPitch;
	UINT16 i, j;
	static UINT8 ubPixelationAmount=255;
	BOOLEAN fReturnStatus=FALSE;
	i=0;

	pBuffer = (UINT16*)LockVideoSurface( FRAME_BUFFER, &uiPitch );
	Assert( pBuffer );

	if( ubPixelationAmount == 255 )
	{
		if( fUp )
			ubPixelationAmount = 1;
		else
			ubPixelationAmount = 4;
		uiLastTime = GetJA2Clock();
	}

	//is it time to change the animation
	if( ( uiCurTime - uiLastTime ) > 100 )
	{
		//if we are starting to pixelate the image
		if( fUp )
		{
			//the varying degrees of pixelation
			if( ubPixelationAmount <= 4 )
			{
				ubPixelationAmount++;
				fReturnStatus = FALSE;
			}
			else
			{
				ubPixelationAmount = 255;
				fReturnStatus = TRUE;
			}
		}
		//else we are pixelating down
		else
		{
			if( ubPixelationAmount > 1 )
			{
				ubPixelationAmount--;
				fReturnStatus = FALSE;
			}
			else
			{
				ubPixelationAmount = 255;
				fReturnStatus = TRUE;
			}
		}
		uiLastTime = GetJA2Clock();
	}
	else
		i=i;

	uiPitch /= 2;
	i=j=0;
	DestColor = pBuffer[ (j*uiPitch) + i ];

	for(j=usPosY; j<usPosY+usHeight; j++)
	{
		for(i=usPosX; i<usPosX+usWidth; i++)
		{
			//get the next color
			if( !(i % ubPixelationAmount) )
			{
				if( i < usPosX+usWidth-ubPixelationAmount)
					DestColor = pBuffer[ (j*uiPitch) + i+ubPixelationAmount/2];
				else
					DestColor = pBuffer[ (j*uiPitch) + i];
			}

			pBuffer[ (j*uiPitch) + i] = DestColor;
		}
	}

	UnLockVideoSurface( FRAME_BUFFER );

	return( fReturnStatus );
}






BOOLEAN DistortVideoMercImage( UINT16 usPosX, UINT16 usPosY, UINT16 usWidth, UINT16 usHeight )
{
	UINT32 uiPitch;
	UINT16 i, j;
	UINT16 *pBuffer=NULL, DestColor;
	UINT32 uiColor;
	UINT8 red, green, blue;
	static UINT16 usDistortionValue=255;
	UINT8	uiReturnValue;
	UINT16	usEndOnLine=0;

	pBuffer = (UINT16*)LockVideoSurface( FRAME_BUFFER, &uiPitch );
	Assert( pBuffer );

	uiPitch /= 2;
	j=MERC_VIDEO_FACE_Y;
	i=MERC_VIDEO_FACE_X;

	DestColor = pBuffer[ (j*uiPitch) + i ];

	if( usDistortionValue >= usPosY+usHeight )
	{
		usDistortionValue = 0;
		uiReturnValue = TRUE;
	}
	else
	{
		usDistortionValue++;

		uiReturnValue = FALSE;


		if( usDistortionValue + 10 >= usHeight )
			usEndOnLine = usHeight-1;
		else
			usEndOnLine = usDistortionValue + 10;


		for(j=usPosY+usDistortionValue; j<usPosY+usEndOnLine; j++)
		{
			for(i=usPosX; i<usPosX+usWidth; i++)
			{
				DestColor = pBuffer[ (j*uiPitch) + i ];

				uiColor = GetRGBColor( DestColor );

				red = (UINT8)uiColor;
				green = (UINT8)(uiColor >> 8);
				blue = (UINT8)(uiColor >> 16);

				DestColor = Get16BPPColor(FROMRGB( 255-red, 250-green, 250-blue) );

				pBuffer[ (j*uiPitch) + i ] = DestColor;
			}
		}
	}
	UnLockVideoSurface( FRAME_BUFFER );

	return(uiReturnValue);
}




BOOLEAN InitDestroyXToCloseVideoWindow( BOOLEAN fCreate )
{
	static BOOLEAN fButtonCreated=FALSE;

	//if we are asked to create the buttons and the button isnt already created
	if( fCreate && !fButtonCreated )
	{
		guiXToCloseMercVideoButtonImage = LoadButtonImage("LAPTOP\\CloseButton.sti", -1,0,-1,1,-1 );

		guiXToCloseMercVideoButton = QuickCreateButton( guiXToCloseMercVideoButtonImage, MERC_X_TO_CLOSE_VIDEO_X, MERC_X_TO_CLOSE_VIDEO_Y,
																	BUTTON_TOGGLE, MSYS_PRIORITY_HIGH,
																	DEFAULT_MOVE_CALLBACK, BtnXToCloseMercVideoButtonCallback);
		SetButtonCursor(guiXToCloseMercVideoButton, CURSOR_LAPTOP_SCREEN);

		fButtonCreated = TRUE;
	}

	//if we are asked to destroy the buttons and the buttons are created
	if( !fCreate && fButtonCreated )
	{
		UnloadButtonImage( guiXToCloseMercVideoButtonImage );
		RemoveButton( guiXToCloseMercVideoButton );
		fButtonCreated = FALSE;
	}

	return(TRUE);
}


void BtnXToCloseMercVideoButtonCallback(GUI_BUTTON *btn,INT32 reason)
{
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		if (btn->uiFlags & BUTTON_CLICKED_ON)
		{
			btn->uiFlags &= (~BUTTON_CLICKED_ON );

			//Stop speck from talking
//			ShutupaYoFace( giVideoSpeckFaceIndex );
			StopSpeckFromTalking( );

			//make sure we are done the intro speech
			gfDoneIntroSpeech = TRUE;

			//remove the video conf mode
			gubCurrentMercVideoMode = MERC_VIDEO_EXIT_VIDEO_MODE;

			gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;

			InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
		}
	}
	if(reason & MSYS_CALLBACK_REASON_LOST_MOUSE)
	{
		btn->uiFlags &= (~BUTTON_CLICKED_ON );
		InvalidateRegion(btn->Area.RegionTopLeftX, btn->Area.RegionTopLeftY, btn->Area.RegionBottomRightX, btn->Area.RegionBottomRightY);
	}
}


BOOLEAN DisplayMercVideoIntro( UINT16 usTimeTillFinish )
{
	UINT32	uiCurTime = GetJA2Clock();
	static UINT32	uiLastTime=0;

	//init variable
	if( uiLastTime == 0 )
		uiLastTime = uiCurTime;


	ColorFillVideoSurfaceArea( FRAME_BUFFER, MERC_VIDEO_FACE_X, MERC_VIDEO_FACE_Y, MERC_VIDEO_FACE_X+MERC_VIDEO_FACE_WIDTH,	MERC_VIDEO_FACE_Y+MERC_VIDEO_FACE_HEIGHT, Get16BPPColor( FROMRGB( 0, 0, 0 ) ) );

	//if the intro is done
	if( (uiCurTime - uiLastTime) > usTimeTillFinish )
	{
		uiLastTime = 0;
		return(TRUE);
	}
	else
		return(FALSE);
}


void HandleTalkingSpeck()
{
	BOOLEAN fIsSpeckTalking = TRUE;

	switch( gubCurrentMercVideoMode )
	{
		//Init the video conferencing
		case MERC_VIDEO_INIT_VIDEO_MODE:
			//perform some opening animation.	When its done start Speck talking

			//if the intro is finished
			if( DisplayMercVideoIntro( MERC_INTRO_TIME ) )
			{
				//NULL out the string
				gsSpeckDialogueTextPopUp[0] = '\0';

				//Start speck talking
				if( gusMercVideoSpeckSpeech != MERC_VIDEO_SPECK_SPEECH_NOT_TALKING || 	gusMercVideoSpeckSpeech != MERC_VIDEO_SPECK_HAS_TO_TALK_BUT_QUOTE_NOT_CHOSEN_YET )
					StartSpeckTalking( gusMercVideoSpeckSpeech );

				gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;
				gubCurrentMercVideoMode = MERC_VIDEO_VIDEO_MODE;
			}
			break;

		//Display his talking and blinking face
		case MERC_VIDEO_VIDEO_MODE:

			//Make sure the accounts button does not overwrite the dialog text
//			ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
			//def:

			if( gfJustEnteredMercSite && gubArrivedFromMercSubSite != MERC_CAME_FROM_OTHER_PAGE || gfFirstTimeIntoMERCSiteSinceEnteringLaptop )
			{
				gfFirstTimeIntoMERCSiteSinceEnteringLaptop = FALSE;
				GetSpeckConditionalOpening( FALSE );
				gfJustEnteredMercSite = FALSE;
			}
			else
			{
				fIsSpeckTalking = HandleSpeckTalking( FALSE );

				if( !fIsSpeckTalking )
					fIsSpeckTalking = GetSpeckConditionalOpening( FALSE );

				//if speck didnt start talking, see if he just hired someone
				if( !fIsSpeckTalking )
				{
					fIsSpeckTalking = ShouldSpeckStartTalkingDueToActionOnSubPage();
				}
			}

			if( !fIsSpeckTalking )
				gubCurrentMercVideoMode = MERC_VIDEO_EXIT_VIDEO_MODE;

			if( gfDisplaySpeckTextBox && gGameSettings.fOptions[ TOPTION_SUBTITLES ] )
			{
				if( !gfInMercSite )
				{
					StopSpeckFromTalking( );
					return;
				}


				if( gsSpeckDialogueTextPopUp[0] != L'\0' )
				{
//					DrawButton( guiAccountBoxButton );
//					ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;

					if( iMercPopUpBox != -1 )
					{
#ifdef JA2UB
//JA25: removed							DrawButton( guiAccountBoxButton );
//JA25: removed							ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#else
						DrawButton( guiAccountBoxButton );
						ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#endif

						RenderMercPopUpBoxFromIndex( iMercPopUpBox, gusSpeckDialogueX, MERC_TEXT_BOX_POS_Y, FRAME_BUFFER);
					}
				}
			}

			break;

		// shut down the video conferencing
		case MERC_VIDEO_EXIT_VIDEO_MODE:

			//if the exit animation is finished, exit the video conf window
			if( DisplayMercVideoIntro( MERC_EXIT_TIME ) )
			{
				StopSpeckFromTalking( );

				//Delete the face
				DeleteFace( giVideoSpeckFaceIndex	);
				InitDestroyXToCloseVideoWindow( FALSE );

				gfRedrawMercSite = TRUE;
				gfMercVideoIsBeingDisplayed = FALSE;

				//Remove the merc popup
				RemoveSpeckPopupTextBox();

				//maybe display ending animation
				gubCurrentMercVideoMode = MERC_VIDEO_NO_VIDEO_MODE;
			}
			else
			{
				//else we are done the exit animation.	The area is not being invalidated anymore
				InvalidateRegion( MERC_VIDEO_FACE_X, MERC_VIDEO_FACE_Y, MERC_VIDEO_FACE_X+MERC_VIDEO_FACE_WIDTH,	MERC_VIDEO_FACE_Y+MERC_VIDEO_FACE_HEIGHT );
			}
			break;
		}
}

void DisplayTextForSpeckVideoPopUp(STR16 pString)
{
	UINT16	usActualHeight;
	INT32		iOldMercPopUpBoxId = iMercPopUpBox;

	//If the user has selected no subtitles
	if( !gGameSettings.fOptions[ TOPTION_SUBTITLES ] )
		return;

//	wcscpy(gsSpeckDialogueTextPopUp, pString);
	//add the "" around the speech.
#ifdef TAIWANESE
	swprintf( gsSpeckDialogueTextPopUp, L"%s", pString );
#else
	swprintf( gsSpeckDialogueTextPopUp, L"\"%s\"", pString );
#endif

	gfDisplaySpeckTextBox = TRUE;

	//Set this so the popup box doesnt render in RenderMercs()
	iMercPopUpBox = -1;

	//Render the screen to get rid of any old text popup boxes
	RenderMercs();

	iMercPopUpBox = iOldMercPopUpBoxId;

	if( gfMercVideoIsBeingDisplayed && gfMercSiteScreenIsReDrawn )
	{
		DrawMercVideoBackGround();
	}

	//never use it anymore
	//SET_USE_WINFONTS( TRUE );
	//SET_WINFONT( giSubTitleWinFont );
	//Create the popup box
	iMercPopUpBox = PrepareMercPopupBox( iMercPopUpBox, BASIC_MERC_POPUP_BACKGROUND, BASIC_MERC_POPUP_BORDER, gsSpeckDialogueTextPopUp, 300, 0, 0, 0, &gusSpeckDialogueActualWidth, &usActualHeight);
	//SET_USE_WINFONTS( FALSE );

	gusSpeckDialogueX = iScreenWidthOffset + 111 + ((640 - 111) / 2 - (gusSpeckDialogueActualWidth / 2));

	//Render the pop box
	RenderMercPopUpBoxFromIndex( iMercPopUpBox, gusSpeckDialogueX, MERC_TEXT_BOX_POS_Y, FRAME_BUFFER);

	//check to make sure the region is not already initialized
	if( !( gMercSiteSubTitleMouseRegion.uiFlags & MSYS_REGION_EXISTS ) )
	{
		MSYS_DefineRegion( &gMercSiteSubTitleMouseRegion, gusSpeckDialogueX, MERC_TEXT_BOX_POS_Y, (INT16)(gusSpeckDialogueX + gusSpeckDialogueActualWidth), (INT16)(MERC_TEXT_BOX_POS_Y + usActualHeight), MSYS_PRIORITY_HIGH,
									CURSOR_LAPTOP_SCREEN, MSYS_NO_CALLBACK, MercSiteSubTitleRegionCallBack );
		MSYS_AddRegion( &gMercSiteSubTitleMouseRegion );
	}
}



void CheatToGetAll5Merc()
{
	LaptopSaveInfo.guiNumberOfMercPaymentsInDays += 20;

/*
	LaptopSaveInfo.gbNumDaysTillFirstMercArrives = 1;
	LaptopSaveInfo.gbNumDaysTillSecondMercArrives = 1;
	LaptopSaveInfo.gbNumDaysTillThirdMercArrives = 1;
	LaptopSaveInfo.gbNumDaysTillFourthMercArrives = 1;
*/
	LaptopSaveInfo.gubLastMercIndex = NUMBER_MERCS_AFTER_FOURTH_MERC_ARRIVES;
}


BOOLEAN	GetSpeckConditionalOpening( BOOLEAN fJustEnteredScreen )
{
	static UINT16	usQuoteToSay=MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;
	UINT8	ubCnt;
	BOOLEAN	fCanSayLackOfPaymentQuote = TRUE;
	BOOLEAN fCanUseIdleTag = FALSE;

	//If we just entered the screen, reset some variables
	if( fJustEnteredScreen )
	{
		gfDoneIntroSpeech = FALSE;
#ifdef JA2UB
		usQuoteToSay = SPECK_QUOTE_NEW_INTRO_1;
#else
		usQuoteToSay = 0;
#endif
		return( FALSE );
	}

	//if we are done the intro speech, or arrived from a sub page, get out of the function
	if( gfDoneIntroSpeech || gubArrivedFromMercSubSite != MERC_CAME_FROM_OTHER_PAGE )
	{
		return( FALSE );
	}

	gfDoneIntroSpeech = TRUE;

	//set the opening quote based on if the player has been here before

#ifdef JA2UB
	if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_FIRST_VISIT && usQuoteToSay <= SPECK_QUOTE_NEW_INTRO_7 ) //!= 0 )
#else
	if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_FIRST_VISIT && usQuoteToSay <= 8 ) //!= 0 )
#endif
	{
		StartSpeckTalking( usQuoteToSay );
		usQuoteToSay++;
#ifdef JA2UB
		if( usQuoteToSay <= SPECK_QUOTE_NEW_INTRO_7 )
#else
		if( usQuoteToSay <= 8 )
#endif
			gfDoneIntroSpeech = FALSE;
	}
#ifdef JA2UB
	//else if its the first time back since the laptop went down
	else if( gJa25SaveStruct.fHaveAimandMercOffferItems && !HasImportantSpeckQuoteBeingSaid( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_1 ) )
	{
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_1 );
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_2 );
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_3 );
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_4 );
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_5 );
		StartSpeckTalking( SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_6 );
	} 	
#else
	//if its the players second visit
	else if( LaptopSaveInfo.ubPlayerBeenToMercSiteStatus == MERC_SITE_SECOND_VISIT )
	{
		StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_1_TOUGH_START );
		fCanUseIdleTag = TRUE;
	}
#endif
	// We have been here at least 2 times before, Check which quote we should use
	else
	{
		//if the player has not hired any MERC mercs before
		// CJC Dec 1 2002: fixing this, so near-bankrupt msg will play
#ifdef JA2UB		
		if( !IsAnyMercMercsHired( ) && CalcMercDaysServed() == 0)
			StartSpeckTalking( SPECK_QUOTE_DEFAULT_INTRO_HAVENT_HIRED_MERCS );
		else
			StartSpeckTalking( SPECK_QUOTE_DEFAULT_INTRO_HAVE_HIRED_MERCS );
#endif

#ifdef JA2UB
//JA25: not using quote quote
#else
		//if the player has not hired any MERC mercs before
		if( !IsAnyMercMercsHired( ) && CalcMercDaysServed() == 0)
		{
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_2_BUSINESS_BAD );
		}
#endif
#ifdef JA2UB
//JA25: not using quote quote
#else
		//else if it is the first visit since the server went down
		else if( LaptopSaveInfo.fFirstVisitSinceServerWentDown == TRUE )
		{
			LaptopSaveInfo.fFirstVisitSinceServerWentDown = 2;
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_9_FIRST_VISIT_SINCE_SERVER_WENT_DOWN );
			fCanUseIdleTag = TRUE;
		}
#endif
/*
		//else if new mercs are available
		else if( LaptopSaveInfo.fNewMercsAvailableAtMercSite )
		{
			LaptopSaveInfo.fNewMercsAvailableAtMercSite = FALSE;

			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_11_NEW_MERCS_AVAILABLE );
		}
*/
		//else if lots of MERC mercs are DEAD, and speck can say the quote ( dont want him to continously say it )
#ifdef JA2UB
		if( CountNumberOfMercMercsWhoAreDead() >= 2 && LaptopSaveInfo.ubSpeckCanSayPlayersLostQuote )
#else
		else if( CountNumberOfMercMercsWhoAreDead() >= 2 && LaptopSaveInfo.ubSpeckCanSayPlayersLostQuote )
#endif
		{
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_12_PLAYERS_LOST_MERCS );

			//Set it so speck Wont say the quote again till someone else dies
			LaptopSaveInfo.ubSpeckCanSayPlayersLostQuote = 0;
		}
#ifdef JA2UB
//JA25: not using quote quote
#else
		//else if player owes lots of money
		else if( LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_ACCOUNT_SUSPENDED )
		{
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_5_PLAYER_OWES_SPECK_ACCOUNT_SUSPENDED );

			fCanSayLackOfPaymentQuote = FALSE;
		}
#endif
		//else if the player owes speck a large sum of money, have speck say so
#ifdef JA2UB
//JA25: not using quote quote
#else
		else if( CalculateHowMuchPlayerOwesSpeck() > 5000 )
		{
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_6_PLAYER_OWES_SPECK_ALMOST_BANKRUPT_1 );
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_6_PLAYER_OWES_SPECK_ALMOST_BANKRUPT_2 );

			fCanSayLackOfPaymentQuote = FALSE;
		}
#endif
		else
		{
#ifdef JA2UB
			UINT8	ubNumMercsDead = NumberOfMercMercsDead();
			BOOLEAN fCanUseIdleTag = FALSE;
#endif
			UINT8	ubRandom = ( UINT8 ) Random( 100 );
#ifdef JA2UB
//JA25: not using quote quote
#else
			//if business is good
//			if( ubRandom < 40 && ubNumMercsDead < 2 && CountNumberOfMercMercsHired() > 1 )
			if( ubRandom < 40 && AreAnyOfTheNewMercsAvailable() && CountNumberOfMercMercsHired() > 1 )
			{
				StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_3_BUSINESS_GOOD );
				fCanUseIdleTag = TRUE;
			}
#endif
			//or if still trying to recruit ( the last recruit hasnt arrived and the player has paid for some of his mercs )
//			else if( ubRandom < 80 && LaptopSaveInfo.gbNumDaysTillFourthMercArrives != -1 && LaptopSaveInfo.gbNumDaysTillFirstMercArrives < MERC_NUM_DAYS_TILL_FIRST_MERC_AVAILABLE )
#ifdef JA2UB
//JA25: not using quote quote
#else
			else if( ubRandom < 80 && gConditionsForMercAvailability[ LaptopSaveInfo.ubLastMercAvailableId ].usMoneyPaid <= LaptopSaveInfo.uiTotalMoneyPaidToSpeck && CanMercBeAvailableYet( LaptopSaveInfo.ubLastMercAvailableId ) )
			{
				StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_4_TRYING_TO_RECRUIT );
				fCanUseIdleTag = TRUE;
			}

			//else use the generic opening
			else
#endif
			{
#ifdef JA2UB
//JA25: not using quote quote
#else
				StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_10_GENERIC_OPENING );

				fCanUseIdleTag = TRUE;

//JA25: not using quote quote
				//if the	merc hasnt said the line before
				if( !LaptopSaveInfo.fSaidGenericOpeningInMercSite )
				{
					LaptopSaveInfo.fSaidGenericOpeningInMercSite = TRUE;
					StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_10_TAG_FOR_20 );
				}
			}
#endif
		}
#ifdef JA2UB
//no UB
#else
		if( fCanUseIdleTag )
		{
			UINT8 ubRandom = Random( 100 );

			if( ubRandom < 50 )
			{
				ubRandom = Random( 4 );

				switch( ubRandom )
				{
					case 0:
						StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_ON_AFTER_OTHER_TAGS_1 );
						break;
					case 1:
						StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_ON_AFTER_OTHER_TAGS_2 );
						break;
					case 2:
						StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_ON_AFTER_OTHER_TAGS_3 );
						break;
					case 3:
						StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_ON_AFTER_OTHER_TAGS_4 );
						break;
					default:
						Assert( 0 );
				}
			}
#endif
		}
	}

#ifdef JA2UB
//JA25: not using quote quote
#else
	//If Speck has sent an email to the player, and the player still hasnt paid, has speck complain about it.
	// CJC Dec 1 2002 ACTUALLY HOOKED IN THAT CHECK
	if (fCanSayLackOfPaymentQuote)
	{
		if( LaptopSaveInfo.uiSpeckQuoteFlags & SPECK_QUOTE__SENT_EMAIL_ABOUT_LACK_OF_PAYMENT )
		{
			LaptopSaveInfo.uiSpeckQuoteFlags &= ~SPECK_QUOTE__SENT_EMAIL_ABOUT_LACK_OF_PAYMENT;

			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_PLAYER_OWES_MONEY );
		}
	}

	//if new mercs are available
	if( LaptopSaveInfo.fNewMercsAvailableAtMercSite )
	{
		LaptopSaveInfo.fNewMercsAvailableAtMercSite = FALSE;

		StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_11_NEW_MERCS_AVAILABLE );
	}
#endif

	//if any mercs are dead
	if( IsAnyMercMercsDead() )
	{
		UINT8 ubMercID;
		//if no merc has died before
#ifdef JA2UB
//JA25: not using quote quote
#else
		if( !LaptopSaveInfo.fHasAMercDiedAtMercSite )
		{
			LaptopSaveInfo.fHasAMercDiedAtMercSite = TRUE;
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_FIRST_MERC_DIES );
		}
#endif
		//loop through all the mercs and see if any are dead and the quote is not said
		for( ubCnt=0; ubCnt<NUMBER_OF_MERCS; ubCnt++ )
		{
			ubMercID = GetMercIDFromMERCArray( (UINT8) ubCnt );
			//if the merc is dead
			if( IsMercDead( ubMercID ) )
			{
				//if the quote has not been said
				if( !( gMercProfiles[ ubMercID ].ubMiscFlags3 & PROFILE_MISC_FLAG3_MERC_MERC_IS_DEAD_AND_QUOTE_SAID ) )
				{
					//set the flag
					gMercProfiles[ ubMercID ].ubMiscFlags3 |= PROFILE_MISC_FLAG3_MERC_MERC_IS_DEAD_AND_QUOTE_SAID;

					switch( ubMercID )
					{
						case BIFF:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_BIFF_IS_DEAD );
							break;
						case HAYWIRE:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_HAYWIRE_IS_DEAD );
							break;
						case GASKET:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_GASKET_IS_DEAD );
							break;
						case RAZOR:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_RAZOR_IS_DEAD );
							break;
						case FLO:
							//if biff is dead
							if( IsMercDead( BIFF ) )
								StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_FLO_IS_DEAD_BIFF_IS_DEAD );
							else
							{
								StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_FLO_IS_DEAD_BIFF_ALIVE );
								MakeBiffAwayForCoupleOfDays();
							}
							break;

						case GUMPY:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_GUMPY_IS_DEAD );
							break;
						case LARRY_NORMAL:
						case LARRY_DRUNK:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_LARRY_IS_DEAD );
							break;
						case COUGAR:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_COUGER_IS_DEAD );
							break;
						case NUMB:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_NUMB_IS_DEAD );
							break;
						case BUBBA:
							StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_BUBBA_IS_DEAD );
							break;
#ifdef JA2UB
						case 58://GASTON:
							StartSpeckTalking( SPECK_QUOTE_GASTON_DEAD );
							break;
						case 59://STOGIE:
							StartSpeckTalking( SPECK_QUOTE_STOGIE_DEAD );
							break;
#else
						case GASTON:
							StartSpeckTalking( SPECK_QUOTE_GASTON_DEAD );
							break;
						case STOGIE:
							StartSpeckTalking( SPECK_QUOTE_STOGIE_DEAD );
							break;
#endif
					};

				}
			}
		}
	}

#ifdef JA2UB
//JA25: not using quote quote
#else
	//if flo has married the cousin
	if( gubFact[ FACT_PC_MARRYING_DARYL_IS_FLO ] )
	{
		//if speck hasnt said the quote before, and Biff is NOT dead
		if( !LaptopSaveInfo.fSpeckSaidFloMarriedCousinQuote && !IsMercDead( BIFF ) )
		{
			StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_FLO_MARRIED_A_COUSIN_BIFF_IS_ALIVE );
			LaptopSaveInfo.fSpeckSaidFloMarriedCousinQuote = TRUE;

			MakeBiffAwayForCoupleOfDays();
		}
	}
#endif

	//if larry has relapsed
	if( HasLarryRelapsed() && !( LaptopSaveInfo.uiSpeckQuoteFlags & SPECK_QUOTE__ALREADY_TOLD_PLAYER_THAT_LARRY_RELAPSED ) )
	{
		LaptopSaveInfo.uiSpeckQuoteFlags |= SPECK_QUOTE__ALREADY_TOLD_PLAYER_THAT_LARRY_RELAPSED;

		StartSpeckTalking( SPECK_QUOTE_ALTERNATE_OPENING_TAG_LARRY_RELAPSED );
	}

	return( TRUE );
}




BOOLEAN IsAnyMercMercsHired( )
{
	UINT8	ubMercID;
	UINT8	i;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( i );
		if( IsMercOnTeam( ubMercID ) )
		{
			return( TRUE );
		}
	}

	return( FALSE );
}

BOOLEAN IsAnyMercMercsDead()
{
	UINT8	i;
	UINT8 ubMercID;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( (UINT8) i );
		if( gMercProfiles[ ubMercID ].bMercStatus == MERC_IS_DEAD )
			return( TRUE );
	}

	return( FALSE );
}


UINT8 NumberOfMercMercsDead()
{
	UINT8	i;
	UINT8	ubNumDead = 0;
	UINT8	ubMercID;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( (UINT8) i );
		if( gMercProfiles[ ubMercID ].bMercStatus == MERC_IS_DEAD )
			ubNumDead++;
	}

	return( ubNumDead );
}



UINT8	CountNumberOfMercMercsHired()
{
	UINT8	ubMercID;
	UINT8	i;
	UINT8	ubCount=0;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( i );
		if( IsMercOnTeam( ubMercID ) )
		{
			ubCount++;
		}
	}

	return( ubCount );
}


UINT8	CountNumberOfMercMercsWhoAreDead()
{
	UINT8	i;
	UINT8	ubCount=0;
	UINT8	ubMercID;

	//loop through all of the hired mercs from M.E.R.C.
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		ubMercID = GetMercIDFromMERCArray( (UINT8) i );

		if( gMercProfiles[ ubMercID ].bMercStatus == MERC_IS_DEAD )
		{
			ubCount++;
		}
	}

	return( ubCount );
}




//Mouse Call back for the pop up text box
void MercSiteSubTitleRegionCallBack( MOUSE_REGION * pRegion, INT32 iReason )
{
	if (iReason & MSYS_CALLBACK_REASON_INIT)
	{
	}
	else if(iReason & MSYS_CALLBACK_REASON_LBUTTON_UP || iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		StopSpeckFromTalking( );
	}
}


void RemoveSpeckPopupTextBox()
{
	if( iMercPopUpBox == -1 )
		return;

	if( gMercSiteSubTitleMouseRegion.uiFlags & MSYS_REGION_EXISTS )
		MSYS_RemoveRegion( &gMercSiteSubTitleMouseRegion );

	if( RemoveMercPopupBoxFromIndex( iMercPopUpBox ) )
	{
		iMercPopUpBox = -1;
	}

	//redraw the screen
	gfRedrawMercSite = TRUE;
}



void HandlePlayerHiringMerc( UINT8 ubHiredMercID )
{
	gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;

	//if the players is in good finacial standing
//DEF: 3/19/99: Dont know why this was done
//	if( LaptopSaveInfo.iCurrentBalance >= 2000 )
	{
		//determine which quote to say based on the merc that was hired
		switch( ubHiredMercID )
		{
			//Biff is hired
			case BIFF:
				//if Larry is available, advertise for larry
				if( IsMercMercAvailable( LARRY_NORMAL ) || IsMercMercAvailable( LARRY_DRUNK ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_BIFF_SPECK_PLUGS_LARRY );

				//if flo is available, advertise for flo
				if( IsMercMercAvailable( FLO ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_BIFF_SPECK_PLUGS_FLO );
				break;

			//haywire is hired
			case HAYWIRE:
				//if razor is available, advertise for razor
				if( IsMercMercAvailable( RAZOR ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_HAYWIRE_SPECK_PLUGS_RAZOR );
				break;

			//razor is hired
			case RAZOR:
				//if haywire is available, advertise for haywire
				if( IsMercMercAvailable( HAYWIRE ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_RAZOR_SPECK_PLUGS_HAYWIRE );
				break;


			//flo is hired
			case FLO:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( BIFF ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_FLO_SPECK_PLUGS_BIFF );
				break;


			//larry is hired
			case LARRY_NORMAL:
			case LARRY_DRUNK:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( BIFF ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYERS_HIRES_LARRY_SPECK_PLUGS_BIFF );
				break;
#ifdef JA2UB
			//Gaston is hired
			case 58: //GASTON:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( FLO ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYER_HIRES_GASTON );
				break;

			//Stogie is hired
			case 59: //STOGIE:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( BIFF ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYER_HIRES_STOGIE );
				break;
#else
			//Gaston is hired
			case GASTON:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( FLO ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYER_HIRES_GASTON );
				break;

			//Stogie is hired
			case STOGIE:
				//if biff is available, advertise for biff
				if( IsMercMercAvailable( BIFF ) )
					StartSpeckTalking( SPECK_QUOTE_PLAYER_HIRES_STOGIE );
				break;
#endif

		}
	}

	gubArrivedFromMercSubSite = MERC_CAME_FROM_HIRE_PAGE;
}


BOOLEAN IsMercMercAvailable( UINT8 ubMercID )
{
	UINT8	cnt;

	//loop through the array of mercs
	for( cnt=0; cnt<NUM_PROFILES; cnt++ ) //LaptopSaveInfo.gubLastMercIndex; cnt++ )
	{
		//if this is the merc
		if( GetMercIDFromMERCArray( cnt ) == ubMercID )
		{
			//if the merc is available, and Not dead
//			if( gMercProfiles[ ubMercID ].bMercStatus == 0 && !IsMercDead( ubMercID ) )
			if( IsMercHireable( ubMercID ) )
				return( TRUE );
		}
	}

	return( FALSE );
}

BOOLEAN ShouldSpeckStartTalkingDueToActionOnSubPage()
{
	//if the merc came from the hire screen
	if( gfJustHiredAMercMerc )
	{

		HandlePlayerHiringMerc( GetMercIDFromMERCArray( gubCurMercIndex ) );
#ifdef JA2UB
		//if it hasnt been said, say the better equipment quote
		if( !HasImportantSpeckQuoteBeingSaid( SPECK_QUOTE_BETTER_STARTING_EQPMNT_TAG_ON ) )
		{
			StartSpeckTalking( SPECK_QUOTE_BETTER_STARTING_EQPMNT_TAG_ON );
		}
#endif
		//get speck to say the thank you 
		if( Random( 100 ) > 50 )
			StartSpeckTalking( SPECK_QUOTE_GENERIC_THANKS_FOR_HIRING_MERCS_1 );
		else
			StartSpeckTalking( SPECK_QUOTE_GENERIC_THANKS_FOR_HIRING_MERCS_2 );
#ifdef JA2UB
		//if it hasnt been said, say the encouraged to shop quote
		if( !HasImportantSpeckQuoteBeingSaid( SPECK_QUOTE_ENCOURAGE_SHOP_TAG_ON ) )
		{
			StartSpeckTalking( SPECK_QUOTE_ENCOURAGE_SHOP_TAG_ON );
		}
#endif
		gfJustHiredAMercMerc = FALSE;
//				gfDoneIntroSpeech = TRUE;

		return( TRUE );
	}



	return( FALSE );
}



BOOLEAN ShouldSpeckSayAQuote()
{


	//if we are entering from anywhere except a sub page, and we should say the opening quote
	if( gfJustEnteredMercSite && gubArrivedFromMercSubSite == MERC_CAME_FROM_OTHER_PAGE )
	{
		//if the merc has something to say
		if( gusMercVideoSpeckSpeech != MERC_VIDEO_SPECK_SPEECH_NOT_TALKING )
			return( FALSE );
	}


	//if the player just hired a merc
	if( gfJustHiredAMercMerc )
	{
		gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_HAS_TO_TALK_BUT_QUOTE_NOT_CHOSEN_YET;
		return( TRUE );

/*
		//if the merc has something to say
		if( gusMercVideoSpeckSpeech != MERC_VIDEO_SPECK_SPEECH_NOT_TALKING )
			return( TRUE );
		else
		{
			gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_HAS_TO_TALK_BUT_QUOTE_NOT_CHOSEN_YET;
			return( TRUE );
		}
*/
	}

	//If it is the first time into the merc site
	if( gfFirstTimeIntoMERCSiteSinceEnteringLaptop )
	{
//		gfFirstTimeIntoMERCSiteSinceEnteringLaptop = FALSE;
		gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_HAS_TO_TALK_BUT_QUOTE_NOT_CHOSEN_YET;
		return( TRUE );
	}

/*
	//if we are entering from anywhere except a sub page
	if( gubArrivedFromMercSubSite == MERC_CAME_FROM_OTHER_PAGE )
	{
		GetSpeckConditionalOpening( FALSE );
		return( TRUE );
	}
*/
	return( FALSE );
}

void HandleSpeckIdleConversation( BOOLEAN fReset )
{
	static UINT32	uiLastTime=0;
	UINT32	uiCurTime = GetJA2Clock();
	INT16		sLeastSaidQuote;

	//if we should reset the variables
	if( fReset )
	{
		uiLastTime = GetJA2Clock();
		return;
	}



	if( ( uiCurTime - uiLastTime ) > SPECK_IDLE_CHAT_DELAY )
	{

		//if Speck is not talking
		if( !gfMercVideoIsBeingDisplayed )
		{
			sLeastSaidQuote = GetRandomQuoteThatHasBeenSaidTheLeast( );

			if( sLeastSaidQuote != -1 )
				gusMercVideoSpeckSpeech = (UINT8)sLeastSaidQuote;

			//Say the aim slander quotes the least
			if( sLeastSaidQuote >= 47 && sLeastSaidQuote <= 57 )
			{
				IncreaseMercRandomQuoteValue( (UINT8)sLeastSaidQuote, 1 );
			}
#ifdef JA2UB			
			//if its the biff is dead quote, only say the quote once
			else if( sLeastSaidQuote == SPECK_QUOTE_BIFF_DEAD_WHEN_IMPORTING )
				IncreaseMercRandomQuoteValue( (UINT8)sLeastSaidQuote, 255 );
#endif
			else if( sLeastSaidQuote != -1 )
				IncreaseMercRandomQuoteValue( (UINT8)sLeastSaidQuote, 3 );
		}

		uiLastTime = GetJA2Clock();
	}
}



INT16	GetRandomQuoteThatHasBeenSaidTheLeast( )
{
	UINT8	cnt;
	INT16	sSmallestNumber=255;

	for( cnt=0; cnt<MERC_NUMBER_OF_RANDOM_QUOTES; cnt++)
	{
		//if the quote can be said ( the merc has not been hired )
		if( CanMercQuoteBeSaid( gNumberOfTimesQuoteSaid[cnt].ubQuoteID ) )
		{
			//if this quote has been said less times then the last one
			if( gNumberOfTimesQuoteSaid[cnt].uiNumberOfTimesQuoteSaid < gNumberOfTimesQuoteSaid[ sSmallestNumber ].uiNumberOfTimesQuoteSaid )
			{
				sSmallestNumber = cnt;
			}
		}
	}

	if( sSmallestNumber == 255 )
		return( -1 );
	else
		return( gNumberOfTimesQuoteSaid[ sSmallestNumber ].ubQuoteID );
}

void IncreaseMercRandomQuoteValue( UINT8 ubQuoteID, UINT8 ubValue )
{
	UINT8	cnt;

	for( cnt=0; cnt<MERC_NUMBER_OF_RANDOM_QUOTES; cnt++)
	{
		if( gNumberOfTimesQuoteSaid[ cnt ].ubQuoteID == ubQuoteID )
		{
			if( gNumberOfTimesQuoteSaid[ cnt ].uiNumberOfTimesQuoteSaid + ubValue > 255 )
				gNumberOfTimesQuoteSaid[ cnt ].uiNumberOfTimesQuoteSaid = 255;
			else
				gNumberOfTimesQuoteSaid[ cnt ].uiNumberOfTimesQuoteSaid += ubValue;
			break;
		}
	}
}


void StopSpeckFromTalking( )
{
	if( giVideoSpeckFaceIndex == -1 )
		return;

	//Stop speck from talking
	ShutupaYoFace( giVideoSpeckFaceIndex );

	RemoveSpeckPopupTextBox();

	gusMercVideoSpeckSpeech = MERC_VIDEO_SPECK_SPEECH_NOT_TALKING;
}

BOOLEAN	HasLarryRelapsed()
{
	return( CheckFact( FACT_LARRY_CHANGED, 0 ) );
}


//Gets Called on each enter into laptop.
void EnterInitMercSite()
{
	gfFirstTimeIntoMERCSiteSinceEnteringLaptop = TRUE;
	gubCurMercIndex = 0;
}



BOOLEAN ShouldTheMercSiteServerGoDown()
{
	UINT32	uiDay = GetWorldDay();

	// If the merc site has never gone down, the first new merc has shown ( which shows the player is using the site ),
	// and the players account status is ok ( cant have the merc site going down when the player owes him money, player may lose account that way )
//	if( !LaptopSaveInfo.fMercSiteHasGoneDownYet	&& LaptopSaveInfo.gbNumDaysTillThirdMercArrives <= 6 && LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_ACCOUNT_VALID )
	if( !LaptopSaveInfo.fMercSiteHasGoneDownYet	&& LaptopSaveInfo.ubLastMercAvailableId >= 1 && LaptopSaveInfo.gubPlayersMercAccountStatus == MERC_ACCOUNT_VALID )
	{
		if( Random( 100 ) < ( uiDay * 2 + 10 ) )
		{
			return( TRUE );
		}
		else
		{
			return( FALSE );
		}
	}

	return( FALSE );
}

#ifdef JA2UB
//no UB
#else
void GetMercSiteBackOnline()
{
	//Add an email telling the user the site is back up
	AddEmail( MERC_NEW_SITE_ADDRESS, MERC_NEW_SITE_ADDRESS_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), -1, -1 , TYPE_EMAIL_EMAIL_EDT);

	//Set a flag indicating that the server just went up ( so speck can make a comment when the player next visits the site )
	LaptopSaveInfo.fFirstVisitSinceServerWentDown = TRUE;
}
#endif

void DrawMercVideoBackGround()
{
	HVOBJECT hPixHandle;

	GetVideoObject(&hPixHandle, guiMercVideoPopupBackground);
	BltVideoObject(FRAME_BUFFER, hPixHandle, 0,MERC_VIDEO_BACKGROUND_X, MERC_VIDEO_BACKGROUND_Y, VO_BLT_SRCTRANSPARENCY, NULL);

	//put the title on the window
	DrawTextToScreen(MercHomePageText[MERC_SPECK_COM], MERC_X_VIDEO_TITLE_X, MERC_X_VIDEO_TITLE_Y, 0, MERC_VIDEO_TITLE_FONT, MERC_VIDEO_TITLE_COLOR, FONT_MCOLOR_BLACK, FALSE, LEFT_JUSTIFIED);
	InvalidateRegion(MERC_VIDEO_BACKGROUND_X, MERC_VIDEO_BACKGROUND_Y, (MERC_VIDEO_BACKGROUND_X + MERC_VIDEO_BACKGROUND_WIDTH), (MERC_VIDEO_BACKGROUND_Y + MERC_VIDEO_BACKGROUND_HEIGHT) );
}

void DisableMercSiteButton()
{
	if( iMercPopUpBox != -1 )
	{
#ifdef JA2UB
//JA25: removed			ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#else
		ButtonList[ guiAccountBoxButton ]->uiFlags |= BUTTON_FORCE_UNDIRTY;
#endif
	}
}

BOOLEAN CanMercQuoteBeSaid( UINT32 uiQuoteID )
{
	BOOLEAN fRetVal = TRUE;

	//switch onb the quote being said, if hes plugging a merc that has already been hired, dont say it
	switch( uiQuoteID )
	{
		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_BIFF:
			if( !IsMercMercAvailable( BIFF ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_HAYWIRE:
			if( !IsMercMercAvailable( HAYWIRE ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_GASKET:
			if( !IsMercMercAvailable( GASKET ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_RAZOR:
			if( !IsMercMercAvailable( RAZOR ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_FLO:
			if( !IsMercMercAvailable( FLO ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_GUMPY:
			if( !IsMercMercAvailable( GUMPY ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_LARRY:
			if( !IsMercMercAvailable( LARRY_NORMAL ) || IsMercMercAvailable( LARRY_DRUNK ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_COUGER:
			if( !IsMercMercAvailable( COUGAR ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_NUMB:
			if( !IsMercMercAvailable( NUMB ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_PLAYER_NOT_DOING_ANYTHING_SPECK_SELLS_BUBBA:
			if( !IsMercMercAvailable( BUBBA ) )
				fRetVal = FALSE;
			break;
#ifdef JA2UB
		case SPECK_QUOTE_BIFF_DEAD_WHEN_IMPORTING:
			if( !gJa25SaveStruct.fBiffWasKilledWhenImportingSave )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_ADVERTISE_GASTON:
			if( !IsMercMercAvailable( 58 ) )//GASTON
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_ADVERTISE_STOGIE:
			if( !IsMercMercAvailable( 59 ) )//STOGIE
				fRetVal = FALSE;
			break;
#else
		case SPECK_QUOTE_ADVERTISE_GASTON:
			if( !IsMercMercAvailable( GASTON ) )
				fRetVal = FALSE;
			break;

		case SPECK_QUOTE_ADVERTISE_STOGIE:
			if( !IsMercMercAvailable( STOGIE ) )
				fRetVal = FALSE;
			break;
#endif
	}


	return( fRetVal );
}


void InitializeNumDaysMercArrive()
{
/*
	LaptopSaveInfo.gbNumDaysTillFirstMercArrives = MERC_NUM_DAYS_TILL_FIRST_MERC_AVAILABLE;
	LaptopSaveInfo.gbNumDaysTillSecondMercArrives = MERC_NUM_DAYS_TILL_SECOND_MERC_AVAILABLE;
	LaptopSaveInfo.gbNumDaysTillThirdMercArrives = MERC_NUM_DAYS_TILL_THIRD_MERC_AVAILABLE;
	LaptopSaveInfo.gbNumDaysTillFourthMercArrives = MERC_NUM_DAYS_TILL_FOURTH_MERC_AVAILABLE;
*/
}


void MakeBiffAwayForCoupleOfDays()
{
	gMercProfiles[ BIFF ].uiDayBecomesAvailable = Random( 2 ) + 2;
}


BOOLEAN AreAnyOfTheNewMercsAvailable()
{
	UINT8	i;
	UINT8	ubMercID;


	if( LaptopSaveInfo.fNewMercsAvailableAtMercSite )
		return( FALSE );

	//for(i=(LARRY_NORMAL-BIFF); i<=LaptopSaveInfo.gubLastMercIndex; i++)
	for(i=0; i<=NUM_PROFILES; i++)
	{
		if ( gConditionsForMercAvailability[i].NewMercsAvailable == FALSE && gProfilesMERC[i].ProfilId != 0 )
		{
			ubMercID = GetMercIDFromMERCArray( i );
			if( IsMercMercAvailable( ubMercID ) ) 
				return( TRUE );
		}
	}

	return( FALSE );
}

void ShouldAnyNewMercMercBecomeAvailable()
{	
	//Kaiden: Added this if test to make sure that the "New Mercs Available"
	// e-mail doesn't show up and no unneccessary checks are made when you
	// have the ALL_MERCS_AT_MERC set to TRUE in the INI file.
	if(!gGameExternalOptions.fAllMercsAvailable)
	{
		for(UINT8 i=0; i<NUM_PROFILES; i++)
		{
			if ( gConditionsForMercAvailability[i].ProfilId != 0 && gConditionsForMercAvailability[i].NewMercsAvailable == FALSE && gConditionsForMercAvailability[i].StartMercsAvailable == FALSE )
			{
				if( CanMercBeAvailableYet( gConditionsForMercAvailability[i].uiIndex ) )
				{
					//Set up an event to add the merc in x days
					AddStrategicEvent( EVENT_MERC_SITE_NEW_MERC_AVAILABLE, GetMidnightOfFutureDayInMinutes( 1 ) + 420 + Random( 3 * 60 ), 0 );
				}
			}
		}	
	}
}

BOOLEAN CanMercBeAvailableYet( UINT8 ubMercToCheck )
{
	// WANNE: If we have a drunken profile, skip
	if (gConditionsForMercAvailability[ ubMercToCheck ].Drunk)
		return ( FALSE );

	//if the merc is already hired
	if( !IsMercHireable( GetMercIDFromMERCArray( gConditionsForMercAvailability[ ubMercToCheck ].ubMercArrayID ) ) )
		return( FALSE );

	//if player has paid enough money for the merc to be available, and the it is after the current day
	if( gConditionsForMercAvailability[ ubMercToCheck ].usMoneyPaid <= LaptopSaveInfo.uiTotalMoneyPaidToSpeck &&
			gConditionsForMercAvailability[ ubMercToCheck ].usDay <= GetWorldDay() )
	{
		return( TRUE );
	}

	return( FALSE );
}

void NewMercsAvailableAtMercSiteCallBack( )
{
	for(UINT8 i=0; i<NUM_PROFILES; i++)
	{			
		if ( gConditionsForMercAvailability[i].ProfilId != 0 && gConditionsForMercAvailability[i].NewMercsAvailable == FALSE && gConditionsForMercAvailability[i].StartMercsAvailable == FALSE )
		{
			if( CanMercBeAvailableYet( gConditionsForMercAvailability[i].uiIndex ) )
			{
				gConditionsForMercAvailability[i].NewMercsAvailable = TRUE;
			
				if ( gConditionsForMercAvailability[ gConditionsForMercAvailability[i].uiIndex ].Drunk == TRUE )
				{
					LaptopSaveInfo.gubLastMercIndex = gConditionsForMercAvailability[gConditionsForMercAvailability[i].uiAlternateIndex].uiIndex;
				}
				else
				{
					// If Previous merc has alternate index
					if (i > 0 && gConditionsForMercAvailability[ gConditionsForMercAvailability[i - 1].uiIndex ].uiAlternateIndex != 255)					
					{
						// Previous merc has alternate (drunk) merc, skip his one!						
						LaptopSaveInfo.gubLastMercIndex = LaptopSaveInfo.gubLastMercIndex + 2;
					}
					else
					{
						LaptopSaveInfo.gubLastMercIndex++;
					}
				}

				gConditionsForMercAvailability[gConditionsForMercAvailability[i].uiIndex].NewMercsAvailable = TRUE;
				LaptopSaveInfo.ubLastMercAvailableId = gConditionsForMercAvailability[i].uiIndex;
				gConditionsForMercAvailability[i].StartMercsAvailable = TRUE;
				
				AddEmail( NEW_MERCS_AT_MERC, NEW_MERCS_AT_MERC_LENGTH, SPECK_FROM_MERC, GetWorldTotalMin(), -1, -1, TYPE_EMAIL_EMAIL_EDT);

				//new mercs are available
				LaptopSaveInfo.fNewMercsAvailableAtMercSite = TRUE;
			}
		}
	}
}

//used for older saves
void CalcAproximateAmountPaidToSpeck()
{
	UINT8	i, ubMercID;

	//loop through all the mercs and tally up the amount speck should have been paid
	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		//get the id
		ubMercID = GetMercIDFromMERCArray( i );

		//increment the amount
		LaptopSaveInfo.uiTotalMoneyPaidToSpeck += gMercProfiles[ ubMercID ].uiTotalCostToDate;
	}
}

// CJC Dec 1 2002: calculate whether any MERC characters have been used at all
UINT32 CalcMercDaysServed()
{
	UINT8	i, ubMercID;
	UINT32 uiDaysServed = 0;

	for(i=0; i<NUMBER_OF_MERCS; i++)
	{
		//get the id
		ubMercID = GetMercIDFromMERCArray( i );

		uiDaysServed += gMercProfiles[ ubMercID ].usTotalDaysServed;

	}
	return( uiDaysServed );
}
#ifdef JA2UB
INT8	IsSpeckQuoteImportantQuote( UINT32 uiQuoteNum )
{
	INT32 iFlag=-1;
	switch( uiQuoteNum )
	{
		case SPECK_QUOTE_BETTER_STARTING_EQPMNT_TAG_ON:
			iFlag = SPECK__BETTER_EQUIPMENT;
			break;
		case SPECK_QUOTE_ENCOURAGE_SHOP_TAG_ON:
			iFlag = SPECK__ENCOURAGE_POAYER_TO_KEEP_SHOPPING;
			break;
		case SPECK_QUOTE_2ND_INTRO_LAPTOP_WORKING_AGAIN_1:
			iFlag = SPECK__SECOND_INTRO_BEEN_SAID;
			break;
	}

	return( (INT8) iFlag );
}

BOOLEAN HasImportantSpeckQuoteBeingSaid( UINT32 uiQuoteNum )
{
	INT8	iFlag;

	iFlag = IsSpeckQuoteImportantQuote( uiQuoteNum );
	if( iFlag == -1 )
	{
		return( FALSE );
	}

		//has the quote been said
	return( ( gJa25SaveStruct.ubImportantSpeckQuotesSaidBefore & ( 1 << iFlag ) ) != 0 );
}

//if the quote is a special quote, mark it said so we dont say it again
void MarkSpeckImportantQuoteUsed( UINT32 uiQuoteNum )
{
	INT8	iFlag;

	iFlag = IsSpeckQuoteImportantQuote( uiQuoteNum );
	if( iFlag == -1 )
	{
		return;
	}

	gJa25SaveStruct.ubImportantSpeckQuotesSaidBefore |= ( 1 << iFlag );
}
#endif