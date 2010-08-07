//#pragma setlocale("ITALIAN")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Italiantext.h"
#else
	#include "Language Defines.h"
	#ifdef ITALIAN
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25ItalianText_public_symbol(void){;}

#ifdef ITALIAN

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"Scassinare",
	L"Lottare",
	L"Elettronica",
	L"Operazioni Notturne",
	L"Lanciare",
	L"Insegnare",
	L"Armi Pesanti",
	L"Armi Automatiche",
	L"Muoversi Silenziosamente",
	L"Ambidestro",
	L"Combattimento con il coltello",
	L"Cecchino",
	L"Mimetismo",
	L"Arti Marziali",

	L"Nessuna",
	L"Specialità I.M.P.",
};
//New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Hai scelto la modalità IRON MAN. Questa impostazione rende il gioco notevolmente più impegnativo, poiché non potrai salvare la partita in un settore occupato da nemici. Non potrai cambiare questa decisione nel corso della partita. Sei sicuro di voler giocare al livello IRON MAN?",
};

STR16 gzDisplayCoverText[]=
{
	L"Copertura: %d/100 %s, Luminosità: %d/100",
	L"Gittata dell'arma: %d/%d tiles, Probabilità di colpire: %d/100",
	L"Disabilita visualizzazione copertura",
	L"Mostra visuale del mercenario",
	L"Mostra zone di pericolo per il mercenario",
	L"Bosco", // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Urbano",
	L"Deserto",
	L"Neve", // NOT USED!!!
	L"Bosco e deserto",
	L"" // yes empty for now
};


#endif
