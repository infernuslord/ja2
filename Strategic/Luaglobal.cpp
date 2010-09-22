#include <iostream>
#include <string>
#include <sstream>


#include "connect.h"
#include "FileMan.h"
#include "GameSettings.h"
#include "Game Init.h"
#include "interface Dialogue.h"
#include "opplist.h"
#include "Strategic All.h"
#include "Luaglobal.h"
#include "Boxing.h"
#include "LuaInitNPCs.h"
#include "Game Clock.h"
#include "Overhead.h"
#include "Music Control.h"

#include "Intro.h"
#include "End Game.h"
#include "Queen Command.h"
#include "gamescreen.h"
#include "Map Screen Interface Map.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std;

extern	BOOLEAN	gfDoneWithSplashScreen;


void IniGlobalGameSetting(lua_State *L)
{
	
	lua_pushinteger(L, is_networked);
	lua_setglobal(L, "is_networked");
	
	lua_pushinteger(L, gWorldSectorX);
	lua_setglobal(L, "gWorldSectorX");
	
	lua_pushinteger(L, gWorldSectorY);
	lua_setglobal(L, "gWorldSectorY");
	
	lua_pushinteger(L, gbWorldSectorZ);
	lua_setglobal(L, "gWorldSectorZ");
	
	lua_pushinteger(L, gbWorldSectorZ);
	lua_setglobal(L, "gbWorldSectorZ");

	
	lua_pushinteger(L, giHospitalTempBalance);
	lua_setglobal(L, "giHospitalTempBalance");
	
	lua_pushinteger(L, gbHospitalPriceModifier);
	lua_setglobal(L, "gbHospitalPriceModifier");
	
	lua_pushinteger(L, giHospitalRefund);
	lua_setglobal(L, "giHospitalRefund");
	
	
	//boxer
	lua_pushboolean(L, gfBoxersResting);
	lua_setglobal(L, "gfBoxersResting");
	
	
	lua_pushinteger(L, gubBoxersRests);
	lua_setglobal(L, "gubBoxersRests");
	
	lua_pushinteger(L, gubBoxingMatchesWon);
	lua_setglobal(L, "gubBoxingMatchesWon");
	
	lua_pushinteger(L, gbPlayerNum);
	lua_setglobal(L, "gbPlayerNum");
	
	lua_pushinteger(L, uiMusicHandle);
	lua_setglobal(L, "uiMusicHandle");
	
	lua_pushinteger(L, gubMusicMode);
	lua_setglobal(L, "gubMusicMode");
	
	lua_pushboolean(L, fMusicPlaying);
	lua_setglobal(L, "fMusicPlaying");

	lua_pushboolean(L, gfForceMusicToTense);
	lua_setglobal(L, "gfForceMusicToTense");
	
	//GameExternalOptions
	lua_pushboolean(L, gGameExternalOptions.gfInvestigateSector);
	lua_setglobal(L, "gfInvestigateSector");
	
	lua_pushboolean(L, gGameExternalOptions.fMercDayOne);
	lua_setglobal(L, "fMercDayOne");
	
	lua_pushinteger(L, gGameOptions.ubGameStyle);
	lua_setglobal(L, "gameStyle");
	
	lua_pushinteger(L, gGameExternalOptions.fEnableCrepitus);
	lua_setglobal(L, "enableCrepitus");
	
	lua_pushinteger(L, gGameOptions.ubDifficultyLevel);
	lua_setglobal(L, "difficultyLevel");
	
	lua_pushinteger(L, gGameExternalOptions.iStartingCashNovice);
	lua_setglobal(L, "startingCashNovice");
	
	lua_pushinteger(L, gGameExternalOptions.iStartingCashExperienced);
	lua_setglobal(L, "startingCashExperienced");
	
	lua_pushinteger(L, gGameExternalOptions.iStartingCashExpert);
	lua_setglobal(L, "startingCashExpert");
	
	lua_pushinteger(L, gGameExternalOptions.iStartingCashInsane);
	lua_setglobal(L, "startingCashInsane");
	
	lua_pushinteger(L, gGameExternalOptions.fCanTrueCiviliansBecomeHostile);
	lua_setglobal(L, "fCanTrueCiviliansBecomeHostile");
	
	//intro
	lua_pushboolean(L, gfEnteringMapScreen);
	lua_setglobal(L, "gfEnteringMapScreen");
	
	lua_pushboolean(L, guiIntroExitScreen);
	lua_setglobal(L, "guiIntroExitScreen");
	
	lua_pushboolean(L, gfIntroScreenExit);
	lua_setglobal(L, "gfIntroScreenExit");
	
	lua_pushinteger(L, sSelMapX);
	lua_setglobal(L, "sSelMapX");
	
	lua_pushinteger(L, sSelMapY);
	lua_setglobal(L, "sSelMapY");
	
	lua_pushinteger(L, iCurrentMapSectorZ);
	lua_setglobal(L, "iCurrentMapSectorZ");	
	
	lua_pushboolean(L, gfDoneWithSplashScreen);
	lua_setglobal(L, "gfDoneWithSplashScreen");		
	
	lua_pushinteger(L, gbIntroScreenMode);
	lua_setglobal(L, "gbIntroScreenMode");	

	
}