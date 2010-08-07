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
	L"Otwieranie zamków",
	L"Walka wrêcz",
	L"Elektronika",
	L"Operacje nocne",
	L"Rzucanie",
	L"Szkolenie",
	L"Broñ ciê¿ka",
	L"Broñ automatyczna",
	L"Skradanie siê",
	L"Oburêcznoœæ",
	L"Broñ bia³a",
	L"Snajper",
	L"Kamufla¿",
	L"Sztuki walki",

	L"Brak",
	L"Umiejêtnoœci",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Wybra³eœ tryb CZ£OWIEK ZE STALI. Opcja ta sprawi, ¿e gra bêdzie du¿o trudniejsza poniewa¿ nie bêdzie mo¿liwoœci zapisywania gry podczas walki. Bêdzie to mia³o wp³yw na ca³y przebieg rozgrywki. Czy na pewno chcesz graæ w trybie CZ£OWIEK ZE STALI?",
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
