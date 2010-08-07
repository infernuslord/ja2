//#pragma setlocale("GERMAN")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25GermanText.h"
#else
	#include "Language Defines.h"
	#ifdef GERMAN
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25GermanText_public_symbol(void){;}

#ifdef GERMAN

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"Schlösser knacken",
	L"Nahkampf",
	L"Elektronik",
	L"Nachteinsatz",
	L"Werfen",
	L"Lehren",
	L"Schwere Waffen",
	L"Automatische Waffen",
	L"Schleichen",
	L"Beidhändig geschickt",
	L"Messer",
	L"Dach-Treffer Bonus",
	L"Getarnt",
	L"Kampfsport",

	L"Keine",
	L"B.S.E. Persönlichkeiten",
};

//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Sie haben sich für den Ironman- Modus entschieden. Mit dieser Einstellung können Sie das Spiel nicht speichern, wenn Feinde im Sektor sind. Sind Sie sicher, dass Sie im Ironman- Modus spielen wollen?",
};

STR16 gzDisplayCoverText[]=
{
	L"Deckung: %d/100 %s, Helligkeit: %d/100",
	L"Waffen-Rchwt.: %d/%d Felder, Trefferwahrsch.: %d/100",
	L"Deckungsanzeige ausschalten",
	L"Zeige Ansicht für Söldner",
	L"Zeige Gefahrenbereich für Söldner",
	L"Wald", // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Stadt",
	L"Wüste",
	L"Schnee", // NOT USED!!!
	L"Wald and Wüste",
	L"" // yes empty for now
};


#endif