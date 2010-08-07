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
	L"Schl�sser knacken",
	L"Nahkampf",
	L"Elektronik",
	L"Nachteinsatz",
	L"Werfen",
	L"Lehren",
	L"Schwere Waffen",
	L"Automatische Waffen",
	L"Schleichen",
	L"Beidh�ndig geschickt",
	L"Messer",
	L"Dach-Treffer Bonus",
	L"Getarnt",
	L"Kampfsport",

	L"Keine",
	L"B.S.E. Pers�nlichkeiten",
};

//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Sie haben sich f�r den Ironman- Modus entschieden. Mit dieser Einstellung k�nnen Sie das Spiel nicht speichern, wenn Feinde im Sektor sind. Sind Sie sicher, dass Sie im Ironman- Modus spielen wollen?",
};

STR16 gzDisplayCoverText[]=
{
	L"Deckung: %d/100 %s, Helligkeit: %d/100",
	L"Waffen-Rchwt.: %d/%d Felder, Trefferwahrsch.: %d/100",
	L"Deckungsanzeige ausschalten",
	L"Zeige Ansicht f�r S�ldner",
	L"Zeige Gefahrenbereich f�r S�ldner",
	L"Wald", // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Stadt",
	L"W�ste",
	L"Schnee", // NOT USED!!!
	L"Wald and W�ste",
	L"" // yes empty for now
};


#endif