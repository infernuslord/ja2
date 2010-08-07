//#pragma setlocale("FRENCH")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Frenchtext.h"
#else
	#include "Language Defines.h"
	#ifdef FRENCH
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25FrenchText_public_symbol(void){;}

#ifdef FRENCH

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD


//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"crochetage",
	L"combat à mains nues",
	L"Electronique",
	L"Operations de nuit",
	L"Lancer",
	L"Enseigner",
	L"Armes lourdes",
	L"Armes automatiques",
	L"Discretion",
	L"Ambidextre",
	L"Couteau",
	L"Tireur isolé",
	L"Camouflage",
	L"Arts martiaux",

	L"aucune",
	L"Spécialtés I.M.P.",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Vous avez choisi le mode IRON MAN. La difficultée du jeu s'en trouveras considerablement augmentée du fait de l'imposssiblité de sauvegarder en territoire ennemi. Ce paramètre prendra effet tout au long de la partie.  Etes vous vraiment sûr de vouloir jouer en mode IRON MAN ?",
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
