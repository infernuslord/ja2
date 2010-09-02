#pragma setlocale("POLISH")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
#else
	#include "Language Defines.h"
	#if defined( POLISH )
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_PolishText_public_symbol(void){;}

#ifdef POLISH

/*

******************************************************************************************************
**                                  IMPORTANT TRANSLATION NOTES                                     **
******************************************************************************************************

GENERAL INSTRUCTIONS
- Always be aware that foreign strings should be of equal or shorter length than the English equivalent.  
	I know that this is difficult to do on many occasions due to the nature of foreign languages when 
	compared to English.  By doing so, this will greatly reduce the amount of work on both sides.  In 
	most cases (but not all), JA2 interfaces were designed with just enough space to fit the English word.  
	The general rule is if the string is very short (less than 10 characters), then it's short because of 
	interface limitations.  On the other hand, full sentences commonly have little limitations for length.  
	Strings in between are a little dicey.
- Never translate a string to appear on multiple lines.  All strings L"This is a really long string...", 
	must fit on a single line no matter how long the string is.  All strings start with L" and end with ",
- Never remove any extra spaces in strings.  In addition, all strings containing multiple sentences only 
	have one space after a period, which is different than standard typing convention.  Never modify sections 
	of strings contain combinations of % characters.  These are special format characters and are always 
	used in conjunction with other characters.  For example, %s means string, and is commonly used for names,
	locations, items, etc.  %d is used for numbers.  %c%d is a character and a number (such as A9).  
	%% is how a single % character is built.  There are countless types, but strings containing these 
	special characters are usually commented to explain what they mean.  If it isn't commented, then 
	if you can't figure out the context, then feel free to ask SirTech.
- Comments are always started with // Anything following these two characters on the same line are 
	considered to be comments.  Do not translate comments.  Comments are always applied to the following 
	string(s) on the next line(s), unless the comment is on the same line as a string.  
- All new comments made by SirTech will use "//@@@ comment" (without the quotes) notation.  By searching 
	for @@@ everytime you recieve a new version, it will simplify your task and identify special instructions.
  Commonly, these types of comments will be used to ask you to abbreviate a string.  Please leave the 
	comments intact, and SirTech will remove them once the translation for that particular area is resolved.
- If you have a problem or question with translating certain strings, please use "//!!! comment" 
	(without the quotes).  The syntax is important, and should be identical to the comments used with @@@ 
	symbols.  SirTech will search for !!! to look for your problems and questions.  This is a more 
	efficient method than detailing questions in email, so try to do this whenever possible.


	
FAST HELP TEXT -- Explains how the syntax of fast help text works.
**************

1) BOLDED LETTERS
	The popup help text system supports special characters to specify the hot key(s) for a button.  
	Anytime you see a '|' symbol within the help text string, that means the following key is assigned
	to activate the action which is usually a button.  

	EX:  L"|Map Screen" 

	This means the 'M' is the hotkey.  In the game, when somebody hits the 'M' key, it activates that
	button.  When translating the text to another language, it is best to attempt to choose a word that
	uses 'M'.  If you can't always find a match, then the best thing to do is append the 'M' at the end
	of the string in this format:

	EX:  L"Ecran De Carte (|M)"  (this is the French translation)

	Other examples are used multiple times, like the Esc key  or "|E|s|c" or Space -> (|S|p|a|c|j|a)

2) NEWLINE
  Any place you see a \n within the string, you are looking at another string that is part of the fast help
	text system.  \n notation doesn't need to be precisely placed within that string, but whereever you wish 
	to start a new line. 

	EX:  L"Clears all the mercs' positions,\nand allows you to re-enter them manually." 

	Would appear as:

				Clears all the mercs' positions,
				and allows you to re-enter them manually.

	NOTE:  It is important that you don't pad the characters adjacent to the \n with spaces.  If we did this
	       in the above example, we would see

	WRONG WAY -- spaces before and after the \n
	EX:  L"Clears all the mercs' positions, \n and allows you to re-enter them manually." 

	Would appear as: (the second line is moved in a character)
		
				Clears all the mercs' positions,
 				 and allows you to re-enter them manually.


@@@ NOTATION
************

	Throughout the text files, you'll find an assortment of comments.  Comments are used to describe the
	text to make translation easier, but comments don't need to be translated.  A good thing is to search for
	"@@@" after receiving new version of the text file, and address the special notes in this manner.  

!!! NOTATION
************

	As described above, the "!!!" notation should be used by you to ask questions and address problems as
	SirTech uses the "@@@" notation.

*/

// by Jazz: TODO.Translate
CHAR16 zGrod[][500] =
{
	L"Robot", //0    // Robot
};

STR16 pCreditsJA2113[] =
{
	L"@T,{;JA2 v1.13 Development Team",
	L"@T,C144,R134,{;Kodowanie",
	L"@T,C144,R134,{;Grafika i d�wi�ki",
	L"@};(R�ne inne mody!)",
	L"@T,C144,R134,{;Przedmioty",
	L"@T,C144,R134,{;Pozostali autorzy",
	L"@};(Wszyscy pozostali cz�onkowie sceny JA kt�rzy nas wsparli!)",
};

CHAR16 ItemNames[MAXITEMS][80] =
{
	L"",
};


CHAR16 ShortItemNames[MAXITEMS][80] =
{
	L"",
};

// Different weapon calibres
// CAWS is Close Assault Weapon System and should probably be left as it is
// NATO is the North Atlantic Treaty Organization
// WP is Warsaw Pact
// cal is an abbreviation for calibre
CHAR16 AmmoCaliber[MAXITEMS][20];// =
//{
//	L"0",
//	L".38 cal",
//	L"9mm",
//	L".45 cal",
//	L".357 cal",
//	L"12 gauge",
//	L"CAWS",
//	L"5.45mm",
//	L"5.56mm",
//	L"7.62mm NATO",
//	L"7.62mm WP",
//	L"4.7mm",
//	L"5.7mm",
//	L"Monstrum",
//	L"Rakiety",
//	L"strza�ka", // dart
//	L"", // flame
//	L".50 cal", // barrett
//	L"9mm Hvy", // Val silent
//};

// This BobbyRayAmmoCaliber is virtually the same as AmmoCaliber however the bobby version doesnt have as much room for the words.
// 
// Different weapon calibres
// CAWS is Close Assault Weapon System and should probably be left as it is
// NATO is the North Atlantic Treaty Organization
// WP is Warsaw Pact
// cal is an abbreviation for calibre
CHAR16 BobbyRayAmmoCaliber[MAXITEMS][20] ;//=
//{
//	L"0",
//	L".38 cal",
//	L"9mm",
//	L".45 cal",
//	L".357 cal",
//	L"12 gauge",
//	L"CAWS",
//	L"5.45mm",
//	L"5.56mm",
//	L"7.62mm N.",
//	L"7.62mm WP",
//	L"4.7mm",
//	L"5.7mm",
//	L"Monstrum",
//	L"Rakiety",
//	L"strza�ka", // dart
//	L"", // flamethrower
//	L".50 cal", // barrett
//	L"9mm Hvy", // Val silent
//};


CHAR16 WeaponType[MAXITEMS][30] =
{
	L"Inny",
	L"Pistolet",
	L"Pistolet maszynowy",
	L"Karabin maszynowy",
	L"Karabin",
	L"Karabin snajperski",
	L"Karabin bojowy",
	L"Lekki karabin maszynowy",
	L"Strzelba"
};

CHAR16 TeamTurnString[][STRING_LENGTH] =
{
	L"Tura gracza", // player's turn
	L"Tura przeciwnika",
	L"Tura stworze�",
	L"Tura samoobrony",
	L"Tura cywili"
	L"Player_Plan",// planning turn
	L"Client #1",//hayden
	L"Client #2",//hayden
	L"Client #3",//hayden
	L"Client #4",//hayden
};

CHAR16 Message[][STRING_LENGTH] =
{
	L"",

	// In the following 8 strings, the %s is the merc's name, and the %d (if any) is a number.

	L"%s dosta�(a) w g�ow� i traci 1 punkt inteligencji!",
	L"%s dosta�(a) w rami� i traci 1 punkt zr�czno�ci!",
	L"%s dosta�(a) w klatk� piersiow� i traci 1 punkt si�y!",
	L"%s dosta�(a) w nogi i traci 1 punkt zwinno�ci!",
	L"%s dosta�(a) w g�ow� i traci %d pkt. inteligencji!",
	L"%s dosta�(a) w rami� i traci %d pkt. zr�czno�ci!",
	L"%s dosta�(a) w klatk� piersiow� i traci %d pkt. si�y!",
	L"%s dosta�(a) w nogi i traci %d pkt. zwinno�ci!",
	L"Przerwanie!",

	// The first %s is a merc's name, the second is a string from pNoiseVolStr,
	// the third is a string from pNoiseTypeStr, and the last is a string from pDirectionStr

	L"", //OBSOLETE
	L"Dotar�y twoje posi�ki!",

	// In the following four lines, all %s's are merc names

	L"%s prze�adowuje.",
	L"%s posiada za ma�o Punkt�w Akcji!",
	L"%s udziela pierwszej pomocy. (Naci�nij dowolny klawisz aby przerwa�.)",
	L"%s i %s udzielaj� pierwszej pomocy. (Naci�nij dowolny klawisz aby przerwa�.)",
	// the following 17 strings are used to create lists of gun advantages and disadvantages
	// (separated by commas)
	L"niezawodna",
	L"zawodna",
	L"�atwa w naprawie",
	L"trudna do naprawy",
	L"solidna",
	L"niesolidna",
	L"szybkostrzelna",
	L"wolno strzelaj�ca",
	L"daleki zasi�g",
	L"kr�tki zasi�g",
	L"ma�a waga",
	L"du�a waga",
	L"niewielkie rozmiary",
	L"szybki ci�g�y ogie�",
	L"brak mo�liwo�ci strzelania seri�",
	L"du�y magazynek",
	L"ma�y magazynek",

	// In the following two lines, all %s's are merc names

	L"%s: kamufla� si� star�.",
	L"%s: kamufla� si� zmy�.",

	// The first %s is a merc name and the second %s is an item name

	L"Brak amunicji w dodatkowej broni!",
	L"%s ukrad�(a): %s.",

	// The %s is a merc name

	L"%s ma bro� bez funkcji ci�g�ego ognia.",

	L"Ju� masz co� takiego do��czone.",
	L"Po��czy� przedmioty?",

	// Both %s's are item names

	L"%s i %s nie pasuj� do siebie.",

	L"Brak",
	L"Wyjmij amunicj�",
	L"Dodatki",
	
	//You cannot use "item(s)" and your "other item" at the same time.
	//Ex:  You cannot use sun goggles and you gas mask at the same time.
	L" %s i %s nie mog� by� u�ywane jednocze�nie.",

	L"Element, kt�ry masz na kursorze myszy mo�e by� do��czony do pewnych przedmiot�w, poprzez umieszczenie go w jednym z czterech slot�w.",
	L"Element, kt�ry masz na kursorze myszy mo�e by� do��czony do pewnych przedmiot�w, poprzez umieszczenie go w jednym z czterech slot�w. (Jednak w tym przypadku, przedmioty do siebie nie pasuj�.)",
	L"Ten sektor nie zosta� oczyszczony z wrog�w!",
	L"Wci�� musisz da� %s %s", 
	L"%s dosta�(a) w g�ow�!",
	L"Przerwa� walk�?",
	L"Ta zmiana b�dzie trwa�a. Kontynuowa�?",
	L"%s ma wi�cej energii!",
	L"%s po�lizgn��(n�a) si� na kulkach!",
	L"%s nie chwyci�(a) - %s!",    //to by�o - L"%s nie zdo�a� chwyci� %s!",		teraz jest - L"%s nie zdo�a� zabra� %s z r�ki wroga!",
	L"%s naprawi�(a) %s",
	L"Przerwanie dla: ",
	L"Podda� si�?",
	L"Ta osoba nie chce twojej pomocy.",
	L"NIE S�DZ�!",
  	L"Aby podr�owa� helikopterem Skyridera, musisz najpierw zmieni� przydzia� najemnik�w na POJAZD/HELIKOPTER.",
	L"%s mia�(a) czas by prze�adowa� tylko jedn� bro�",
	L"Tura dzikich kot�w",
	L"ogie� ci�g�y",
	L"brak ognia ci�g�ego",
	L"celna",
	L"niecelna",
	L"bro� samoczynna",
	L"Wr�g nie ma przedmiot�w, kt�re mo�na ukra��!",
	L"Wr�g nie ma �adnego przedmiotu w r�ce!",
	
	//add new camo string
	L"%s: kamufla� pustynny si� star�.",
	L"%s: kamufla� pustynny si� zmy�.",
	
	L"%s: kamufla� le�ny si� star�.",
	L"%s: kamufla� le�ny si� zmy�.",
	
	L"%s: kamufla� miejski si� star�.",
	L"%s: kamufla� miejski si� zmy�.",
	
	L"%s: kamufla� zimowy si� star�.",
	L"%s: kamufla� zimowy si� zmy�.",

	// TODO.Translate
	L"You cannot attach %s to this slot.",
};


// the names of the towns in the game

CHAR16 pTownNames[MAX_TOWNS][MAX_TOWN_NAME_LENGHT] =
{
	L"",
	L"Omerta",
	L"Drassen",
	L"Alma",
	L"Grumm",
	L"Tixa",
	L"Cambria",
	L"San Mona",
	L"Estoni",
	L"Orta",
	L"Balime",
	L"Meduna",
	L"Chitzena",
};

// the types of time compression. For example: is the timer paused? at normal speed, 5 minutes per second, etc.
// min is an abbreviation for minutes

STR16 sTimeStrings[] =
{
	L"Pauza",
	L"Normalna",
	L"5 min.",
	L"30 min.",
	L"60 min.",
	L"6 godz.", //NEW
};


// Assignment Strings: what assignment does the merc  have right now? For example, are they on a squad, training, 
// administering medical aid (doctor) or training a town. All are abbreviated. 8 letters is the longest it can be.

STR16 pAssignmentStrings[] =
{
	L"Oddz. 1",
	L"Oddz. 2",
	L"Oddz. 3",
	L"Oddz. 4",
	L"Oddz. 5",
	L"Oddz. 6",
	L"Oddz. 7",
	L"Oddz. 8",
	L"Oddz. 9",
	L"Oddz. 10",
	L"Oddz. 11",
	L"Oddz. 12",
	L"Oddz. 13",
	L"Oddz. 14",
	L"Oddz. 15",
	L"Oddz. 16",
	L"Oddz. 17",
	L"Oddz. 18",
	L"Oddz. 19",
	L"Oddz. 20",
	L"S�u�ba", // on active duty
	L"Lekarz", // administering medical aid
	L"Pacjent", // getting medical aid
	L"Pojazd", // in a vehicle
	L"Podr�", // in transit - abbreviated form
	L"Naprawa", // repairing
	L"Praktyka", // training themselves  
	L"Samoobr.", // training a town to revolt 
	L"M.Militia", //training moving militia units		// TODO.Translate
	L"Instruk.", // training a teammate
	L"Ucze�", // being trained by someone else 
	L"Staff", // operating a strategic facility			// TODO.Translate
	L"Rest", // Resting at a facility					// TODO.Translate
	L"Nie �yje", // dead
	L"Obezw�.", // abbreviation for incapacitated
	L"Jeniec", // Prisoner of war - captured
	L"Szpital", // patient in a hospital 
	L"Pusty",	// Vehicle is empty
};


STR16 pMilitiaString[] =
{
	L"Samoobrona", // the title of the militia box
	L"Bez przydzia�u", //the number of unassigned militia troops
	L"Nie mo�esz przemieszcza� oddzia��w samoobrony gdy nieprzyjaciel jest w sektorze!",
	L"Some militia were not assigned to a sector. Would you like to disband them?", // TODO.Translate
};


STR16 pMilitiaButtonString[] =
{
	L"Auto", // auto place the militia troops for the player
	L"OK", // done placing militia troops
	L"Disband", // HEADROCK HAM 3.6: Disband militia	// TODO.Translate
};

STR16 pConditionStrings[] = 
{
	L"Doskona�y", //the state of a soldier .. excellent health
	L"Dobry", // good health
	L"Do�� dobry", // fair health
	L"Ranny", // wounded health	
	L"Zm�czony",//L"Wyczerpany", // tired
	L"Krwawi", // bleeding to death
	L"Nieprzyt.", // knocked out 
	L"Umieraj�cy", // near death
	L"Nie �yje", // dead
};

STR16 pEpcMenuStrings[] =
{
	L"S�u�ba", // set merc on active duty
	L"Pacjent", // set as a patient to receive medical aid
	L"Pojazd", // tell merc to enter vehicle
	L"Wypu��", // let the escorted character go off on their own
	L"Anuluj", // close this menu
};


// look at pAssignmentString above for comments

STR16 pPersonnelAssignmentStrings[] =
{
	L"Oddz. 1",
	L"Oddz. 2",
	L"Oddz. 3",
	L"Oddz. 4",
	L"Oddz. 5",
	L"Oddz. 6",
	L"Oddz. 7",
	L"Oddz. 8",
	L"Oddz. 9",
	L"Oddz. 10",
	L"Oddz. 11",
	L"Oddz. 12",
	L"Oddz. 13",
	L"Oddz. 14",
	L"Oddz. 15",
	L"Oddz. 16",
	L"Oddz. 17",
	L"Oddz. 18",
	L"Oddz. 19",
	L"Oddz. 20",
	L"S�u�ba",
	L"Lekarz",
	L"Pacjent",
	L"Pojazd",
	L"Podr�",
	L"Naprawa",
	L"Praktyka",
	L"Trenuje samoobron�",
	L"Training Mobile Militia",	// TODO.Translate
	L"Instruktor",
	L"Ucze�",
	L"Facility Staff",			// TODO.Translate
	L"Resting at Facility",		// TODO.Translate
	L"Nie �yje",
	L"Obezw�adniony",
	L"Jeniec",
	L"Szpital",
	L"Pusty",	// Vehicle is empty
};


// refer to above for comments

STR16 pLongAssignmentStrings[] =
{
	L"Oddzia� 1",
	L"Oddzia� 2",
	L"Oddzia� 3",
	L"Oddzia� 4",
	L"Oddzia� 5",
	L"Oddzia� 6",
	L"Oddzia� 7",
	L"Oddzia� 8",
	L"Oddzia� 9",
	L"Oddzia� 10",
	L"Oddzia� 11",
	L"Oddzia� 12",
	L"Oddzia� 13",
	L"Oddzia� 14",
	L"Oddzia� 15",
	L"Oddzia� 16",
	L"Oddzia� 17",
	L"Oddzia� 18",
	L"Oddzia� 19",
	L"Oddzia� 20",
	L"S�u�ba",
	L"Lekarz",
	L"Pacjent",
	L"Pojazd",
	L"W podr�y",
	L"Naprawa",
	L"Praktyka",
	L"Trenuj samoobron�",
	L"Train Mobiles",		// TODO.Translate
	L"Trenuj oddzia�",
	L"Ucze�",
	L"Staff Facility",		// TODO.Translate
	L"Rest at Facility",	// TODO.Translate
	L"Nie �yje",
	L"Obezw�adniony",
	L"Jeniec",
	L"W szpitalu", // patient in a hospital 
	L"Pusty",	// Vehicle is empty
};


// the contract options

STR16 pContractStrings[] =
{
	L"Opcje kontraktu:", 
	L"", // a blank line, required
	L"Zaproponuj 1 dzie�", // offer merc a one day contract extension
	L"Zaproponuj 1 tydzie�", // 1 week
	L"Zaproponuj 2 tygodnie", // 2 week
	L"Zwolnij", // end merc's contract
	L"Anuluj", // stop showing this menu
};

STR16 pPOWStrings[] =
{
	L"Jeniec",  //an acronym for Prisoner of War
	L"??",
};

STR16 pLongAttributeStrings[] =
{
	L"SI�A", //The merc's strength attribute. Others below represent the other attributes.
	L"ZR�CZNO��",  
	L"ZWINNO��", 
	L"INTELIGENCJA", 
	L"UMIEJ�TNO�CI STRZELECKIE",
	L"WIEDZA MEDYCZNA",
	L"ZNAJOMO�� MECHANIKI",
	L"UMIEJ�TNO�� DOWODZENIA",
	L"ZNAJOMO�� MATERIA��W WYBUCHOWYCH",
	L"POZIOM DO�WIADCZENIA",
};

STR16 pInvPanelTitleStrings[] =
{
	L"Os�ona", // the armor rating of the merc
	L"Ekwip.", // the weight the merc is carrying
	L"Kamuf.", // the merc's camouflage rating
	L"Kamufla�:",
	L"Ochrona:",
};

STR16 pShortAttributeStrings[] =
{
	L"Zwn", // the abbreviated version of : agility
	L"Zrc", // dexterity
	L"Si�", // strength
	L"Dow", // leadership
	L"Int", // wisdom
	L"Do�", // experience level
	L"Str", // marksmanship skill
	L"Wyb", // explosive skill
	L"Mec", // mechanical skill
	L"Med", // medical skill
};


STR16 pUpperLeftMapScreenStrings[] =
{
	L"Przydzia�", // the mercs current assignment 
	L"Kontrakt", // the contract info about the merc
	L"Zdrowie", // the health level of the current merc
	L"Morale", // the morale of the current merc
	L"Stan",	// the condition of the current vehicle
	L"Paliwo",	// the fuel level of the current vehicle
};

STR16 pTrainingStrings[] =
{
	L"Praktyka", // tell merc to train self 
	L"Samoobrona", // tell merc to train town 
	L"Instruktor", // tell merc to act as trainer
	L"Ucze�", // tell merc to be train by other 
};

STR16 pGuardMenuStrings[] =
{
	L"Limit ognia:", // the allowable rate of fire for a merc who is guarding
	L" Agresywny ogie�", // the merc can be aggressive in their choice of fire rates
	L" Oszcz�dzaj amunicj�", // conserve ammo 
	L" Strzelaj w ostateczno�ci", // fire only when the merc needs to 
	L"Inne opcje:", // other options available to merc
	L" Mo�e si� wycofa�", // merc can retreat
	L" Mo�e szuka� schronienia",  // merc is allowed to seek cover
	L" Mo�e pomaga� partnerom", // merc can assist teammates
	L"OK", // done with this menu
	L"Anuluj", // cancel this menu
};

// This string has the same comments as above, however the * denotes the option has been selected by the player

STR16 pOtherGuardMenuStrings[] =
{
	L"Limit ognia:",
	L" *Agresywny ogie�*",
	L" *Oszcz�dzaj amunicj�*",
	L" *Strzelaj w ostateczno�ci*",
	L"Inne opcje:",
	L" *Mo�e si� wycofa�*",
	L" *Mo�e szuka� schronienia*",
	L" *Mo�e pomaga� partnerom*",
	L"OK",
	L"Anuluj",
};

STR16 pAssignMenuStrings[] =
{
	L"S�u�ba", // merc is on active duty
	L"Lekarz", // the merc is acting as a doctor
	L"Pacjent", // the merc is receiving medical attention
	L"Pojazd", // the merc is in a vehicle
	L"Naprawa", // the merc is repairing items 
	L"Szkolenie", // the merc is training
	L"Facility", // the merc is using/staffing a facility	// TODO.Translate
	L"Anuluj", // cancel this menu
};

//lal
STR16 pMilitiaControlMenuStrings[] =
{
	L"Atakuj", // set militia to aggresive
	L"Utrzymaj pozycj�", // set militia to stationary
	L"Wycofaj si�", // retreat militia
	L"Chod� do mnie", // retreat militia
	L"Padnij", // retreat militia	
	L"Kryj si�",
	L"Wszyscy: Atakujcie", 
	L"Wszyscy: Utrzymajcie pozycje",
	L"Wszyscy: Wycofajcie si�",
	L"Wszyscy: Chod�cie do mnie",
	L"Wszyscy: Rozproszcie si�",
	L"Wszyscy: Padnijcie",
	L"Wszyscy: Kryjcie si�",
	//L"Wszyscy: Szukajcie przedmiot�w",
	L"Anuluj", // cancel this menu
};

//STR16 pTalkToAllMenuStrings[] =
//{
//	L"Atak", // set militia to aggresive
//	L"Utrzymaj pozycj�", // set militia to stationary
//	L"Odwr�t", // retreat militia
//	L"Za mn�", // retreat militia
//	L"Padnij", // retreat militia		 
//	L"Anuluj", // cancel this menu
//};

STR16 pRemoveMercStrings[] =
{
	L"Usu� najemnika", // remove dead merc from current team
	L"Anuluj",
};

STR16 pAttributeMenuStrings[] =
{
	L"Si�a",
	L"Zr�czno��",
	L"Zwinno��",
	L"Zdrowie",
	L"Um. strzeleckie",
	L"Wiedza med.",
	L"Zn. mechaniki",
	L"Um. dowodzenia",
	L"Zn. mat. wyb.",
	L"Anuluj",
};

STR16 pTrainingMenuStrings[] =
{
 L"Praktyka", // train yourself 
 L"Samoobrona", // train the town 
 L"Mobile Militia",		// TODO.Translate
 L"Instruktor", // train your teammates 
 L"Ucze�",  // be trained by an instructor 
 L"Anuluj", // cancel this menu
};


STR16 pSquadMenuStrings[] =
{
	L"Oddzia�  1",
	L"Oddzia�  2",
	L"Oddzia�  3",
	L"Oddzia�  4",
	L"Oddzia�  5",
	L"Oddzia�  6",
	L"Oddzia�  7",
	L"Oddzia�  8",
	L"Oddzia�  9",
	L"Oddzia� 10",
	L"Oddzia� 11",
	L"Oddzia� 12",
	L"Oddzia� 13",
	L"Oddzia� 14",
	L"Oddzia� 15",
	L"Oddzia� 16",
	L"Oddzia� 17",
	L"Oddzia� 18",
	L"Oddzia� 19",
	L"Oddzia� 20",
	L"Anuluj",
};

STR16 pPersonnelTitle[] =
{
	L"Personel", // the title for the personnel screen/program application
};

STR16 pPersonnelScreenStrings[] =
{
	L"Zdrowie: ", // health of merc
	L"Zwinno��: ", 
	L"Zr�czno��: ",
 	L"Si�a: ",
 	L"Um. dowodzenia: ",
 	L"Inteligencja: ",
 	L"Poziom do�w.: ", // experience level
 	L"Um. strzeleckie: ", 
 	L"Zn. mechaniki: ",
 	L"Zn. mat. wybuchowych: ",
 	L"Wiedza medyczna: ",
 	L"Zastaw na �ycie: ", // amount of medical deposit put down on the merc
 	L"Bie��cy kontrakt: ", // cost of current contract
 	L"Liczba zab�jstw: ", // number of kills by merc
 	L"Liczba asyst: ", // number of assists on kills by merc
 	L"Dzienny koszt:", // daily cost of merc
 	L"Og�lny koszt:", // total cost of merc
 	L"Warto�� kontraktu:", // cost of current contract
 	L"Us�ugi og�em", // total service rendered by merc
 	L"Zaleg�a kwota", // amount left on MERC merc to be paid
 	L"Celno��:", // percentage of shots that hit target
 	L"Ilo�� walk:", // number of battles fought
 	L"Ranny(a):", // number of times merc has been wounded
 	L"Umiej�tno�ci:",
 	L"Brak umi�j�tno�ci",
};


//These string correspond to enums used in by the SkillTrait enums in SoldierProfileType.h
STR16 gzMercSkillText[] = 
{
	L"Brak umiej�tno�ci",
	L"Otwieranie zamk�w",
	L"Walka wr�cz",		//JA25: modified
	L"Elektronika",
	L"Nocne operacje",			//JA25: modified
	L"Rzucanie",
	L"Szkolenie",
	L"Ci�ka bro�",
	L"Bro� automatyczna",
	L"Skradanie si�",
	L"Obur�czno��",
	L"Kradzie�",
	L"Sztuki walki",
	L"Bro� bia�a",
	L"Snajper",				//JA25: modified
	L"Kamufla�",						//JA25: modified
	L"Kamufla� (miasto)",
	L"Kamufla� (pustynia)",
	L"Kamufla� (�nieg)",
	L"(Eksp.)",
};


// This is pop up help text for the options that are available to the merc

STR16 pTacticalPopupButtonStrings[] =
{
	L"W|sta�/Id�",
	L"S|chyl si�/Id�",
	L"Wsta�/Biegnij (|R)",
	L"|Padnij/Czo�gaj si�",
	L"Patrz (|L)",
	L"Akcja",
	L"Rozmawiaj",
	L"Zbadaj (|C|t|r|l)",

	// Pop up door menu
	L"Otw�rz",
	L"Poszukaj pu�apek",
	L"U�yj wytrych�w",
	L"Wywa�",
	L"Usu� pu�apki",
	L"Zamknij na klucz",
	L"Otw�rz kluczem",
	L"U�yj �adunku wybuchowego",
	L"U�yj �omu",
	L"Anuluj (|E|s|c)",
	L"Zamknij"
};

// Door Traps. When we examine a door, it could have a particular trap on it. These are the traps.

STR16 pDoorTrapStrings[] =
{
	L"nie posiada �adnych pu�apek",
	L"ma za�o�ony �adunek wybuchowy",
	L"jest pod napi�ciem",
	L"posiada syren� alarmow�",
	L"posiada dyskretny alarm"
};

// Contract Extension. These are used for the contract extension with AIM mercenaries.

STR16 pContractExtendStrings[] =
{
	L"dzie�",
	L"tydzie�",
	L"dwa tygodnie",
};

// On the map screen, there are four columns. This text is popup help text that identifies the individual columns.

STR16 pMapScreenMouseRegionHelpText[] =
{
	L"Wyb�r postaci",
	L"Przydzia� najemnika",
	L"Nanie� tras� podr�y",
	L"Kontrakt najemnika",
	L"Usu� najemnika",
	L"�pij", 
};

// volumes of noises 

STR16 pNoiseVolStr[] =
{
	L"CICHY",
	L"WYRA�NY",
	L"G�O�NY",
	L"BARDZO G�O�NY"
};

// types of noises 

STR16 pNoiseTypeStr[] = // OBSOLETE
{
	L"NIEOKRE�LONY D�WI�K",
	L"ODG�OS RUCHU",
	L"ODG�OS SKRZYPNI�CIA",
	L"PLUSK",
	L"ODG�OS UDERZENIA",
	L"STRZA�",
	L"WYBUCH",
	L"KRZYK",
	L"ODG�OS UDERZENIA",
	L"ODG�OS UDERZENIA",
	L"�OMOT",
	L"TRZASK"
};

// Directions that are used to report noises

STR16 pDirectionStr[] = 
{
	L"P�N-WSCH",
	L"WSCH",
	L"P�D-WSCH",
	L"P�D",
	L"P�D-ZACH",
	L"ZACH",
	L"P�N-ZACH",
	L"P�N"
};

// These are the different terrain types. 

STR16 pLandTypeStrings[] =
{
	L"Miasto",
	L"Droga",
	L"Otwarty teren",
	L"Pustynia",
	L"Las",
	L"Las",	 
	L"Bagno",
	L"Woda",	
	L"Wzg�rza",
	L"Teren nieprzejezdny",
	L"Rzeka",	//river from north to south
	L"Rzeka",	//river from east to west
	L"Terytorium innego kraju",
	//NONE of the following are used for directional travel, just for the sector description.
	L"Tropiki",
	L"Pola uprawne",
	L"Otwarty teren, droga",
	L"Las, droga",
	L"Las, droga",
	L"Tropiki, droga",
	L"Las, droga",
	L"Wybrze�e",
	L"G�ry, droga",
	L"Wybrze�e, droga",
	L"Pustynia, droga",
	L"Bagno, droga",
	L"Las, Rakiety Z-P",
	L"Pustynia, Rakiety Z-P",
	L"Tropiki, Rakiety Z-P",
	L"Meduna, Rakiety Z-P",
	
	//These are descriptions for special sectors
	L"Szpital w Cambrii",
	L"Lotnisko w Drassen",
	L"Lotnisko w Medunie",
	L"Rakiety Z-P",
	L"Kryj�wka rebeliant�w", //The rebel base underground in sector A10
	L"Tixa - Lochy",	//The basement of the Tixa Prison (J9)
	L"Gniazdo stworze�",	//Any mine sector with creatures in it
	L"Orta - Piwnica",	//The basement of Orta (K4)
	L"Tunel",				//The tunnel access from the maze garden in Meduna 
						//leading to the secret shelter underneath the palace
	L"Schron",				//The shelter underneath the queen's palace
	L"",							//Unused
};

STR16 gpStrategicString[] =
{
	L"",	//Unused
	L"%s wykryto w sektorze %c%d, a inny oddzia� jest w drodze.",	//STR_DETECTED_SINGULAR
	L"%s wykryto w sektorze %c%d, a inne oddzia�y s� w drodze.",	//STR_DETECTED_PLURAL
	L"Chcesz skoordynowa� jednoczesne przybycie?",			//STR_COORDINATE

	//Dialog strings for enemies.

	L"Wr�g daje ci szans� si� podda�.",			//STR_ENEMY_SURRENDER_OFFER
	L"Wr�g schwyta� reszt� twoich nieprzytomnych najemnik�w.",	//STR_ENEMY_CAPTURED

	//The text that goes on the autoresolve buttons							

	L"Odwr�t", 		//The retreat button				//STR_AR_RETREAT_BUTTON
	L"OK",		//The done button				//STR_AR_DONE_BUTTON

	//The headers are for the autoresolve type (MUST BE UPPERCASE)

	L"OBRONA",								//STR_AR_DEFEND_HEADER
	L"ATAK",								//STR_AR_ATTACK_HEADER
	L"STARCIE",								//STR_AR_ENCOUNTER_HEADER
	L"Sektor",		//The Sector A9 part of the header		//STR_AR_SECTOR_HEADER

	//The battle ending conditions						

	L"ZWYCI�STWO!",								//STR_AR_OVER_VICTORY
	L"PORA�KA!",								//STR_AR_OVER_DEFEAT
	L"KAPITULACJA!",							//STR_AR_OVER_SURRENDERED
	L"NIEWOLA!",								//STR_AR_OVER_CAPTURED
	L"ODWR�T!",								//STR_AR_OVER_RETREATED

	//These are the labels for the different types of enemies we fight in autoresolve.

	L"Samoobrona",							//STR_AR_MILITIA_NAME,
	L"Elity",								//STR_AR_ELITE_NAME,
	L"�o�nierze",								//STR_AR_TROOP_NAME,
	L"Administrator",							//STR_AR_ADMINISTRATOR_NAME,
	L"Stworzenie",								//STR_AR_CREATURE_NAME,

	//Label for the length of time the battle took

	L"Czas trwania",							//STR_AR_TIME_ELAPSED,

	//Labels for status of merc if retreating.  (UPPERCASE)			

	L"WYCOFA�(A) SI�",								//STR_AR_MERC_RETREATED,
	L"WYCOFUJE SI�",								//STR_AR_MERC_RETREATING,
	L"WYCOFAJ SI�",								//STR_AR_MERC_RETREAT,

	//PRE BATTLE INTERFACE STRINGS 
	//Goes on the three buttons in the prebattle interface.  The Auto resolve button represents
	//a system that automatically resolves the combat for the player without having to do anything.
	//These strings must be short (two lines -- 6-8 chars per line)

	L"Rozst. autom.",							//STR_PB_AUTORESOLVE_BTN,
	L"Id� do sektora",							//STR_PB_GOTOSECTOR_BTN,
	L"Wycof. ludzi",							//STR_PB_RETREATMERCS_BTN,

	//The different headers(titles) for the prebattle interface.
	L"STARCIE Z WROGIEM",							//STR_PB_ENEMYENCOUNTER_HEADER,
	L"INWAZJA WROGA",							//STR_PB_ENEMYINVASION_HEADER, // 30
	L"ZASADZKA WROGA",								//STR_PB_ENEMYAMBUSH_HEADER
	L"WEJ�CIE DO WROGIEGO SEKTORA",				//STR_PB_ENTERINGENEMYSECTOR_HEADER
	L"ATAK STWOR�W",							//STR_PB_CREATUREATTACK_HEADER
	L"ATAK DZIKICH KOT�W",							//STR_PB_BLOODCATAMBUSH_HEADER
	L"WEJ�CIE DO LEGOWISKA DZIKICH KOT�W",			//STR_PB_ENTERINGBLOODCATLAIR_HEADER

	//Various single words for direct translation.  The Civilians represent the civilian
	//militia occupying the sector being attacked.  Limited to 9-10 chars

	L"Po�o�enie",
	L"Wrogowie",
	L"Najemnicy",
	L"Samoobrona",
	L"Stwory",
	L"Dzikie koty",
	L"Sektor",
	L"Brak",		//If there are no uninvolved mercs in this fight.
	L"N/D",			//Acronym of Not Applicable
	L"d",			//One letter abbreviation of day
	L"g",			//One letter abbreviation of hour

	//TACTICAL PLACEMENT USER INTERFACE STRINGS
	//The four buttons 

	L"Wyczy��",
	L"Rozprosz",
	L"Zgrupuj",
	L"OK",

	//The help text for the four buttons.  Use \n to denote new line (just like enter).

	L"Kasuje wszystkie pozy|cje najemnik�w, \ni pozwala ponownie je wprowadzi�.", 
	L"Po ka�dym naci�ni�ciu rozmie|szcza\nlosowo twoich najemnik�w.",
	L"|Grupuje najemnik�w w wybranym miejscu.",
	L"Kliknij ten klawisz gdy ju� rozmie�cisz \nswoich najemnik�w. (|E|n|t|e|r)",
	L"Musisz rozmie�ci� wszystkich najemnik�w \nzanim rozpoczniesz walk�.",

	//Various strings (translate word for word)

	L"Sektor",
	L"Wybierz pocz�tkowe pozycje",

	//Strings used for various popup message boxes.  Can be as long as desired.

	L"To miejsce nie jest zbyt dobre. Jest niedost�pne. Spr�buj gdzie indziej.",
	L"Rozmie�� swoich najemnik�w na pod�wietlonej cz�ci mapy.",

	//This message is for mercs arriving in sectors.  Ex:  Red has arrived in sector A9.
	//Don't uppercase first character, or add spaces on either end.

	L"przyby�(a) do sektora", 

	//These entries are for button popup help text for the prebattle interface.  All popup help
	//text supports the use of \n to denote new line.  Do not use spaces before or after the \n.
	L"Automatycznie prowadzi walk� za ciebie, \nnie �aduj�c planszy. (|A)",
	L"Atakuj�c sektor wroga \nnie mo�na automatycznie rozstrzygn�� walki.",
	L"Wej�cie do sektora \nby nawi�za� walk� z wrogiem. (|E)",
	L"Wycofuje oddzia� \ndo s�siedniego sektora. (|R)",				//singular version
	L"Wycofuje wszystkie oddzia�y \ndo s�siedniego sektora. (|R)", //multiple groups with same previous sector

	//various popup messages for battle conditions.  

	//%c%d is the sector -- ex:  A9
	L"Nieprzyjaciel zatakowa� oddzia�y samoobrony w sektorze %c%d.",
	//%c%d is the sector -- ex:  A9
	L"Stworzenia zaatakowa�y oddzia�y samoobrony w sektorze %c%d.",
	//1st %d refers to the number of civilians eaten by monsters,  %c%d is the sector -- ex:  A9
	//Note:  the minimum number of civilians eaten will be two.
	L"Stworzenia zatakowa�y i zabi�y %d cywili w sektorze %s.",
	//%c%d is the sector -- ex:  A9
	L"Nieprzyjaciel zatakowa� twoich najemnik�w w sektorze %s.  �aden z twoich najemnik�w nie mo�e walczy�!",
	//%c%d is the sector -- ex:  A9
	L"Stworzenia zatakowa�y twoich najemnik�w w sektorze %s.  �aden z twoich najemnik�w nie mo�e walczy�!",

};

STR16 gpGameClockString[] = 
{
	//This is the day represented in the game clock.  Must be very short, 4 characters max.
	L"Dzie�",	
};

//When the merc finds a key, they can get a description of it which 
//tells them where and when they found it.
STR16 sKeyDescriptionStrings[2] =
{
	L"Zn. w sektorze:",
	L"Zn. w dniu:",
};

//The headers used to describe various weapon statistics.

CHAR16		gWeaponStatsDesc[][ 17 ] =
{
	// HEADROCK: Changed this for Extended Description project
	L"Stan:",
	L"Waga (%s):", 
	L"PA Koszty",	
	L"Zas.:",		// Range
	L"Si�a:",		// Damage
	L"Ilo��:", 		// Number of bullets left in a magazine
    L"PA:",                 // abbreviation for Action Points
	L"=",
	L"=",
						//Lal: additional strings for tooltips
	L"Celno��:",	//9
	L"Zasi�g:",		//10	
	L"Si�a:",		//11
	L"Waga:",		//12
	L"Og�uszenie:",//13
	// HEADROCK: Added new strings for extended description ** REDUNDANT **
	L"Attachments:",	//14	// TODO.Translate
	L"AUTO/5:",		//15
	L"Liczba:",		//16

	// TODO.Translate
	L"Default:",	//17 //WarmSteel - So we can also display default attachments

};

// HEADROCK: Several arrays of tooltip text for new Extended Description Box
// Please note, several of these are artificially inflated to 19 entries to help fix a complication with
// changing item type while watching its description box
STR16		gzWeaponStatsFasthelp[ 29 ] =
{
	L"Zas.",
	L"Obra�.",
	L"PA: (mniej - lepiej)",
	L"Auto/5AP",
	L"Celno��",
	L"Stan",
	L"Trud napraw",
	L"AP/przygot.",
	L"AP za 1 strza�",
	L"AP za seri�",
	L"AP za Auto",
	L"AP/prze�aduj",
	L"AP/prze�aduj r�cznie",
	L"T�umienie b�ysku",
	L"G�o�no�� (mniej - lepiej)",
	L"Modyf. trafie�",
	L"�redni max zasg. lasera",
	L"Modf. celowania",
	L"Min. zasg. dla bonusu cel.",
	L"Modf. dw�jnogu",
	L"AP za rzut",
	L"AP za strza�",
	L"AP/cios-n�",
	L"Wy�. 1 strza�!",
	L"Wy�. seri�!",
	L"Wy�. auto!",
	L"AP/cios-�om",
	L"Autofire Penalty (Lower is better)",
    L"Burst Penalty (Lower is better)",
};

STR16		gzWeaponStatsFasthelpTactical[ 29 ] =
{
	L"Zas.",
	L"Obra�.",
	L"PA: (mniej - lepiej)",
	L"Auto/5AP",
	L"Celno��",
	L"Stan",
	L"Trud napraw",
	L"AP/przygot.",
	L"AP za 1 strza�",
	L"AP za seri�",
	L"AP za Auto",
	L"AP/prze�aduj",
	L"AP/prze�aduj r�cznie",
	L"Modyf. trafie�",
	L"�redni max zasg. lasera",
	L"Modf. celowania",
	L"Min. zasg. dla bonusu cel.",
	L"T�umienie b�ysku",
	L"G�o�no�� (mniej - lepiej)",
	L"Modf. dw�jnogu",
	L"AP za rzut",
	L"AP za strza�",
	L"AP/cios-n�",
	L"Wy�. 1 strza�!",
	L"Wy�. seri�!",
	L"Wy�. auto!",
	L"AP/cios-�om",
	L"Autofire Penalty (Lower is better)",
    L"Burst Penalty (Lower is better)",
};

STR16		gzAmmoStatsFasthelp[ 20 ] =
{
	L"Penetracja os�on (mniej � lepiej)",
	L"Moc obalaj�ca (wi�cej � lepiej)",
	L"Eksplozja przed celem (wi�cej � lepiej)",
	L"Efekt smugowy",
	L"P. czo�g.",
	L"Nisc zamka",
	L"Pomija os�on�",
	L"Korozj",
	L"Modyf. zasg.",
	L"Modyf. obra�e�",
	L"Modyf. trafie�",
	L"Autofire Penalty Modifier (Higher is better)",
	L"Modyf. kary za seri� (wi�cej � lepiej)",
	L"Modyf. sprawno�ci",
	L"Modyf. g�o�no�ci (mniej - lepiej)",
	L"",
	L"",
	L"",
	L"",
	L"",
};

STR16		gzArmorStatsFasthelp[ 20 ] =
{
	L"Os�ona",
	L"Pokrycie (wi�cej - lepiej)",
	L"Zu�ycie (mniej - lepiej)",
	L"Modyf. AP",
	L"Modyf. trafie�",
	L"Kam le�ny",
	L"Kam miasto",
	L"Kam pustyn.",
	L"Kam �nieg",
	L"Modyf. skradania",
	L"Modyf. zasg. wzroku",
	L"Modyf. zasg. wzroku/dzie�",
	L"Modyf. zasg. wzroku/noc",
	L"Modyf. zasg. wzroku/jasne �wiat�o",
	L"Modyf. zasg. wzr./jaskinia",
	L"Widzenie tunelowe (w %)",
	L"Modyf. zasg. s�uchu",
	L"",
	L"",
	L"",
};

STR16		gzExplosiveStatsFasthelp[ 20 ] =
{
	L"Obra�.",
	L"Og�uszanie",
	L"G�o�n. wybuchu (mniej - lepiej)",
	L"Niestabilno��! (mniej - lepiej)",
	L"Zsg. wybuchu",
	L"Zsg efektu pocz�tk.",
	L"Zsg. efektu ko�cow.",
	L"Trwanie efektu",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
	L"",
};

STR16		gzMiscItemStatsFasthelp[ 34 ] =
{
	L"Modyf. rozmiaru (mniej - lepiej)", // 0
	L"Modyf. sprawno�ci",
	L"Modyf. g�o�no�ci (mniej - lepiej)",
	L"Ukrywa b�ysk",
	L"Modf. dw�jnogu",
	L"Modyf. zasi�gu", // 5
	L"Modyf. trafie�",
	L"Max zasg. lasera",
	L"Modf bonusu celowania",
	L"Modyf. d�ug. serii",
	L"Modyf. kary za seri� (wi�cej - lepiej)", // 10
	L"Modyf. kary za ogie� auto (wi�cej - lepiej)",
	L"Modyf. AP",
	L"Modyf. AP za seri� (mniej - lepiej)",
	L"Modyf. AP za ogie� auto (mniej - lepiej)",
	L"Modf AP/przygotwanie (mniej - lepiej)", // 15
	L"Modf AP/prze�adowanie (mniej - lepiej)",
	L"Modyf. wlk. magazynka",
	L"Modyf. AP/atak (mniej - lepiej)",
	L"Modyf. obra�e�",
	L"Modf obr. walki wr�cz", // 20
	L"Kam le�ny",
	L"Kam miasto",
	L"Kam pustyn.",
	L"Kam �nieg",
	L"Modyf. skradania", // 25
	L"Modyf. zasg. s�uchu",
	L"Modyf. zasg. wzroku",
	L"Modyf. zasg. wzroku/dzie�",
	L"Modyf. zasg. wzroku/noc",
	L"Modyf. zasg. wzroku/jasne �wiat�o", //30
	L"Modyf. zasg. wzr./jaskinia",
	L"Widzenie tunelowe w % (mniej - lepiej)",
	L"Min. zasg. dla bonusu cel.",
};

// HEADROCK: End new tooltip text

//The headers used for the merc's money.

CHAR16 gMoneyStatsDesc[][ 13 ] =
{
	L"Kwota",
	L"Pozosta�o:", //this is the overall balance
	L"Kwota",
	L"Wydzieli�:", // the amount he wants to separate from the overall balance to get two piles of money

	L"Bie��ce",
	L"Saldo",
	L"Kwota do",
	L"podj�cia",
};

//The health of various creatures, enemies, characters in the game. The numbers following each are for comment
//only, but represent the precentage of points remaining. 

CHAR16 zHealthStr[][13] =
{
	L"UMIERAJ�CY",		//	>= 0
	L"KRYTYCZNY", 		//	>= 15
	L"KIEPSKI",		//	>= 30
	L"RANNY",    	//	>= 45
	L"ZDROWY",    	//	>= 60
	L"SILNY",     	// 	>= 75
	L"DOSKONA�Y",		// 	>= 90
};

STR16	gzMoneyAmounts[6] = 
{ 
	L"$1000",
	L"$100",
	L"$10",
	L"OK",
	L"Wydziel",
	L"Podejmij",
};

// short words meaning "Advantages" for "Pros" and "Disadvantages" for "Cons." 
CHAR16		gzProsLabel[10] = 
{
	L"Zalety:",
};

CHAR16		gzConsLabel[10] = 
{
	L"Wady:",
};

//Conversation options a player has when encountering an NPC
CHAR16 zTalkMenuStrings[6][ SMALL_STRING_LENGTH ] =
{
	L"Powt�rz", 	//meaning "Repeat yourself"
	L"Przyja�nie",		//approach in a friendly
	L"Bezpo�rednio",		//approach directly - let's get down to business
	L"Gro�nie",		//approach threateningly - talk now, or I'll blow your face off
	L"Daj",		
	L"Rekrutuj",
};

//Some NPCs buy, sell or repair items. These different options are available for those NPCs as well.
CHAR16 zDealerStrings[4][ SMALL_STRING_LENGTH ]=
{
	L"Kup/Sprzedaj",
	L"Kup",
	L"Sprzedaj",
	L"Napraw",
};

CHAR16 zDialogActions[1][ SMALL_STRING_LENGTH ] = 
{
	L"OK",
};


//These are vehicles in the game.

STR16 pVehicleStrings[] =
{
 L"Eldorado",
 L"Hummer", // a hummer jeep/truck -- military vehicle
 L"Furgonetka z lodami",
 L"Jeep",
 L"Czo�g",
 L"Helikopter",
};

STR16 pShortVehicleStrings[] =
{
	L"Eldor.",
	L"Hummer",			// the HMVV
	L"Furg.",
	L"Jeep",
	L"Czo�g",
	L"Heli.", 				// the helicopter
};

STR16	zVehicleName[] =
{
	L"Eldorado",
	L"Hummer",		//a military jeep. This is a brand name.
	L"Furg.",			// Ice cream truck
	L"Jeep",
	L"Czo�g",
	L"Heli.", 		//an abbreviation for Helicopter
};


//These are messages Used in the Tactical Screen

CHAR16 TacticalStr[][ MED_STRING_LENGTH ] =
{
	L"Nalot",
	L"Udzieli� automatycznie pierwszej pomocy?",
	
	// CAMFIELD NUKE THIS and add quote #66.
	
	L"%s zauwa�y�(a) �e dostawa jest niekompletna.",
	
	// The %s is a string from pDoorTrapStrings
	
	L"Zamek %s.", 
	L"Brak zamka.",
	L"Sukces!",
	L"Niepowodzenie.",
	L"Sukces!",
	L"Niepowodzenie.",
	L"Zamek nie ma pu�apek.",
	L"Sukces!",
	// The %s is a merc name
	L"%s nie posiada odpowiedniego klucza.",
	L"Zamek zosta� rozbrojony.",
	L"Zamek nie ma pu�apek.",
	L"Zamkni�te.",
	L"DRZWI",
	L"ZABEZP.",
	L"ZAMKNI�TE",
	L"OTWARTE",
	L"ROZWALONE",
	L"Tu jest prze��cznik. W��czy� go?",
	L"Rozbroi� pu�apk�?",
	L"Poprz...",
	L"Nast...",
	L"Wi�cej...",

	// In the next 2 strings, %s is an item name

	L"%s - po�o�ono na ziemi.",
	L"%s - przekazano do - %s.",

	// In the next 2 strings, %s is a name

	L"%s otrzyma�(a) ca�� zap�at�.",
	L"%s - nale�no�� wobec niej/niego wynosi jeszcze %d.",
	L"Wybierz cz�stotliwo�� sygna�u detonuj�cego:",  	//in this case, frequency refers to a radio signal
	L"Ile tur do eksplozji:",	//how much time, in turns, until the bomb blows
	L"Ustaw cz�stotliwo�� zdalnego detonatora:", 	//in this case, frequency refers to a radio signal
	L"Rozbroi� pu�apk�?",
	L"Usun�� niebiesk� flag�?",
	L"Umie�ci� tutaj niebiesk� flag�?",
	L"Ko�cz�ca tura",

	// In the next string, %s is a name. Stance refers to way they are standing.

	L"Na pewno chcesz zaatakowa� - %s?",
	L"Pojazdy nie mog� zmienia� pozycji.",
	L"Robot nie mo�e zmienia� pozycji.",

	// In the next 3 strings, %s is a name

	L"%s nie mo�e zmieni� pozycji w tym miejscu.",
	L"%s nie mo�e tu otrzyma� pierwszej pomocy.",	
	L"%s nie potrzebuje pierwszej pomocy.",
	L"Nie mo�na ruszy� w to miejsce.",
	L"Oddzia� jest ju� kompletny. Nie ma miejsca dla nowych rekrut�w.",	//there's no room for a recruit on the player's team

	// In the next string, %s is a name

	L"%s pracuje ju� dla ciebie.",

	// Here %s is a name and %d is a number

	L"%s - nale�no�� wobec niej/niego wynosi %d$.",

	// In the next string, %s is a name

	L"%s - Eskortowa� t� osob�?",

	// In the next string, the first %s is a name and the second %s is an amount of money (including $ sign)

	L"%s - Zatrudni� t� osob� za %s dziennie?",

	// This line is used repeatedly to ask player if they wish to participate in a boxing match. 

	L"Chcesz walczy�?",

	// In the next string, the first %s is an item name and the 
	// second %s is an amount of money (including $ sign)

	L"%s - Kupi� to za %s?",

	// In the next string, %s is a name

	L"%s jest pod eskort� oddzia�u %d.",

	// These messages are displayed during play to alert the player to a particular situation

	L"ZACI�TA",					//weapon is jammed.
	L"Robot potrzebuje amunicji kaliber %s.",		//Robot is out of ammo
	L"Rzuci� tam? To niemo�liwe.",		//Merc can't throw to the destination he selected

	// These are different buttons that the player can turn on and off.

	L"Skradanie si� (|Z)",
	L"Ekran |Mapy",
	L"Koniec tury (|D)",
	L"Rozmowa",
	L"Wycisz",
	L"Pozycja do g�ry (|P|g|U|p)",
	L"Poziom kursora (|T|a|b)",
	L"Wspinaj si� / Zeskocz (|J)",
	L"Pozycja w d� (|P|g|D|n)",
	L"Bada� (|C|t|r|l)",
	L"Poprzedni najemnik",
	L"Nast�pny najemnik (|S|p|a|c|j|a)",
	L"|Opcje",
	L"Ci�g�y ogie� (|B)",
	L"Sp�jrz/Obr�� si� (|L)",
	L"Zdrowie: %d/%d\nEnergia: %d/%d\nMorale: %s",
	L"Co?",					//this means "what?"
	L"Kont",					//an abbrieviation for "Continued"
	L"%s ma w��czone potwierdzenia g�osowe.",
	L"%s ma wy��czone potwierdzenia g�osowe.",
	L"Stan: %d/%d\nPaliwo: %d/%d",
	L"Wysi�d� z pojazdu" ,
	L"Zmie� oddzia� ( |S|h|i|f|t |S|p|a|c|j|a )",
	L"Prowad�",
	L"N/D",						//this is an acronym for "Not Applicable."
	L"U�yj ( Walka wr�cz )",
	L"U�yj ( Broni palnej )",
	L"U�yj ( Broni bia�ej )",
	L"U�yj ( Mat. wybuchowych )",
	L"U�yj ( Apteczki )",
	L"(�ap)",
	L"(Prze�aduj)",
	L"(Daj)",
	L"%s - pu�apka zosta�a uruchomiona.",
	L"%s przyby�(a) na miejsce.",
	L"%s straci�(a) wszystkie Punkty Akcji.",
	L"%s jest nieosi�galny(na).",
	L"%s ma ju� za�o�one opatrunki.",
	L"%s nie ma banda�y.",
	L"Wr�g w sektorze!",
	L"Nie ma wroga w zasi�gu wzroku.",
	L"Zbyt ma�o Punkt�w Akcji.",
	L"Nikt nie u�ywa zdalnego sterowania.",
	L"Ci�g�y ogie� opr�ni� magazynek!",
	L"�O�NIERZ",
	L"STW�R",
	L"SAMOOBRONA",
	L"CYWIL",
	L"Wyj�cie z sektora",
	L"OK",
	L"Anuluj",
	L"Wybrany najemnik",
	L"Wszyscy najemnicy w oddziale",
	L"Id� do sektora",
	L"Otw�rz map�",
	L"Nie mo�na opu�ci� sektora z tej strony.",
	L"%s jest zbyt daleko.",
	L"Usu� korony drzew",
	L"Poka� korony drzew",
	L"WRONA",				//Crow, as in the large black bird
	L"SZYJA",
	L"G�OWA",
	L"TU��W",
	L"NOGI",
	L"Powiedzie� kr�lowej to, co chce wiedzie�?",
	L"Wz�r odcisku palca pobrany",
	L"Niew�a�ciwy wz�r odcisku palca. Bro� bezu�yteczna.",
	L"Cel osi�gni�ty",
	L"Droga zablokowana",
	L"Wp�ata/Podj�cie pieni�dzy",		//Help text over the $ button on the Single Merc Panel 
	L"Nikt nie potrzebuje pierwszej pomocy.",
	L"Zac.",						// Short form of JAMMED, for small inv slots
	L"Nie mo�na si� tam dosta�.",					// used ( now ) for when we click on a cliff
	L"Przej�cie zablokowane. Czy chcesz zamieni� si� miejscami z t� osob�?",
	L"Osoba nie chce si� przesun��.",
	// In the following message, '%s' would be replaced with a quantity of money (e.g. $200)
	L"Zgadzasz si� zap�aci� %s?",
	L"Zgadzasz si� na darmowe leczenie?",
	L"Zgadasz si� na ma��e�stwo z Darylem?",
	L"K�ko na klucze",
	L"Nie mo�esz tego zrobi� z eskortowan� osob�.",
	L"Oszcz�dzi� Krotta?",
	L"Poza zasi�giem broni",
	L"G�rnik",
	L"Pojazdem mo�na podr�owa� tylko pomi�dzy sektorami",
	L"Teraz nie mo�na automatycznie udzieli� pierwszej pomocy",
	L"Przej�cie zablokowane dla - %s",
	L"Twoi najemnicy, schwytani przez �o�nierzy Deidranny, s� tutaj uwi�zieni!",
	L"Zamek zosta� trafiony",
	L"Zamek zosta� zniszczony",
	L"Kto� inny majstruje przy tych drzwiach.",
	L"Stan: %d/%d\nPaliwo: %d/%d",
	L"%s nie widzi - %s.",  // Cannot see person trying to talk to
	L"Dodatek usuni�ty",
	L"Nie mo�esz zdoby� kolejnego pojazdu, poniewa� posiadasz ju� 2",
};

//Varying helptext explains (for the "Go to Sector/Map" checkbox) what will happen given different circumstances in the "exiting sector" interface.
STR16 pExitingSectorHelpText[] =
{
	//Helptext for the "Go to Sector" checkbox button, that explains what will happen when the box is checked.
	L"Je�li zaznaczysz t� opcj�, to s�siedni sektor zostanie natychmiast za�adowany.",
	L"Je�li zaznaczysz t� opcj�, to na czas podr�y pojawi si� automatycznie ekran mapy.",

	//If you attempt to leave a sector when you have multiple squads in a hostile sector.
	L"Ten sektor jest okupowany przez wroga i nie mo�esz tu zostawi� najemnik�w.\nMusisz upora� si� z t� sytuacj� zanim za�adujesz inny sektor.",

	//Because you only have one squad in the sector, and the "move all" option is checked, the "go to sector" option is locked to on. 
	//The helptext explains why it is locked.
	L"Gdy wyprowadzisz swoich pozosta�ych najemnik�w z tego sektora,\ns�siedni sektor zostanie automatycznie za�adowany.",
	L"Gdy wyprowadzisz swoich pozosta�ych najemnik�w z tego sektora,\nto na czas podr�y pojawi si� automatycznie ekran mapy.",

	//If an EPC is the selected merc, it won't allow the merc to leave alone as the merc is being escorted.  The "single" button is disabled.
	L"%s jest pod eskort� twoich najemnik�w i nie mo�e bez nich opu�ci� tego sektora.",

	//If only one conscious merc is left and is selected, and there are EPCs in the squad, the merc will be prohibited from leaving alone.
	//There are several strings depending on the gender of the merc and how many EPCs are in the squad.
	//DO NOT USE THE NEWLINE HERE AS IT IS USED FOR BOTH HELPTEXT AND SCREEN MESSAGES!
	L"%s nie mo�e sam opu�ci� tego sektora, gdy� %s jest pod jego eskort�.", //male singular
	L"%s nie mo�e sama opu�ci� tego sektora, gdy� %s jest pod jej eskort�.", //female singular
	L"%s nie mo�e sam opu�ci� tego sektora, gdy� eskortuje inne osoby.", //male plural
	L"%s nie mo�e sama opu�ci� tego sektora, gdy� eskortuje inne osoby.", //female plural

	//If one or more of your mercs in the selected squad aren't in range of the traversal area, then the  "move all" option is disabled,
	//and this helptext explains why.
	L"Wszyscy twoi najemnicy musz� by� w pobli�u,\naby oddzia� m�g� si� przemieszcza�.",

	L"", //UNUSED

	//Standard helptext for single movement.  Explains what will happen (splitting the squad)
	L"Je�li zaznaczysz t� opcj�, %s b�dzie podr�owa� w pojedynk�\ni automatycznie znajdzie si� w osobnym oddziale.",

	//Standard helptext for all movement.  Explains what will happen (moving the squad)
	L"Je�li zaznaczysz t� opcj�, aktualnie\nwybrany oddzia� opu�ci ten sektor.",

	//This strings is used BEFORE the "exiting sector" interface is created.  If you have an EPC selected and you attempt to tactically
	//traverse the EPC while the escorting mercs aren't near enough (or dead, dying, or unconscious), this message will appear and the
	//"exiting sector" interface will not appear.  This is just like the situation where
	//This string is special, as it is not used as helptext.  Do not use the special newline character (\n) for this string.
	L"%s jest pod eskort� twoich najemnik�w i nie mo�e bez nich opu�ci� tego sektora. Aby opu�ci� sektor twoi najemnicy musz� by� w pobli�u.",
};



STR16 pRepairStrings[] = 
{
	L"Wyposa�enie", 		// tell merc to repair items in inventory
	L"Baza rakiet Z-P", // tell merc to repair SAM site - SAM is an acronym for Surface to Air Missile
	L"Anuluj", 		// cancel this menu
	L"Robot", 		// repair the robot
};


// NOTE: combine prestatbuildstring with statgain to get a line like the example below.
// "John has gained 3 points of marksmanship skill." 

STR16 sPreStatBuildString[] =
{
	L"traci", 		// the merc has lost a statistic
	L"zyskuje", 		// the merc has gained a statistic
	L"pkt.",	// singular
	L"pkt.",	// plural
	L"pkt.",	// singular
	L"pkt.",	// plural
};

STR16 sStatGainStrings[] =
{
	L"zdrowia.",
	L"zwinno�ci.",
	L"zr�czno�ci.",
	L"inteligencji.",
	L"umiej�tno�ci medycznych.",
	L"umiej�tno�ci w dziedzinie materia��w wybuchowych.",
	L"umiej�tno�ci w dziedzinie mechaniki.",
	L"umiej�tno�ci strzeleckich.",
	L"do�wiadczenia.",
	L"si�y.",
	L"umiej�tno�ci dowodzenia.",
};


STR16 pHelicopterEtaStrings[] =
{
	L"Ca�kowita trasa:  ",// total distance for helicopter to travel
	L" Bezp.:   ", 			// distance to travel to destination
	L" Niebezp.:", 			// distance to return from destination to airport
	L"Ca�kowity koszt: ", 		// total cost of trip by helicopter
	L"PCP:  ", 			// ETA is an acronym for "estimated time of arrival" 
	L"Helikopter ma ma�o paliwa i musi wyl�dowa� na terenie wroga.",	// warning that the sector the helicopter is going to use for refueling is under enemy control -> 
  L"Pasa�erowie: ",
  L"Wyb�r Skyridera lub pasa�er�w?",
  L"Skyrider",
  L"Pasa�erowie",
};

STR16 sMapLevelString[] =
{
	L"Poziom:", 			// what level below the ground is the player viewing in mapscreen
};

STR16 gsLoyalString[] =
{
	L"Lojalno�ci", 			// the loyalty rating of a town ie : Loyal 53%
};


// error message for when player is trying to give a merc a travel order while he's underground.

STR16 gsUndergroundString[] =
{
	L"nie mo�na wydawa� rozkaz�w podr�y pod ziemi�.", 
};

STR16 gsTimeStrings[] =
{
	L"g",				// hours abbreviation
	L"m",				// minutes abbreviation
	L"s",				// seconds abbreviation
	L"d",				// days abbreviation
};

// text for the various facilities in the sector

STR16 sFacilitiesStrings[] =
{
	L"Brak", 		
	L"Szpital",  		 
	L"Factory",	// TODO.Translate
	L"Wi�zienie",
	L"Baza wojskowa",
	L"Lotnisko",
	L"Strzelnica",		// a field for soldiers to practise their shooting skills
};

// text for inventory pop up button

STR16 pMapPopUpInventoryText[] =
{
	L"Inwentarz",
	L"Zamknij",
};

// town strings

STR16 pwTownInfoStrings[] =
{
	L"Rozmiar",					// 0 // size of the town in sectors
	L"", 						// blank line, required
	L"Pod kontrol�", 					// how much of town is controlled
	L"Brak", 					// none of this town
	L"Przynale�na kopalnia", 				// mine associated with this town
	L"Lojalno��",					// 5 // the loyalty level of this town
	L"Wyszkolonych", 					// the forces in the town trained by the player
	L"",
	L"G��wne obiekty", 				// main facilities in this town
	L"Poziom", 					// the training level of civilians in this town
	L"Szkolenie cywili",				// 10 // state of civilian training in town
	L"Samoobrona", 					// the state of the trained civilians in the town
	L"Mobile Training",			// HEADROCK HAM 3.6: The stat of Mobile militia training in town	// TODO.Translate
};

// Mine strings

STR16 pwMineStrings[] =
{
	L"Kopalnia",						// 0
	L"Srebro",
	L"Z�oto",
	L"Dzienna produkcja",
	L"Mo�liwa produkcja",
	L"Opuszczona",				// 5
	L"Zamkni�ta",
	L"Na wyczerpaniu",
	L"Produkuje",
	L"Stan",
	L"Tempo produkcji",
	L"Typ z�o�a",				// 10
	L"Kontrola miasta",
	L"Lojalno�� miasta",
//	L"G�rnicy",
};

// blank sector strings

STR16 pwMiscSectorStrings[] =
{
	L"Si�y wroga",
	L"Sektor",
	L"Przedmiot�w",
	L"Nieznane",
	L"Pod kontrol�",
	L"Tak",
	L"Nie",
};

// error strings for inventory

STR16 pMapInventoryErrorString[] =
{
	L"%s jest zbyt daleko.",	//Merc is in sector with item but not close enough
	L"Nie mo�na wybra� tego najemnika.",  //MARK CARTER
	L"%s nie mo�e st�d zabra� tego przedmiotu, gdy� nie jest w tym sektorze.",
	L"Podczas walki nie mo�na korzysta� z tego panelu.",
	L"Podczas walki nie mo�na korzysta� z tego panelu.",
	L"%s nie mo�e tu zostawi� tego przedmiotu, gdy� nie jest w tym sektorze.",
	L"W trakcie walki nie mo�esz do�adowywa� magazynka.",
};

STR16 pMapInventoryStrings[] =
{
	L"Po�o�enie", 			// sector these items are in
	L"Razem przedmiot�w", 		// total number of items in sector
};


// help text for the user

STR16 pMapScreenFastHelpTextList[] =
{
	L"Kliknij w kolumnie 'Przydz.', aby przydzieli� najemnika do innego oddzia�u lub wybranego zadania.",
	L"Aby wyznaczy� najemnikowi cel w innym sektorze, kliknij pole w kolumnie 'Cel'.",
	L"Gdy najemnicy otrzymaj� ju� rozkaz przemieszczenia si�, kompresja czasu pozwala im szybciej dotrze� na miejsce.",
	L"Kliknij lewym klawiszem aby wybra� sektor. Kliknij ponownie aby wyda� najemnikom rozkazy przemieszczenia, lub kliknij prawym klawiszem by uzyska� informacje o sektorze.",
	L"Naci�nij w dowolnym momencie klawisz 'H' by wy�wietli� okienko pomocy.",
	L"Pr�bny tekst",
	L"Pr�bny tekst",
	L"Pr�bny tekst",
	L"Pr�bny tekst",
	L"Niewiele mo�esz tu zrobi�, dop�ki najemnicy nie przylec� do Tracona. Gdy ju� zbierzesz sw�j oddzia�, kliknij przycisk Kompresji Czasu, w prawym dolnym rogu. W ten spos�b twoi najemnicy szybciej dotr� na miejsce.",
};

// movement menu text

STR16 pMovementMenuStrings[] =
{
	L"Przemie�� najemnik�w", 	// title for movement box 
	L"Nanie� tras� podr�y", 		// done with movement menu, start plotting movement
	L"Anuluj", 		// cancel this menu
	L"Inni",		// title for group of mercs not on squads nor in vehicles
};


STR16 pUpdateMercStrings[] =
{
	L"Oj:", 			// an error has occured
	L"Wygas� kontrakt najemnik�w:", 	// this pop up came up due to a merc contract ending
	L"Najemnicy wype�nili zadanie:", // this pop up....due to more than one merc finishing assignments
	L"Najemnicy wr�cili do pracy:", // this pop up ....due to more than one merc waking up and returing to work
	L"Odpoczywaj�cy najemnicy:", // this pop up ....due to more than one merc being tired and going to sleep
	L"Wkr�tce wygasn� kontrakty:", 	// this pop up came up due to a merc contract ending
};

// map screen map border buttons help text

STR16 pMapScreenBorderButtonHelpText[] =
{
	L"Poka� miasta (|W)",
	L"Poka� kopalnie (|M)",
	L"Poka� oddzia�y i wrog�w (|T)",
	L"Poka� przestrze� powietrzn� (|A)",
	L"Poka� przedmioty (|I)",
	L"Poka� samoobron� i wrog�w (|Z)",
};


STR16 pMapScreenBottomFastHelp[] =
{
	L"|Laptop",
	L"Ekran taktyczny (|E|s|c)",
	L"|Opcje",
	L"Kompresja czasu (|+)", 	// time compress more
	L"Kompresja czasu (|-)", 	// time compress less
	L"Poprzedni komunikat (|S|t|r|z|a|�|k|a |w |g|�|r|�)\nPoprzednia strona (|P|g|U|p)", 	// previous message in scrollable list
	L"Nast�pny komunikat (|S|t|r|z|a|�|k|a |w |d|�|�)\nNast�pna strona (|P|g|D|n)", 	// next message in the scrollable list
	L"W��cz/Wy��cz kompresj� czasu (|S|p|a|c|j|a)",	// start/stop time compression
};

STR16 pMapScreenBottomText[] =
{
	L"Saldo dost�pne", 	// current balance in player bank account
};

STR16 pMercDeadString[] =
{
	L"%s nie �yje.",
};


STR16 pDayStrings[] =
{
	L"Dzie�",
};

// the list of email sender names

CHAR16 pSenderNameList[500][128] =
{
	L"",
};
/*
{
	L"Enrico",
	L"Psych Pro Inc",
	L"Pomoc",
	L"Psych Pro Inc",
	L"Speck",
	L"R.I.S.",		//5
	L"Barry",
	L"Blood",
	L"Lynx",
	L"Grizzly",
	L"Vicki",			//10
	L"Trevor",
	L"Grunty",
	L"Ivan",
	L"Steroid",
	L"Igor",			//15
	L"Shadow",
	L"Red",
	L"Reaper",
	L"Fidel",
	L"Fox",				//20
	L"Sidney",
	L"Gus",
	L"Buns",
	L"Ice",
	L"Spider",		//25
	L"Cliff",
	L"Bull",
	L"Hitman",
	L"Buzz",
	L"Raider",		//30
	L"Raven",
	L"Static",
	L"Len",
	L"Danny",
	L"Magic",
	L"Stephen",
	L"Scully",
	L"Malice",
	L"Dr.Q",
	L"Nails",
	L"Thor",
	L"Scope",
	L"Wolf",
	L"MD",
	L"Meltdown",
	//----------
	L"M.I.S. Ubezpieczenia",	
	L"Bobby Rays",
	L"Kingpin",
	L"John Kulba",
	L"A.I.M.",
};
*/

// next/prev strings

STR16 pTraverseStrings[] =
{
  L"Poprzedni",
  L"Nast�pny",
};

// new mail notify string 

STR16 pNewMailStrings[] =
{
 L"Masz now� poczt�...",
};


// confirm player's intent to delete messages

STR16 pDeleteMailStrings[] =
{
 L"Usun�� wiadomo��?",
 L"Usun�� wiadomo��?",
};


// the sort header strings

STR16 pEmailHeaders[] =
{
 	L"Od:",
 	L"Temat:",
 	L"Dzie�:",
};

// email titlebar text

STR16 pEmailTitleText[] =
{
 	L"Skrzynka odbiorcza",
};


// the financial screen strings
STR16 pFinanceTitle[] =
{
	L"Ksi�gowy Plus",		//the name we made up for the financial program in the game
};

STR16 pFinanceSummary[] =
{
	L"Wyp�ata:", 				// credit (subtract from) to player's account
	L"Wp�ata:", 				// debit (add to) to player's account
	L"Wczorajsze wp�ywy:",
	L"Wczorajsze dodatkowe wp�ywy:",
	L"Wczorajsze wydatki:",
	L"Saldo na koniec dnia:",
	L"Dzisiejsze wp�ywy:",
	L"Dzisiejsze dodatkowe wp�ywy:",
	L"Dzisiejsze wydatki:",
	L"Saldo dost�pne:",
	L"Przewidywane wp�ywy:",
	L"Przewidywane saldo:", 		// projected balance for player for tommorow
};


// headers to each list in financial screen

STR16 pFinanceHeaders[] =
{
	L"Dzie�", 					// the day column
	L"Ma", 				// the credits column (to ADD money to your account)
	L"Winien",				// the debits column (to SUBTRACT money from your account)
	L"Transakcja", 			// transaction type - see TransactionText below
	L"Saldo", 				// balance at this point in time
	L"Strona", 				// page number
	L"Dzie� (dni)", 		// the day(s) of transactions this page displays 
};


STR16 pTransactionText[] =
{
	L"Naros�e odsetki",			// interest the player has accumulated so far
	L"Anonimowa wp�ata",
	L"Koszt transakcji", 
	L"Wynaj�to -", 				// Merc was hired
	L"Zakupy u Bobby'ego Ray'a", 		// Bobby Ray is the name of an arms dealer
	L"Uregulowanie rachunk�w w M.E.R.C.",
	L"Zastaw na �ycie dla - %s", 		// medical deposit for merc
	L"Analiza profilu w IMP", 		// IMP is the acronym for International Mercenary Profiling
	L"Ubezpieczneie dla - %s", 
	L"Redukcja ubezp. dla - %s",
	L"Przed�. ubezp. dla - %s", 				// johnny contract extended
	L"Anulowano ubezp. dla - %s", 
	L"Odszkodowanie za - %s", 		// insurance claim for merc
	L"1 dzie�", 				// merc's contract extended for a day
	L"1 tydzie�", 				// merc's contract extended for a week
	L"2 tygodnie", 				// ... for 2 weeks
	L"Przych�d z kopalni", 
	L"", //String nuked
	L"Zakup kwiat�w",
	L"Pe�ny zwrot zastawu za - %s",
	L"Cz�ciowy zwrot zastawu za - %s",
	L"Brak zwrotu zastawu za - %s",
	L"Zap�ata dla - %s",		// %s is the name of the npc being paid
	L"Transfer funduszy do - %s", 			// transfer funds to a merc
	L"Transfer funduszy od - %s", 		// transfer funds from a merc
	L"Samoobrona w - %s", // initial cost to equip a town's militia
	L"Zakupy u - %s.",	//is used for the Shop keeper interface.  The dealers name will be appended to the end of the string.
	L"%s wp�aci�(a) pieni�dze.",
	L"Sprzedano rzecz(y) miejscowym",
	L"Facility Use", // HEADROCK HAM 3.6		// TODO.Translate
	L"Militia upkeep", // HEADROCK HAM 3.6		// TODO.Translate
};

STR16 pTransactionAlternateText[] =
{
	L"Ubezpieczenie dla -", 				// insurance for a merc
	L"Przed�. kontrakt z - %s o 1 dzie�.", 				// entend mercs contract by a day
	L"Przed�. kontrakt z - %s o 1 tydzie�.",
	L"Przed�. kontrakt z - %s o 2 tygodnie.",
};

// helicopter pilot payment 

STR16 pSkyriderText[] =
{
	L"Skyriderowi zap�acono %d$", 			// skyrider was paid an amount of money
	L"Skyriderowi trzeba jeszcze zap�aci� %d$", 		// skyrider is still owed an amount of money
	L"Skyrider zatankowa�",	// skyrider has finished refueling
	L"",//unused
	L"",//unused
	L"Skyrider jest got�w do kolejnego lotu.", // Skyrider was grounded but has been freed
	L"Skyrider nie ma pasa�er�w. Je�li chcesz przetransportowa� najemnik�w, zmie� ich przydzia� na POJAZD/HELIKOPTER.",
};


// strings for different levels of merc morale

STR16 pMoralStrings[] =
{
 L"�wietne", 
 L"Dobre",
 L"Stabilne",
 L"S�abe",
 L"Panika",
 L"Z�e",
};

// Mercs equipment has now arrived and is now available in Omerta or Drassen.

STR16 pLeftEquipmentString[] =
{ 
	L"%s - jego/jej sprz�t jest ju� w Omercie( A9 ).", 
	L"%s - jego/jej sprz�t jest ju� w Drassen( B13 ).",
};

// Status that appears on the Map Screen

STR16 pMapScreenStatusStrings[] =
{
	L"Zdrowie",
	L"Energia",
	L"Morale",
	L"Stan",	// the condition of the current vehicle (its "health")
	L"Paliwo",	// the fuel level of the current vehicle (its "energy")
};


STR16 pMapScreenPrevNextCharButtonHelpText[] =
{
	L"Poprzedni najemnik (|S|t|r|z|a|�|k|a |w |l|e|w|o)", 			// previous merc in the list
	L"Nast�pny najemnik (|S|t|r|z|a|�|k|a |w |p|r|a|w|o)", 				// next merc in the list
};


STR16 pEtaString[] =
{
	L"PCP:", 				// eta is an acronym for Estimated Time of Arrival
};

STR16 pTrashItemText[] =
{
	L"Wi�cej tego nie zobaczysz. Czy na pewno chcesz to zrobi�?", 	// do you want to continue and lose the item forever
	L"To wygl�da na co� NAPRAWD� wa�nego. Czy NA PEWNO chcesz to zniszczy�?", // does the user REALLY want to trash this item
};


STR16 pMapErrorString[] = 
{
	L"Oddzia� nie mo�e si� przemieszcza�, je�li kt�ry� z najemnik�w �pi.",

//1-5
	L"Najpierw wyprowad� oddzia� na powierzchni�.",
	L"Rozkazy przemieszczenia? To jest sektor wroga!",
	L"Aby podr�owa� najemnicy musz� by� przydzieleni do oddzia�u lub pojazdu.",
	L"Nie masz jeszcze ludzi.", 		// you have no members, can't do anything 
	L"Najemnik nie mo�e wype�ni� tego rozkazu.",			 		// merc can't comply with your order
//6-10
	L"musi mie� eskort�, aby si� przemieszcza�. Umie�� go w oddziale z eskort�.", // merc can't move unescorted .. for a male
	L"musi mie� eskort�, aby si� przemieszcza�. Umie�� j� w oddziale z eskort�.", // for a female
	L"Najemnik nie przyby� jeszcze do Tracona!",
	L"Wygl�da na to, �e trzeba wpierw uregulowa� sprawy kontraktu.",
	L"Nie mo�na przemie�ci� najemnika. Trwa nalot powietrzny.",
//11-15
	L"Rozkazy przemieszczenia? Trwa walka!",
	L"Zaatakowa�y ci� dzikie koty, w sektorze %s!",
	L"W sektorze %s znajduje si� co�, co wygl�da na legowisko dzikich kot�w!", 
	L"", 
	L"Baza rakiet Ziemia-Powietrze zosta�a przej�ta.",
//16-20
	L"%s - kopalnia zosta�a przej�ta. Tw�j dzienny przych�d zosta� zredukowany do %s.",
	L"Nieprzyjaciel bezkonfliktowo przej�� sektor %s.",
	L"Przynajmniej jeden z twoich najemnik�w nie zosta� do tego przydzielony.",
	L"%s nie mo�e si� przy��czy�, poniewa� %s jest pe�ny",
	L"%s nie mo�e si� przy��czy�, poniewa� %s jest zbyt daleko.",
//21-25
	L"%s - kopalnia zosta�a przej�ta przez si�y Deidranny!",
	L"Si�y wroga w�a�nie zaatakowa�y baz� rakiet Ziemia-Powietrze w - %s.",
	L"Si�y wroga w�a�nie zaatakowa�y - %s.",
	L"W�a�nie zauwa�ono si�y wroga w - %s.",
	L"Si�y wroga w�a�nie przej�y - %s.",
//26-30
	L"Przynajmniej jeden z twoich najemnik�w nie m�g� si� po�o�y� spa�.",
	L"Przynajmniej jeden z twoich najemnik�w nie m�g� wsta�.",
	L"Oddzia�y samoobrony nie pojawi� si� dop�ki nie zostan� wyszkolone.",
	L"%s nie mo�e si� w tej chwili przemieszcza�.",
	L"�o�nierze samoobrony, kt�rzy znajduj� si� poza granicami miasta, nie mog� by� przeniesieni do innego sektora.",
//31-35
	L"Nie mo�esz trenowa� samoobrony w - %s.",
	L"Pusty pojazd nie mo�e si� porusza�!",
	L"%s ma zbyt wiele ran by podr�owa�!",
	L"Musisz wpierw opu�ci� muzeum!",
	L"%s nie �yje!",
//36-40
	L"%s nie mo�e si� zamieni� z - %s, poniewa� si� porusza",
	L"%s nie mo�e w ten spos�b wej�c do pojazdu",
	L"%s nie mo�e si� do��czy� do - %s",
	L"Nie mo�esz kompresowa� czasu dop�ki nie zatrudnisz sobie kilku nowych najemnik�w!",
	L"Ten pojazd mo�e si� porusza� tylko po drodze!",
//41-45
	L"Nie mo�na zmienia� przydzia�u najemnik�w, kt�rzy s� w drodze",
	L"Pojazd nie ma paliwa!",
	L"%s jest zbyt zm�czony(na) by podr�owa�.",
	L"�aden z pasa�er�w nie jest w stanie kierowa� tym pojazdem.",
	L"Jeden lub wi�cej cz�onk�w tego oddzia�u nie mo�e si� w tej chwili przemieszcza�.",
//46-50
	L"Jeden lub wi�cej INNYCH cz�onk�w tego oddzia�u nie mo�e si� w tej chwili przemieszcza�.",
	L"Pojazd jest uszkodzony!",
	L"Pami�taj, �e w jednym sektorze tylko dw�ch najemnik�w mo�e trenowa� �o�nierzy samoobrony.",
	L"Robot nie mo�e si� porusza� bez operatora. Umie�� ich razem w jednym oddziale.",
};


// help text used during strategic route plotting
STR16 pMapPlotStrings[] =
{
	L"Kliknij ponownie sektor docelowy, aby zatwierdzi� tras� podr�y, lub kliknij inny sektor, aby j� wyd�u�y�.",
	L"Trasa podr�y zatwierdzona.",
	L"Cel podr�y nie zosta� zmieniony.",
	L"Trasa podr�y zosta�a anulowana.",
	L"Trasa podr�y zosta�a skr�cona.",
};


// help text used when moving the merc arrival sector
STR16 pBullseyeStrings[] =
{
	L"Kliknij sektor, do kt�rego maj� przylatywa� najemnicy.",
	L"Dobrze. Przylatuj�cy najemnicy b�d� zrzucani w %s",
	L"Najemnicy nie mog� tu przylatywa�. Przestrze� powietrzna nie jest zabezpieczona!",
	L"Anulowano. Sektor zrzutu nie zosta� zmieniony.",
	L"Przestrze� powietrzna nad %s nie jest ju� bezpieczna! Sektor zrzutu zosta� przesuni�ty do %s.",
};


// help text for mouse regions

STR16 pMiscMapScreenMouseRegionHelpText[] =
{
	L"Otw�rz wyposa�enie (|E|n|t|e|r)",
	L"Zniszcz przedmiot",
	L"Zamknij wyposa�enie (|E|n|t|e|r)",
};



// male version of where equipment is left
STR16 pMercHeLeaveString[] =
{
	L"Czy %s ma zostawi� sw�j sprz�t w sektorze, w kt�rym si� obecnie znajduje (%s), czy w Dressen (B13), sk�d odlatuje? ",
	L"Czy %s ma zostawi� sw�j sprz�t w sektorze, w kt�rym si� obecnie znajduje (%s), czy w Omercie (A9), sk�d odlatuje?",
	L"wkr�tce odchodzi i zostawi sw�j sprz�t w Omercie (A9).",
	L"wkr�tce odchodzi i zostawi sw�j sprz�t w Drassen (B13).",
	L"%s wkr�tce odchodzi i zostawi sw�j sprz�t w %s.",
};


// female version
STR16 pMercSheLeaveString[] =
{
	L"Czy %s ma zostawi� sw�j sprz�t w sektorze, w kt�rym si� obecnie znajduje (%s), czy w Dressen (B13), sk�d odlatuje? ",
	L"Czy %s ma zostawi� sw�j sprz�t w sektorze, w kt�rym si� obecnie znajduje (%s), czy w Omercie (A9), sk�d odlatuje?",
	L"wkr�tce odchodzi i zostawi sw�j sprz�t w Omercie (A9).",
	L"wkr�tce odchodzi i zostawi sw�j sprz�t w Drassen (B13).",
	L"%s wkr�tce odchodzi i zostawi sw�j sprz�t w %s.",
};


STR16 pMercContractOverStrings[] =
{
	L" zako�czy� kontrakt wi�c wyjecha�.", 		// merc's contract is over and has departed
	L" zako�czy�a kontrakt wi�c wyjecha�a.", 		// merc's contract is over and has departed
	L" - jego kontrakt zosta� zerwany wi�c odszed�.", 		// merc's contract has been terminated
	L" - jej kontrakt zosta� zerwany wi�c odesz�a.",		// merc's contract has been terminated
	L"Masz za du�y d�ug wobec M.E.R.C. wi�c %s odchodzi.", // Your M.E.R.C. account is invalid so merc left
};

// Text used on IMP Web Pages

// WDS: Allow flexible numbers of IMPs of each sex
//    note: I only updated the English text to remove "three" below
STR16 pImpPopUpStrings[] =
{
	L"Nieprawid�owy kod dost�pu",
	L"Czy na pewno chcesz wznowi� proces okre�lenia profilu?",
	L"Wprowad� nazwisko oraz p�e�",
	L"Wst�pna kontrola stanu twoich finans�w wykaza�a, �e nie sta� ci� na analiz� profilu.",
	L"Opcja tym razem nieaktywna.",
	L"Aby wykona� profil, musisz mie� miejsce dla przynajmniej jednego cz�onka za�ogi.",
	L"Profil zosta� ju� wykonany.",
	L"Nie mo�na za�adowa� postaci I.M.P. z dysku.",
	L"Wykorzysta�e� ju� maksymaln� liczb� postaci I.M.P.",
	L"Masz ju� w oddziale trzy postacie I.M.P. tej samej p�ci.",					//L"You have already the maximum number of I.M.P characters with that gender on your team.",  BY�o ->>L"You have already three I.M.P characters with the same gender on your team.",
	L"Nie sta� ci� na posta� I.M.P.",
	L"Nowa posta� I.M.P. do��czy�a do oddzia�u.",
};


// button labels used on the IMP site

STR16 pImpButtonText[] =
{
	L"O Nas", 			// about the IMP site
	L"ZACZNIJ", 			// begin profiling
	L"Umiej�tno�ci", 		// personality section
	L"Atrybuty", 		// personal stats/attributes section
	L"Appearance", 			// changed from portrait - SANDRO
	L"G�os %d", 			// the voice selection
	L"Gotowe", 			// done profiling
	L"Zacznij od pocz�tku", 		// start over profiling
	L"Tak, wybieram t� odpowied�.", 
	L"Tak", 
	L"Nie",
	L"Sko�czone", 			// finished answering questions
	L"Poprz.", 			// previous question..abbreviated form
	L"Nast.", 			// next question
	L"TAK, JESTEM.", 		// yes, I am certain 
	L"NIE, CHC� ZACZ�� OD NOWA.", // no, I want to start over the profiling process
	L"TAK",
	L"NIE",
	L"Wstecz", 			// back one page
	L"Anuluj", 			// cancel selection
	L"Tak.",
	L"Nie, Chc� spojrze� jeszcze raz.",
	L"Rejestr", 			// the IMP site registry..when name and gender is selected
	L"Analizuj�...", 			// analyzing your profile results
	L"OK",
	L"Character", // Change from "Voice" - SANDRO
};

STR16 pExtraIMPStrings[] =
{
	// These texts have been also slightly changed - SANDRO
	L"With your character traits chosen, it is time to select your skills.",
	L"To complete the process, select your attributes.",
	L"To commence actual profiling, select portrait, voice and colors.",
	L"Now that you have completed your appearence choice, procced to character analysis.",
};

STR16 pFilesTitle[] =
{
	L"Przegl�darka plik�w",
};

STR16 pFilesSenderList[] =
{
	L"Raport Rozp.", 		// the recon report sent to the player. Recon is an abbreviation for reconissance
	L"Intercept #1", 		// first intercept file .. Intercept is the title of the organization sending the file...similar in function to INTERPOL/CIA/KGB..refer to fist record in files.txt for the translated title
	L"Intercept #2",	   // second intercept file
	L"Intercept #3",			 // third intercept file
	L"Intercept #4", // fourth intercept file
	L"Intercept #5", // fifth intercept file
	L"Intercept #6", // sixth intercept file
};

// Text having to do with the History Log

STR16 pHistoryTitle[] =
{
	L"Historia",
};

STR16 pHistoryHeaders[] =
{
	L"Dzie�", 			// the day the history event occurred
	L"Strona", 			// the current page in the history report we are in
	L"Dzie�", 			// the days the history report occurs over
	L"Po�o�enie", 			// location (in sector) the event occurred
	L"Zdarzenie", 			// the event label
};

// various history events
// THESE STRINGS ARE "HISTORY LOG" STRINGS AND THEIR LENGTH IS VERY LIMITED.
// PLEASE BE MINDFUL OF THE LENGTH OF THESE STRINGS. ONE WAY TO "TEST" THIS
// IS TO TURN "CHEAT MODE" ON AND USE CONTROL-R IN THE TACTICAL SCREEN, THEN
// GO INTO THE LAPTOP/HISTORY LOG AND CHECK OUT THE STRINGS. CONTROL-R INSERTS
// MANY (NOT ALL) OF THE STRINGS IN THE FOLLOWING LIST INTO THE GAME.
STR16 pHistoryStrings[] =
{
	L"",																						// leave this line blank
	//1-5
	L"%s naj�ty(ta) w A.I.M.", 										// merc was hired from the aim site
	L"%s naj�ty(ta) w M.E.R.C.", 									// merc was hired from the aim site
	L"%s ginie.", 															// merc was killed
	L"Uregulowano rachunki w M.E.R.C.",								// paid outstanding bills at MERC
	L"Przyj�to zlecenie od Enrico Chivaldori",	
	//6-10
	L"Profil IMP wygenerowany",
	L"Podpisano umow� ubezpieczeniow� dla %s.", 				// insurance contract purchased
	L"Anulowano umow� ubezpieczeniow� dla %s.", 				// insurance contract canceled
	L"Wyp�ata ubezpieczenia za %s.", 							// insurance claim payout for merc
	L"Przed�u�ono kontrakt z: %s o 1 dzie�.", 						// Extented "mercs name"'s for a day
	//11-15
	L"Przed�u�ono kontrakt z: %s o 1 tydzie�.", 					// Extented "mercs name"'s for a week
	L"Przed�u�ono kontrakt z: %s o 2 tygodnie.", 					// Extented "mercs name"'s 2 weeks
	L"%s zwolniony(na).", 													// "merc's name" was dismissed.
	L"%s odchodzi.", 																		// "merc's name" quit.
	L"przyj�to zadanie.", 															// a particular quest started
	//16-20
	L"zadanie wykonane.",
	L"Rozmawiano szefem kopalni %s",									// talked to head miner of town
	L"Wyzwolono - %s",
	L"U�yto kodu Cheat",
	L"�ywno�� powinna by� jutro w Omercie",
	//21-25
	L"%s odchodzi, aby wzi�� �lub z Darylem Hickiem",
	L"Wygas� kontrakt z - %s.",
	L"%s zrekrutowany(na).",
	L"Enrico narzeka na brak post�p�w",
	L"Walka wygrana",
	//26-30
	L"%s - w kopalni ko�czy si� ruda",
	L"%s - w kopalni sko�czy�a si� ruda",
	L"%s - kopalnia zosta�a zamkni�ta",
	L"%s - kopalnia zosta�a otwarta",
	L"Informacja o wi�zieniu zwanym Tixa.",
	//31-35
	L"Informacja o tajnej fabryce broni zwanej Orta.",
	L"Naukowiec w Orcie ofiarowa� kilka karabin�w rakietowych.",
	L"Kr�lowa Deidranna robi u�ytek ze zw�ok.",
	L"Frank opowiedzia� o walkach w San Monie.",
	L"Pewien pacjent twierdzi, �e widzia� co� w kopalni.",
	//36-40
	L"Go�� o imieniu Devin sprzedaje materia�y wybuchowe.",
	L"Spotkanie ze s�awynm eks-najemnikiem A.I.M. - Mike'iem!",
	L"Tony handluje broni�.",
	L"Otrzymano karabin rakietowy od sier�anta Krotta.",
	L"Dano Kyle'owi akt w�asno�ci sklepu Angela.",
	//41-45
	L"Madlab zaoferowa� si� zbudowa� robota.",
	L"Gabby potrafi zrobi� mikstur� chroni�c� przed robakami.",
	L"Keith wypad� z interesu.",
	L"Howard dostarcza� cyjanek kr�lowej Deidrannie.",
	L"Spotkanie z handlarzem Keithem w Cambrii.",
	//46-50
	L"Spotkanie z aptekarzem Howardem w Balime",
	L"Spotkanie z Perko, prowadz�cym ma�y warsztat.",
	L"Spotkanie z Samem z Balime - prowadzi sklep z narz�dziami.",
	L"Franz handluje sprz�tem elektronicznym.",
	L"Arnold prowadzi warsztat w Grumm.",
	//51-55
	L"Fredo naprawia sprz�t elektroniczny w Grumm.",
	L"Otrzymano darowizn� od bogatego go�cia w Balime.",
	L"Spotkano Jake'a, kt�ry prowadzi z�omowisko.",
	L"Jaki� w��cz�ga da� nam elektroniczn� kart� dost�pu.",
	L"Przekupiono Waltera, aby otworzy� drzwi do piwnicy.",
	//56-60
	L"Dave oferuje darmowe tankowania, je�li b�dzie mia� paliwo.",
	L"Greased Pablo's palms.",
	L"Kingpin trzyma pieni�dze w kopalni w San Mona.",
	L"%s wygra�(a) walk�",
	L"%s przegra�(a) walk�",
	//61-65
	L"%s zdyskwalifikowany(na) podczas walki",
	L"Znaleziono du�o pieni�dzy w opuszczonej kopalni.",
	L"Spotkano zab�jc� nas�anego przez Kingpina.",
	L"Utrata kontroli nad sektorem",				//ENEMY_INVASION_CODE
	L"Sektor obroniony",
	//66-70
	L"Przegrana bitwa",							//ENEMY_ENCOUNTER_CODE
	L"Fatalna zasadzka",						//ENEMY_AMBUSH_CODE
	L"Usunieto zasadzk� wroga",
	L"Nieudany atak",			//ENTERING_ENEMY_SECTOR_CODE
	L"Udany atak!",
	//71-75
	L"Stworzenia zaatakowa�y",			//CREATURE_ATTACK_CODE
	L"Zabity(ta) przez dzikie koty",			//BLOODCAT_AMBUSH_CODE
	L"Wyr�ni�to dzikie koty",
	L"%s zabity(ta)",
	L"Przekazano Carmenowi g�ow� terrorysty",
	L"Slay odszed�",
	L"Zabito: %s",
};

STR16 pHistoryLocations[] =
{
	L"N/D",						// N/A is an acronym for Not Applicable
};

// icon text strings that appear on the laptop

STR16 pLaptopIcons[] =
{
	L"E-mail",
	L"Sie�",
	L"Finanse",
	L"Personel",
	L"Historia",
	L"Pliki",
	L"Zamknij",
	L"sir-FER 4.0",			// our play on the company name (Sirtech) and web surFER
};

// bookmarks for different websites
// IMPORTANT make sure you move down the Cancel string as bookmarks are being added

STR16 pBookMarkStrings[] =
{
	L"A.I.M.",
	L"Bobby Ray's",
	L"I.M.P",
	L"M.E.R.C.",
	L"Pogrzeby",
	L"Kwiaty",
	L"Ubezpieczenia",
	L"Anuluj",
};

STR16 pBookmarkTitle[] =
{
	L"Ulubione",
	L"Aby w przysz�o�ci otworzy� to menu, kliknij prawym klawiszem myszy.",
};

// When loading or download a web page

STR16 pDownloadString[] =
{
	L"�adowanie strony...",
	L"Otwieranie strony...",
};

//This is the text used on the bank machines, here called ATMs for Automatic Teller Machine

STR16 gsAtmSideButtonText[] =
{
	L"OK",
	L"We�", 			// take money from merc
	L"Daj", 			// give money to merc
	L"Anuluj", 			// cancel transaction
	L"Skasuj", 			// clear amount being displayed on the screen
};

STR16 gsAtmStartButtonText[] =
{
	L"Transfer $", 		// transfer money to merc -- short form
	L"Atrybuty", 			// view stats of the merc
	L"Wyposa�enie", 			// view the inventory of the merc
	L"Zatrudnienie",
};

STR16 sATMText[ ]=
{
	L"Przes�a� fundusze?", 		// transfer funds to merc?
	L"OK?", 			// are we certain?
	L"Wprowad� kwot�", 		// enter the amount you want to transfer to merc
	L"Wybierz typ", 		// select the type of transfer to merc
	L"Brak �rodk�w", 	// not enough money to transfer to merc
	L"Kwota musi by� podzielna przez $10", // transfer amount must be a multiple of $10
};

// Web error messages. Please use foreign language equivilant for these messages. 
// DNS is the acronym for Domain Name Server
// URL is the acronym for Uniform Resource Locator

STR16 pErrorStrings[] =
{
	L"B��d",
	L"Serwer nie posiada DNS.",	
	L"Sprawd� adres URL i spr�buj ponownie.",
	L"OK",
	L"Niestabilne po��czenie z Hostem. Transfer mo�e trwa� d�u�ej.",
};


STR16 pPersonnelString[] =
{
	L"Najemnicy:", 			// mercs we have
};


STR16 pWebTitle[ ]=
{
	L"sir-FER 4.0",		// our name for the version of the browser, play on company name
};


// The titles for the web program title bar, for each page loaded

STR16 pWebPagesTitles[] =
{
	L"A.I.M.",
	L"A.I.M. Cz�onkowie",
	L"A.I.M. Portrety",		// a mug shot is another name for a portrait
	L"A.I.M. Lista",
	L"A.I.M.",
	L"A.I.M. Weterani",
	L"A.I.M. Polisy",
	L"A.I.M. Historia",
	L"A.I.M. Linki",
	L"M.E.R.C.",
	L"M.E.R.C. Konta",
	L"M.E.R.C. Rejestracja",
	L"M.E.R.C. Indeks",
	L"Bobby Ray's",
	L"Bobby Ray's - Bro�",
	L"Bobby Ray's - Amunicja",
	L"Bobby Ray's - Pancerz",
	L"Bobby Ray's - R�ne",							//misc is an abbreviation for miscellaneous				
	L"Bobby Ray's - U�ywane",
	L"Bobby Ray's - Zam�wienie pocztowe",
	L"I.M.P.",
	L"I.M.P.",
	L"United Floral Service",
	L"United Floral Service - Galeria",
	L"United Floral Service - Zam�wienie",
	L"United Floral Service - Galeria kartek",
	L"Malleus, Incus & Stapes - Brokerzy ubezpieczeniowi",
	L"Informacja",
	L"Kontrakt",
	L"Uwagi",
	L"McGillicutty - Zak�ad pogrzebowy",
	L"",
	L"Nie odnaleziono URL.",
	L"Bobby Ray's - Ostatnie dostawy",
	L"",
	L"",
};

STR16 pShowBookmarkString[] =
{
	L"Sir-Pomoc",
	L"Kliknij ponownie Sie� by otworzy� menu Ulubione.",
};

STR16 pLaptopTitles[] =
{
	L"Poczta",
	L"Przegl�darka plik�w",
	L"Personel",
	L"Ksi�gowy Plus",
	L"Historia",
};

STR16 pPersonnelDepartedStateStrings[] =
{
	//reasons why a merc has left.
	L"�mier� w akcji",
	L"Zwolnienie",
	L"Inny",
	L"Ma��e�stwo",
	L"Koniec kontraktu",
	L"Rezygnacja",
};
// personnel strings appearing in the Personnel Manager on the laptop

STR16 pPersonelTeamStrings[] =
{
	L"Bie��cy oddzia�",
	L"Wyjazdy",
	L"Koszt dzienny:",
	L"Najwy�szy koszt:",
	L"Najni�szy koszt:",
	L"�mier� w akcji:",
	L"Zwolnienie:",
	L"Inny:",
};


STR16 pPersonnelCurrentTeamStatsStrings[] =
{
	L"Najni�szy",
	L"�redni",
	L"Najwy�szy",
};


STR16 pPersonnelTeamStatsStrings[] =
{
	L"ZDR",
	L"ZWN",
	L"ZRCZ",
	L"SI�A",
	L"DOW",
	L"INT",
	L"DO�W",
	L"STRZ",
	L"MECH",
	L"WYB",
	L"MED",
};


// horizontal and vertical indices on the map screen

STR16 pMapVertIndex[] =
{
	L"X",
	L"A",
	L"B",
	L"C",
	L"D",
	L"E",
	L"F",
	L"G",
	L"H",
	L"I",
	L"J",
	L"K",
	L"L",
	L"M",
	L"N",
	L"O",
	L"P",
};

STR16 pMapHortIndex[] =
{
	L"X",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"10",
	L"11",
	L"12",
	L"13",
	L"14",
	L"15",
	L"16",
};

STR16 pMapDepthIndex[] =
{
	L"",
	L"-1",
	L"-2",
	L"-3",
};

// text that appears on the contract button

STR16 pContractButtonString[] =
{
	L"Kontrakt",
};

// text that appears on the update panel buttons

STR16 pUpdatePanelButtons[] =
{
	L"Dalej",
	L"Stop",
};

// Text which appears when everyone on your team is incapacitated and incapable of battle

CHAR16 LargeTacticalStr[][ LARGE_STRING_LENGTH ] =
{
	L"Pokonano ci� w tym sektorze!",
	L"Wr�g nie zna lito�ci i po�era was wszystkich!",
	L"Nieprzytomni cz�onkowie twojego oddzia�u zostali pojmani!",
	L"Cz�onkowie twojego oddzia�u zostali uwi�zieni.",
};


//Insurance Contract.c
//The text on the buttons at the bottom of the screen.

STR16			InsContractText[] = 
{ 
	L"Wstecz",
	L"Dalej",
	L"Akceptuj�",
	L"Skasuj",
};



//Insurance Info
// Text on the buttons on the bottom of the screen

STR16		InsInfoText[] = 
{ 
	L"Wstecz", 
	L"Dalej"
};



//For use at the M.E.R.C. web site. Text relating to the player's account with MERC

STR16			MercAccountText[] = 
{
	// Text on the buttons on the bottom of the screen
	L"Autoryzacja",
	L"Strona g��wna",
	L"Konto #:",
	L"Najemnik",
	L"Dni",
	L"Stawka",	//5
	L"Op�ata",
	L"Razem:",
	L"Czy na pewno chcesz zatwierdzi� p�atno��: %s?",		//the %s is a string that contains the dollar amount ( ex. "$150" )
};

// Merc Account Page buttons
STR16			MercAccountPageText[] = 
{
	// Text on the buttons on the bottom of the screen
	L"Wstecz",
	L"Dalej",
};

//For use at the M.E.R.C. web site. Text relating a MERC mercenary


STR16			MercInfo[] =
{
	L"Zdrowie",
	L"Zwinno��",
	L"Sprawno��",
	L"Si�a",
	L"Um. dowodz.",
	L"Inteligencja",
	L"Poz. do�wiadczenia",
	L"Um. strzeleckie",
	L"Zn. mechaniki",
	L"Mat. wybuchowe",
	L"Wiedza medyczna",

	L"Poprzedni",
	L"Najmij",
	L"Nast�pny",
	L"Dodatkowe informacje",
	L"Strona g��wna",
	L"Naj�ty",
	L"Koszt:",
	L"Dziennie",
	L"Nie �yje",

	L"Wygl�da na to, �e chcesz wynaj�� zbyt wielu najemnik�w. Limit wynosi 18.",
	L"Niedost�pny",
};



// For use at the M.E.R.C. web site. Text relating to opening an account with MERC

STR16			MercNoAccountText[] =
{
	//Text on the buttons at the bottom of the screen
	L"Otw�rz konto",
	L"Anuluj",
	L"Nie posiadasz konta. Czy chcesz sobie za�o�y�?"
};



// For use at the M.E.R.C. web site. MERC Homepage

STR16			MercHomePageText[] =
{
	//Description of various parts on the MERC page
	L"Speck T. Kline, za�o�yciel i w�a�ciciel",
	L"Aby otworzy� konto naci�nij tu",
	L"Aby zobaczy� konto naci�nij tu",
	L"Aby obejrze� akta naci�nij tu",
	// The version number on the video conferencing system that pops up when Speck is talking
	L"Speck Com v3.2",
};

// For use at MiGillicutty's Web Page.

STR16			sFuneralString[] =
{
	L"Zak�ad pogrzebowy McGillicutty, pomaga rodzinom pogr��onym w smutku od 1983.",
	L"Kierownik, by�y najemnik A.I.M. Murray \'Pops\' McGillicutty jest do�wiadczonym pracownikiem zak�adu pogrzebowego.",
	L"Przez ca�e �ycie obcowa� ze �mierci�, 'Pops' wie jak trudne s� te chwile.",
	L"Zak�ad pogrzebowy McGillicutty oferuje szeroki zakres us�ug, od duchowego wsparcia po rekonstrukcj� silnie zniekszta�conych zw�ok.",
	L"Pozw�l by McGillicutty ci pom�g� a tw�j ukochany b�dzie spoczywa� w pokoju.",

	// Text for the various links available at the bottom of the page
	L"WY�LIJ KWIATY",
	L"KOLEKCJA TRUMIEN I URN",
	L"US�UGI KREMA- CYJNE",
	L"US�UGI PLANOWANIA POGRZEBU",
	L"KARTKI POGRZE- BOWE",

	// The text that comes up when you click on any of the links ( except for send flowers ).
	L"Niestety, z powodu �mierci w rodzinie, nie dzia�aj� jeszcze wszystkie elementy tej strony.",
	L"Przepraszamy za powy�sze uniedogodnienie."
};

// Text for the florist Home page

STR16			sFloristText[] = 
{
	//Text on the button on the bottom of the page

	L"Galeria",

	//Address of United Florist

	L"\"Zrzucamy z samolotu w dowolnym miejscu\"",
	L"1-555-POCZUJ-MNIE",
	L"333 Dr Nos, Miasto Nasion, CA USA 90210",
	L"http://www.poczuj-mnie.com",

	// detail of the florist page

	L"Dzia�amy szybko i sprawnie!",	
	L"Gwarantujemy dostaw� w dowolny punkt na Ziemi, nast�pnego dnia po z�o�eniu zam�wienia!",
	L"Oferujemy najni�sze ceny na �wiecie!",	
	L"Poka� nam ofert� z ni�sz� cen�, a dostaniesz w nagrod� tuzin r�, za darmo!",
	L"Lataj�ca flora, fauna i kwiaty od 1981.",
	L"Nasz ozdobiony bombowiec zrzuci tw�j bukiet w promieniu co najwy�ej dziesi�ciu mil od ��danego miejsca. Kiedy tylko zechcesz!",
	L"Pozw�l nam zaspokoi� twoje kwieciste fantazje.",
	L"Bruce, nasz �wiatowej renomy projektant bukiet�w, zerwie dla ciebie naj�wie�sze i najwspanialsze kwiaty z naszej szklarni.",
	L"I pami�taj, je�li czego� nie mamy, mo�emy to szybko zasadzi�!"
};



//Florist OrderForm

STR16			sOrderFormText[] = 
{
	//Text on the buttons

	L"Powr�t",
	L"Wy�lij",
	L"Skasuj",
	L"Galeria",

	L"Nazwa bukietu:",
	L"Cena:",			//5
	L"Zam�wienie numer:",
	L"Czas dostawy",
	L"nast. dnia",
	L"dostawa gdy to b�dzie mo�liwe",
	L"Miejsce dostawy",			//10
	L"Dodatkowe us�ugi",
	L"Zgnieciony bukiet($10)",
	L"Czarne R�e($20)",
	L"Zwi�dni�ty bukiet($10)",
	L"Ciasto owocowe (je�eli b�dzie)($10)",		//15
	L"Osobiste kondolencje:",
	L"Ze wzgl�du na rozmiar karteczek, tekst nie mo�e zawiera� wi�cej ni� 75 znak�w.",
	L"...mo�esz te� przejrze� nasze",

	L"STANDARDOWE KARTKI",	
	L"Informacja o rachunku",//20

	//The text that goes beside the area where the user can enter their name

	L"Nazwisko:",
};




//Florist Gallery.c

STR16		sFloristGalleryText[] =
{
	//text on the buttons

	L"Poprz.",	//abbreviation for previous
	L"Nast.",	//abbreviation for next

	L"Kliknij wybran� pozycj� aby z�o�y� zam�wienie.",
	L"Uwaga: $10 dodatkowej op�aty za zwi�dni�ty lub zgnieciony bukiet.",

	//text on the button

	L"G��wna",
};

//Florist Cards

STR16			sFloristCards[] =
{
	L"Kliknij sw�j wyb�r",
	L"Wstecz"
};



// Text for Bobby Ray's Mail Order Site

STR16			BobbyROrderFormText[] = 
{
	L"Formularz zam�wienia",				//Title of the page
	L"Ilo��",					// The number of items ordered
	L"Waga (%s)",			// The weight of the item
	L"Nazwa",				// The name of the item
	L"Cena",				// the item's weight
	L"Warto��",				//5	// The total price of all of items of the same type
	L"W sumie",				// The sub total of all the item totals added
	L"Transport",		// S&H is an acronym for Shipping and Handling 
	L"Razem",			// The grand total of all item totals + the shipping and handling
	L"Miejsce dostawy",	
	L"Czas dostawy",			//10	// See below
	L"Koszt (za %s.)",			// The cost to ship the items
	L"Ekspres - 24h",			// Gets deliverd the next day
	L"2 dni robocze",			// Gets delivered in 2 days
	L"Standardowa dostawa",			// Gets delivered in 3 days
	L" Wyczy��",//15			// Clears the order page
	L" Akceptuj�",			// Accept the order
	L"Wstecz",				// text on the button that returns to the previous page
	L"Strona g��wna",				// Text on the button that returns to the home page
	L"* oznacza u�ywane rzeczy",		// Disclaimer stating that the item is used
	L"Nie sta� ci� na to.",		//20	// A popup message that to warn of not enough money
	L"<BRAK>",				// Gets displayed when there is no valid city selected
	L"Miejsce docelowe przesy�ki: %s. Potwierdzasz?",		// A popup that asks if the city selected is the correct one
	L"Waga przesy�ki*",			// Displays the weight of the package
	L"* Min. Waga",				// Disclaimer states that there is a minimum weight for the package
	L"Dostawy",
};

STR16			BobbyRFilter[] =
{
	// Guns
	L"Inny",
	L"Pistolet",
	L"Pistolet maszynowy",
	L"Karabin maszynowy",
	L"Karabin",
	L"Karabin snajperski",
	L"Karabin bojowy",
	L"Lekki karabin maszynowy",
	L"Strzelba",

	// Ammo
	L"Pistolet",
	L"Pistolet maszynowy",
	L"Karabin maszynowy",
	L"Karabin",
	L"Karabin snajperski",
	L"Karabin bojowy",
	L"Lekki karabin maszynowy",
	L"Strzelba",

	// Used
	L"Bro�",
	L"Pancerz",
	L"Oporz�dzenie",
	L"R�ne",

	// Armour
	L"He�my",
	L"Kamizelki",
	L"Getry ochronne",
	L"P�ytki ceramiczne",

	// Misc
	L"Ostrza",
	L"No�e do rzucania",
	L"Punch. W.",
	L"Granaty",
	L"Bomby",
	L"Apteczki",
	L"Ekwipunek",
	L"Na twarz",
	L"Oporz�dzenie",	//LBE Gear
	L"Inne",
};


// This text is used when on the various Bobby Ray Web site pages that sell items

STR16			BobbyRText[] = 
{
	L"Zam�w",				// Title
	// instructions on how to order
	L"Kliknij wybrane towary. Lewym klawiszem zwi�kszasz ilo�� towaru, a prawym zmniejszasz. Gdy ju� skompletujesz swoje zakupy przejd� do formularza zam�wienia.",			

	//Text on the buttons to go the various links

	L"Poprzednia",		// 
	L"Bro�", 			//3
	L"Amunicja",			//4
	L"Ochraniacze",			//5
	L"R�ne",			//6	//misc is an abbreviation for miscellaneous
	L"U�ywane",			//7
	L"Nast�pna",
	L"FORMULARZ",
	L"Strona g��wna",			//10

	//The following 2 lines are used on the Ammunition page.  
	//They are used for help text to display how many items the player's merc has
	//that can use this type of ammo

	L"Tw�j zesp� posiada",//11
	L"szt. broni do kt�rej pasuje amunicja tego typu", //12

	//The following lines provide information on the items

	L"Waga:",			// Weight of all the items of the same type
	L"Kal:",			// the caliber of the gun
	L"Mag:",			// number of rounds of ammo the Magazine can hold
	L"Zas:",				// The range of the gun
	L"Si�a:",				// Damage of the weapon	
	L"CS:",			// Weapon's Rate Of Fire, acronym ROF
	L"Koszt:",			// Cost of the item
	L"Na stanie:",			// The number of items still in the store's inventory
	L"Ilo�� na zam�w.:",		// The number of items on order
	L"Uszkodz.",			// If the item is damaged
	L"Waga:",			// the Weight of the item
	L"Razem:",			// The total cost of all items on order
	L"* Stan: %%",		// if the item is damaged, displays the percent function of the item

	//Popup that tells the player that they can only order 10 items at a time
	
	L"Przepraszamy za to utrudnienie, ale na jednym zam�wieniu mo�e si� znajdowa� tylko 10 pozycji! Je�li potrzebujesz wi�cej, z�� kolejne zam�wienie.",

	// A popup that tells the user that they are trying to order more items then the store has in stock

	L"Przykro nam. Chwilowo nie mamy tego wi�cej na magazynie. Prosz� spr�bowa� p�niej.",

	//A popup that tells the user that the store is temporarily sold out

	L"Przykro nam, ale chwilowo nie mamy tego towaru na magazynie",

};


// Text for Bobby Ray's Home Page

STR16			BobbyRaysFrontText[] =
{
	//Details on the web site

	L"Tu znajdziesz nowo�ci z dziedziny broni i osprz�tu wojskowego",
	L"Zaspokoimy wszystkie twoje potrzeby w dziedzinie materia��w wybuchowych",
	L"U�YWANE RZECZY",

	//Text for the various links to the sub pages

	L"RӯNE",
	L"BRO�",
	L"AMUNICJA",		//5
	L"OCHRANIACZE",

	//Details on the web site

	L"Je�li MY tego nie mamy, to znaczy, �e nigdzie tego nie dostaniesz!",
	L"W trakcie budowy",
};



// Text for the AIM page.
// This is the text used when the user selects the way to sort the aim mercanaries on the AIM mug shot page

STR16			AimSortText[] =
{
	L"Cz�onkowie A.I.M.",				// Title
	// Title for the way to sort
	L"Sortuj wg:",					

	// sort by...

	L"Ceny",											
	L"Do�wiadczenia",
	L"Um. strzeleckich",
	L"Um. med.",
	L"Zn. mat. wyb.",
	L"Zn. mechaniki",

	//Text of the links to other AIM pages

	L"Portrety najemnik�w",
	L"Akta najemnika",
	L"Poka� galeri� by�ych cz�onk�w A.I.M.",

	// text to display how the entries will be sorted

	L"Rosn�co",
	L"Malej�co",
};


//Aim Policies.c
//The page in which the AIM policies and regulations are displayed

STR16		AimPolicyText[] =
{
	// The text on the buttons at the bottom of the page

	L"Poprzednia str.",
	L"Strona g��wna", 
	L"Przepisy",
	L"Nast�pna str.",
	L"Rezygnuj�",
	L"Akceptuj�",
};



//Aim Member.c
//The page in which the players hires AIM mercenaries

// Instructions to the user to either start video conferencing with the merc, or to go the mug shot index

STR16			AimMemberText[] =
{
	L"Lewy klawisz myszy",
	L"kontakt z najemnikiem",
	L"Prawy klawisz myszy",
	L"lista portret�w",
};					

//Aim Member.c
//The page in which the players hires AIM mercenaries

STR16			CharacterInfo[] =
{
	// The various attributes of the merc

	L"Zdrowie",										
	L"Zwinno��",										
	L"Sprawno��",									
	L"Si�a",
	L"Um. dowodzenia",
	L"Inteligencja",
	L"Poziom do�w.",
	L"Um. strzeleckie",
	L"Zn. mechaniki",
	L"Zn. mat. wyb.",
	L"Wiedza med.",				//10

	// the contract expenses' area

	L"Zap�ata",
	L"Czas",				
	L"1 dzie�",					
	L"1 tydzie�",
	L"2 tygodnie",

	// text for the buttons that either go to the previous merc, 
	// start talking to the merc, or go to the next merc

	L"Poprzedni",
	L"Kontakt",
	L"Nast�pny",

	L"Dodatkowe informacje",				// Title for the additional info for the merc's bio
	L"Aktywni cz�onkowie",		//20		// Title of the page
	L"Opcjonalne wyposa�enie:",				// Displays the optional gear cost
	L"Wymagany jest zastaw na �ycie",			// If the merc required a medical deposit, this is displayed
};


//Aim Member.c
//The page in which the player's hires AIM mercenaries

//The following text is used with the video conference popup

STR16			VideoConfercingText[] =
{
	L"Warto�� kontraktu:",				//Title beside the cost of hiring the merc

	//Text on the buttons to select the length of time the merc can be hired

	L"Jeden dzie�",										
	L"Jeden tydzie�",
	L"Dwa tygodnie",

	//Text on the buttons to determine if you want the merc to come with the equipment 

	L"Bez sprz�tu",
	L"We� sprz�t",

	// Text on the Buttons

	L"TRANSFER",			// to actually hire the merc
	L"ANULUJ",				// go back to the previous menu
	L"WYNAJMIJ",				// go to menu in which you can hire the merc
	L"ROZ��CZ",				// stops talking with the merc
	L"OK",									
	L"NAGRAJ SI�",			// if the merc is not there, you can leave a message 

	//Text on the top of the video conference popup

	L"Wideo konferencja z - ",		
	L"��cz�. . .",

	L"z zastawem"			// Displays if you are hiring the merc with the medical deposit
};



//Aim Member.c
//The page in which the player hires AIM mercenaries

// The text that pops up when you select the TRANSFER FUNDS button

STR16			AimPopUpText[] =
{
	L"TRANSFER ZAKO�CZONY POMY�LNIE",	// You hired the merc
	L"PRZEPROWADZENIE TRANSFERU NIE MO�LIWE",		// Player doesn't have enough money, message 1
	L"BRAK �RODK�W",				// Player doesn't have enough money, message 2

	// if the merc is not available, one of the following is displayed over the merc's face

	L"Wynaj�to",											
	L"Prosz� zostaw wiadomo��",
	L"Nie �yje",

	//If you try to hire more mercs than game can support

	L"You have a full team of mercs already.",

	L"Nagrana wiadomo��",
	L"Wiadomo�� zapisana",
};


//AIM Link.c

STR16			AimLinkText[] =
{
	L"A.I.M. Linki",	//The title of the AIM links page
};



//Aim History

// This page displays the history of AIM

STR16			AimHistoryText[] =
{
	L"A.I.M. Historia",					//Title

	// Text on the buttons at the bottom of the page

	L"Poprzednia str.",
	L"Strona g��wna", 
	L"Byli cz�onkowie",
	L"Nast�pna str."
};


//Aim Mug Shot Index

//The page in which all the AIM members' portraits are displayed in the order selected by the AIM sort page.

STR16			AimFiText[] =
{
	// displays the way in which the mercs were sorted

	L"ceny",
	L"do�wiadczenia",
	L"um. strzeleckich",
	L"um. medycznych",
	L"zn. materia��w wyb.",
	L"zn. mechaniki",

	// The title of the page, the above text gets added at the end of this text

	L"Cz�onkowie A.I.M. posortowani rosn�co wg %s",
	L"Cz�onkowie A.I.M. posortowani malej�co wg %s",

	// Instructions to the players on what to do

	L"Lewy klawisz",
	L"Wyb�r najemnika",			//10
	L"Prawy klawisz",
	L"Opcje sortowania",

	// Gets displayed on top of the merc's portrait if they are...

	L"Wyjecha�(a)",
	L"Nie �yje",						//14
	L"Wynaj�to",
};



//AimArchives.
// The page that displays information about the older AIM alumni merc... mercs who are no longer with AIM

STR16			AimAlumniText[] =
{
	// Text of the buttons

	L"STRONA 1",
	L"STRONA 2",
	L"STRONA 3",

	L"Byli cz�onkowie A.I.M.",	// Title of the page


	L"OK"			// Stops displaying information on selected merc
};






//AIM Home Page

STR16			AimScreenText[] =
{
	// AIM disclaimers
	
	L"Znaki A.I.M. i logo A.I.M. s� prawnie chronione w wi�kszo�ci kraj�w.",
	L"Wi�c nawet nie my�l o pr�bie ich podrobienia.",
	L"Wszelkie prawa zastrze�one A.I.M. 2005, Ltd.",

	//Text for an advertisement that gets displayed on the AIM page

	L"United Floral Service",
	L"\"Zrzucamy gdziekolwiek\"",				//10
	L"Zr�b to jak nale�y...",
	L"...za pierwszym razem",
	L"Bro� i akcesoria, je�li czego� nie mamy, to tego nie potrzebujesz.",
};


//Aim Home Page

STR16			AimBottomMenuText[] =
{
	//Text for the links at the bottom of all AIM pages
	L"Strona g��wna",
	L"Cz�onkowie",
	L"Byli cz�onkowie",
	L"Przepisy",
	L"Historia",
	L"Linki",
};



//ShopKeeper Interface
// The shopkeeper interface is displayed when the merc wants to interact with 
// the various store clerks scattered through out the game.

STR16 SKI_Text[ ] = 
{
	L"TOWARY NA STANIE",		//Header for the merchandise available
	L"STRONA",				//The current store inventory page being displayed
	L"KOSZT OGӣEM",				//The total cost of the the items in the Dealer inventory area
	L"WARTO�� OGӣEM",			//The total value of items player wishes to sell
	L"WYCENA",				//Button text for dealer to evaluate items the player wants to sell
	L"TRANSAKCJA",			//Button text which completes the deal. Makes the transaction.
	L"OK",				//Text for the button which will leave the shopkeeper interface.
	L"KOSZT NAPRAWY",			//The amount the dealer will charge to repair the merc's goods
	L"1 GODZINA",			// SINGULAR! The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"%d GODZIN(Y)",		// PLURAL!   The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"NAPRAWIONO",		// Text appearing over an item that has just been repaired by a NPC repairman dealer
	L"Brak miejsca by zaoferowa� wi�cej rzeczy.",	//Message box that tells the user there is no more room to put there stuff
	L"%d MINUT(Y)",		// The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"Upu�� przedmiot na ziemi�.",
};

//ShopKeeper Interface
//for the bank machine panels. Referenced here is the acronym ATM, which means Automatic Teller Machine

STR16	SkiAtmText[] =
{
	//Text on buttons on the banking machine, displayed at the bottom of the page
	L"0",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"7",
	L"8",
	L"9",
	L"OK",						// Transfer the money
	L"We�",					// Take money from the player
	L"Daj",					// Give money to the player
	L"Anuluj",					// Cancel the transfer
	L"Skasuj",					// Clear the money display
};


//Shopkeeper Interface
STR16	gzSkiAtmText[] = 
{	

	// Text on the bank machine panel that....
	L"Wybierz",			// tells the user to select either to give or take from the merc
	L"Wprowad� kwot�",			// Enter the amount to transfer
	L"Transfer got�wki do najemnika",		// Giving money to the merc
	L"Transfer got�wki od najemnika",		// Taking money from the merc
	L"Brak �rodk�w",			// Not enough money to transfer
	L"Saldo",				// Display the amount of money the player currently has
};


STR16	SkiMessageBoxText[] =
{
	L"Czy chcesz do�o�y� %s ze swojego konta, aby pokry� r�nic�?",
	L"Brak �rodk�w. Brakuje ci %s",
	L"Czy chcesz przeznaczy� %s ze swojego konta, aby pokry� koszty?",
	L"Popro� o rozpocz�cie transakscji",
	L"Popro� o napraw� wybranych przedmiot�w",
	L"Zako�cz rozmow�",
	L"Saldo dost�pne",
};


//OptionScreen.c

STR16	zOptionsText[] = 
{
	//button Text
	L"Zapisz gr�",
	L"Odczytaj gr�",
	L"Wyj�cie",
	L">>",
	L"<<",
	L"OK",

	//Text above the slider bars
	L"Efekty",
	L"Dialogi",
	L"Muzyka",

	//Confirmation pop when the user selects..
	L"Zako�czy� gr� i wr�ci� do g��wnego menu?",

	L"Musisz w��czy� opcj� dialog�w lub napis�w.",
};


//SaveLoadScreen 
STR16			zSaveLoadText[] = 
{
	L"Zapisz gr�",
	L"Odczytaj gr�",
	L"Anuluj",
	L"Zapisz wybran�",
	L"Odczytaj wybran�",

	L"Gra zosta�a pomy�lnie zapisana",
	L"B��D podczas zapisu gry!",
	L"Gra zosta�a pomy�lnie odczytana",
	L"B��D podczas odczytu gry!",

	L"Wersja gry w zapisanym pliku r�ni si� od bie��cej. Prawdopodobnie mo�na bezpiecznie kontynuowa�. Kontynuowa�?",
	L"Zapisane pliki gier mog� by� uszkodzone. Czy chcesz je usun��?",

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.	
#ifdef JA2BETAVERSION
	L"Nieprawid�owa wersja zapisu gry. W razie problem�w prosimy o raport. Kontynuowa�?",
#else
	L"Pr�ba odczytu starszej wersji zapisu gry. Zaktualizowa� ten zapis i odczyta� gr�?",
#endif

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.
#ifdef JA2BETAVERSION
	L"Nieprawid�owa wersja zapisu gry. W razie problem�w prosimy o raport. Kontynuowa�?",
#else
	L"Pr�ba odczytu starszej wersji zapisu gry. Zaktualizowa� ten zapis i odczyta� gr�?",
#endif

	L"Czy na pewno chcesz nadpisa� gr� na pozycji %d?",
	L"Chcesz odczyta� gr� z pozycji",


	//The first %d is a number that contains the amount of free space on the users hard drive,
	//the second is the recommended amount of free space.
	L"Brak miejsca na dysku twardym.  Na dysku wolne jest %d MB, a wymagane jest przynajmniej %d MB.",	

	L"Zapisuj�...",			//When saving a game, a message box with this string appears on the screen

	L"Standardowe uzbrojenie",
	L"Ca�e mn�stwo broni",
	L"Realistyczna gra",
	L"Elementy S-F",

	L"Stopie� trudno�ci",
	L"Platynowy tryb", //Placeholder English

	L"Wyposa�enie Bobby Ray's",
	L"Normalne",
	L"�wietne",
	L"Wy�mienite",
	L"Niewiarygodne",

	L"Nowy inwentarz nie dzia�a w rozdzielczo�ci 640x480. Aby z niego korzysta� zmie� rozdzielczo�� i spr�buj ponownie.",
	L"Nowy inwentarz nie korzysta z domy�lnego folderu 'Data'.",

	// TODO.Translate
	L"You cannot play this savegame with the New Attachment System, because this savegame does not use the New Inventory.",
};



//MapScreen
STR16		zMarksMapScreenText[] =
{
	L"Poziom mapy",
	L"Nie masz jeszcze �o�nierzy samoobrony.  Musisz najpierw wytrenowa� mieszka�c�w miast.",
	L"Dzienny przych�d",
	L"Najmemnik ma polis� ubezpieczeniow�", 
    L"%s nie potrzebuje snu.", 
	L"%s jest w drodze i nie mo�e spa�", 
	L"%s jest zbyt zm�czony(na), spr�buj troch� p�niej.",
	L"%s prowadzi.",
	L"Oddzia� nie mo�e si� porusza� je�eli jeden z najemnik�w �pi.",

	// stuff for contracts
	L"Mimo, �e mo�esz op�aci� kontrakt, to jednak nie masz got�wki by op�aci� sk�adk� ubezpieczeniow� za najemnika.",
	L"%s - sk�adka ubezpieczeniowa najemnika b�dzie kosztowa� %s za %d dzie�(dni). Czy chcesz j� op�aci�?",
	L"Inwentarz sektora",
	L"Najemnik posiada zastaw na �ycie.", 
	
	// other items
	L"Lekarze", // people acting a field medics and bandaging wounded mercs 
	L"Pacjenci", // people who are being bandaged by a medic 
	L"Gotowe", // Continue on with the game after autobandage is complete 
	L"Przerwij", // Stop autobandaging of patients by medics now 
	L"Przykro nam, ale ta opcja jest wy��czona w wersji demo.", // informs player this option/button has been disabled in the demo 
	L"%s nie ma zestawu narz�dzi.",
	L"%s nie ma apteczki.",
	L"Brak ch�tnych ludzi do szkolenia, w tej chwili.",
	L"%s posiada ju� maksymaln� liczb� oddzia��w samoobrony.",
	L"Najemnik ma kontrakt na okre�lony czas.",
	L"Kontrakt najemnika nie jest ubezpieczony",
	L"Mapa",		// 24
};


STR16 pLandMarkInSectorString[] =
{
	L"Oddzia� %d zauwa�y� kogo� w sektorze %s",
};

// confirm the player wants to pay X dollars to build a militia force in town
STR16 pMilitiaConfirmStrings[] =
{
	L"Szkolenie oddzia�u samoobrony b�dzie kosztowa�o $", // telling player how much it will cost
	L"Zatwierdzasz wydatek?", // asking player if they wish to pay the amount requested
	L"Nie sta� ci� na to.", // telling the player they can't afford to train this town
	L"Kontynuowa� szkolenie samoobrony w - %s (%s %d)?", // continue training this town?
	L"Koszt $", // the cost in dollars to train militia
	L"( T/N )",   // abbreviated yes/no
	L"",	// unused
	L"Szkolenie samoobrony w %d sektorach b�dzie kosztowa�o $ %d. %s", // cost to train sveral sectors at once
	L"Nie masz %d$, aby wyszkoli� samoobron� w tym mie�cie.",
	L"%s musi mie� %d% lojalno�ci, aby mo�na by�o kontynuowa� szkolenie samoobrony.",
	L"Nie mo�esz ju� d�u�ej szkoli� samoobrony w mie�cie %s.",
	L"You cannot afford the $%d to train mobile militia here.", // HEADROCK HAM 3.6: Mobile Militia		// TODO.Translate
	L"Continue training mobile militia in %s (%s %d)?", // HEADROCK HAM 3.6: Mobile Militia				// TODO.Translate
	L"Training mobile militia in %d sectors will cost $ %d. %s", // HEADROCK HAM 3.6: Mobile Militia	// TODO.Translate
	L"Training a squad of mobile militia will cost $", // HEADROCK HAM 3.6: Mobile Militia				// TODO.Translate
};

//Strings used in the popup box when withdrawing, or depositing money from the $ sign at the bottom of the single merc panel
STR16	gzMoneyWithdrawMessageText[] = 
{
	L"Jednorazowo mo�esz wyp�aci� do 20,000$.",
	L"Czy na pewno chcesz wp�aci� %s na swoje konto?",
};

STR16	gzCopyrightText[] = 
{
	L"Prawa autorskie nale�� do (C) 1999 Sir-tech Canada Ltd. Wszelkie prawa zastrze�one.",
};

//option Text
STR16		zOptionsToggleText[] = 
{
	L"Dialogi",
	L"Wycisz potwierdzenia",
	L"Napisy",
	L"Wstrzymuj napisy",
	L"Animowany dym",
	L"Drastyczne sceny",
	L"Nigdy nie ruszaj mojej myszki!",
	L"Stara metoda wyboru",
	L"Pokazuj tras� ruchu",
	L"Pokazuj chybione strza�y",
	L"Potwierdzenia Real-Time",
	L"Najemnik �pi/budzi si�",
	L"U�ywaj systemu metrycznego",
	L"O�wietlenie podczas ruchu",
	L"Przyci�gaj kursor do najemnik�w",
	L"Przyci�gaj kursor do drzwi",
	L"Pulsuj�ce przedmioty",
	L"Pokazuj korony drzew",
	L"Pokazuj siatk�",
	L"Pokazuj kursor 3D",
	L"Pokazuj szans� na trafienie",
	L"Zamiana kursora granatnika",
	L"Wr�g opuszcza ca�y ekwipunek",
	L"Wysoki k�t strza��w z granatnika",
	L"Ograniczenie poziom�w celowania",
	L"Spacja = nast�pny oddzia�",
	L"Pokazuj cienie przedmiot�w",
	L"Pokazuj zasi�g broni w polach",
	L"Efekt smugowy dla poj. strza�u",
	L"Odg�osy padaj�cego deszczu",
	L"Pokazuj wrony",
	L"Show Soldier Tooltips",	// Changed from "Random I.M.P personality" - SANDRO
	L"Automatyczny zapis",
	L"Cichy Skyrider",
	L"Niskie obci��enie procesora",
	L"Rozszerzone Okno Opisu (EDB)",	//Enhanced Description Box
	L"Wymu� tryb turowy",					// add forced turn mode
	L"Stat Progress Bars",					// Show progress towards stat increase		// TODO.Translate
	L"Alternate bullet graphics",			// Show alternate bullet graphics (tracers) // TODO.Translate
	L"--Cheat Mode Options--",				// TOPTION_CHEAT_MODE_OPTIONS_HEADER,
	L"Force Bobby Ray shipments",			// force all pending Bobby Ray shipments
	L"-----------------",					// TOPTION_CHEAT_MODE_OPTIONS_END
	L"--DEBUG OPTIONS--",					// an example options screen options header (pure text)
	L"Reset ALL game options",				// failsafe show/hide option to reset all options
	L"Do you really want to reset?",		// a do once and reset self option (button like effect)
	L"Debug Options in other builds",		// allow debugging in release or mapeditor
	L"DEBUG Render Option group",			// an example option that will show/hide other options
	L"Render Mouse Regions",				// an example of a DEBUG build option
	L"-----------------",					// an example options screen options divider (pure text)

	// this is THE LAST option that exists (debug the options screen, doesnt do anything, except exist)
	L"THE_LAST_OPTION",
};

//This is the help text associated with the above toggles.
STR16	zOptionsScreenHelpText[] =
{
	//speech
	L"Je�li W��CZONE, w grze pojawia� si� b�d� dialogi.",

	//Mute Confirmation
	L"Je�li W��CZONE, g�osowe potwierdzenia postaci zostan� wyciszone.",

		//Subtitles
	L"Je�li W��CZONE, pojawia� si� b�d� napisy podczas rozm�w z innymi postaciami.",

	//Key to advance speech
	L"Je�li W��CZONE, napisy pojawiaj�ce si� podczas dialog�w b�d� znika�y dopiero po klikni�ciu.",

	//Toggle smoke animation
	L"Je�li W��CZONE, dym z granat�w b�dzie animowany. Mo�e spowolni� dzia�anie gry.",

	//Blood n Gore
	L"Je�li W��CZONE, pokazywane b�d� bardzo drastyczne sceny.",

	//Never move my mouse
	L"Je�li W��CZONE, kursor nie b�dzie automatycznie ustawia� si� nad pojawiaj�cymi si� okienkami dialogowymi.",

	//Old selection method
	L"Je�li W��CZONE, wyb�r postaci b�dzie dzia�a� tak jak w poprzednich cz�ciach gry.",

	//Show movement path
	L"Je�li W��CZONE, b�dziesz widzia� tras� ruchu w trybie Real-Time.",

	//show misses
	L"Je�li W��CZONE, b�dzie m�g� obserwowa� w co trafiaj� twoje kule gdy spud�ujesz.",
	
	//Real Time Confirmation
	L"Je�li W��CZONE, ka�dy ruch najemnika w trybie Real-Time b�dzie wymaga� dodatkowego, potwierdzaj�cego klikni�cia.",

	//Sleep/Wake notification
	L"Je�li W��CZONE, wy�wietlana b�dzie informacja, �e najemnik po�o�y� si� spa� lub wsta� i wr�ci� do pracy.",

	//Use the metric system
	L"Je�li W��CZONE, gra b�dzie u�ywa�a systemu metrycznego.",

	//Merc Lighted movement
	L"Je�li W��CZONE, teren wok� najemnika b�dzie o�wietlony podczas ruchu. Mo�e spowolni� dzia�anie gry.",

	//Smart cursor
	L"Je�li W��CZONE, kursor b�dzie automatycznie ustawia� si� na najemnikach gdy znajdzie si� w ich pobli�u.",

	//snap cursor to the door
	L"Je�li W��CZONE, kursor b�dzie automatycznie ustawia� si� na drzwiach gdy znajdzie si� w ich pobli�u.",

	//glow items 
	L"Je�li W��CZONE, przedmioty b�d� pulsowa�. ( |I )",

	//toggle tree tops
	L"Je�li W��CZONE, wy�wietlane b�d� korony drzew. ( |T )",

	//toggle wireframe
	L"Je�li W��CZONE, wy�wietlane b�d� zarysy niewidocznych �cian. ( |W )",

	L"Je�li W��CZONE, kursor ruchu wy�wietlany b�dzie w 3D. ( |Home )",

	// Options for 1.13
	L"Je�li W��CZONE, kursor b�dzie pokazywa� szans� na trafienie.",
	L"Je�li W��CZONE, seria z granatnika b�dzie u�ywa�a kursora serii z broni palnej.",
	L"Je�li W��CZONE, martwi wrogowie b�d� upuszcza� ca�y ekwipunek.",
	L"Je�li W��CZONE, granatniki b�d� strzela�y pod wysokim k�tem. ( |Q )",
	L"Je�li W��CZONE, poziom celowania powy�ej 4 b�dzie dost�pny tylko dla karabin�w i karabin�w snajperskich.",
	L"Je�li W��CZONE, |S|p|a|c|j|a wybiera kolejny oddzia�.",
	L"Je�li W��CZONE, pokazywane b�d� cienie przedmiot�w.",
	L"Je�li W��CZONE, zasi�g broni b�dzie wy�wietlany w polach.",
	L"Je�li W��CZONE, pojedynczy strza� b�dzie z efektem pocisku smugowego",
	L"Je�li W��CZONE, b�dziesz s�ysza� padaj�cy deszcz.",
	L"Je�li W��CZONE, w grze pojawia� si� b�d� wrony.",
	L"When ON, a tooltip window is shown when pressing |A|l|t and hovering cursor over an enemy.", 	// - Changed from random IMP personality - SANDRO
	L"Je�li W��CZONE, gra b�dzie zapisywana ka�dorazowo po zako�czeniu tury gracza.",
	L"Je�li W��CZONE, Skyrider nie b�dzie nic m�wi�.",
	L"Je�li W��CZONE, gra b�dzie obci��a�a procesor w mniejszym stopniu.",
	L"Je�li W��CZONE, rozszerzone opisy b�d� pokazane dla przedmiot�w i broni.",
	L"Je�li W��CZONE i wr�g jest obecny, \ntryb turowy jest w��czony, \ndop�ki sektor nie zostanie oczyszczony (|C|T|R|L+|S|H|I|F|T+|A|L|T+|T).",	// add forced turn mode
	L"When ON, shows character progress towards gaining levels.",	// TODO.Translate
	L"When ON, alternate bullet graphics will be shown when you shoot.", // TODO.Translate
	L"(text not rendered)TOPTION_CHEAT_MODE_OPTIONS_HEADER",
	L"Force all pending Bobby Ray shipments",
	L"(text not rendered)TOPTION_CHEAT_MODE_OPTIONS_END",
	L"(text not rendered)TOPTION_DEBUG_MODE_OPTIONS_HEADER",			// an example options screen options header (pure text)
	L"Click me to fix corrupt game settings",							// failsafe show/hide option to reset all options
	L"Click me to fix corrupt game settings",							// a do once and reset self option (button like effect)
	L"Allows debug options in release or mapeditor builds",				// allow debugging in release or mapeditor
	L"Toggle to display debugging render options",						// an example option that will show/hide other options
	L"Attempts to display slash-rects around mouse regions",			// an example of a DEBUG build option
	L"(text not rendered)TOPTION_DEBUG_MODE_OPTIONS_END",				// an example options screen options divider (pure text)


	// this is THE LAST option that exists (debug the options screen, doesnt do anything, except exist)
	L"TOPTION_LAST_OPTION",
};

STR16	gzGIOScreenText[] =
{
	L"POCZ�TKOWE USTAWIENIA GRY",
	L"Styl gry",
	L"Realistyczny",
	L"S-F",
	L"Platynowy", //Placeholder English
	L"Opcje broni",
	L"Mn�stwo broni",
	L"Standardowe uzbrojenie",
	L"Stopie� trudno�ci",
	L"Nowicjusz",
	L"Do�wiadczony",
	L"Ekspert",
	L"SZALONY",
	L"Ok",
	L"Anuluj",
	L"Rozszerzony poziom trudno�ci",
	L"Zapis gry w dowolnym momencie",
	L"CZ�OWIEK ZE STALI",
	L"Nie dzia�a w wersji demo",
	L"Wyposa�enie Bobby Ray's",
	L"Normalne",
	L"�wietne",
	L"Wy�mienite",
	L"Niewiarygodne",
	L"System Inwentarza",
	L"Tradycyjny",
	L"Rozbudowany",
	L"Load MP Game",
	L"POCZ�TKOWE USTAWIENIA GRY (Only the server settings take effect)",
};

STR16	gzMPJScreenText[] =
{
	L"MULTIPLAYER",
	L"Join",
	L"Host",
	L"Cancel",
	L"Refresh",
	L"Player Name",
	L"Server IP",
	L"Port",
	L"Server Name",
	L"# Plrs",
	L"Version",
	L"Game Type",
	L"Ping",
	L"You must enter a player name",
	L"You must enter a valid server IP address.\n (eg 84.114.195.239).",
	L"You must enter a valid Server Port between 1 and 65535.",
};

STR16	gzMPHScreenText[] =
{
	L"HOST GAME",
	L"Start",
	L"Cancel",
	L"Server Name",
	L"Game Type",
	L"Deathmatch",
	L"Team Deathmatch",
	L"Co-operative",
	L"Max Players",
	L"Squad Size",
	L"Merc Selection",
	L"Random Mercs",
	L"Hired by Player",
	L"Starting Balance",
	L"Can Hire Same Merc",
	L"Report Hired Mercs",
	L"Allow Bobby Rays",
	L"Randomise Starting Edge",
	L"You must enter a server name",
	L"Max Players must be between 2 and 4",
	L"Squad size must be between 1 and 6",
	L"Time of Day",
	L"Time of Day must be a 24 hour time (HH:MM)",
	L"Starting Cash must be a valid dollar amount (no cents)" ,
	L"Damage Multiplier",
	L"Damage Multiplier must be a number between 0 and 5",
	L"Turn Timer Multiplier",
	L"Turn Timer multiplier must be a number between 0 (no timed turns) and 200 (short timed turns)",
	L"Enable Civilians in CO-OP",
	L"Use New Inventory (NIV)",
	L"Sync. MP Clients Directory",
	L"MP Sync. Directory",
	L"You must enter a file transfer directory.",
	L"(Use '/' instead of '\\' for directory delimiters.)",
	L"The specified synchronisation directory does not exist.",
};

STR16 pDeliveryLocationStrings[] =
{
	L"Austin",			//Austin, Texas, USA	
	L"Bagdad",			//Baghdad, Iraq (Suddam Hussein's home)
	L"Drassen",			//The main place in JA2 that you can receive items.  The other towns are dummy names...
	L"Hong Kong",		//Hong Kong, Hong Kong
	L"Bejrut",			//Beirut, Lebanon	(Middle East)
	L"Londyn",			//London, England
	L"Los Angeles",	//Los Angeles, California, USA (SW corner of USA)
	L"Meduna",			//Meduna -- the other airport in JA2 that you can receive items.
	L"Metavira",		//The island of Metavira was the fictional location used by JA1
	L"Miami",				//Miami, Florida, USA (SE corner of USA)
	L"Moskwa",			//Moscow, USSR
	L"Nowy Jork",		//New York, New York, USA
	L"Ottawa",			//Ottawa, Ontario, Canada -- where JA2 was made!
	L"Pary�",				//Paris, France
	L"Trypolis",			//Tripoli, Libya (eastern Mediterranean)
	L"Tokio",				//Tokyo, Japan
	L"Vancouver",		//Vancouver, British Columbia, Canada (west coast near US border)
};

STR16 pSkillAtZeroWarning[] =
{ //This string is used in the IMP character generation.  It is possible to select 0 ability
	//in a skill meaning you can't use it.  This text is confirmation to the player.
	L"Na pewno? Warto�� zero oznacza brak jakichkolwiek umiej�tno�ci w tej dziedzinie.",
};

STR16 pIMPBeginScreenStrings[] =
{
	L"( Maks. 8 znak�w )",
};

STR16 pIMPFinishButtonText[ 1 ]=
{
	L"Analizuj�",
};

STR16 pIMPFinishStrings[ ]=
{
	L"Dzi�kujemy, %s", //%s is the name of the merc
};

// the strings for imp voices screen
STR16 pIMPVoicesStrings[] =
{
	L"G�os", 
};

STR16 pDepartedMercPortraitStrings[ ]=
{
	L"�mier� w akcji",
	L"Zwolnienie",
	L"Inny",
};

// title for program
STR16 pPersTitleText[] =
{
	L"Personel",
};

// paused game strings
STR16 pPausedGameText[] =
{
	L"Gra wstrzymana",
	L"Wzn�w gr� (|P|a|u|s|e)",
	L"Wstrzymaj gr� (|P|a|u|s|e)",
};


STR16 pMessageStrings[] =
{
	L"Zako�czy� gr�?",
	L"OK",
	L"TAK",
	L"NIE",
	L"ANULUJ",
	L"NAJMIJ",
	L"LIE",
	L"Brak opisu", //Save slots that don't have a description.
	L"Gra zapisana.",
	L"Gra zapisana.",
	L"Szybki zapis", //10	The name of the quicksave file (filename, text reference)
	L"SaveGame",	//The name of the normal savegame file, such as SaveGame01, SaveGame02, etc.
	L"sav",				//The 3 character dos extension (represents sav)
	L"..\\SavedGames", //The name of the directory where games are saved.
	L"Dzie�",
	L"Najemn.",
	L"Wolna pozycja", //An empty save game slot
	L"Demo",				//Demo of JA2
	L"Debug",				//State of development of a project (JA2) that is a debug build
	L"",			//Release build for JA2
	L"strz/min",					//20	Abbreviation for Rounds per minute -- the potential # of bullets fired in a minute.
	L"min",					//Abbreviation for minute.
	L"m",						//One character abbreviation for meter (metric distance measurement unit).
	L"kul",				//Abbreviation for rounds (# of bullets)
	L"kg",					//Abbreviation for kilogram (metric weight measurement unit)
	L"lb",					//Abbreviation for pounds (Imperial weight measurement unit)
	L"Strona g��wna",				//Home as in homepage on the internet.
	L"USD",					//Abbreviation to US dollars
	L"N/D",					//Lowercase acronym for not applicable.
	L"Tymczasem",		//Meanwhile
	L"%s przyby�(a) do sektora %s%s", //30	Name/Squad has arrived in sector A9.  Order must not change without notifying
																		//SirTech
	L"Wersja",
	L"Wolna pozycja na szybki zapis",
	L"Ta pozycja zarezerwowana jest na szybkie zapisy wykonywane podczas gry kombinacj� klawiszy ALT+S.",
	L"Otwarte",
	L"Zamkni�te",
	L"Brak miejsca na dysku twardym.  Na dysku wolne jest %s MB, a wymagane jest przynajmniej %s MB.",
	L"Naj�to - %s z A.I.M.", 
	L"%s z�apa�(a) %s",		//'Merc name' has caught 'item' -- let SirTech know if name comes after item.
	L"%s zaaplikowa�(a) sobie lekarstwo", //'Merc name' has taken the drug
	L"%s nie posiada wiedzy medycznej",//40	'Merc name' has no medical skill.

	//CDRom errors (such as ejecting CD while attempting to read the CD)
	L"Integralno�� gry zosta�a nara�ona na szwank.",
	L"B��D: Wyj�to p�yt� CD",

	//When firing heavier weapons in close quarters, you may not have enough room to do so.
	L"Nie ma miejsca, �eby st�d odda� strza�.",
	
	//Can't change stance due to objects in the way...
	L"Nie mo�na zmieni� pozycji w tej chwili.",

	//Simple text indications that appear in the game, when the merc can do one of these things.
	L"Upu��",
	L"Rzu�",
	L"Podaj",

	L"%s przekazano do - %s.", //"Item" passed to "merc".  Please try to keep the item %s before the merc %s, otherwise,
											 //must notify SirTech.
	L"Brak wolnego miejsca, by przekaza� %s do - %s.", //pass "item" to "merc".  Same instructions as above.

	//A list of attachments appear after the items.  Ex:  Kevlar vest ( Ceramic Plate 'Attached )'
	L" do��czono]",			// 50

	//Cheat modes
	L"Pierwszy poziom lamerskich zagrywek osi�gni�ty",
	L"Drugi poziom lamerskich zagrywek osi�gni�ty",

	//Toggling various stealth modes
	L"Oddzia� ma w��czony tryb skradania si�.",
	L"Oddzia� ma wy��czony tryb skradania si�.",
	L"%s ma w��czony tryb skradania si�.",
	L"%s ma wy��czony tryb skradania si�.",

	//Wireframes are shown through buildings to reveal doors and windows that can't otherwise be seen in 
	//an isometric engine.  You can toggle this mode freely in the game.
	L"Dodatkowe siatki w��czone.",
	L"Dodatkowe siatki wy��czone.",

	//These are used in the cheat modes for changing levels in the game.  Going from a basement level to
	//an upper level, etc.  
	L"Nie mo�na wyj�� do g�ry z tego poziomu...",
	L"Nie ma ju� ni�szych poziom�w...",		// 60
	L"Wej�cie na %d poziom pod ziemi�...",
	L"Wyj�cie z podziemii...",

	L"'s",		// used in the shop keeper inteface to mark the ownership of the item eg Red's gun
	L"Automatyczne centrowanie ekranu wy��czone.",
	L"Automatyczne centrowanie ekranu w��czone.",
	L"Kursor 3D wy��czony.",
	L"Kursor 3D w��czony.",
	L"Oddzia� %d aktywny.",
	L"%s - Nie sta� ci� by wyp�aci� jej/jemu dzienn� pensj� w wysoko�ci %s.",	//first %s is the mercs name, the seconds is a string containing the salary
	L"Pomi�",				// 70
	L"%s nie mo�e odej�� sam(a).",
	L"Utworzono zapis gry o nazwie SaveGame99.sav. W razie potrzeby zmie� jego nazw� na SaveGame01..10. Wtedy b�dzie mo�na go odczyta� ze standardowego okna odczytu gry.",
	L"%s wypi�(a) troch� - %s",
	L"Przesy�ka dotar�a do Drassen.",
 	L"%s przyb�dzie do wyznaczonego punktu zrzutu (sektor %s) w dniu %d, oko�o godziny %s.",		//first %s is mercs name, next is the sector location and name where they will be arriving in, lastely is the day an the time of arrival	
	L"Lista historii zaktualizowana.",
	L"Seria z granatnika u�ywa kursora celowania (dost�pny ogie� rozproszony)",		//L"Grenade Bursts use Targeting Cursor (Spread fire enabled)", BY�O -->>L"Grenade Bursts - Using Targeting Cursor (Spread fire enabled)",
	L"Seria z granatnika u�ywa kursora trajektorii (dost�pny ogie� rozproszony)",		//L"Grenade Bursts use Trajectory Cursor (Spread fire disabled)", BY�O -->L"Grenade Bursts - Using Trajectory Cursor (Spread fire disabled)",
	L"Upuszczanie wszystkiego w��czone",
	L"Upuszczanie wszystkiego wy��czone",
	L"Granatniki strzelaj� pod standardowymi k�tami",					//L"Grenade Launchers fire at standard angles", BY�o->>L"Grenade Launchers - Fire at standard angles",
	L"Granatniki strzelaj� pod wysokimi k�tami",						//L"Grenade Launchers fire at higher angles", BY�o-->>L"Grenade Launchers - Fire at high angles",
	// forced turn mode strings
    L"Forced Turn Mode",
	L"Normal turn mode",
	L"Exit combat mode",
	L"Forced Turn Mode Active, Entering Combat",
#ifdef JA2BETAVERSION
	L"Automatyczny zapis zosta� pomy�lnie wykonany.",
#endif
	L"..\\SavedGames\\MP_SavedGames", //The name of the directory where games are saved.
	L"Client",

	// TODO.Translate
	L"You cannot use the Old Inventory and the New Attachment System at the same time.",
};


CHAR16 ItemPickupHelpPopup[][40] =
{
	L"OK",
	L"W g�r�",
	L"Wybierz wszystko",
	L"W d�",
	L"Anuluj",
};

STR16 pDoctorWarningString[] =
{
	L"%s jest za daleko, aby podda� si� leczeniu.",
	L"Lekarze nie mogli opatrzy� wszystkich rannych.",
};

STR16 pMilitiaButtonsHelpText[] =
{
	L"Podnie�(Prawy klawisz myszy)/upu��(Lewy klawisz myszy) Zielonych �o�nierzy", // button help text informing player they can pick up or drop militia with this button
	L"Podnie�(Prawy klawisz myszy)/upu��(Lewy klawisz myszy) Do�wiadczonych �o�nierzy",
	L"Podnie�(Prawy klawisz myszy)/upu��(Lewy klawisz myszy) Weteran�w",
	L"Umieszcza jednakow� ilo�� �o�nierzy samoobrony w ka�dym sektorze.",
};

STR16 pMapScreenJustStartedHelpText[] =
{
	L"Zajrzyj do A.I.M. i zatrudnij kilku najemnik�w (*Wskaz�wka* musisz otworzy� laptopa)", // to inform the player to hired some mercs to get things going
	L"Je�li chcesz ju� uda� si� do Tracona, kliknij przycisk kompresji czasu, w prawym dolnym rogu ekranu.", // to inform the player to hit time compression to get the game underway
};

STR16 pAntiHackerString[] = 
{
	L"B��d. Brakuje pliku, lub jest on uszkodzony. Gra zostanie przerwana.",
};


STR16 gzLaptopHelpText[] =
{
	//Buttons:
	L"Przegl�danie poczty",
	L"Przegl�danie stron internetowych",
	L"Przegl�danie plik�w i za��cznik�w pocztowych",
	L"Rejestr zdarze�",
	L"Informacje o cz�onkach oddzia�u",
	L"Finanse i rejestr transakcji",
	L"Koniec pracy z laptopem",

	//Bottom task bar icons (if they exist):
	L"Masz now� poczt�",
	L"Masz nowe pliki",

	//Bookmarks:
	L"Mi�dzynarodowe Stowarzyszenie Najemnik�w",
	L"Bobby Ray's - Internetowy sklep z broni�",
	L"Instytut Bada� Najemnik�w",
	L"Bardziej Ekonomiczne Centrum Rekrutacyjne",
	L"McGillicutty's - Zak�ad pogrzebowy",
	L"United Floral Service",
	L"Brokerzy ubezpieczeniowi",
};


STR16	gzHelpScreenText[] =
{
	L"Zamknij okno pomocy",	
};

STR16 gzNonPersistantPBIText[] =
{
	L"Trwa walka. Najemnik�w mo�na wycofa� tylko na ekranie taktycznym.",
	L"W|ejd� do sektora, aby kontynuowa� walk�.",
	L"|Automatycznie rozstrzyga walk�.",
	L"Nie mo�na automatycznie rozstrzygn�� walki, gdy atakujesz.",
	L"Nie mo�na automatycznie rozstrzygn�� walki, gdy wpadasz w pu�apk�.",
	L"Nie mo�na automatycznie rozstrzygn�� walki, gdy walczysz ze stworzeniami w kopalni.",
	L"Nie mo�na automatycznie rozstrzygn�� walki, gdy w sektorze s� wrodzy cywile.",
	L"Nie mo�na automatycznie rozstrzygn�� walki, gdy w sektorze s� dzikie koty.",
	L"TRWA WALKA",
	L"W tym momencie nie mo�esz si� wycofa�.",
};

STR16 gzMiscString[] =
{
	L"�o�nierze samoobrony kontynuuj� walk� bez pomocy twoich najemnik�w...",
	L"W tym momencie tankowanie nie jest konieczne.",
	L"W baku jest %d%% paliwa.",
	L"�o�nierze Deidranny przej�li ca�kowit� kontrol� nad - %s.",
	L"Nie masz ju� gdzie zatankowa�.",
};

STR16	gzIntroScreen[] = 
{
	L"Nie odnaleziono filmu wprowadzaj�cego",
};

// These strings are combined with a merc name, a volume string (from pNoiseVolStr),
// and a direction (either "above", "below", or a string from pDirectionStr) to 
// report a noise.
// e.g. "Sidney hears a loud sound of MOVEMENT coming from the SOUTH."
STR16 pNewNoiseStr[] =
{
	L"%s s�yszy %s D�WI�K dochodz�cy z %s.",
	L"%s s�yszy %s ODG�OS RUCHU dochodz�cy z %s.",
	L"%s s�yszy %s ODG�OS SKRZYPNI�CIA dochodz�cy z %s.",
	L"%s s�yszy %s PLUSK dochodz�cy z %s.",
	L"%s s�yszy %s ODG�OS UDERZENIA dochodz�cy z %s.",
	L"%s s�yszy %s WYBUCH dochodz�cy z %s.",
	L"%s s�yszy %s KRZYK dochodz�cy z %s.",
	L"%s s�yszy %s ODG�OS UDERZENIA dochodz�cy z %s.",
	L"%s s�yszy %s ODG�OS UDERZENIA dochodz�cy z %s.",
	L"%s s�yszy %s �OMOT dochodz�cy z %s.",
	L"%s s�yszy %s TRZASK dochodz�cy z %s.",
};

STR16 wMapScreenSortButtonHelpText[] =
{
	L"Sortuj wed�ug kolumny Imi� (|F|1)",
	L"Sortuj wed�ug kolumny Przydzia� (|F|2)",
	L"Sortuj wed�ug kolumny Sen (|F|3)",
	L"Sortuj wed�ug kolumny Lokalizacja (|F|4)",
	L"Sortuj wed�ug kolumny Cel podr�y (|F|5)",
	L"Sortuj wed�ug kolumny Wyjazd (|F|6)",
};



STR16		BrokenLinkText[] = 
{
	L"B��d 404",
	L"Nie odnaleziono strony.",
};


STR16 gzBobbyRShipmentText[] = 
{
	L"Ostatnie dostawy",
	L"Zam�wienie nr ",
	L"Ilo�� przedmiot�w",
	L"Zam�wiono:",
};


STR16	gzCreditNames[]=
{
	L"Chris Camfield",
	L"Shaun Lyng",
	L"Kris M�rnes",
	L"Ian Currie",
	L"Linda Currie",
	L"Eric \"WTF\" Cheng",
	L"Lynn Holowka",
	L"Norman \"NRG\" Olsen",
	L"George Brooks",
	L"Andrew Stacey",
	L"Scot Loving",
	L"Andrew \"Big Cheese\" Emmons",
	L"Dave \"The Feral\" French",
	L"Alex Meduna",
	L"Joey \"Joeker\" Whelan",
};


STR16	gzCreditNameTitle[]=
{
	L"Game Internals Programmer", 			// Chris Camfield
	L"Co-designer/Writer",							// Shaun Lyng
	L"Strategic Systems & Editor Programmer",					//Kris \"The Cow Rape Man\" Marnes
	L"Producer/Co-designer",						// Ian Currie
	L"Co-designer/Map Designer",				// Linda Currie
	L"Artist",													// Eric \"WTF\" Cheng
	L"Beta Coordinator, Support",				// Lynn Holowka
	L"Artist Extraordinaire",						// Norman \"NRG\" Olsen
	L"Sound Guru",											// George Brooks
	L"Screen Designer/Artist",					// Andrew Stacey
	L"Lead Artist/Animator",						// Scot Loving
	L"Lead Programmer",									// Andrew \"Big Cheese Doddle\" Emmons
	L"Programmer",											// Dave French
	L"Strategic Systems & Game Balance Programmer",					// Alex Meduna
	L"Portraits Artist",								// Joey \"Joeker\" Whelan",
};

STR16	gzCreditNameFunny[]=
{
	L"", 																			// Chris Camfield
	L"(wci�� uczy si� interpunkcji)",					// Shaun Lyng
	L"(\"Sko�czone, tylko to posk�adam\")",	//Kris \"The Cow Rape Man\" Marnes
	L"(robi� si� na to za stary)",				// Ian Currie
	L"(i pracuje nad Wizardry 8)",						// Linda Currie
	L"(zmuszony pod broni� do ko�cowych test�w jako�ci produktu)",			// Eric \"WTF\" Cheng
	L"(Opu�ci� nas dla Stowarzyszenia na Rzecz Rozs�dnych Wynagrodze�. Ciekawe czemu... )",	// Lynn Holowka
	L"",																			// Norman \"NRG\" Olsen
	L"",																			// George Brooks
	L"(mi�o�nik zespo�u Dead Head i jazzu)",						// Andrew Stacey
	L"(tak naprawd� na imi� ma Robert)",							// Scot Loving
	L"(jedyna odpowiedzialna osoba)",					// Andrew \"Big Cheese Doddle\" Emmons
	L"(teraz mo�e wr�ci� do motocrossu)",	// Dave French
	L"(ukradziony z projektu Wizardry 8)",							// Alex Meduna
	L"(zrobi� przedmioty i ekrany wczytywania!!)",	// Joey \"Joeker\" Whelan",
};

STR16 sRepairsDoneString[] =
{
	L"%s sko�czy�(a) naprawia� w�asne wyposa�enie",
	L"%s sko�czy�(a) naprawia� bro� i ochraniacze wszystkich cz�onk�w oddzia�u",
	L"%s sko�czy�(a) naprawia� wyposa�enie wszystkich cz�onk�w oddzia�u",
	L"%s finished repairing everyone's large carried items",
	L"%s finished repairing everyone's medium carried items",
	L"%s finished repairing everyone's small carried items",
	L"%s finished repairing everyone's LBE gear",
};

STR16 zGioDifConfirmText[]=
{
	L"Wybrano opcj� NOWICJUSZ. Opcja ta jest przeznaczona dla niedo�wiadczonych graczy, lub dla tych, kt�rzy nie maj� ochoty na d�ugie i ci�kie walki. Pami�taj, �e opcja ta ma wp�yw na przebieg ca�ej gry. Czy na pewno chcesz gra� w trybie Nowicjusz?",
	L"Wybrano opcj� DO�WIADCZONY. Opcja ta jest przenaczona dla graczy posiadaj�cych ju� pewne do�wiadczenie w grach tego typu. Pami�taj, �e opcja ta ma wp�yw na przebieg ca�ej gry. Czy na pewno chcesz gra� w trybie Do�wiadczony?",
	L"Wybrano opcj� EKSPERT. Jakby co, to ostrzegali�my ci�. Nie obwiniaj nas, je�li wr�cisz w plastikowym worku. Pami�taj, �e opcja ta ma wp�yw na przebieg ca�ej gry. Czy na pewno chcesz gra� w trybie Ekspert?",
	L"Wybrano opcj� SZALONY. OSTRZE�ENIE: Nie obwiniaj nas, je�li wr�cisz w malutkich kawa�eczkach... Deidranna NAPRAWD� skopie ci ty�ek. Mocno. Pami�taj, �e opcja ta ma wp�yw na przebieg ca�ej gry. Czy na pewno chcesz gra� w trybie SZALONY?",
};

STR16 gzLateLocalizedString[] =
{
	L"%S - nie odnaleziono pliku...",

	//1-5
	L"Robot nie mo�e opu�ci� sektora bez operatora.",

	//This message comes up if you have pending bombs waiting to explode in tactical.
	L"Nie mo�na teraz kompresowa� czasu.  Poczekaj na fajerwerki!",  

	//'Name' refuses to move.
	L"%s nie chce si� przesun��.",

	//%s a merc name
	L"%s ma zbyt ma�o energii, aby zmieni� pozycj�.",

	//A message that pops up when a vehicle runs out of gas.
	L"%s nie ma paliwa i stoi w sektorze %c%d.",

	//6-10

	// the following two strings are combined with the pNewNoise[] strings above to report noises
	// heard above or below the merc
	L"G�RY",
	L"DO�U",

	//The following strings are used in autoresolve for autobandaging related feedback.
	L"�aden z twoich najemnik�w nie posiada wiedzy medycznej.",
	L"Brak �rodk�w medycznych, aby za�o�y� rannym opatrunki.",
	L"Zabrak�o �rodk�w medycznych, aby za�o�y� wszystkim rannym opatrunki.",
	L"�aden z twoich najemnik�w nie potrzebuje pomocy medycznej.",
	L"Automatyczne zak�adanie opatrunk�w rannym najemnikom.",
	L"Wszystkim twoim najemnikom za�o�ono opatrunki.",

	//14
	L"Tracona",

  L"(dach)",

	L"Zdrowie: %d/%d",

	//In autoresolve if there were 5 mercs fighting 8 enemies the text would be "5 vs. 8"
	//"vs." is the abbreviation of versus.
	L"%d vs. %d",
	
	L"%s - brak wolnych miejsc!",  //(ex "The ice cream truck is full")

  L"%s nie potrzebuje pierwszej pomocy lecz opieki lekarza lub d�u�szego odpoczynku.",

	//20
	//Happens when you get shot in the legs, and you fall down.
	L"%s dosta�(a) w nogi i upad�(a)!",
	//Name can't speak right now.
	L"%s nie mo�e teraz m�wi�.",

	//22-24 plural versions 
	L"%d zielonych �o�nierzy samoobrony awansowa�o na weteran�w.",
	L"%d zielonych �o�nierzy samoobrony awansowa�o na regularnych �o�nierzy.",
	L"%d regularnych �o�nierzy samoobrony awansowa�o na weteran�w.",

	//25
	L"Prze��cznik",

	//26
	//Name has gone psycho -- when the game forces the player into burstmode (certain unstable characters)
	L"%s dostaje �wira!",

	//27-28
	//Messages why a player can't time compress.
	L"Niebezpiecznie jest kompresowa� teraz czas, gdy� masz najemnik�w w sektorze %s.",
	L"Niebezpiecznie jest kompresowa� teraz czas, gdy� masz najemnik�w w kopalni zaatakowanej przez robale.",

	//29-31 singular versions 
	L"1 zielony �o�nierz samoobrony awansowa� na weterana.",
	L"1 zielony �o�nierz samoobrony awansowa� na regularnego �o�nierza.",
	L"1 regularny �o�nierz samoobrony awansowa� na weterana.",

	//32-34
	L"%s nic nie m�wi.",
	L"Wyj�� na powierzchni�?",
	L"(Oddzia� %d)",

	//35
	//Ex: "Red has repaired Scope's MP5K".  Careful to maintain the proper order (Red before Scope, Scope before MP5K)
	L"%s naprawi�(a) najemnikowi - %s, jego/jej - %s",

	//36
	L"DZIKI KOT",

	//37-38 "Name trips and falls"
	L"%s potyka si� i upada",
	L"Nie mo�na st�d podnie�� tego przedmiotu.",

	//39
	L"�aden z twoich najemnik�w nie jest w stanie walczy�.  �o�nierze samoobrony sami b�d� walczy� z robalami.",

	//40-43
	//%s is the name of merc.
	L"%s nie ma �rodk�w medycznych!",
	L"%s nie posiada odpowiedniej wiedzy, aby kogokolwiek wyleczy�!",
	L"%s nie ma narz�dzi!",
	L"%s nie posiada odpowiedniej wiedzy, aby cokolwiek naprawi�!",

	//44-45
	L"Czas naprawy",
	L"%s nie widzi tej osoby.",

	//46-48
	L"%s - przed�u�ka lufy jego/jej broni odpada!",
	L"No more than %d militia trainers are permitted in this sector.",		// TODO.Translate
  	L"Na pewno?",

	//49-50
	L"Kompresja czasu",
	L"Pojazd ma pe�ny zbiornik paliwa.",

	//51-52 Fast help text in mapscreen.
	L"Kontynuuj kompresj� czasu (|S|p|a|c|j|a)",
	L"Zatrzymaj kompresj� czasu (|E|s|c)",

	//53-54 "Magic has unjammed the Glock 18" or "Magic has unjammed Raven's H&K G11" 
	L"%s odblokowa�(a) - %s",
	L"%s odblokowa�(a) najemnikowi - %s, jego/jej - %s",

	//55 
	L"Nie mo�na kompresowa� czasu, gdy otwarty jest inwentarz sektora.",

	L"Nie odnaleziono p�yty nr 2 Jagged Alliance 2.",

	L"Przedmioty zosta�y pomy�lnie po��czone.",
	
	//58
	//Displayed with the version information when cheats are enabled.
	L"Bie��cy/Maks. post�p: %d%%/%d%%",

	L"Eskortowa� Johna i Mary?",
	
	// 60
	L"Prze��cznik aktywowany.",

	L"%s: dodatki do pancerza zosta�y zniszczone!",
	L"%s wystrzeli�(a) %d pocisk(�w) wi�cej ni� to by�o zamierzone!",
	L"%s wystrzeli�(a) %d pocisk(�w) wi�cej ni� to by�o zamierzone!",
};

STR16 gzCWStrings[] = 
{
	L"Call reinforcements to %s from adjacent sectors?",		// TODO.Translate
};

// WANNE: Tooltips
STR16 gzTooltipStrings[] =
{
	// Debug info
	L"%s|Miejsce: %d\n",
	L"%s|Jasno��: %d / %d\n",
	L"%s|Odleg�o�� do |Celu: %d\n",
	L"%s|I|D: %d\n",
	L"%s|Rozkazy: %d\n",
	L"%s|Postawa: %d\n",
	L"%s|Aktualne |P|A: %d\n",
	L"%s|Aktualne |Zdrowie: %d\n",
	// Full info
	L"%s|He�m: %s\n",
	L"%s|Kamizelka: %s\n",
	L"%s|Getry ochronne: %s\n",
	// Limited, Basic
	L"|Pancerz: ",
	L"he�m ",
	L"kamizelka ",
	L"getry ochronne",
	L"u�ywane",
	L"brak pancerza",
	L"%s|N|V|G: %s\n",
	L"brak NVG",
	L"%s|Maska |Gazowa: %s\n",
	L"brak maski gazowej",
	L"%s|Pozycja |G�owy |1: %s\n",
	L"%s|Pozycja |G��w |2: %s\n",
	L"\n(w plecaku) ",
	L"%s|Bro�: %s ",
	L"brak broni",
	L"rewolwer",
	L"SMG",
	L"karabin",
	L"MG",
	L"strzelba",
	L"n�",
	L"bro� Ci�ka",
	L"brak he�mu",
	L"brak kamizelki",
	L"brak getr�w ochronnych",
	L"|Pancerz: %s\n", 
};

STR16 New113Message[] =
{
	L"Nadesz�a burza.",
	L"Burza sko�czy�a si�.",
	L"Rozpada� si� deszcz.",
	L"Deszcz przesta� pada�.",
	L"Uwa�aj na snajper�w...",
	L"Ogie� d�awi�cy!",	
	L"BRST",
	L"AUTO",
	L"GL",
	L"GL BRST",
	L"GL AUTO",
	L"Snajper!",
	L"Nie mo�na podzieli� pieni�dzy z powodu przedmiotu na kursorze.",
	L"Przybycie nowych rekrut�w zosta�o przekierowane do sektora %s , z uwagi na to, �e poprzedni punkt zrzutu w sektorze %s jest zaj�ty przez wroga.",
	L"Przedmiot usuni�ty",
	L"Usuni�to wszystkie przedmioty tego typu",
	L"Przedmiot sprzedany",
	L"Wszystkie przedmioty tego typu sprzedane",
	L"Sprawd� swoje gogle",
	// Real Time Mode messages
	L"In combat already",
	L"No enemies in sight",
	L"Real-time sneaking OFF",
	L"Real-time sneaking ON",
	L"Enemy spotted! (Ctrl + x to enter turn based)",
};

// TODO.Translate
STR16 New113HAMMessage[] = 
{
	// 0 - 5
	L"%s cowers in fear!",
	L"%s is pinned down!",
	L"%s fires more rounds than intended!",
	L"You cannot train militia in this sector.",
	L"Militia picks up %s.",
	L"Cannot train militia with enemies present!", 
	// 6 - 10
	L"%s lacks sufficient Leadership score to train militia.",
	L"No more than %d Mobile Militia trainers are permitted in this sector.",
	L"No room in %s or around it for new Mobile Militia!",
	L"You need to have %d Town Militia in each of %s's liberated sectors before you can train Mobile Militia here.",
	L"Can't staff a facility while enemies are present!",
	// 11 - 15
	L"%s lacks sufficient Wisdom to staff this facility.",
	L"The %s is already fully-staffed.",
	L"It will cost $%d per hour to staff this facility. Do you wish to continue?",
	L"You have insufficient funds to pay for all Facility work today. $%d have been paid, but you still owe $%d. The locals are not pleased.",
	L"You have insufficient funds to pay for all Facility work today. You owe $%d. The locals are not pleased.",
	// 16 - 20
	L"You have an outstanding debt of $%d for Facility Operation, and no money to pay it off!",
	L"You have an outstanding debt of $%d for Facility Operation. You can't assign this merc to facility duty until you have enough money to pay off the entire debt.",
	L"You have an outstanding debt of $%d for Facility Operation. Would you like to pay it all back?",
	L"N/A in this sector",
	L"Daily Expenses",
	// 21 - 25
	L"Insufficient funds to pay all enlisted militia! %d militia have disbanded and returned home.",
};

// WANNE: This are the email texts, when one of the 4 new 1.13 MERC mercs have levelled up, that Speck sends
// INFO: Do not replace the � characters. They indicate the <B2> (-> Newline) from the edt files
STR16	New113MERCMercMailTexts[] =
{
	// Gaston: Text from Line 39 in Email.edt
	L"Niniejszym informuj�, i� w zwi�zku z dotychczasowymi osi�gni�ciami Gastona, op�ata za jego us�ugi zosta�a podniesiona. Osobi�cie, nie jestem tymfaktem zaskoczony.  � � Speck T. Kline � ",
	// Stogie: Text from Line 43 in Email.edt
	L"Informujemy, i� od chwili obecnej cena za us�ugi �wiadczone przez pana Stoggiego wzros�a w zwi�zku ze wzrostem jego umiej�tno�ci. � � Speck T. Kline � ", 
	// Tex: Text from Line 45 in Email.edt
	L"Informujemy, i� nabyte przez Texa do�wiadczenie upowa�nia go do wy�szego wynagrodzenia, z tego wzgl�du jego wynagrodzenie zosta�o zwi�kszone w celu lepszego odzwierciedlenia jego warto�ci. � � Speck T. Kline � ",
	// Biggens: Text from Line 49 in Email.edt
	L"Prosz� o zwr�cenie uwagi, i� w zwi�zku ze wzrostem jako�ci us�ug �wiadczonych przez pana Biggens`a jego pensja tak�e uleg�a podwy�szeniu. � � Speck T. Kline � ",
};

// WANNE: These are the missing skills from the impass.edt file
// INFO: Do not replace the � characters. They indicate the <B2> (-> Newline) from the edt files
STR16 MissingIMPSkillsDescriptions[] =
{
	// Sniper
	L"Snajper: Sokole oczy! Mo�esz odstrzeli� skrzyd�a muszce ze stu jard�w. � ",
	// Camouflage
	L"Kamufla�: Przy tobie nawet krzaki wygl�daj� na sztuczne! � ",	
};

STR16 NewInvMessage[] = 
{
	L"Nie mo�esz teraz podnie�� plecaka.",
	L"Nie ma miejsca, aby po�o�y� tutaj plecak",
	L"Nie znaleziono plecaka",
	L"Zamek b�yskawiczny dzia�a tylko podczas walki.",
	L"Nie mo�esz si� przemieszcza�, gdy zamek plecaka jest aktywny.",
	L"Na pewno chcesz sprzeda� wszystkie przedmioty z tego sektora?",
	L"Na pewno chcesz skasowa� wszystkie przedmioty z tego sektora?",
	L"Nie mo�na wspina� si� z plecakiem",
};

// WANNE - MP: Multiplayer messages
STR16 MPServerMessage[] =
{
	// 0
	L"Inicjacja serwera RakNet...",
	L"Serwer w�., oczekiwanie na po��czenie",
	L"Musisz teraz po��czy� swojego klienta z serwerem, wciskaj�c 2",
	L"Serwer ju� dzia�a",
	L"W�. nie powiod�o si�. Przerwanie.",
	// 5
	L"%d/%d klient�w gotowych na tryb realtime.",
	L"Serwer roz��czony i wy�.",
	L"Serwer nie dzia�a",
	L"�adowanie klient�w, czekaj.",
	L"Nie mo�na zmienia� miejsc zrzutu po starcie serwera.",
	// 10
	L"Sent file '%S' - 100/100",
	L"Finished sending files to '%S'.",
	L"Started sending files to '%S'.",
};

STR16 MPClientMessage[] =
{
	// 0
	L"Inicjacja klienta RakNet�",		
	L"��czenie z IP: %S ...",
	L"Otrzymano ustawienia:",
	L"Jeste� ju� po��czony.",
	L"Jeste� ju� w trakcie ��czenia",
	// 5
	L"Klient #%d - '%S' wynaj�� '%s'.",
	L"Klient #%d - '%S' has hired another merc.",
	L"Gotowy! Wszystkich gotowych - %d/%d.",
	L"Nie jeste� ju� gotowy. Gotowych - %d/%d.",
	L"Pocz�tek bitwy...",
	// 10
	L"Klient #%d - '%S' jest got�w. Gotowych - %d/%d.",
	L"Klient #%d - '%S' nie jest ju� gotowy. Gotowych - %d/%d",
	L"Jeste� got�w. Czekanie na pozosta�ych� Naci�nij OK., je�li ju� nie jeste� got�w.",
	L"Zaczynajmy ju�!",
	L"Klient A musi dzia�a�, by zacz�� gr�.",
	// 15
	L"Nie mo�na zacz��. Brak najemnik�w.",
	L"Czekaj na zgod� serwera, by odblokowa� laptopa�",
	L"Przerwano",
	L"Koniec przerwania",
	L"Po�o�enie siatki myszy:",
	// 20
	L"X: %d, Y: %d",
	L"Numer siatki %d",
	L"W�a�ciwo�ci serwera",
	L"Ustaw r�cznie stopie� nadrz�dno�ci serwera: �1� � w�.laptop/rekrut.; �2�- w�./�aduj poziom; �3� � odblok. UI; �4� � ko�czy rozmieszczanie",
	//L"Sektor=%s, MaxKlient�w=%d, Max Najem=%d, Tryb_Gry=%d, TenSamNaj=%d, Mno�nik obra�.=%f, Wrog�w=%d, Stworze�=%d, Milicji=%d, Cywili=%d, TuryCzasowe=%d, Sek/ruch=%d,  Kasa na start=$%d, Kupa broni=%d, Sci-Fi=%d, Trudno��=%d, Iron-Man=%d, Zas�b BobbyRays=%d, Wy� BobbyRay=%d, Wy� ekwip Aim/Merc=%d, Wy� morale=%d, Test=%d",
	L"Sektor=%s, MaxKlient�w=%d, Max Najem=%d, Tryb_Gry=%d, TenSamNaj=%d, Mno�nik obra�.=%f, TuryCzas=%d, Sek/ruch=%d, Dis BobbyRay=%d, Wy� Aim/Merc Ekwip=%d, Wy� morale=%d, Test=%d",
	// 25
	L"Test, funkcja cheat��w '9' jest w��czona.",
	L"Nowe po��czenie Client #%d - '%S'.",
	L"Team: %d.",//not used any more
	L"'%s' (klient %d - '%S') zabity przez '%s' (client %d - '%S')",
	L"Wyrzucono #%d - '%S'",
	// 30
	L"Zacz�� tur� dla klient�w nr: #1 - '%S' | #2 - '%S' | #3 - '%S' | #4 - '%S'",
	L"Pocz�tek tury dla #%d",
	L"��danie trybu realtime�",
	L"Zmieniono w tryb realtime.",
	L"B��d. Co� posz�o nie tak przy prze��czaniu.",
	// 35
	L"Odblokowa� laptopy? (Czy gracze s� ju� pod��czeni?)",
	L"Serwer odblokowa� laptopa. Zaczynaj rekrutowa�!",
	L"Przerywaj�cy",
	L"Nie mo�esz zmienia� strefy zrzutu, je�li nie  jeste� serwerem gry.",
	L"Odrzuci�e� ofert� poddania si�, gdy� grasz w trybie Multiplayer.",
	// 40
	L"Wszyscy twoi ludzie s� martwi!",
	L"Tryb obserwatora w�..",
	L"Zosta�e� pokonany!",
	L"Wspinanie wy��czone w MP",
	L"Wynaj�to '%s'",
	// 45
	L"You cant change the map once purchasing has commenced",
	L"Map changed to '%s'",
	L"Client '%s' disconnected, removing from game",
	L"You were disconnected from the game, returning to the Main Menu",
	L"Connection failed, Retrying in 5 seconds, %i retries left...",
	//50
	L"Connection failed, giving up...",
	L"You cannot start the game until another player has connected",
	L"%s : %s",
	L"Send to All",
	L"Allies only",
	// 55
	L"Cannot join game. This game has already started.",
	L"%s (team): %s",
	L"#%i - '%s'",
	L"%S - 100/100",
	L"%S - %i/100",
	// 60
	L"Received all files from server.",
	L"'%S' finished downloading from server.",
	L"'%S' started downloading from server.",
	L"Cannot start the game until all clients have finished receiving files",
	L"This server requires that you download modified files to play, do you wish to continue?",
	// 65
	L"Press 'Ready' to enter tactical screen.",
	L"Cannot connect because your version %S is different from the server version %S.",
	L"You killed an enemy soldier.",
	L"Cannot start the game, because all teams are the same.",
};

STR16 MPHelp[] =
{
	// 0
	L"Witaj w  JAGGED ALLIANCE 2 v1.13 Multiplayer",
	L"F1 - pomoc ",
	L"Przyciski mutliplayera (ekran strategii)",
	L"* Ustaw ja2_mp.ini *",
	L"'1' - W�. serwer", 
	// 5
	L"'2' - Po��cz z serwerem",
	L"'3' - Gdy serwer odblokuje laptopa, ustaw got�w do bitwy",
	L"'4' - Opu�� serwera i klient",
	L"'5' - Poka� po�o�enie myszy (ekr. taktyczny)",
	L"'7' - Pop-up dla komunikat�w serwera",
	// 10
	L"'F2' - Wy�wietl 2. pomoc",
	L"Czytaj readme_mp.html po wi�cej info.",
	L"Tip: (gdy ja2_mp.ini jest ustawione)",
	L"* Upewnij si� �e wszyscy maj� r�ne CLIENT_NUM *",
	L"* Gra nie zapisuje porz�dku w Bobby ray�s *",
	// 15
	L"* Nie ustawiaj przeciwnik�w w zasi�gu ich wzroku *",
	L"'F1' - Wy�wietl 1. pomoc",
};

STR16 gszMPEdgesText[] =
{
	L"N",
	L"S",
	L"E",
	L"W",
	L"C",	// "C"enter
};

STR16 gszMPTeamNames[] =
{
	L"Foxtrot",
	L"Bravo",
	L"Delta",
	L"Charlie",
	L"N/D",		// Acronym of Not Applicable
};

STR16 gszMPMapscreenText[] =
{
	L"Game Type: ",
	L"Players: ",
	L"Mercs each: ",
	L"You cannot change starting edge once Laptop is unlocked.",
	L"You cannot change teams once the Laptop is unlocked.",
	L"Random Mercs: ",
	L"Y",
	L"Difficulty:",
	L"Server Version:",
};

STR16 gzMPSScreenText[] =
{
	L"Scoreboard",
	L"Continue",
	L"Cancel",
	L"Player",
	L"Kills",
	L"Deaths",
	L"Queen's Army",
	L"Hits",
	L"Misses",
	L"Accuracy",
	L"Damage Dealt",
	L"Damage Taken",
	L"Please wait for the server to press 'Continue'."
};

STR16 gzMPCScreenText[] =
{
	L"Cancel",
	L"Connecting to Server",
	L"Getting Server Settings",
	L"Downloading custom files",
	L"Press 'ESC' to cancel or 'Y' to chat",
	L"Press 'ESC' to cancel",
	L"Ready"
};

STR16 gzMPChatToggleText[] =
{
	L"Send to All",
	L"Send to Allies only",
};

STR16 gzMPChatboxText[] =
{
	L"Multiplayer Chat",
	L"Chat: Press 'ENTER' to send of 'ESC' to cancel.",
};

// Following strings added - SANDRO
STR16 pSkillTraitBeginIMPStrings[] =
{
	L"On the next page, you are going to choose your skill traits according to your proffessional specialization as a mercenary. No more than two different traits or one expert trait can be selected. To achieve an expert level on a trait, simply choose only that one trait.",
	L"You can also choose only one or even no traits, which will give you a bonus to your attribute points as a compensation. Note that Electronics and Ambidextrous traits cannot be achieved at expert levels, and if you choose one of them only, you will have only one skill trait.",
};

STR16 sgAttributeSelectionText[] = 
{
	L"Please adjust your physical attributes as comapred to that of an avarage merc. You cannot raise any score above",
	L"I.M.P. Attributes and skills review.",
	L"Bonus Pts.:",
	L"Starting Level",
};

STR16 pCharacterTraitBeginIMPStrings[] =
{
	L"I.M.P. Character Analysis",
	L"The analysis of your character is the next step on your profile creation. On the first page you will be shown a list of attitudes to choose. We imagine you could identify yourself with more of them, but here you will be able to pick only one. Choose the one which you feel aligned with mostly. ",
	L"The second page enlists possible disabilities you might have. If you suffer from any of these disabilities, choose which one (we believe that everyone has only one such disablement). Be honest, as it is important to inform potential employers of your true condition.",
};

STR16 gzIMPCharacterTraitText[]=
{
	L"Normal",
	L"Friendly",
	L"Loner",
	L"Optimist",
	L"Pessimist",
	L"Aggressive",
	L"Arrogant",
	L"Big Shot",
	L"Asshole",
	L"Coward",
	L"I.M.P. Character Traits",
};

STR16 gzIMPColorChoosingText[] = 
{
	L"I.M.P. Colors and Body Type",
	L"I.M.P. Colors",
	L"Please select the respective colors of your skin, hair and clothing. And select what body type you have.",
	L"Please select the respective colors of your skin, hair and clothing.",
	L"Toggle this to use alternative rifle holding.",
};

STR16 sColorChoiceExplanationTexts[]=
{
	L"Hair Color",
	L"Skin Color",
	L"Shirt Color",
	L"Pants Color",
	L"Normal Body",
	L"Big Body",
};

STR16 gzIMPDisabilityTraitText[]=
{
	L"No Disability",
	L"Heat Intolerant",
	L"Nervous",
	L"Claustrophobic",
	L"Nonswimmer",
	L"Fear of Insects",
	L"Forgetful",
	L"Psychotic",
	L"I.M.P. Disabilities",
};

// TODO.Translate
// HEADROCK HAM 3.6: Error strings for assigning a merc to a facility
STR16 gzFacilityErrorMessage[]=
{
	L"%s lacks sufficient Strength to perform this task.",
	L"%s lacks sufficient Dexterity to perform this task.",
	L"%s lacks sufficient Agility to perform this task.",
	L"%s is not Healthy enough to perform this task.",
	L"%s lacks sufficient Wisdom to perform this task.",
	L"%s lacks sufficient Marksmanship to perform this task.",
	// 6 - 10
	L"%s lacks sufficient Medical Skill to perform this task.",
	L"%s lacks sufficient Mechanical Skill to perform this task.",
	L"%s lacks sufficient Leadership to perform this task.",
	L"%s lacks sufficient Explosives Skill to perform this task.",
	L"%s lacks sufficient Experience to perform this task.",
	// 11 - 15
	L"%s lacks sufficient Morale to perform this task.",
	L"%s is too exhausted to perform this task.",
	L"Insufficient loyalty in %s. The locals refuse to allow you to perform this task.",
	L"Too many people are already working at the %s.",
	L"Too many people are already performing this task at the %s.",
	// 16 - 20
	L"%s can find no items to repair.",
	L"%s has lost some %s while working in sector %s!",
	L"%s has lost some %s while working at the %s in %s!",
	L"%s was injured while working in sector %s, and requires immediate medical attention!",
	L"%s was injured while working at the %s in %s, and requires immediate medical attention!",
	// 21 - 25
	L"%s was injured while working in sector %s. It doesn't seem too bad though.",
	L"%s was injured while working at the %s in %s. It doesn't seem too bad though.",
	L"The residents of %s seem upset about %s's presence.",
	L"The residents of %s seem upset about %s's work at the %s.",
	L"%s's actions in sector %s have caused loyalty loss throughout the region!",
	// 26 - 30
	L"%s's actions at the %s in %s have caused loyalty loss throughout the region!",
	L"%s is drunk.", // <--- This is a log message string.
	L"%s has become severely ill in sector %s, and has been taken off duty.",
	L"%s has become severely ill and cannot continue his work at the %s in %s.",
	L"%s was injured in sector %s.", // <--- This is a log message string.
	// 31 - 35
	L"%s was severely injured in sector %s.", //<--- This is a log message string.


};

// TODO.Translate
STR16 gzFacilityRiskResultStrings[]=
{
	L"Strength",
	L"Agility",
	L"Dexterity",
	L"Wisdom",
	L"Health",
	L"Marksmanship",
	// 5-10
	L"Leadership",
	L"Mechanical skill",
	L"Medical skill",
	L"Explosives skill",
};

// TODO.Translate
STR16 gzFacilityAssignmentStrings[]=
{
	L"AMBIENT",
	L"Staff",
	L"Rest",
	L"Repair Items",
	L"Repair %s", // Vehicle name inserted here
	L"Repair Robot",
	// 6-10
	L"Doctor",
	L"Patient",
	L"Practice Strength",
	L"Practice Dexterity",
	L"Practice Agility",
	L"Practice Health",
	// 11-15
	L"Practice Marksmanship",
	L"Practice Medical",
	L"Practice Mechanical",
	L"Practice Leadership",
	L"Practice Explosives",
	// 16-20
	L"Student Strength",
	L"Student Dexterity",
	L"Student Agility",
	L"Student Health",
	L"Student Marksmanship",
	// 21-25
	L"Student Medical",
	L"Student Mechanical",
	L"Student Leadership",
	L"Student Explosives",
	L"Trainer Strength",
	// 26-30
	L"Trainer Dexterity",
	L"Trainer Agility",
	L"Trainer Health",
	L"Trainer Marksmanship",
	L"Trainer Medical",
	// 30-35
	L"Trainer Mechanical",
	L"Trainer Leadership",
	L"Trainer Explosives",
};

STR16 Additional113Text[]=
{
	L"Jagged Alliance 2 v1.13 trybie okienkowym wymaga g��bi koloru 16-bitowego lub mniej.",
};

//Ja25 UB

STR16	gzNewLaptopMessages[]=
{
	L"Zapytaj o nasz� specjaln� ofert�!",
	L"Temporarily Unavailable",
	L"This special press preview of Jagged Alliance 2: Unfinished Business contains the only first 6 sector maps. The final version of the game will feature many more - please see the included readme file for details.",
};

STR16	zNewTacticalMessages[]=
{
	//L"Odleg�o�� od celu (w polach): %d, Jasno�� = %d/%d",
	L"Nadajnik zosta� pod��czony do twojego laptopa.",
	L"Nie mo�esz zatrudni� %s(a)",
	L"Na okre�lony czas, poni�sze honorarium pokryje koszt ca�ej misji razem z wyposa�eniem zamieszonym poni�ej.",
	L"Zatrudnij %s(a) ju� teraz i we� udzia� naszej promocji 'jedno honorarium pokrywa wszystko'.  Ponadto w tej niewiarygodnej ofercie ca�y ekwipunek najemnika dostaniesz za darmo.",
	L"Honorarium",
	L"Kto� jest w sektorze...",
	//L"Zasi�g broni (w polach): %d, Szansa na trafienie: %d procent",
	L"Poka� os�on�",
	L"Zasi�g wzroku",
	L"Nowi rekruci nie mog� tam przyby�.",
	L"Dop�ki tw�j laprop b�dzie bez nadajnika, nie b�dziesz m�g� zatrudnia� nowych cz�onk�w zespo�u.  Mo�liwe, �e to odpowiedni moment �eby odczyta� zapisany stan gry lub zacz�� gra� od nowa!",
	L"%s s�yszy d�wi�k zgniatanego metalu dochodz�cy spod cia�a Jerrego.  To niestety zabrzmia�o jak d�wi�k zgniatanej anteny od twojego laptopa.",  //the %s is the name of a merc.  @@@  Modified
	L"After scanning the note left behind by Deputy Commander Morris, %s senses an oppurtinity.  The note contains the coordinates for launching missiles against different towns in Tracona.  It also gives the coodinates of the origin - the missile facility.",
	L"Noticing the control panel, %s figures the numbers can be reveresed, so that the missile might destroy this very facility.  %s needs to find an escape route.  The elevator appears to offer the fastest solution...",
	L"To jest tryb CZ�OWIEK ZE STALI i nie mo�esz zapisywa� gry gdy wr�g jest w sektorze.",	//	@@@  new text
	L"(Nie mo�na zapisywa� gry podczas walki)", //@@@@ new text
	L"Kampania ma wi�cej ni� 30 postaci.",							// @@@ new text
	L"Nie mo�na odnale�� kampanii.",																	// @@@ new text
	L"Kampania: Standardowa ( %S )",																							// @@@ new text
	L"Kampania: %S",																													// @@@ new text
	L"Wybra�e� kampani� %S. Ta kampania zosta�a stworzona przez fan�w gry. Czy jeste� pewien, �e chcesz w ni� zagra�?",			// @@@ new text
	L"�eby u�y� edytora powiniene� wcze�niej wybra� kampani� inn� ni� standardowa.",		///@@new
};

#endif //POLISH
