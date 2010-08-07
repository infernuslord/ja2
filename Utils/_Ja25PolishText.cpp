#pragma setlocale("POLISH")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Polishtext.h"
#else
	#include "Language Defines.h"
	#ifdef POLISH
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25PolishText_public_symbol(void){;}

#ifdef POLISH

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"Otwieranie zamk�w",
	L"Walka wr�cz",
	L"Elektronika",
	L"Operacje nocne",
	L"Rzucanie",
	L"Szkolenie",
	L"Bro� ci�ka",
	L"Bro� automatyczna",
	L"Skradanie si�",
	L"Obur�czno��",
	L"Bro� bia�a",
	L"Snajper",
	L"Kamufla�",
	L"Sztuki walki",

	L"Brak",
	L"Umiej�tno�ci",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Wybra�e� tryb CZ�OWIEK ZE STALI. Opcja ta sprawi, �e gra b�dzie du�o trudniejsza poniewa� nie b�dzie mo�liwo�ci zapisywania gry podczas walki. B�dzie to mia�o wp�yw na ca�y przebieg rozgrywki. Czy na pewno chcesz gra� w trybie CZ�OWIEK ZE STALI?",
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
