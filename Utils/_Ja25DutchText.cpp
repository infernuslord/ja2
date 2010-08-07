//#pragma setlocale("DUTCH")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Dutchtext.h"
#else
	#include "Language Defines.h"
	#ifdef DUTCH
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25DutchText_public_symbol(void){;}

#ifdef DUTCH

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"Lock picking",
	L"Hand to hand combat",
	L"Electronics",
	L"Night operations",
	L"Throwing",
	L"Teaching",
	L"Heavy Weapons",
	L"Auto Weapons",
	L"Stealth",
	L"Ambidextrous",
	L"Knifing",
	L"Sniper",
	L"Camouflage",
	L"Martial Arts",

	L"None",
	L"I.M.P. Specialties",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"You have chosen IRON MAN mode. This setting makes the game considerably more challenging as you will not be able to save your game when in a sector occupied by enemies. This setting will affect the entire course of the game.  Are you sure want to play in IRON MAN mode?",
};

STR16 gzDisplayCoverText[]=
{
	L"Cover: %d/100 %s, Brightness: %d/100",
	L"Gun Range: %d/%d tiles, Chance to hit: %d/100",
	L"Disabling cover display",
	L"Showing mercenary view",
	L"Showing danger zones for mercenary",
	L"Wood", // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Urban",
	L"Desert",
	L"Snow", // NOT USED!!!
	L"Wood and Desert",
	L"" // yes empty for now
};


#endif
