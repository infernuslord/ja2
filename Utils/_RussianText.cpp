#pragma setlocale("RUSSIAN")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
#else
	#include "Language Defines.h"
	#if defined( RUSSIAN )
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_RussianText_public_symbol(void){;}

#ifdef RUSSIAN

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

	Other examples are used multiple times, like the Esc key  or "|E|s|c" or Space -> (|S|p|a|c|e)

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

// by Jazz
CHAR16 zGrod[][500] =
{
	L"�����", //0    // Robot
};

STR16 pCreditsJA2113[] =
{
	L"@T,{;������������ JA2 v1.13",
	L"@T,C144,R134,{;����������������",
	L"@T,C144,R134,{;������� � ����",
	L"@};(������ ����� �� ������ �����)",
	L"@T,C144,R134,{;��������",
	L"@T,C144,R134,{;����� ��������",
	L"@};(� ������ ������, ������������ ������� ���� � ����������� ������ ���������!)",
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
//	L",38 ���",
//	L"9��",
//	L",45 ���",
//	L",357 ���",
//	L"12 ���",
//	L"���",
//	L"5,45��",
//	L"5,56��",
//	L"7,62�� ����",
//	L"7,62�� ��",
//	L"4,7��",
//	L"5,7��",
//	L"������",
//	L"������",
//	L"", // ������
//	L"", // �����
////	L".50 cal", // barrett
////	L"9mm Hvy", // Val silent
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
//	L",38 ���",
//	L"9��",
//	L",45 ���",
//	L",357 ���",
//	L"12 ���",
//	L"���",
//	L"5,45��",
//	L"5,56��",
//	L"7,62�� �.",
//	L"7,62�� ��",
//	L"4,7��",
//	L"5.7��",
//	L"������",
//	L"������",
//	L"", // ������
////	L"", // flamethrower
////	L".50 cal", // barrett
////	L"9mm Hvy", // Val silent
//};


CHAR16 WeaponType[MAXITEMS][30] =
{
	L"",			//Other
	L"��������",		//Pistol
	L"���.��������",	//MP '�������������� ��������'
	L"��",			//SMG '��������-�������'
	L"��������",		//Rifle
	L"��.��������",		//Sniper rifle '����������� ��������'
	L"��.��������",		//Assault rifle '��������� ��������'
	L"������ �������",	//LMG '������ �������'
	L"�����",		//Shotgun '��������������� �����'
};

CHAR16 TeamTurnString[][STRING_LENGTH] =
{
	L"��� ������", // player's turn
	L"��� ����������",
	L"��� ������",
	L"��� ���������",
	L"��� �����������",
	L"Player_Plan",// planning turn
	L"Client �1",//hayden
	L"Client �2",//hayden
	L"Client �3",//hayden
	L"Client �4",//hayden
};

CHAR16 Message[][STRING_LENGTH] =
{
	L"",

	// In the following 8 strings, the %s is the merc's name, and the %d (if any) is a number.

	L"%s �������� ������� � ������ � ������ � ����������!",
	L"%s �������� ������� � ����� � ������ � ��������!",
	L"%s �������� ������� � ����� � ������ � ����!",
	L"%s �������� ������� � ���� � ������ � �����������!",
	L"%s �������� ������� � ������ � ������ %d ������ ����������!",
	L"%s �������� ������� � ����� � ������ %d ������ ��������!",
	L"%s �������� ������� � ����� � ������ %d ������ ����!",
	L"%s �������� ������� � ���� � ������ %d ������ �����������!",
	L"��������!",

	// The first %s is a merc's name, the second is a string from pNoiseVolStr,
	// the third is a string from pNoiseTypeStr, and the last is a string from pDirectionStr

	L"", //OBSOLETE
	L"� ��� �� ������ ������� ������������!",

	// In the following four lines, all %s's are merc names

	L"%s ������������ ������.",
	L"%s ������������ ����� ��������!",
	L"%s ��������� ������ ������ (����� ������� - ������).",
	L"%s � %s ��������� ������ ������ (����� ������� - ������).",
	// the following 17 strings are used to create lists of gun advantages and disadvantages
	// (separated by commas)
	L"������",
	L"��������",
	L"������� ������",
	L"������� ������",
	L"������� ����",
	L"����� ����",
	L"��������������",
	L"����������������",
	L"������� ���",
	L"������� ���",
	L"�����",
	L"������",
	L"����������",
	L"���������",	//fast burst fire
	L"��� ������� �������",
	L"���.�������",
	L"���.�������",

	// In the following two lines, all %s's are merc names

	L"%s: ����������� ������ �������.",
	L"%s: ����������� ������ �������.",

	// The first %s is a merc name and the second %s is an item name

	L"������ ������: ����������� �������!",
	L"%s ����� %s.",

	// The %s is a merc name

	L"%s: ������ �� �������� ���������.",

	L"��� �����������!",
	L"����������?",

	// Both %s's are item names

	L"������ ������������ %s � %s.",

	L"������",
	L"���������", 
	L"�������",
	
	//You cannot use "item(s)" and your "other item" at the same time.
	//Ex:  You cannot use sun goggles and you gas mask at the same time.
	L"������ ������������ %s � %s ������������.",

	L"���� ������� ����� ������������ � ������ ���������, �������� ��� � ���� �� ������� ���� ��� ��������������.",
	L"���� ������� ����� ������������ � ������ ���������, �������� ��� � ���� �� ������� ���� ��� ��������������. (������ ��� �������� ������������)",
	L"� ������� ��� �������� �����!",
	L"%s ������� ������ ������, ����� ��������� ��� %s", 
	L"%s: ��������� � ������!",
	L"�������� �����?",
	L"��� ��������� ��������������. ���������� ���?",
	L"%s ��������� ������ �������!",
	L"%s ��������������� �� ���������� �������!",
	L"%s �� ������� �������� %s � �����!",
	L"%s ����� %s",
	L"����������� ���: ",
	L"�������?",
	L"������� ������ ���� ������.",
	L"��� ��� ����?",
  L"����� ��������������� ��������� ��������� �������� - �������� '������/�������'.",
	L"%s �������� �������� ������ ���� ������.", //%s only had enough time to reload ONE gun
	L"��� �����-�����", //Bloodcats' turn
	L"��������������", //full auto
	L"����������������", //no full auto
	L"������", //accurate
	L"��������", //inaccurate
	L"��� ���������", //no semi auto
	L"���� ������� �� �����!",
	L"� ����� � ����� ������ ���!",

	L"%s: �������� �������� ������.",
	L"%s: �������� �������� ����.",
	
	L"%s: ������������ �������� ������.",
	L"%s: ������������ �������� ����.",
	
	L"%s: ��������� �������� ������.",
	L"%s: ��������� �������� ����.",
	
	L"%s: ����������� �������� ������.",
	L"%s: ����������� �������� ����.",

	L"������ ���������� ������� %s �� ��� �����.",
};


// the names of the towns in the game

CHAR16 pTownNames[MAX_TOWNS][MAX_TOWN_NAME_LENGHT] =
{
	L"",
	L"������",
	L"�������",
	L"�����",
	L"����",
	L"�����",
	L"�������",
	L"���-����",
	L"������",
	L"����",
	L"������",
	L"������",
	L"�������",
};

// the types of time compression. For example: is the timer paused? at normal speed, 5 minutes per second, etc.
// min is an abbreviation for minutes

STR16 sTimeStrings[] =
{
	L"�����",
	L"�����",
	L"5 ���",
	L"30 ���",
	L"60 ���",
	L"6 �����",
};


// Assignment Strings: what assignment does the merc  have right now? For example, are they on a squad, training, 
// administering medical aid (doctor) or training a town. All are abbreviated. 8 letters is the longest it can be.

STR16 pAssignmentStrings[] =
{
	L"����� 1",
	L"����� 2",
	L"����� 3",
	L"����� 4",
	L"����� 5",
	L"����� 6",
	L"����� 7",
	L"����� 8",
	L"����� 9",
	L"����� 10",
	L"����� 11",
	L"����� 12",
	L"����� 13",
	L"����� 14",
	L"����� 15",
	L"����� 16",
	L"����� 17",
	L"����� 18",
	L"����� 19",
	L"����� 20",
	L"�� ������",	// on active duty
	L"�����",	// administering medical aid
	L"�������",	// getting medical aid
	L"���������",	// in a vehicle
	L"� ����",	// in transit - abbreviated form
	L"������",	// repairing
	L"��������",	// training themselves  
  L"���������",		// training a town to revolt 
	L"�����.��.", //training moving militia units		//M.Militia
	L"������",	// training a teammate
	L"������",	// being trained by someone else 
	L"����", // operating a strategic facility			//Staff
	L"�����", // Resting at a facility					//Rest
	L"�����",	// dead
	L"�������.",	// abbreviation for incapacitated
	L"� �����",	// Prisoner of war - captured
	L"���������",	// patient in a hospital 
	L"����",	// Vehicle is empty
};


STR16 pMilitiaString[] =
{
	L"���������", // the title of the militia box
	L"�����", //the number of unassigned militia troops
	L"������ ���������������� ���������, ����� ���� ��������� � ���� ������!",
	L"����� ������������ ��������� �� ������ ��������. ���������� �� �� ����� ������� ��������?", //Some militia were not assigned to a sector. Would you like to disband them?
};


STR16 pMilitiaButtonString[] =
{
	L"����", // auto place the militia troops for the player
	L"������", // done placing militia troops
	L"����������", // HEADROCK HAM 3.6: Disband militia	//Disband
};

STR16 pConditionStrings[] = 
{
	L"��������",	//the state of a soldier .. excellent health
	L"�������",	//good health
	L"�������",	//fair health
	L"�����",	//wounded health
	L"�����",	//tired
	L"������������", //bleeding to death
	L"��� ��������", //knocked out 
	L"�������",	//near death
	L"�����",	//dead
};

STR16 pEpcMenuStrings[] =
{
	L"���������", // set merc on active duty
	L"�������", // set as a patient to receive medical aid
	L"���������", // tell merc to enter vehicle
	L"��� �������", // let the escorted character go off on their own
	L"������", // close this menu
};


// look at pAssignmentString above for comments

STR16 pPersonnelAssignmentStrings[] =
{
	L"����� 1",
	L"����� 2",
	L"����� 3",
	L"����� 4",
	L"����� 5",
	L"����� 6",
	L"����� 7",
	L"����� 8",
	L"����� 9",
	L"����� 10",
	L"����� 11",
	L"����� 12",
	L"����� 13",
	L"����� 14",
	L"����� 15",
	L"����� 16",
	L"����� 17",
	L"����� 18",
	L"����� 19",
	L"����� 20",
	L"�� ������",
	L"�����",
	L"�������",
	L"���������",
	L"� ����",
	L"������",
	L"��������", 
	L"���������",
	L"��������� ��������� ������",	//Training Mobile Militia
	L"������",
	L"������",
	L"�������� � ����������",			//Facility Staff
	L"��������",		//Resting at Facility
	L"�����",
	L"�������.",
	L"� �����",
	L"���������", 
	L"����",	// Vehicle is empty
};


// refer to above for comments

STR16 pLongAssignmentStrings[] =
{
	L"����� 1",
	L"����� 2",
	L"����� 3",
	L"����� 4",
	L"����� 5",
	L"����� 6",
	L"����� 7",
	L"����� 8",
	L"����� 9",
	L"����� 10",
	L"����� 11",
	L"����� 12",
	L"����� 13",
	L"����� 14",
	L"����� 15",
	L"����� 16",
	L"����� 17",
	L"����� 18",
	L"����� 19",
	L"����� 20",
	L"�� ������",
	L"�����",
	L"�������",
	L"� ����������",
	L"� ����",
	L"�����������",
	L"������������", 
	L"��������� ���������",
	L"��������� ��������� ������",	//Train Mobiles
	L"���������",
	L"���������",
	L"�������� � ����������",		//Staff Facility
	L"�������� � ���������",		//Resting at Facility
	L"�����",
	L"�������������",
	L"� �����",
	L"� ���������", // patient in a hospital 
	L"��� ����������",	// Vehicle is empty
};


// the contract options

STR16 pContractStrings[] =
{
	L"��������� ���������:", 
	L"", // a blank line, required
	L"�������� �� 1 ����", // offer merc a one day contract extension
	L"�������� �� 7 ����", // 1 week
	L"�������� �� 14 ����", // 2 week
	L"�������", // end merc's contract
	L"������", // stop showing this menu
};

STR16 pPOWStrings[] =
{
	L"� �����",  //an acronym for Prisoner of War
	L"??",
};

STR16 pLongAttributeStrings[] =
{
    L"����", 
	L"��������",  
	L"�����������", 
	L"���������", 
	L"��������",
	L"��������",
	L"��������",
	L"���������",
	L"����������",
	L"�������",
};

STR16 pInvPanelTitleStrings[] =
{
	L"�����", // the armor rating of the merc
	L"���", // the weight the merc is carrying
	L"�����.", // the merc's camouflage rating
	L"��������:",
	L"�����:",
};

STR16 pShortAttributeStrings[] =
{
	L"���", // the abbreviated version of : agility
	L"���", // dexterity
	L"���", // strength
	L"���", // leadership
	L"���", // wisdom
	L"���", // experience level
	L"���", // marksmanship skill
	L"���", // explosive skill
	L"���", // mechanical skill
	L"���", // medical skill
};


STR16 pUpperLeftMapScreenStrings[] =
{
	L"����������", // the mercs current assignment 
	L"��������", // the contract info about the merc
	L"��������", // the health level of the current merc
	L"����.���", // the morale of the current merc
	L"����.",	// the condition of the current vehicle
	L"������",	// the fuel level of the current vehicle
};

STR16 pTrainingStrings[] =
{
	L"�������", // tell merc to train self 
    L"���������", // tell merc to train town 
	L"������", // tell merc to act as trainer
	L"������", // tell merc to be train by other 
};

STR16 pGuardMenuStrings[] =
{
	L"������� ����:", // the allowable rate of fire for a merc who is guarding
	L" ����������� �����", // the merc can be aggressive in their choice of fire rates
	L" ������ �������", // conserve ammo 
	L" ������������ �� ��������", // fire only when the merc needs to 
	L"������ ���������:", // other options available to merc
	L" ����� ���������", // merc can retreat
	L" ����� ������ �������",  // merc is allowed to seek cover
	L" ����� ������ �������", // merc can assist teammates
	L"������", // done with this menu
	L"������", // cancel this menu
};

// This string has the same comments as above, however the * denotes the option has been selected by the player

STR16 pOtherGuardMenuStrings[] =
{
	L"������� ����:",
	L" *����������� �����*",
	L" *������ �������*",
	L" *������������ �� ��������*",
	L"������ ���������:",
	L" *����� ���������*",
	L" *����� ������ �������*",
	L" *����� ������ �������*",
	L"������",
	L"������",
};

STR16 pAssignMenuStrings[] =
{
	L"�� ������", // merc is on active duty
	L"�����", // the merc is acting as a doctor
	L"�������", // the merc is receiving medical attention
	L"������", // the merc is in a vehicle
	L"������", // the merc is repairing items 
	L"��������", // the merc is training
	L"��������", // the merc is using/staffing a facility	//Facility
	L"������", // cancel this menu
};

//lal
STR16 pMilitiaControlMenuStrings[] =
{
	L"� �����", // set militia to aggresive
	L"������� �������", // set militia to stationary
	L"���������", // retreat militia
	L"�� ����", // retreat militia
	L"������", // retreat militia	
	L"� �������",
	L"��� � �����", 
	L"���� ������� �������",
	L"���� ���������",
	L"��� �� ����",
	L"���� ����������",
	L"���� ������",
	L"���� � �������",
	//L"���� ������ ��������",
	L"������", // cancel this menu
};

//STR16 pTalkToAllMenuStrings[] =
//{
//	L"� �����", // set militia to aggresive
//	L"������� �������", // set militia to stationary
//	L"���������", // retreat militia
//	L"�� ����", // retreat militia
//	L"������", // retreat militia		 
//	L"������", // cancel this menu
//};

STR16 pRemoveMercStrings[] =
{
	L"������ �����", // remove dead merc from current team
	L"������",
};

STR16 pAttributeMenuStrings[] =
{
	L"����",
	L"��������",
	L"�����������",
	L"��������",
	L"��������",
	L"��������",
	L"��������",
	L"���������",
	L"����������",
	L"������",
};

STR16 pTrainingMenuStrings[] =
{
 L"��������", // train yourself 
 L"���������", // train the town 
 L"�����. ������",		//Mobile Militia
 L"������", // train your teammates 
 L"������",  // be trained by an instructor 
 L"������", // cancel this menu
};


STR16 pSquadMenuStrings[] =
{
	L"�����  1",
	L"�����  2",
	L"�����  3",
	L"�����  4",
	L"�����  5",
	L"�����  6",
	L"�����  7",
	L"�����  8",
	L"�����  9",
	L"����� 10",
	L"����� 11",
	L"����� 12",
	L"����� 13",
	L"����� 14",
	L"����� 15",
	L"����� 16",
	L"����� 17",
	L"����� 18",
	L"����� 19",
	L"����� 20",
	L"������",
};

STR16 pPersonnelTitle[] =
{
	L"�������", // the title for the personnel screen/program application
};

STR16 pPersonnelScreenStrings[] =
{
	L"��������:",		// health of merc
	L"�����������:", 
	L"��������:",
	L"����:",
	L"���������:",
	L"���������:",
	L"����:",		// experience level
	L"��������:", 
	L"��������:",
	L"����������:",
	L"��������:",
	L"���. �������:",	// amount of medical deposit put down on the merc
	L"�� ����� ���������:",	// cost of current contract
	L"���� ������:",	// number of kills by merc
	L"����� �����:",	// number of assists on kills by merc
	L"������� �� ����:",	// daily cost of merc
	L"����� ���� �����:",	// total cost of merc
	L"��������:",		// cost of current contract
	L"� ��� �� ������:",	// total service rendered by merc
	L"������. ���������:",	// amount left on MERC merc to be paid
	L"������� ���������:",	// percentage of shots that hit target
	L"���:", 		// number of battles fought
	L"�������:",		// number of times merc has been wounded
	L"������:",
	L"��� �������",
	L"����������:", //Achievements
};

// SANDRO - helptexts for merc records
STR16 pPersonnelRecordsHelpTexts[] =
{
	L"�����:              %d\n",
	L"������:             %d\n",
	L"�������:            %d\n",
	L"���������� �������: %d\n",
	L"��������:           %d\n",
	L"������:             %d\n", 
	L"������ ��������:    %d\n",

	L"�����:..............%d\n",
	L"���������:...%d\n",
	L"������:...........%d\n",

	L"�������� ����:         %d\n",
	L"�������� �����:        %d\n",
	L"������� ������:        %d\n",
	L"������� �����:         %d\n",
	L"������ �����:          %d\n",
	L"������ ��������:       %d\n",
	L"������� ���������:     %d\n",

	L"������ ��������:             %d\n",
	L"������ �������:              %d\n",
	L"������� �����������:         %d\n",
	L"���������� ��������:         %d\n",
	L"��������� ����������������:  %d\n",
	L"��������� �������:           %d\n",
	L"����� ��������:              %d\n",
	L"���������� �������������:    %d\n",
	L"������ ����������:           %d\n",
	L"�������:                     %d\n",
	L"��������� ������������:      %d\n",
	L"�������� ���������:          %d\n",
	L"������� �� ���������:        %d\n",	//Ambushes Prevented
	L"������� ������� ���������:   %d\n",

	L"����������� ��������:.......%d\n",
	L"��������:......................................%d\n",
	L"���������� �����������:...%d\n",
	L"��������� � ������:............%d\n",
	L"���������� �����:.................%d ������\n",

	L"��������� ���:........................%d\n",
	L"������� ���:............................%d\n",
	L"����������� ������:........%d\n",
	L"����������:................................%d\n",
	L"��������� ����������:....%d\n",
	L"������� ���. ������������:..%d\n",	//Surgeries Undergoed
	L"����� �� ������������:......%d\n",	//Facility Accidents

	L"��������:",
	L"����������:",
};


//These string correspond to enums used in by the SkillTrait enums in SoldierProfileType.h
STR16 gzMercSkillText[] = 
{
	L"��� ������",
	L"����� ������",
	L"���������� ���",
	L"�����������",
	L"������ ��������", 
	L"�������",
	L"����������",
	L"������� ������",
	L"�������������� ������",
	L"����������",
	L"������",
	L"���������",
	L"������ ���������",
	L"�������� ������",
	L"�������", 
	L"��������",
	//L"�������� (�����)",
	//L"�������� (�������)",
	//L"�������� (����)",
	L"(�������)",
};

// TODO.Translate
//////////////////////////////////////////////////////////
// SANDRO - added this
STR16 gzMercSkillTextNew[] = 
{
	// Major traits
	L"��� ������",	//No Skill
	L"����������",	//Auto Weapons
	L"�������",	//Heavy Weapons
	L"�������",	//Marksman
	L"�������",	//Hunter
	L"������",	//Gunslinger
	L"�����",	//Hand to Hand
	L"��������",	//Deputy
	L"�������-�����������",	//Technician
	L"�������",	//Paramedic
	// Minor traits
	L"������",	//Ambidextrous
	L"������ ������",	//Melee
	L"������ �� �������",	//Throwing
	L"������� ����",	//Night Ops
	L"��������� ������",	//Stealthy
	L"���������",	//Athletics
	L"����������",	//Bodybuilding
	L"���������",	//Demolitions
	L"����������",	//Teaching
	L"���������",	//Scouting
	// second names for major skills
	L"���������",	//Machinegunner
	L"�����������",	//Bombardier
	L"�������",	//Sniper
	L"��������",	//Ranger
	L"�����������",	//Gunfighter
	L"������ ���������",	//Martial Arts
	L"��������",	//Squadleader
	L"�������",	//Engineer
	L"������",	//Doctor
};
//////////////////////////////////////////////////////////


// This is pop up help text for the options that are available to the merc

STR16 pTacticalPopupButtonStrings[] =
{
	L"������/���� (|S)", 
	L"��������/������� ��� (|C)",
	L"������/������ (|R)",
	L"����/������ (|P)",
	L"������� (|L)",
	L"��������",
	L"����������",
	L"��������� (|C|t|r|l)",

	// Pop up door menu
	L"�������",
	L"������ �������", 
	L"������� ���������", 
	L"������� c����",
	L"�����������",
	L"��������",
	L"��������",
	L"������������ ����� ����������", 
	L"�������� �����",
	L"������ (|E|s|c)",
	L"�������",
};

// Door Traps. When we examine a door, it could have a particular trap on it. These are the traps.

STR16 pDoorTrapStrings[] =
{
	L"��� �������",
	L"�����-�������",
	L"��������������",
	L"������",
	L"������������",
};

// Contract Extension. These are used for the contract extension with AIM mercenaries.

STR16 pContractExtendStrings[] =
{
	L"1 ����",
	L"7 ����",
	L"14 ����",
};

// On the map screen, there are four columns. This text is popup help text that identifies the individual columns.

STR16 pMapScreenMouseRegionHelpText[] =
{
	L"������� ��������",
	L"������ ������",
	L"��������� ���� ��������",
	L"�������� �������� (|C)",
	L"��������������� �����",
	L"�����", 
};

// volumes of noises 

STR16 pNoiseVolStr[] =
{
	L"�����",
	L"������",
	L"�������",
	L"����� �������",
};

// types of noises 

STR16 pNoiseTypeStr[] = // OBSOLETE
{
	L"����������",
	L"���� �����",
	L"�����",
	L"�������",
	L"����",
	L"�������",
	L"�����",
	L"����",
	L"����",
	L"����",
	L"����",
	L"������",
};

// Directions that are used to report noises

STR16 pDirectionStr[] = 
{
	L"c ������-�������",
	L"c �������",
	L"c ���-�������",
	L"c ���",
	L"c ���-������",
	L"c ������",
	L"c ������-������",
	L"c ������",
};

// These are the different terrain types. 

STR16 pLandTypeStrings[] =
{
	L"�����",
	L"������",
	L"�������",
	L"�������",
	L"������",
	L"���",	 
	L"������",
	L"����",	
	L"�����",
	L"�����������",
	L"����",	//river from north to south
	L"����",	//river from east to west
	L"����� ������",
	//NONE of the following are used for directional travel, just for the sector description.
	L"�������",
	L"�����",
	L"����, ������",
	L"����, ������",
	L"�����, ������",
	L"�������, ������",
	L"����, ������",
	L"���������",
	L"����, ������",
	L"�����, ������",
	L"�������, ������",
	L"������, ������",
	L"������, ���", 
	L"�������, ���",
	L"�������, ���",
	L"������, ���",
	
	//These are descriptions for special sectors
	L"��������� �������",
	L"�������� ��������",
	L"�������� ������",
	L"���� ���",
	L"������� ����������",	//The rebel base underground in sector A10
	L"������� �����",	//The basement of the Tixa Prison (J9)
	L"������ ������",	//Any mine sector with creatures in it
	L"������� ����",	//The basement of Orta (K4)
	L"�������",		//The tunnel access from the maze garden in Meduna 
	//leading to the secret shelter underneath the palace
	L"�������",		//The shelter underneath the queen's palace
	L"",			//Unused
};

STR16 gpStrategicString[] =
{
	L"",	//Unused
	L"%s ������� � ������� %c%d, � ������ ����� ��� �� �������.",	//STR_DETECTED_SINGULAR
	L"%s ������� � ������� %c%d, � ��������� ������ ��� �� �������.",	//STR_DETECTED_PLURAL
	L"������� ��������� �������� ���������?",													//STR_COORDINATE

	//Dialog strings for enemies.

	L"���� ���������� ��� �������.",			//STR_ENEMY_SURRENDER_OFFER
	L"���������� ��� �������� ����� ������ � ����.",	//STR_ENEMY_CAPTURED

	//The text that goes on the autoresolve buttons							

	L"���������", 		//The retreat button		//STR_AR_RETREAT_BUTTON
	L"OK",		//The done button			//STR_AR_DONE_BUTTON

	//The headers are for the autoresolve type (MUST BE UPPERCASE)

	L"�������",								//STR_AR_DEFEND_HEADER
	L"�����",								//STR_AR_ATTACK_HEADER
	L"�������",								//STR_AR_ENCOUNTER_HEADER
	L"������",		//The Sector A9 part of the header		//STR_AR_SECTOR_HEADER

	//The battle ending conditions						

	L"������!",					//STR_AR_OVER_VICTORY
	L"���������!",					//STR_AR_OVER_DEFEAT
	L"������!",					//STR_AR_OVER_SURRENDERED
	L"������!",					//STR_AR_OVER_CAPTURED
	L"��������!",					//STR_AR_OVER_RETREATED

	//These are the labels for the different types of enemies we fight in autoresolve.

	L"���������",					//STR_AR_MILITIA_NAME,
	L"�����",					//STR_AR_ELITE_NAME,
	L"������",					//STR_AR_TROOP_NAME,
	L"�������",					//STR_AR_ADMINISTRATOR_NAME,
	L"�������",					//STR_AR_CREATURE_NAME,

	//Label for the length of time the battle took

	L"������ �������",				//STR_AR_TIME_ELAPSED,

	//Labels for status of merc if retreating.  (UPPERCASE)			

	L"��������",					//STR_AR_MERC_RETREATED,
	L"���������",					//STR_AR_MERC_RETREATING,
	L"���������",					//STR_AR_MERC_RETREAT,

	//PRE BATTLE INTERFACE STRINGS 
	//Goes on the three buttons in the prebattle interface.  The Auto resolve button represents
	//a system that automatically resolves the combat for the player without having to do anything.
	//These strings must be short (two lines -- 6-8 chars per line)

	L"���� �����",					//STR_PB_AUTORESOLVE_BTN,
	L"������� � ������",				//STR_PB_GOTOSECTOR_BTN,
	L"���� �� �������",				//STR_PB_RETREATMERCS_BTN,

	//The different headers(titles) for the prebattle interface.
	L"������� � ������",				//STR_PB_ENEMYENCOUNTER_HEADER,
	L"����������� �����",				//STR_PB_ENEMYINVASION_HEADER, // 30
	L"��������� ������",				//STR_PB_ENEMYAMBUSH_HEADER
	L"��������� ������",				//STR_PB_ENTERINGENEMYSECTOR_HEADER
	L"����� ������",				//STR_PB_CREATUREATTACK_HEADER
	L"������ �����-�����",				//STR_PB_BLOODCATAMBUSH_HEADER
	L"���� � �������� �����-�����",			//STR_PB_ENTERINGBLOODCATLAIR_HEADER

	//Various single words for direct translation.  The Civilians represent the civilian
	//militia occupying the sector being attacked.  Limited to 9-10 chars

	L"�������",
	L"����",
	L"��������",
	L"���������",
	L"��������",
	L"�����-������",
	L"������",
	L"���",			//If there are no uninvolved mercs in this fight.
	L"�/�",			//Acronym of Not Applicable
	L"�",			//One letter abbreviation of day
	L"�",			//One letter abbreviation of hour

	//TACTICAL PLACEMENT USER INTERFACE STRINGS
	//The four buttons 

	L"������",
	L"��������",
	L"�������",
	L"B a�a��!",

	//The help text for the four buttons.  Use \n to denote new line (just like enter).

	L"������� ��� ������� ������ \n� ��������� ������ ���������� ��. (|C)", 
	L"��� ������ ������� ������������ \n������ ��������� �������. (|S)",
	L"��������� ������� �����, \n��� ������������� ����� ������. (|G)",
	L"������� ��� ������, ����� ��������� \n����� ������� ��� ������. (|�|�|�|�)",
	L"�� ������ ���������� ���� ����� ������ \n�� ����, ��� ������ ���.",

	//Various strings (translate word for word)

	L"������",
	L"����� ����� �����",

	//Strings used for various popup message boxes.  Can be as long as desired.

	L"�����������. ����� ����������. ���������� ������ ������ �����.",
	L"��������� ������ � ������������ ����� �����.",

	//This message is for mercs arriving in sectors.  Ex:  Red has arrived in sector A9.
	//Don't uppercase first character, or add spaces on either end.

	L"������(�) � ������", 

	//These entries are for button popup help text for the prebattle interface.  All popup help
	//text supports the use of \n to denote new line.  Do not use spaces before or after the \n.
	L"������������� ������������ ���\n��� �������� �����. (|A)",
	L"������ �������� �������\n�� ����� ���������.",
	L"����� � ������, ����� ��������� �����. (|E)",
	L"��������� ������� � ���������� ������. (|R)",				//singular version
	L"���� ������� ��������� � ���������� ������. (|R)", //multiple groups with same previous sector

	//various popup messages for battle conditions.  

	//%c%d is the sector -- ex:  A9
	L"����� ��������� ����� ���������� � ������� %c%d.",
	//%c%d ������ -- ����:  A9
	L"����� ��������� ����� ���������� � ������� %c%d.",
	//1st %d refers to the number of civilians eaten by monsters,  %c%d is the sector -- ex:  A9
	//Note:  the minimum number of civilians eaten will be two.
	L"����� ����� %d ����������� �� ����� ����� ������� %s.",
	//%s is the sector location -- ex:  A9: Omerta
	L"����� ��������� ����� ��������� � ������� %s. �� ���� �� ����� ������ �� � ��������� ���������!",
	//%s is the sector location -- ex:  A9: Omerta
	L"����� ��������� ����� ��������� � ������� %s. �� ���� �� ����� ������ �� � ��������� ���������!",

};

STR16 gpGameClockString[] = 
{
	//This is the day represented in the game clock.  Must be very short, 4 characters max.
	L"����",	
};

//When the merc finds a key, they can get a description of it which 
//tells them where and when they found it.
STR16 sKeyDescriptionStrings[2] =
{
	L"������� � �������:",
	L"������� �� ����:",
};

//The headers used to describe various weapon statistics.

CHAR16		gWeaponStatsDesc[][ 17 ] =
{
	// HEADROCK: Changed this for Extended Description project
	L"���������:",
	L"��� (%s):", 
	L"����� ��",	
	L"����:",		// Range
	L"����:",		// Damage
	L"�����:", 		// Number of bullets left in a magazine
	L"��:",			// abbreviation for Action Points
	L"=",
	L"=",
						//Lal: additional strings for tooltips
	L"��������:",	//9
	L"����:",		//10	
	L"����:", 	//11
	L"���:",		//12
	L"���������:",//13
	// HEADROCK: Added new strings for extended description ** REDUNDANT **
	L"�������:",	//14	//Attachments
	L"AUTO/5:",		//15
	L"�����:",		//16

	L"�������������:",	//17 //WarmSteel - So we can also display default attachments

};

// HEADROCK: Several arrays of tooltip text for new Extended Description Box
// Please note, several of these are artificially inflated to 19 entries to help fix a complication with
// changing item type while watching its description box
STR16		gzWeaponStatsFasthelp[ 29 ] =
{
	L"��������������",						//Range
	L"����",							//Damage
	L"����� �� ������ ���\n�������� ��������\n(c ��������/���) (��� ������, ��� �����)",	//Burst/Auto Penalty
	L"��������� � ��������������\n������ �� 5 ��",			//Autofire shots per 5 AP
	L"��������",							//Accuracy
	L"���������",							//Reliability
	L"�������� �������",						//Repair Ease
	L"�� �� �������",						//APs to ready
	L"�� �� 1 �������",						//APs to fire Single
	L"�� �� ����� � ��������",					//APs to fire Burst
	L"�� �� ����� ��������",					//APs to fire Auto
	L"�� �� ������ ��������",					//APs to Reload
	L"�� �� ������� �������",					//APs to Reload Manually
	L"�������������",						//Flash Suppression
	L"�������� (��� ������, ��� �����)",				//Loudness (Lower is better)
	L"����������� ��������",					//To-Hit Modifier
	L"������ ��������� ���������\n����� ������������",		//Average Best Laser Range
	L"����������� ���������� ��������",				//Aiming Modifier
	L"����������� ����������� ���������",				//Min. Range for Aiming Bonus
	L"����� �� �����\n(��� �������� ���)",				//Bipod Modifier
	L"�� �� ������",						//APs to Throw
	L"�� �� �������",						//APs to Launch
	L"�� �� ���� �����",						//APs to Stab
	L"�� �������� ����������!",					//No Single Shot!
	L"��� ������� �������!",					//No Burst Mode!
	L"��� ��������������� ������!",					//No Auto Mode!
	L"�� �� ����",							//APs to Bash
	L"����� �� ������ ��� \n�������� �������� \n(��� ������, ��� �����)",	//Autofire Penalty (Lower is better)
    L"����� �� ������ ���\n�������� �������� c ��������\n(��� ������, ��� �����)",		//Burst Penalty (Lower is better)
};

STR16		gzWeaponStatsFasthelpTactical[ 29 ] =
{
	L"��������������",
	L"����",
	L"����� �� ������ ���\n�������� ��������\n(c ��������/���) (��� ������, ��� �����)",
	L"��������� � ��������������\n������ �� 5 ��",
	L"��������",
	L"���������",
	L"�������� �������",
	L"�� �� �������",
	L"�� �� 1 �������",
	L"�� �� ����� � ��������",
	L"�� �� ����� ��������",
	L"�� �� ������ ��������",
	L"�� �� ������� �������",
	L"����������� ��������",
	L"������ ��������� ���������\n����� ������������",
	L"����������� ���������� ��������",
	L"����������� ����������� ���������",
	L"�������������",
	L"��������\n(��� ������, ��� �����)",
	L"����� �� �����\n(��� �������� ���)",
	L"�� �� ������",
	L"�� �� �������",
	L"�� �� ���� �����",
	L"�� �������� ����������!",
	L"��� ������� �������!",
	L"��� ��������������� ������!",
	L"�� �� ����",
	L"����� �� ������ ��� \n�������� �������� \n(��� ������, ��� �����)",
    L"����� �� ������ ���\n�������� �������� c ��������\n(��� ������, ��� �����)",
};

STR16		gzAmmoStatsFasthelp[ 20 ] =
{
	L"����������� ������\n(��� ������, ��� �����)",		//Armor Penetration (Lower is better)
	L"���������� ������\n(��� ����, ��� �����)",		//Bullet Tumble (Higher is better)
	L"��������� ������\n(��� ����, ��� �����)",		//Pre-impact Explosion (Higher is better)
	L"������������ ������",					//Tracer Effect
	L"���������������",					//Anti-Tank
	L"��������� �����",					//Lockbuster
	L"������������ ������� �����",				//Ignores Armor
	L"��������� ������",					//Acidic
	L"����������� ��������������",				//Range Modifier
	L"����������� �����",					//Damage Modifier
	L"����������� ��������",				//To-Hit Modifier
	L"����������� ������\n�� ������ ��� ��������\n� �������������� ������\n(��� ������, ��� �����)",	//Autofire Penalty Modifier (Higher is better)
	L"����������� ������ ��� ������� \n(��� ������, ��� �����)",	//Burst Penalty Modifier (Higher is better)
	L"����������� ���������",				//Reliability Modifier
	L"����������� ��������\n(��� ������, ��� �����)",	//Loudness Modifier (Lower is better)
	L"",
	L"",
	L"",
	L"",
	L"",
};

STR16		gzArmorStatsFasthelp[ 20 ] =
{
	L"������",						//Protection
	L"�������� ����\n(��� ������, ��� �����)",		//Coverage (Higher is better)
	L"��������������\n(��� ������, ��� �����)",		//Degrade Rate (Lower is better)
	L"������� �� �����������",				//AP Modifier
	L"����������� ��������",				//To-Hit Modifier
	L"�������� '���'",
	L"�������� '�����'",
	L"�������� '�������'",
	L"�������� '����'",
	L"����������� ����������",				//Stealth Modifier
	L"����������� ���������\n���������",			//Vision Range Modifier
	L"����������� ���������\n��������� ����",		//Day Vision Range Modifier
	L"����������� ���������\n��������� �����",		//Night Vision Range Modifier
	L"����������� ���������\n��������� ��� ����� ���������",//Bright Light Vision Range Modifier
	L"����������� ���������\n��������� � ������",		//Cave Vision Range Modifier
	L"������� ������� ������",				//Tunnel Vision Percentage
	L"����������� ���������\n����������",			//Hearing Range Modifier
	L"",
	L"",
	L"",
};

STR16		gzExplosiveStatsFasthelp[ 20 ] =
{
	L"����",						//Damage
	L"���������", //�������� �������			//Stun Damage
	L"���� ���������� ������\n(��� ������, ��� �����)",	//Blast Loudness (Lower is better)
	L"���������������!!!\n(��� ������, ��� �����)",		//Volatility!!! (Lower is better)
	L"���� �������� ������",				//Blast Radius
	L"��������� ���� ��������",				//Effect Start Radius
	L"�������� ���� ��������",				//Effect Final Radius
	L"����� ��������",					//Effect Duration
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
	L"����������� ������� ��������\n(��� ������, ��� �����)",		//Item Size Modifier (Lower is better)
	L"����������� ���������",						//Reliability Modifier
	L"����������� ��������\n(��� ������, ��� �����)",			//Loudness Modifier (Lower is better)
	L"�������� �������",							//Hides Muzzle Flash
	L"����������� �����",							//Bipod Modifier
	L"����������� ��������������",						//Range Modifier
	L"����������� ��������",						//To-Hit Modifier
	L"������ ��������� ���������\n����� ������������",			//Best Laser Range
	L"����������� ������� ������",						//Aiming Bonus Modifier
	L"����������� ������� � ��������",					//Burst Size Modifier
	L"����������� ������ �� ������\n��� �������� c ��������\n(��� ������, ��� �����)",	//Burst Penalty Modifier (Higher is better)
	L"����������� ������ �� ������\n��� �������� ��������\n(��� ������, ��� �����)",	//Auto-Fire Penalty Modifier (Higher is better)
	L"����������� ��",							//AP Modifier
	L"����������� ��\n�� ������� � ��������\n(��� ������, ��� �����)",	//AP to Burst Modifier (Lower is better)
	L"����������� ��\n�� ������� ��� �������\n(��� ������, ��� �����)",	//AP to Auto-Fire Modifier (Lower is better)
	L"����������� �� �� �������\n(��� ������, ��� �����)",			//AP to Ready Modifier (Lower is better)
	L"����������� ��\n�� ������ ��������\n(��� ������, ��� �����)",		//AP to Reload Modifier (Lower is better)
	L"����������� ������ ��������",						//Magazine Size Modifier
	L"����������� �� �� �������\n(��� ������, ��� �����)",			//AP to Attack Modifier (Lower is better)
	L"����������� �����",							//Damage Modifier
	L"����������� �����\n� ������� ���", 					//Melee Damage Modifier
	L"�������� '���'",
	L"�������� '�����'",
	L"�������� '�������'",
	L"�������� '����'",
	L"����������� ����������", // 25
	L"����������� ���������\n����������",
	L"����������� ���������\n���������",
	L"����������� ���������\n��������� ����",
	L"����������� ���������\n��������� �����",
	L"����������� ���������\n��������� ��� ����� ���������", //30
	L"����������� ���������\n��������� � ������",
	L"������� ������� ������\n(��� ������, ��� �����)",		//Tunnel Vision Percentage (Lower is better)
	L"����������� �����������\n��������� ������",				//Minimum Range for Aiming Bonus
};

// HEADROCK: End new tooltip text

//The headers used for the merc's money.

CHAR16 gMoneyStatsDesc[][ 13 ] =
{
	L"���-��",
	L"��������:", //this is the overall balance
	L"���-��",
	L"��������:", //the amount he wants to separate from the overall balance to get two piles of money

	L"�������",
	L"������",
	L"���������",
	L"�����",
};

//The health of various creatures, enemies, characters in the game. The numbers following each are for comment
//only, but represent the precentage of points remaining. 

CHAR16 zHealthStr[][13] =
{
	L"�������",		//	>= 0
	L"��������", 		//	>= 15
	L"����",		//	>= 30
	L"�����",    	//	>= 45
	L"������",    	//	>= 60
	L"�����",     	// 	>= 75
	L"�������",		// 	>= 90
};

STR16	gzMoneyAmounts[6] = 
{ 
	L"1000$",
	L"100$",
	L"10$",
	L"�����",
	L"���������",
	L"�����",
};

// short words meaning "Advantages" for "Pros" and "Disadvantages" for "Cons."
CHAR16		gzProsLabel[10] = 
{
	L"+",
};

CHAR16		gzConsLabel[10] = 
{
	L"-",
};

//Conversation options a player has when encountering an NPC
CHAR16 zTalkMenuStrings[6][ SMALL_STRING_LENGTH ] =
{
	L"���������", 	//meaning "Repeat yourself"
	L"������������",		//approach in a friendly
	L"��������",		//approach directly - let's get down to business
	L"��������",		//approach threateningly - talk now, or I'll blow your face off
	L"����",		
	L"������",
};

//Some NPCs buy, sell or repair items. These different options are available for those NPCs as well.
CHAR16 zDealerStrings[4][ SMALL_STRING_LENGTH ]=
{
	L"������/�������",
	L"������",
	L"�������",
	L"�������������",
};

CHAR16 zDialogActions[1][ SMALL_STRING_LENGTH ] = 
{
	L"�� �������",
};


//These are vehicles in the game.

STR16 pVehicleStrings[] =
{
 L"���������",
 L"������", // a hummer jeep/truck -- military vehicle
 L"������",
 L"����",
 L"����",
 L"��������",
};

STR16 pShortVehicleStrings[] =
{
	L"������",
	L"������",			// the HMVV
	L"������",
	L"����",
	L"����",
	L"����.", 				// the helicopter
};

STR16	zVehicleName[] =
{
	L"���������",
	L"������",		//a military jeep. This is a brand name.
	L"������",			// Ice cream truck
	L"����",
	L"����",
	L"��������", 		//an abbreviation for Helicopter
};


//These are messages Used in the Tactical Screen

CHAR16 TacticalStr[][ MED_STRING_LENGTH ] =
{
	L"��������� ����",
	L"������� ������ ������?",
	
	// CAMFIELD NUKE THIS and add quote #66.
	
	L"%s ��������, ��� ��������� ���� ����������� � �������.",
	
	// The %s is a string from pDoorTrapStrings
	
	L"����� (%s).",
	L"��� ��� �����.",
	L"�����!",
	L"������.",
	L"�����!",
	L"������",
	L"�� ����� ��� �������.",
	L"�����!",
	// The %s is a merc name
	L"� %s ��� ����������� �����",
	L"������� �����������",
	L"�� ����� �� ������� �������.",
	L"�������",
	L"�����",
	L"� ��������",
	L"��������",
	L"����������",
	L"��������",
	L"��� ���� ������. ������?",
	L"��������� �������?",
	L"����...",
	L"����...",
	L"���...",

	// In the next 2 strings, %s is an item name
	
	L"%s �������(�) �� �����.",
	L"%s �����(�) %s.",

	// In the next 2 strings, %s is a name

	L"%s: �������� ������.",
	L"%s: ��� ������ %d.",
	L"���������� ������� ���������������:",  	//in this case, frequency refers to a radio signal
	L"���������� ����� �� ������:",	//how much time, in turns, until the bomb blows
	L"�������� ������� ��������������� �� ������:", 	//in this case, frequency refers to a radio signal
	L"����������� �������?",
	L"������ ����� ����?",
	L"��������� ����� ����� ����?",
	L"����������� ���",

	// In the next string, %s is a name. Stance refers to way they are standing.

	L"�� ������������� ������ ��������� %s?",
	L"���, � ������ ���� �� ����� �������� ���������.",
	L"����� �� ����� ������ ���������.",

	// In the next 3 strings, %s is a name

	L"%s �� ����� �������� ��������� �����.",
	L"%s �� ����� �������� ������ ������.",
	L"%s �� ��������� � ����������� ������.",
	L"���� ���� ������.",
	L"� ��� ��� ������ �������, ���� ���.",	//there's no room for a recruit on the player's team

	// In the next string, %s is a name

	L"%s �����(�).",

	// Here %s is a name and %d is a number

	L"%s ������ �������� $%d.",

	// In the next string, %s is a name

	L"����������� %s?",

	// In the next string, the first %s is a name and the second %s is an amount of money (including $ sign)

	L"������ %s �� %s � ����?",

	// This line is used repeatedly to ask player if they wish to participate in a boxing match. 

	L"������ ����������� � ��������?",

	// In the next string, the first %s is an item name and the 
	// second %s is an amount of money (including $ sign)

	L"������ %s �� %s?",

	// In the next string, %s is a name

	L"%s �������������� ������� %d.",

	// These messages are displayed during play to alert the player to a particular situation

	L"�����",					//weapon is jammed.
	L"������ ����� ������� %s �������.",		//Robot is out of ammo
	L"������� ���� �� ���������.",		//Merc can't throw to the destination he selected

	// These are different buttons that the player can turn on and off.

	L"����� ���������� (|Z)",
	L"����� (|M)",
	L"��������� ��� (|D)",
	L"��������",
	L"�������",
	L"��������� (|P|g|U|p)",
	L"����� ������ (|T|a|b)",
	L"���������/��������� (|J)",
	L"��������/���� (|P|g|D|n)",
	L"��������� (|C|t|r|l)",
	L"���������� ����",
	L"��������� ���� (|�|p|o|�|e|�)",
	L"��������� (|O)",
	L"����� ������� (|B)",
	L"��������/����������� (|L)",
	L"��������: %d/%d\n�������: %d/%d\n������ ���: %s",
	L"�� �?",					//this means "what?"
	L"�������.",					// an abbrieviation for "Continued"
	L"%s ����� ��������.",
	L"%s ����� �������.",
	L"���������: %d/%d\n�������: %d/%d",
	L"����� �� ������",
	L"������� ����� (|S|h|i|f|t |�|p|�|�|e|�)",
	L"�����",
	L"�/�",						//this is an acronym for "Not Applicable."
	L"���������� ���",
	L"��������� ������",
	L"��������������� �����",
	L"������������ ����������",
	L"��������������� ��������",
	L"(�����)",
	L"(�����������)",
	L"(����)",
	L"��������� %s.",	// The %s here is a string from pDoorTrapStrings  ASSUME all traps are female gender
	L"%s ������(�).",
	L"%s: ��������(�) ��� ���� ��������.",
	L"%s ������ �� ����� �����������.",
	L"%s ���������(�).",
	L"%s: ����������� �����.",
	L"���� � �������!",
	L"������ � ���� ������ ���.",
	L"������������ ����� ��������.",
	L"������� �� ������ ������ �� ��������� ����� ���������� �������.",
	L"��������� ������� ���������� �������!",
	L"������",
	L"�������",
	L"���������",
	L"������",
	L"����� �� �������",
	L"��",
	L"������",
	L"��������� ����",
	L"��� ����� ������",
	L"���� � ������",
	L"���� �� �����",
	L"���� ������ ������ �������� ������.",
	L"%s ������� ������.",
	L"������ ����� ��������",
	L"�������� ����� ��������",
	L"������",				//Crow, as in the large black bird
	L"���",
	L"������",
	L"����",
	L"����",
	L"���������� �������� ��, ��� ��� ����� �����?",
	L"����������� ���������� ������� ��������.",
	L"������������ ��������� �������. ������ �������������.",
	L"���� ���������",
	L"���� ������������",
	L"��������/����� ������",		// Help text over the $ button on the Single Merc Panel 
	L"����� �� ��������� � ����������� ������.",
	L"�����",								// Short form of JAMMED, for small inv slots
	L"���� ������������� ����������.",					// used ( now ) for when we click on a cliff
	L"���� ����������. ������ ���������� ������� � ���� ���������?",
	L"������� ������������ ���������.",
	// In the following message, '%s' would be replaced with a quantity of money (e.g. $200)
	L"�� �������� ��������� %s?",
	L"������� ���������� �������?",
	L"����������� ����� ����� �� �������?",
	L"������ ������",
	L"� �������������� ����� ������� ������.",
	L"�������� ��������?",
	L"�� ��������� ���������� ���������.",
	L"������",
	L"������ ����� ������ ������ ����� ���������.",
	L"�� � ���� �� ��������� ��� �������",
	L"���� ��� %s ������������",
	L"���� �����, ����������� ������ ��������, ������� ����� � �����!",
	L"����� ���������.",
	L"����� ��������.",
	L"���-�� � ������ ������� �������� ������� ��� �����.",
	L"���������: %d/%d\n�������: %d/%d",
	L"%s �� ����� %s.",  // Cannot see person trying to talk to
	L"������� �����",
	L"�� �� ������ ��������� ��� ���� ������, ��������������� ��� ���������� �����.",
};

//Varying helptext explains (for the "Go to Sector/Map" checkbox) what will happen given different circumstances in the "exiting sector" interface.
STR16 pExitingSectorHelpText[] =
{
	//Helptext for the "Go to Sector" checkbox button, that explains what will happen when the box is checked.
	L"���� �������, �� ����� ��������� ������� ����� ����� �� ���������.",
	L"���� �������, �� �� ������������� �������� �� ����� �����,\n��� ��� ����������� ������ ��������� �����.",

	//If you attempt to leave a sector when you have multiple squads in a hostile sector.
	L"���� ������ ����������� ������, � �� �� ������ ����� ������.\n�� ������ ����������� � ����, ������ ��� ������� � ����� ������ ������.",

	//Because you only have one squad in the sector, and the "move all" option is checked, the "go to sector" option is locked to on. 
	//The helptext explains why it is locked.
	L"��� ������ ���������� �������� ������� ���� ������,\n����� ����� �������� �������� ������.",
	L"������ ���������� ��������� �� ����� �������,\n�� ������������� �������� �� ����� �����,\n��� ��� �� ����������� ����������� ��������� �����.",

	//If an EPC is the selected merc, it won't allow the merc to leave alone as the merc is being escorted.  The "single" button is disabled.
	L"%s ��������� � ������������� ����� ��������� � �� ����� � �������� �������� ������.",

	//If only one conscious merc is left and is selected, and there are EPCs in the squad, the merc will be prohibited from leaving alone.
	//There are several strings depending on the gender of the merc and how many EPCs are in the squad.
	//DO NOT USE THE NEWLINE HERE AS IT IS USED FOR BOTH HELPTEXT AND SCREEN MESSAGES!
	L"%s �� ����� �������� ������ ����, ��� ��� �� ������������ %s.", //male singular
	L"%s �� ����� �������� ������ ����, ��� ��� ��� ������������ %s.", //female singular
	L"%s �� ����� �������� ������ ����, ��� ��� �� ������������ ������ �� ���������� �������.", //male plural
	L"%s �� ����� �������� ������ ����, ��� ��� ��� ������������ ������ �� ���������� �������.", //female plural

	//If one or more of your mercs in the selected squad aren't in range of the traversal area, then the  "move all" option is disabled,
	//and this helptext explains why.
	L"��� ���� �������� ������ ���� � ������,\n����� ����� ���� ����������� � ����� ����������.",

	L"", //UNUSED

	//Standard helptext for single movement.  Explains what will happen (splitting the squad)
	L"���� �������, �� %s ���������� � ��������\n� ������������� ����� ��������� � ��������� �����.",

	//Standard helptext for all movement.  Explains what will happen (moving the squad)
	L"���� �������, ������ ����� ����������\n� ����� ����������, ������� ���� ������.",

	//This strings is used BEFORE the "exiting sector" interface is created.  If you have an EPC selected and you attempt to tactically
	//traverse the EPC while the escorting mercs aren't near enough (or dead, dying, or unconscious), this message will appear and the
	//"exiting sector" interface will not appear.  This is just like the situation where
	//This string is special, as it is not used as helptext.  Do not use the special newline character (\n) for this string.
	L"%s �������������� ������ ���������� � �� ����� �������� ���� ������ � ��������. ��������� �������� ������ ���� �����, ������ ��� �� ������� �������� ������.",
};



STR16 pRepairStrings[] = 
{
	L"��������", 		// tell merc to repair items in inventory
	L"���� ���", 		// tell merc to repair SAM site - SAM is an acronym for Surface to Air Missile
	L"������", 		// cancel this menu
	L"�����", 		// repair the robot
};


// NOTE: combine prestatbuildstring with statgain to get a line like the example below.
// "John has gained 3 points of marksmanship skill."

STR16 sPreStatBuildString[] =
{
	L"������", 			// the merc has lost a statistic
	L"��������", 		// the merc has gained a statistic
	L"�������",	// singular
	L"������",	// plural
	L"�������",	// singular
	L"������",	// plural
};

STR16 sStatGainStrings[] =
{
	L"��������.",
	L"�����������.",
	L"��������.",
	L"����������.",
	L"��������.",
	L"��������� ����.",
	L"��������.",
	L"��������.",
	L"�����.",
	L"����.",
	L"���������.",
};


STR16 pHelicopterEtaStrings[] =
{
	L"����� ���������:", 			// total distance for helicopter to travel
	L"���������:  ", 			// distance to travel to destination
	L"������:", 			// distance to return from destination to airport
	L"�����:", 		// total cost of trip by helicopter
	L"���:", 			// ETA is an acronym for "estimated time of arrival" 
	L"� ��������� ����������� �������. �������� ��������� ������� �� ��������� ����������!",	// warning that the sector the helicopter is going to use for refueling is under enemy control -> 
  L"���������:",
  L"������� �������� ��� ����� �������?",
  L"��������",
  L"�������",
};

STR16 sMapLevelString[] =
{
	L"����������:", 			// what level below the ground is the player viewing in mapscreen
};

STR16 gsLoyalString[] =
{
	L"����������",	// the loyalty rating of a town ie : Loyal 53%
};


// error message for when player is trying to give a merc a travel order while he's underground.

STR16 gsUndergroundString[] =
{
	L"�� ����� ����� �� ���� � �����������.", 
};

STR16 gsTimeStrings[] =
{
	L"�",				// hours abbreviation
	L"�",				// minutes abbreviation
	L"�",				// seconds abbreviation
	L"�",				// days abbreviation
};

// text for the various facilities in the sector

STR16 sFacilitiesStrings[] =
{
	L"���",	//������ ������� �������
	L"���������",
	L"�����",	//Factory
	L"������",
	L"������� ����",
	L"��������",
	L"����������",		// a field for soldiers to practise their shooting skills
};

// text for inventory pop up button

STR16 pMapPopUpInventoryText[] =
{
	L"���������",
	L"�����",
};

// town strings

STR16 pwTownInfoStrings[] =
{
	L"������",					// 0 // size of the town in sectors
	L"", 						// blank line, required
	L"��������", 					// how much of town is controlled
	L"���", 					// none of this town
	L"����� ������", 				// mine associated with this town
	L"����������",					// 5 // the loyalty level of this town
	L"������", 					// the forces in the town trained by the player
	L"",
	L"������ �������", 				// main facilities in this town
	L"�������", 					// the training level of civilians in this town
	L"���������� ���������",				// 10 // state of civilian training in town
	L"���������", 					// the state of the trained civilians in the town
	L"������� ��������� �����",			// HEADROCK HAM 3.6: The stat of Mobile militia training in town	//Mobile Training
};

// Mine strings

STR16 pwMineStrings[] =
{
	L"�����",						// 0
	L"�������",
	L"������",
	L"������� ���������",
	L"���������������� �����������",
	L"���������",				// 5
	L"�������",
	L"����������",
	L"���� ������",
	L"������",
	L"������� ������",
	L"��� ����",				// 10
	L"��������������",
	L"����������",
//	L"�����.�������",
};

// blank sector strings

STR16 pwMiscSectorStrings[] =
{
	L"��������� ����",
	L"������",
	L"���������� ���������",
	L"����������",
	L"��� ���������",
	L"��",
	L"���",
};

// error strings for inventory

STR16 pMapInventoryErrorString[] =
{
	L"%s ������� ������.",	//Merc is in sector with item but not close enough
	L"������ ������� ����� �����.",  //MARK CARTER
	L"%s ��� ����� �������, � �� ����� ��������� �������.",
	L"�� ����� ��� ��� �������� ��������� ���� � �����.",
	L"�� ����� ��� ��� �������� ����������� ���� �� ����� �� ����������� �����.",
	L"%s ��� ����� �������, � �� ����� �������� �������.",
	L"�� ����� ����� �� �� ������ �������� ������ ��������� �� ������.",
};

STR16 pMapInventoryStrings[] =
{
	L"�������", 			// sector these items are in
	L"����� ���������", 		// total number of items in sector
};


// help text for the user

STR16 pMapScreenFastHelpTextList[] =
{
	L"����� ��������� �������� � ������ �����, ��������� ��� ������ ��� ������ ������ ������������� ����, �������� �� ������� '�������'.",
	L"����� ��������� �������� ������� � ������ ������, �������� � ������� '����'.",
	L"��� ������ ������� ������� ������ �� ������������, ��������� ������ �������.",
	L"�������� ����� ������ ���� ���������� ������. ��� ���� ������� �����, ����� ������ ��������� ������� �� ������������. ������� ������ ������ ���� �� ������� ������� ����� �������������� ����������.",
	L"����� ������� ����� ������ - � ����� ������ ������� ������� 'h'.",
	L"�������� �����",
	L"�������� �����",
	L"�������� �����",
	L"�������� �����",
	L"�� ����������� ������ �� ������� ������� �� ���� ������, ���� �� ��������� � �������. ����� ������������� �� ����� ��������, �������� ������ ������� (������ � ������ ������ ����). ��� ������� ������� �������, ���� ���� ������� �� �������� � �������.",
};

// movement menu text

STR16 pMovementMenuStrings[] =
{
	L"��������� ��������� � ������", 	// title for movement box 
	L"����", 		// done with movement menu, start plotting movement
	L"������", 		// cancel this menu
	L"������",		// title for group of mercs not on squads nor in vehicles
};


STR16 pUpdateMercStrings[] =
{
	L"��!:", 			// an error has occured
	L"���� ��������� �����:", 	// this pop up came up due to a merc contract ending
	L"������� ���������:", // this pop up....due to more than one merc finishing assignments
	L"����� ��������� � ����� ������������:", // this pop up ....due to more than one merc waking up and returing to work
	L"����� ������� �����:", // this pop up ....due to more than one merc being tired and going to sleep
	L"����� ���������� ��������� �:", // this pop up came up due to a merc contract ending
};

// map screen map border buttons help text

STR16 pMapScreenBorderButtonHelpText[] =
{
	L"���������� ������ (|W)",
	L"����� (|M)",
	L"������ � ����� (|T)",
	L"����� ���������� ������������ (|A)",
	L"���� (|I)",
	L"��������� � ����� (|Z)",
};


STR16 pMapScreenBottomFastHelp[] =
{
	L"������ (|L)",
	L"����������� ����� (|E|s|c)",
	L"��������� (|O)",
	L"������ ������� (|+)", 	// time compress more 
	L"������ ������� (|-)", 	// time compress less
	L"���������� ��������� (|�|�|�|�|�|�|� |�|�|�|�|�)\n���������� �������� (|P|g|U|p)", 	// previous message in scrollable list
	L"��������� ��������� (|�|�|�|�|�|�|� |�|�|�|�)\n��������� �������� (|P|g|D|n)", 	// next message in the scrollable list
	L"�������� / ���������\n������ ������� (|�|�|�|�|�|�)",	// start/stop time compression
};

STR16 pMapScreenBottomText[] =
{
	L"������� ������", 	// current balance in player bank account
};

STR16 pMercDeadString[] =
{
	L"%s �����(�)",
};


STR16 pDayStrings[] =
{
	L"����",
};

// the list of email sender names

CHAR16 pSenderNameList[500][128] =
{
	L"",
};
/*
{
	L"������",
	L"Psych Pro Inc.",
	L"������",
	L"Psych Pro Inc.",
	L"����",
	L"R.I.S.",		//5
	L"�����",
	L"����",
	L"����",
	L"������",
	L"����",			//10
	L"������",
	L"������ (����)",
	L"����",
	L"��������",
	L"�����",			//15
	L"����",
	L"�����",
	L"���� (�����������)",
	L"������",
	L"�����",				//20
	L"������",
	L"���",
	L"�����",
	L"���",
	L"����",		//25
	L"����� (�����)",
	L"���",
	L"�������",
	L"�����",
	L"������",		//30
	L"����",
	L"������",
	L"���",
	L"�����",
	L"���",
	L"������",
	L"�����",
	L"�������",
	L"������ ���",
	L"������",
	L"���",
	L"�������",
	L"����",
	L"����",
	L"����",
	//----------
	L"M.I.S. ���������",	
	L"����� ���",
	L"����",
	L"���� ������",
	L"�.I.�.",
};
*/

// next/prev strings

STR16 pTraverseStrings[] =
{
  L"<<",
  L">>",
};

// new mail notify string 

STR16 pNewMailStrings[] =
{
 L"�������� ����� �����...",
};


// confirm player's intent to delete messages

STR16 pDeleteMailStrings[] =
{
 L"������� ������?",
 L"�������, �� ��������?",
};


// the sort header strings

STR16 pEmailHeaders[] =
{
	L"��:",
	L"����:",
	L"����:",
};

// email titlebar text

STR16 pEmailTitleText[] =
{
	L"�������� ����",
};


// the financial screen strings
STR16 pFinanceTitle[] =
{
	L"���������� �����",		//the name we made up for the financial program in the game
};

STR16 pFinanceSummary[] =
{
	L"�����:", 				// credit (subtract from) to player's account
	L"������:", 				// debit (add to) to player's account
	L"��������� ������ �����:",
	L"��������� ������ �����������:",
	L"��������� ������:",
	L"������ �� ����� ���:",
	L"������ ����� �������:",
	L"������ ����������� �� �������:",
	L"������ �� �������:",
	L"������� ������:",
	L"��������� �����:",
	L"��������� ������:", 		// projected balance for player for tommorow
};


// headers to each list in financial screen

STR16 pFinanceHeaders[] =
{
	L"����", 			// the day column
	L"�����", 			// the credits column
	L"������",			// the debits column
	L"��������", 		// transaction type - see TransactionText below
	L"������", 			// balance at this point in time
	L"���.", 			// page number
	L"����", 			// the day(s) of transactions this page displays 
};


STR16 pTransactionText[] =
{
	L"����������� �������",			// interest the player has accumulated so far
	L"��������� �����",
	L"������� �������", 
	L"�����", 				// Merc was hired
	L"������� � ����� ���", 		// Bobby Ray is the name of an arms dealer
	L"������ ����� M.E.R.C.",
	L"%s: ���������.", 		// medical deposit for merc
	L"I.M.P.: ������ �������", 		// IMP is the acronym for International Mercenary Profiling
	L"%s: ������� ���������.", 
	L"%s: ��������� ���������",
	L"%s: ��������� ���������", 				// johnny contract extended
	L"��� %s: ��������� ������������", 
	L"%s: ��������� ���������", 		// insurance claim for merc
	L"1 ����", 				// merc's contract extended for a day
	L"7 ����", 				// merc's contract extended for a week
	L"14 ����", 				// ... for 2 weeks
	L"����� �����", 
	L"", //String nuked
	L"������� �����",
	L"%s: ������� ���. ��������",
	L"%s: ������� ���. ��������",
	L"%s: ���. ������� �������",
	L"%s: ������ �����.",		// %s is the name of the npc being paid
	L"%s ����� ��������.", 			// transfer funds to a merc
	L"%s: ��������� ������.", 		// transfer funds from a merc
	L"%s: ������ ���������.", // initial cost to equip a town's militia
	L"%s ������ ��� ����.",	//is used for the Shop keeper interface.  The dealers name will be appended to the end of the string.
	L"%s ������ �������� �� ����.",
	L"���������� ������� ���������",
	L"��������� ���������", // HEADROCK HAM 3.6		//Facility Use
	L"���������� ���������", // HEADROCK HAM 3.6		//Militia upkeep
};

STR16 pTransactionAlternateText[] =
{
	L"��������� ���", 				// insurance for a merc
	L"%s: �������� ������� �� 1 ����.", 				// entend mercs contract by a day
	L"%s: �������� ������� �� 7 ����.",
	L"%s: �������� ������� �� 14 ����.",
};

// helicopter pilot payment 

STR16 pSkyriderText[] =
{
	L"��������� �������� ��������� $%d", 			// skyrider was paid an amount of money
	L"�� ��� ��� ������ ��������� �������� $%d.", 		// skyrider is still owed an amount of money
	L"�������� ������� �������� ��������.",	// skyrider has finished refueling
	L"",//unused
	L"",//unused
	L"�������� ������� ����� � ������.", // Skyrider was grounded but has been freed
	L"� ��������� �������� ��� ����������. ���� �� ������ ����������� ������ � ���� ������, �������� �� � �������� (������ '������/��������')."
};


// strings for different levels of merc morale

STR16 pMoralStrings[] =
{
	L"�������", 
	L"������",
	L"�����",
	L"������",
	L"������",
	L"����",
};

// Mercs equipment has now arrived and is now available in Omerta or Drassen.

STR16 pLeftEquipmentString[] =
{ 
	L"%s ��������� ���� ���������� � ������ (A9).", 	//%s ����� ����� ���������� ���������� � ������ (A9).
	L"%s ��������� ���� ���������� � �������� (B13).",	//%s ����� ����� ���������� ���������� � �������� (B13).
};

// Status that appears on the Map Screen

STR16 pMapScreenStatusStrings[] =
{
	L"��������",
	L"�������",
	L"������ ���",
	L"���������",	// the condition of the current vehicle (its "health")
	L"������",	// the fuel level of the current vehicle (its "energy")
};


STR16 pMapScreenPrevNextCharButtonHelpText[] =
{
	L"���������� ����\n(|�|�|�|�|�|�|� |�|�|�|�|�)", 			// previous merc in the list
	L"��������� ����\n(|�|�|�|�|�|�|� |�|�|�|�|�|�)", 			// next merc in the list
};


STR16 pEtaString[] =
{
	L"���:", 				// eta is an acronym for Estimated Time of Arrival
};

STR16 pTrashItemText[] =
{
	L"�� ������ ������� �� ������� ���� �������. �������?", 	// do you want to continue and lose the item forever
	L"���� ������� ������� ����� ������. �� ������������� ������ ��������� ���?", // does the user REALLY want to trash this item
};


STR16 pMapErrorString[] = 
{
	L"����� �� ����� ����� �� ����, ����� ���� �� ��������� ����.",

//1-5
	L"������� �������� ����� �� �����������.",
	L"����� �� ����? �� ��� �� ����� �������!",
	L"����� ����� �� ����, �������� ������ ���� ��������� � ����� ��� �������� � ������.",
	L"� ��� ��� ��� �� ������ �����.",	// you have no members, can't do anything 
	L"������� �� ����� ���������.",		// merc can't comply with your order
//6-10
	L"��������� � ������������� ����� ����. ��������� ��� � ���-������ � �����.", // merc can't move unescorted .. for a male
	L"��������� � ������������� ����� ����. ��������� �� � ���-������ � �����.", // for a female
	L"������ ��� �� ������ � �������!",
	L"�������, ������� ���� ������� �������� � ����������.",
	L"������ �� ��������? ������ ����� ���!",	// Cannot give a movement order. Air raid is going on.
//11-15
	L"��������� �� ����? �� � ��� ��� ��� ����!",
	L"�� ������ � ������ �����-����� � ������� %s!",
	L"�� ������ ��� ����� � ������ %s... � ���������� �� ������ �����-�����!", 
	L"", 
	L"���� ��� � %s ���� ���������.",
//16-20
	L"����� � %s ���� ��������� ������. ��� ������� ����� ���������� �� %s � ����.",
	L"���� ����� ��� ������������� ������ %s.",
	L"��� ������� ���� �� ����� ������ �� ����� ��������� ���� ������.",
	L"%s �� ����� �������������� � %s - ��� �����.",
	L"%s �� ����� �������������� � %s - ������� ������� ����������.",
//21-25
	L"����� � %s ���� ��������� �������� ��������!",
	L"������ �������� ������ ��� ��������� �� ���� ��� � %s.",
	L"������ �������� ������ ��� ��������� � %s.",
	L"������ �������� ���� �������� � %s.",
	L"������ �������� ������ ��� ��������� %s.",
//26-30
	L"��� ������� ���� �� ����� ������ �� ����� �����.",
	L"��� ������� ���� �� ����� ������ �� ����� ����������.",
	L"��������� �� ��������, ���� �� �������� ����������.",
	L"%s ������ �� � ��������� ������� ������ � �����������.",
	L"��������� ��� ������ ������ �� ����� ������� � ������ ������.",
//31-35
	L"�� �� ������ ������� ���������� � %s.",
	L"������ ������ �� ����� ���������!",
	L"%s ��-�� ������� ������� �� ����� ����!",
	L"������� ��� ����� �������� �����!",
	L"%s �����(�)!",
//36-40
	L"%s �� ����� ������������� �� %s, ��� ��� ��������� � ��������.",
	L"%s �� ����� ����� � ������ � ���� �������.",
	L"%s �� ����� �������� � %s",
	L"�� �� ������ �������� ������ �������, ���� �� ������� ����� ������!",
	L"��� ������ ����� ��������� ������ �� �������!",
//41-45
	L"�� �� ������ ������������� ��������� �� �����.",
	L"� ������ ���������� ������!",
	L"%s ��� ������� ���� � ���� �� �����.",
	L"�� ���� �� ���������� �� � ��������� ����� ������.",
	L"���� ��� ��������� ��������� �� ����� ������ �� ����� ������ ���������.",
//46-50
	L"���� ��� ��������� ��������� �� ����� ������ ���������.",
	L"������ ������ ����������!",
	L"��������! ����������� ���������� � ����� ������� ����� �� ����� ���� ���������.",
	L"������� ����������� ����� ���������. ��������� �������� � ������� � ������ � ���� �����.",
};


// help text used during strategic route plotting
STR16 pMapPlotStrings[] =
{
	L"��� ��� �������� �� ����� ����������, ����� ����������� ���� ��� �������� �� ������� �������, ����� ���������� ������ ������� �����.",
	L"���� �������� �����������.",
	L"����� ���������� �� ��������.",
	L"���� �������� �������.",
	L"���� ��������.",
};


// help text used when moving the merc arrival sector
STR16 pBullseyeStrings[] =
{
	L"�������� ������, � ������� �������� ��������.",
	L"����� ��������� �������� ��������� � %s.",
	L"�������� ����� ��������� ������. ��������� ������������ �� ���������!",
	L"��������. ������ �������� �� ���������.",
	L"���� ��� %s ����� �� ���������! ����� ������� ���� ���������� � %s.",
};


// help text for mouse regions

STR16 pMiscMapScreenMouseRegionHelpText[] =
{
	L"�������� ���������� (|�|�|�|�)",
	L"�������� �������",
	L"������ ���������� (|�|�|�|�)",
};



// male version of where equipment is left
STR16 pMercHeLeaveString[] =
{
	L"������ �� %s �������� ���� �������� ����� (� %s) ��� ����� � �������� (B13) ����� �������?",
	L"������ �� %s �������� ���� �������� ����� (� %s) ��� ����� � ������ (A9) ����� �������?",
	L"����� ������ � ������� ���� �������� � ������ (�9).",
	L"����� ������ � ������� ���� �������� � �������� (B13).",
	L"%s ����� ������ � ������� ���� �������� � %s.",
};


// female version
STR16 pMercSheLeaveString[] =
{
	L"������ �� %s �������� ���� �������� ����� (� %s) ��� ����� � �������� (B13) ����� �������?",
	L"������ �� %s �������� ���� �������� ����� (� %s) ��� ����� � ������ (A9) ����� �������?",
	L"����� ������ � ������� ���� �������� � ������ (�9).",
	L"����� ������ � ������� ���� �������� � �������� (B13).",
	L"%s ����� ������ � ������� ���� �������� � %s.",
};


STR16 pMercContractOverStrings[] =
{
	L"������������ �����, ��� ��� ��� �������� ��������.", 		// merc's contract is over and has departed
	L"������������ �����, ��� ��� �� �������� ��������.", 		// merc's contract is over and has departed
	L"������, ��� ��� ��� �������� ��� �������.", 		// merc's contract has been terminated
	L"������, ��� ��� �� �������� ��� �������.",		// merc's contract has been terminated
	L"�� ������ M.E.R.C. ������� ����� �����, ��� ��� %s ������.", // Your M.E.R.C. account is invalid so merc left
};

// Text used on IMP Web Pages

STR16 pImpPopUpStrings[] =
{
	L"�������� ��� �������.",
	L"��� �������� � ������ ��� ���������� ����������� ������������. �� �������?",
	L"������� ���������� ��� � ������� ���.",
	L"��������������� ������ ������ ����� ����������, ��� �� �� ������ ��������� ���� ������ ������������.",
	L"������ �� �� ������ ������� ���� �����.",
	L"����� ��������� ������, ����� ����� ����� ��� ���� �� ��� ������ ����� �������.",
	L"������� ��� ������.",
	L"�� ���� ��������� I.M.P.-�������� � �����.",
	L"�� �������� ������������� ���������� I.M.P.-����������.",
	L"� ��� � ������� ��� ���� ��� I.M.P.-��������� ���� �� ����.",
	L"�� �� ������ ��������� ���� ����� I.M.P.-��������.",
	L"����� I.M.P.-�������� ������������� � �������.",
};


// button labels used on the IMP site

STR16 pImpButtonText[] =
{
	L"���������� � ���", 		// about the IMP site
	L"������", 			// begin profiling
	L"�����������", 		//Skills
	L"��������������", 		// personal stats/attributes section
	L"���������", 			// Appearance
	L"�����: %d", 			// the voice selection
	L"������", 			// done profiling
	L"������ �������", 		// start over profiling
	L"��, � ������� ���������� �����.",
	L"��", 
	L"���",
	L"������", 			// finished answering questions
	L"�����", 			// previous question..abbreviated form
	L"������", 			// next question
	L"��.", 			// yes, I am certain 
	L"���, � ���� ������ �����.",	// no, I want to start over the profiling process
	L"��",
	L"���",
	L"�����", 			// back one page
	L"��������", 			// cancel selection
	L"��, ��� �����.",
	L"���, ��� ��� �������.",
	L"�����������", 		// the IMP site registry..when name and gender is selected
	L"������ ������", 		// analyzing your profile results
	L"������",
	L"������ ��������", 			// Character
};

STR16 pExtraIMPStrings[] =
{
	// These texts have been also slightly changed
	L"������, ����� ������������ ��������� � ������ ������� ��������, ������� ���� �����������.",	//With your character traits chosen, it is time to select your skills.
	L"��� ����������, �������� ���� ��������������.",	//To complete the process, select your attributes.
	L"��� ������, ��������� �������� ���������� ��� ����, �����, ������������ � ��������������� ���������.",	//To commence actual profiling, select portrait, voice and colors.
	L"������, ����� �� ��������� ������������ ����� ���������, ������� � ������� ����� ������ �������.",	//Now that you have completed your appearence choice, procced to character analysis.
};

STR16 pFilesTitle[] =
{
  L"�������� ������",
};

CHAR16 pFilesSenderList[255][128];

/*
STR16 pFilesSenderList[] =
{
  L"����� ��������", 		// the recon report sent to the player. Recon is an abbreviation for reconissance
	L"� ������� �1", 		// first intercept file .. Intercept is the title of the organization sending the file...similar in function to INTERPOL/CIA/KGB..refer to fist record in files.txt for the translated title
	L"� ������� �2",	   // second intercept file
	L"� ������� �3",			 // third intercept file
	L"� ������� �4", // fourth intercept file
	L"� ������� �5", // fifth intercept file
	L"� ������� �6", // sixth intercept file
};
*/
// Text having to do with the History Log

STR16 pHistoryTitle[] =
{
	L"������ �������", 
};

STR16 pHistoryHeaders[] =
{
	L"����", 			// the day the history event occurred
	L"���.", 			// the current page in the history report we are in
	L"����", 			// the days the history report occurs over
	L"�������", 			// location (in sector) the event occurred
	L"�������", 			// the event label
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
	L"�����(�) %s �� A.I.M.", 										// merc was hired from the aim site
	L"�����(�) %s �� M.E.R.C.", 									// merc was hired from the aim site
	L"%s �����(�).", 															// merc was killed
	L"�������� ������ M.E.R.C.",				// paid outstanding bills at MERC
	L"������� ������� �� ������ ���������",	
	//6-10
	L"��������������� �������� I.M.P.",
	L"��������� ��������� ��� %s.", 				// insurance contract purchased
	L"%s: c�������� �������� �����������.", 				// insurance contract canceled
	L"������� ��������� %s.", 							// insurance claim payout for merc
	L"%s: �������� ������� �� 1 ����.", 						// Extented "mercs name"'s for a day
	//11-15
	L"%s: �������� ������� �� 7 ����.", 					// Extented "mercs name"'s for a week
	L"%s: �������� ������� �� 14 ����.", 					// Extented "mercs name"'s 2 weeks
	L"�� ������� %s.", 													// "merc's name" was dismissed.
	L"%s ������ �� ���.", 																		// "merc's name" quit.
	L"�������� �������.", 															// a particular quest started
	//16-20
	L"������� ���������.",
	L"���������� �� ������� �������� ������ %s",									// talked to head miner of town
	L"%s ����������(�).",
	L"������� ����� ���-�����",
	L"�������� ����� ���������� � ������ ������.",
	//21-25
	L"%s ����, ����� ����� ����� �� ������ ����.",
	L"����� �������� � %s.",
	L"�����(�) %s.",
	L"������ ������ �� ���������� ������� � ��������.",
	L"������ � ��������!",
	//26-30
	L"� ����� %s �������� ����� ����.",
	L"����� %s ����������.",
	L"����� %s �������.",
	L"����� %s ����� ��������.",
	L"�������� ���������� � ������ �����.",
	//31-35
	L"������ �� ���� - ��������� ������� ������.",
	L"������ �� ���� ������� ��� �������� ��������.",
	L"�������� �������� ����� ���������� ������.",
	L"����� ������� ���-�� � ���� � ���-����.",
	L"�������� �������, ��� �� ���-�� ����� � ������.",
	//36-40
	L"��������� ������ - �������� �����������.",
	L"����������� � ������ ��������� A.I.M., ������!", 
	L"��������� ����, �������� �������.",
	L"�������� �������� �������� �� �������� ������.",
	L"��������� �� ������� ������� �������� �����.",
	//41-45
	L"��� ���������� ��������� ������.",	//�����, ������� ������?
	L"������ ����� ������� ������, ������������ �����.",
	L"��� ������ �� ���.",
	L"������ ��������� ������� ��������.",
	L"��������� �������� ���� �� �������.",
	//46-50
	L"��������� �������, ���������� �� �������.",
	L"��������� �����. �� ������ ��������� ����������.",
	L"��������� ���� �� �������. �� ������� ���������.",
	L"����� ����������� � ����������� � ������ �����.",
	L"������� ������ ���������� � �����.",
	//51-55
	L"����� �� ����� ����� �����������.",
	L"���� ������� �� ������� ��� ��� �����.",
	L"��������� ����������� ������.",
	L"���� ������� ��� ��� ����������� ��������.",
	L"������� ���������, �� ������� ����� � ������.",
	//56-60
	L"���� �������� ������ ���������, ���� ����� ������.",
	L"���� ������ �����.",
	L"���� ������ ������ � ����� ���-����.",
	L"%s: ������ � ��� ��� ������.",
	L"%s: �������� � ��� ��� ������.",
	//61-65
	L"%s: ��������������� � ��� ��� ������.",	//��������������� �� ���?
	L"� ����������� ����� ������� ���� �����.",
	L"�������� ������, ��������� ������.",
	L"������� �������� ��� ��������",				//ENEMY_INVASION_CODE
	L"������ ����� �����",
	//66-70
	L"�������� ���������",							//ENEMY_ENCOUNTER_CODE
	L"����������� ������",						//ENEMY_AMBUSH_CODE
	L"��������� �� ������",
	L"����� �����������!",			//ENTERING_ENEMY_SECTOR_CODE
	L"�������� �����!",
	//71-75
	L"����� ������",			//CREATURE_ATTACK_CODE
	L"�����-������ ���������� ��� �����.",			//BLOODCAT_AMBUSH_CODE
	L"��� �����-������ �����",
	L"%s ��� ����(�).",
	L"������ ������� ������ ����������.",
	L"������ ����.",
	L"%s ����(�) ����� �������.",
};

STR16 pHistoryLocations[] =
{
	L"�/�",						// N/A is an acronym for Not Applicable
};

// icon text strings that appear on the laptop

STR16 pLaptopIcons[] =
{
	L"�����",
	L"�����",
	L"�������",
	L"�������",
	L"������",
	L"������",
	L"���������",
	L"sir-FER 4.0",			// our play on the company name (Sirtech) and web surFER
};

// bookmarks for different websites
// IMPORTANT make sure you move down the Cancel string as bookmarks are being added

STR16 pBookMarkStrings[] =
{
	L"A.I.M.",
	L"����� ���",
	L"I.M.P.",
	L"�.�.R.�.",
	L"��������",
	L"�����",
	L"���������",
	L"������",
};

STR16 pBookmarkTitle[] =
{
	L"��������",
	L"����� ��� ���� ����� ������� ������ ������� ����.",
};

// When loading or download a web page

STR16 pDownloadString[] =
{
	L"��������",
	L"����������",
};

//This is the text used on the bank machines, here called ATMs for Automatic Teller Machine

STR16 gsAtmSideButtonText[] =
{
	L"OK",
	L"�����", 			// take money from merc
	L"����", 			// give money to merc
	L"������", 			// cancel transaction
	L"�����.", 			// clear amount being displayed on the screen
};

STR16 gsAtmStartButtonText[] =
{
	L"��������� $", 		// transfer money to merc -- short form
	L"���������", 			// view stats of the merc
	L"����������", 			// view the inventory of the merc
	L"��������",
};

STR16 sATMText[ ]=
{
	L"��������� ��������?", 		// transfer funds to merc?
	L"�������?", 			// are we certain?
	L"������ �����", 		// enter the amount you want to transfer to merc
	L"������� ���", 		// select the type of transfer to merc
	L"�� ������� �����", 	// not enough money to transfer to merc
	L"����� ������ ���� ������ $10", // transfer amount must be a multiple of $10
};

// Web error messages. Please use foreign language equivilant for these messages. 
// DNS is the acronym for Domain Name Server
// URL is the acronym for Uniform Resource Locator

STR16 pErrorStrings[] =
{
	L"������",
	L"������ �� ����� ������ DNS.",	
	L"��������� ����� � ���������� ��� ���.",
	L"OK", //��������� ����� �������� ������ �������.
	L"����� ���������� � ��������.",
};


STR16 pPersonnelString[] =
{
	L"������:", 			// mercs we have
};


STR16 pWebTitle[ ]=
{
	L"sir-FER 4.0",		// our name for the version of the browser, play on company name
};


// The titles for the web program title bar, for each page loaded

STR16 pWebPagesTitles[] =
{
	L"�.I.M.",
	L"A.I.M. ������",
	L"A.I.M. ��������",		// a mug shot is another name for a portrait
	L"A.I.M. ����������",
	L"A.I.M.",
	L"A.I.M. �������",
	L"A.I.M. �������",
	L"A.I.M. �������",
	L"A.I.M. ������",
	L"M.E.R.C.",
	L"M.E.R.C. �����",
	L"M.E.R.C. �����������",
	L"M.E.R.C. ����������",
	L"����� ���",
	L"����� ��� - ������",
	L"����� ��� - ����������",
	L"����� ��� - �����",
	L"����� ��� - ������",					//misc is an abbreviation for miscellaneous
	L"����� ��� - ���� �/�.",
	L"����� ��� - �������� �����",
	L"I.M.P.",
	L"I.M.P.",
	L"\"����� �� ����� ����\"",
	L"\"����� �� ����� ����\" - �������",
	L"\"����� �� ����� ����\" - ����� ������",
	L"\"����� �� ����� ����\" - ��������",
	L"��������� ������: ������, ����� � ������",
	L"����������",
	L"��������",
	L"�����������",
	L"���������� ������ �������������",
	L"",
	L"����� �� ������.",
	L"����� ��� - ��������� �����������",
	L"",
	L"",
};

STR16 pShowBookmarkString[] =
{
	L"���������",
	L"�������� ��� ��� �� ������ \"�����\" ��� ����������� ���� ������.",
};

STR16 pLaptopTitles[] =
{
	L"�������� ����",
	L"�������� ������",
	L"��������",
	L"���������� �����",
	L"������",
};

STR16 pPersonnelDepartedStateStrings[] =
{
	//reasons why a merc has left.
	L"����� � ���",
	L"������",
	L"������",
	L"����� �����",
	L"�������� �����",
	L"�����",
};
// personnel strings appearing in the Personnel Manager on the laptop

STR16 pPersonelTeamStrings[] =
{
	L"� �������",
	L"��������",
	L"������� �� ����:",
	L"������ �������:",
	L"������ �������:",
	L"������� � ����:",
	L"�������:",
	L"������:",
};


STR16 pPersonnelCurrentTeamStatsStrings[] =
{
	L"������",
	L"�������",
	L"������",
};


STR16 pPersonnelTeamStatsStrings[] =
{
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
	L"���",
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
	L"��������",
};

// text that appears on the update panel buttons

STR16 pUpdatePanelButtons[] =
{
	L"�����",
	L"����",
};

// Text which appears when everyone on your team is incapacitated and incapable of battle

CHAR16 LargeTacticalStr[][ LARGE_STRING_LENGTH ] =
{
	L"�� ��������� ��������� � ���� �������!",
	L"��������, �� ��������� ��������� �������, ������ ���� �� �������!",
	L"���� ����� ��������� � ���� (��������� ��� ��������)!",
	L"���� ����� ��������� � ����.",
};


//Insurance Contract.c
//The text on the buttons at the bottom of the screen.

STR16			InsContractText[] = 
{ 
	L"�����",
	L"������",
	L"��",
	L"��������",
};



//Insurance Info
// Text on the buttons on the bottom of the screen

STR16		InsInfoText[] = 
{ 
	L"�����", 
	L"������",
};



//For use at the M.E.R.C. web site. Text relating to the player's account with MERC

STR16			MercAccountText[] = 
{
	// Text on the buttons on the bottom of the screen
	L"������ �����",
	L"� ������", 
	L"����� �����:",
	L"�������",
	L"����",
	L"������",
	L"���������",
	L"�����:",
	L"�� ������������� ������ � ������� %s?",		//the %s is a string that contains the dollar amount ( ex. "$150" )
};

// Merc Account Page buttons
STR16			MercAccountPageText[] = 
{
	// Text on the buttons on the bottom of the screen
	L"�����",
	L"������",
};

//For use at the M.E.R.C. web site. Text relating a MERC mercenary


STR16			MercInfo[] =
{
	L"��������",
	L"�����������",
	L"��������",
	L"����",
	L"���������",
	L"���������",
	L"������� �����",
	L"��������",
	L"��������",
	L"����������",
	L"��������",

	L"�����",
	L"������",
	L"������",
	L"�������������� ����������",
	L"� ������",
	L"�����",
	L"O��a�a",
	L"� ����",
	L"�����",

	L"������, �� ��������� ������ ����� 18 ���������, � ��� �����������.",
	L"����������",
};



// For use at the M.E.R.C. web site. Text relating to opening an account with MERC

STR16			MercNoAccountText[] =
{
	//Text on the buttons at the bottom of the screen
	L"������� ����",
	L"������",
	L"�� ��� �� ������������������. ������� ������� ����?",
};


// For use at the M.E.R.C. web site. MERC Homepage

STR16			MercHomePageText[] =
{
	//Description of various parts on the MERC page
	L"���� �. �����, ���������� � ������",
	L"������� ����",
	L"�������� �����",
	L"�������� ������",
	// The version number on the video conferencing system that pops up when Speck is talking
	L"Speck Com v3.2",
};

// For use at MiGillicutty's Web Page.

STR16	sFuneralString[] =
{
	L"���������� ��������� �������������: ������� ������ � ������� ������� � 1983.",
	L"�������� �� ��������� � ������ ������� �.I.�. - ������ ������������� \"������\", ���������� �� ����� �������.",
	L"��� ����� ������ ������������ ������ � ������, ������� ��, ��� �����, ������ �� �������.",
	L"���������� ��������� ������������� ���������� ������� ������ ���������� ����� - �� �������, � ������� ����� ���������, �� �������������� ������ ������������ ��������.",
	L"���������� ��������� ������������� ������� ��� � ����� ������������� ��������� � �����.",

	// Text for the various links available at the bottom of the page
	L"�������� ������",
	L"��������� ��� � ������",
	L"������ �� ��������",
	L"������ � ���������� �������",
	L"���������� �������",

	// The text that comes up when you click on any of the links ( except for send flowers ).
	L"� ���������, ��� ���� �� ��������, � ����� � ������� � �����. �� ����������� ���������� ������ ����� ��������� ��������� � ������ ������ ��������. ���� ������ ���������.",
	L"�� �������� ����������� ��� � ��� ������� �����. �������� ���.",
};

// Text for the florist Home page

STR16			sFloristText[] = 
{
	//Text on the button on the bottom of the page

	L"�������",

	//Address of United Florist

	L"\"�� ������� ��� ����� ��� ������!\"",
	L"1-555-SCENT-ME",
	L"333 NoseGay Dr,Seedy City, CA USA 90210",
	L"http://www.scent-me.com",

	// detail of the florist page

	L"�� �������� ������ � ����������!",
	L"����������� �������� �� ��������� ���� ����������� � ����� ������ ����. ���� ��������� �����������.",
	L"����������� ����� ������ ���� � ����!",
	L"�������� ��� ������� ����� �������� ������� � �������� 10 ���������� ���.",
	L"\"�������� �����\", ���������� ������ � ������� � 1981 �.",
	L"���� �������, ������ ������ ����������������, ������� ��� ����� � ������� 10 ���� �� ��������� ������. ����� ������ � ������� ������!",
	L"��������� ��� ������������� ���� ��������� ��������.",
	L"����� ����, ��������� �� ���� ���� ��������, ��� ������� ��� �������� ����� � ����� ����.",
	L"� ���������, ���� � ��� ��� ����� ������, �� ������ �������� ��, ��� ��� ����!",
};



//Florist OrderForm

STR16			sOrderFormText[] = 
{
	//Text on the buttons

	L"�����",
	L"�������",
	L"������",
	L"�������",

	L"�������� ������:",
	L"����:",
	L"����� ������:",
	L"���������",
	L"������",
	L"��� ������ � ��� �����",
	L"����� ��������",
	L"�������������",
	L"������� ����� ($10)",
	L"������ ���� ($20)",
	L"������� ����� ($10)",
	L"��������� ����� (���� ����) ($10)",
	L"����� ������������:",
	L"����� ���������� ������� ��������, ������������ ��������� � 75 ��������.",
	L"...��� �������� ���� ��",

	L"����������� ��������",
	L"���������� � �����",

	//The text that goes beside the area where the user can enter their name

	L"��������:",
};




//Florist Gallery.c

STR16		sFloristGalleryText[] =
{
	//text on the buttons

	L"�����",	//abbreviation for previous
	L"������",	//abbreviation for next

	L"�������� �����, ������� ������ �������.",
	L"����������: ���� ��� ����� ������� ������� ��� ��������� ����� - ��������� ��� $10.",

	//text on the button

	L"� ������",
};

//Florist Cards

STR16			sFloristCards[] =
{
	L"�������� �����, ������� ����� ��������� �� ��������.",
	L"�����",
};



// Text for Bobby Ray's Mail Order Site

STR16			BobbyROrderFormText[] = 
{
	L"����� ������",		//Title of the page
	L"���",					// The number of items ordered
	L"��� (%s)",			// The weight of the item
	L"��������",			// The name of the item
	L"���� 1 ����",			// the item's weight
	L"�����",				// The total price of all of items of the same type
	L"���������",			// The sub total of all the item totals added
	L"��� (��. ����� ��������)",		// S&H is an acronym for Shipping and Handling 
	L"�����",				// The grand total of all item totals + the shipping and handling
	L"����� ��������",
	L"�������� ��������",	// See below
	L"���� (�� %s.)",		// The cost to ship the items
	L"��������-��������",	// Gets deliverd the next day
	L"2 ������� ���",		// Gets delivered in 2 days
	L"������� ��������",	// Gets delivered in 3 days
	L"��������",//15			// Clears the order page
	L"��������",			// Accept the order
	L"�����",				// text on the button that returns to the previous page
	L"� ������",			// Text on the button that returns to the home page
	L"* - ����, ������ � ������������",		// Disclaimer stating that the item is used
	L"�� �� ������ ��� ��������.",		//20	// A popup message that to warn of not enough money
	L"<�� �������>",					// Gets displayed when there is no valid city selected
	L"�� ������������� ������ ��������� ���� � %s?",		// A popup that asks if the city selected is the correct one
	L"��� �����**",			// Displays the weight of the package
	L"** ���. ���",			// Disclaimer states that there is a minimum weight for the package
	L"������",
};


STR16			BobbyRFilter[] =
{
	// Guns
	L"�������",
	L"���������",
	L"���.������.",
	L"��",
	L"��������",
	L"��.��������",
	L"��.��������",
	L"��������",
	L"�����",

	// Ammo
	L"���������",
	L"���.������.",
	L"��",
	L"��������",
	L"��.��������",
	L"��.��������",
	L"��������",
	L"�����",

	// Used
	L"������",
	L"�����",
	L"�����.�-��",
	L"������",

	// Armour
	L"�����",
	L"������",
	L"�����",
	L"��������",

	// Misc
	L"�������",
	L"���������.",
	L"��������",
	L"�������",
	L"�����",
	L"�������",
	L"������",
	L"��������",
	L"�����.�-��",
	L"������",
};


// This text is used when on the various Bobby Ray Web site pages that sell items

STR16			BobbyRText[] = 
{
	L"��������",		// Title
	// instructions on how to order
	L"������� �� �����. ����� ������ - ��������, ������ ������ - ���������. ����� ���� ��� �������� �����, �������� �����.",

	//Text on the buttons to go the various links

	L"�����",
	L"������",
	L"�������",
	L"�����",
	L"������",		//misc is an abbreviation for miscellaneous
	L"�/�",
	L"�����",
	L"����� ������",
	L"� ������",

	//The following 2 lines are used on the Ammunition page.  
	//They are used for help text to display how many items the player's merc has
	//that can use this type of ammo

	L"� ����� ������� ����",
	L"������, ������������ ���� ��� �����������",

	//The following lines provide information on the items

	L"���:",			// Weight of all the items of the same type
	L"���.:",			// the caliber of the gun
	L"���:",			// number of rounds of ammo the Magazine can hold
	L"����:",			// The range of the gun
	L"����:",			// Damage of the weapon
	L"����:",			// Weapon's Rate Of Fire, acronym ROF
	L"����:",			// Cost of the item
	L"�����:",			// The number of items still in the store's inventory
	L"���� � ������:",	// The number of items on order
	L"����:",			// If the item is damaged
	L"���:",			// the Weight of the item
	L"�����:",			// The total cost of all items on order
	L"* %% �� ������",	// if the item is damaged, displays the percent function of the item

	//Popup that tells the player that they can only order 10 items at a time
	
	L"׸��! � ��� ����� ����� ������ �� ����� 10 ������� ��� ������ ������. ���� �� ������ �������� ������ (� �� ��������, �� ������), �� ��������� ��� ���� ����� � ������� ���� ��������� �� ����������.", 

	// A popup that tells the user that they are trying to order more items then the store has in stock

	L"��������, �� ������� ������ ��� �� ������. ���������� ��������� �����.",

	//A popup that tells the user that the store is temporarily sold out

	L"��������, �� ������� ������ ���� ��� �� ������.",

};


// Text for Bobby Ray's Home Page

STR16			BobbyRaysFrontText[] =
{
	//Details on the web site

	L"����� �� ������� ������ � �������� ������� ������",
	L"�� ������� ��� ����, ��� ����� ��� ������ ��� �����������",
	L"���� �/�",

	//Text for the various links to the sub pages

	L"������",
	L"������",
	L"����������",
	L"�����",

	//Details on the web site

	L"���� � ��� ����-�� ���, �� ����� ��� �����!",
	L"� ����������",
};



// Text for the AIM page.
// This is the text used when the user selects the way to sort the aim mercanaries on the AIM mug shot page

STR16			AimSortText[] =
{
	L"�.I.M. ������",		// Title
	// Title for the way to sort
	L"����������:",

	// sort by...

	L"����",
	L"����",
	L"��������",
	L"��������",
	L"����������",
	L"��������",

	//Text of the links to other AIM pages

	L"�������� ���������� ���������",
	L"����������� ���������� � ���������",
	L"����������� �������� ������� A.I.M.", 

	// text to display how the entries will be sorted

	L"�� �����������",
	L"�� ��������",
};


//Aim Policies.c
//The page in which the AIM policies and regulations are displayed

STR16		AimPolicyText[] =
{
	// The text on the buttons at the bottom of the page

	L"�����",
	L"� ������", 
	L"����������",
	L"������",
	L"�� ��������",
	L"��������",
};



//Aim Member.c
//The page in which the players hires AIM mercenaries

// Instructions to the user to either start video conferencing with the merc, or to go the mug shot index

STR16			AimMemberText[] =
{
	L"����� ������ ����",
	L"����� ��������� � ������.",
	L"������ ������ ����",
	L"����� � ������������.",
};

//Aim Member.c
//The page in which the players hires AIM mercenaries

STR16			CharacterInfo[] =
{
	// The various attributes of the merc

	L"��������",
	L"�����������",
	L"��������",
	L"����",
	L"���������",
	L"���������",
	L"������� �����",
	L"��������",
	L"��������",
	L"����������",
	L"��������",

	// the contract expenses' area

	L"�������",
	L"����",
	L"1 ����",
	L"7 ����",
	L"14 ����",

	// text for the buttons that either go to the previous merc, 
	// start talking to the merc, or go to the next merc

	L"<<",
	L"���������",
	L">>",

	L"�������������� ����������",		// Title for the additional info for the merc's bio
	L"����������� ������",				// Title of the page
	L"����������:",						// Displays the optional gear cost
	L"������.",				//"gear",	//tais: Displays the optional gear cost in nsgi, this moved and can have only a small room, so just make it "gear" without extra's
	L"��������� ���. ��������",			// If the merc required a medical deposit, this is displayed
	L"����� 1",				// Text on Starting Gear Selection Button 1
	L"����� 2",				// Text on Starting Gear Selection Button 2
	L"����� 3",				// Text on Starting Gear Selection Button 3
	L"����� 4",				// Text on Starting Gear Selection Button 4
	L"����� 5",				// Text on Starting Gear Selection Button 5
};


//Aim Member.c
//The page in which the player's hires AIM mercenaries

//The following text is used with the video conference popup

STR16			VideoConfercingText[] =
{
	L"����� ���������:",				//Title beside the cost of hiring the merc

	//Text on the buttons to select the length of time the merc can be hired

	L"1 ����",
	L"7 ����",
	L"14 ����",

	//Text on the buttons to determine if you want the merc to come with the equipment 

	L"��� ����������",
	L"�� �����������",

	// Text on the Buttons

	L"��������",			// to actually hire the merc
	L"������",				// go back to the previous menu
	L"������",				// go to menu in which you can hire the merc
	L"�����",				// stops talking with the merc
	L"�������",
	L"���������",			// if the merc is not there, you can leave a message 

	//Text on the top of the video conference popup

	L"���������������� �",
	L"�����������. . .",

	L"+ ���������"			// Displays if you are hiring the merc with the medical deposit
};



//Aim Member.c
//The page in which the player hires AIM mercenaries

// The text that pops up when you select the TRANSFER FUNDS button

STR16			AimPopUpText[] =
{
	L"���������� ����������� ������",	// You hired the merc
	L"������ ��������� ��������",		// Player doesn't have enough money, message 1
	L"�� ������� �������",				// Player doesn't have enough money, message 2

	// if the merc is not available, one of the following is displayed over the merc's face

	L"�� �������",
	L"����������, �������� ���������",
	L"���������",

	//If you try to hire more mercs than game can support

	L"� ��� ��� ������ ������� �� ���������.",

	L"������������",
	L"��������� ��������� �� �������������",
};


//AIM Link.c

STR16			AimLinkText[] =
{
	L"A.I.M. ������",	//The title of the AIM links page
};



//Aim History

// This page displays the history of AIM

STR16			AimHistoryText[] =
{
	L"A.I.M. �������",			//Title

	// Text on the buttons at the bottom of the page

	L"�����",
	L"� ������", 
	L"A.I.M. �������",
	L"������",
};


//Aim Mug Shot Index

//The page in which all the AIM members' portraits are displayed in the order selected by the AIM sort page.

STR16			AimFiText[] =
{
	// displays the way in which the mercs were sorted

	L"����",
	L"����",
	L"��������",
	L"��������",
	L"����������",
	L"��������",

	// The title of the page, the above text gets added at the end of this text

	L"���������� ������� A.I.M. �� �����������, �������� - %s",
	L"���������� ������� A.I.M. �� ��������, �������� - %s",

	// Instructions to the players on what to do

	L"����� ������",
	L"������� ��������",
	L"������ ������",
	L"�������� ����������",

	// Gets displayed on top of the merc's portrait if they are...

	L"�����",
	L"���������",
	L"�� �������",
};



//AimArchives.
// The page that displays information about the older AIM alumni merc... mercs who are no longer with AIM

STR16			AimAlumniText[] =
{
	// Text of the buttons

	L"���. 1",
	L"���. 2",
	L"���. 3",

	L"A.I.M. �������",	// Title of the page

	L"��"			// Stops displaying information on selected merc
};

//AIM Home Page

STR16			AimScreenText[] =
{
	// AIM disclaimers
	
	L"A.I.M. � ������� A.I.M. - ������������������ �� ������ ������� �������� �����.",
	L"��� ��� � �� ����� ��������� ���.",
	L"(�) 1998-1999 A.I.M., Ltd. ��� ����� ��������.",

	//Text for an advertisement that gets displayed on the AIM page

	L"\"����� �� ����� ����\"",
	L"\"�� ������� ��� ����� ��� ������!\"",
	L"������ ��� ����",
	L"...� ������ ���",
	L"���� � ��� ��� ������ ������, �� �� ��� � �� �����.",
};


//Aim Home Page

STR16			AimBottomMenuText[] =
{
	//Text for the links at the bottom of all AIM pages
	L"� ������",
	L"��������",
	L"�����",
	L"�������",
	L"����������",
	L"������",
};



//ShopKeeper Interface
// The shopkeeper interface is displayed when the merc wants to interact with 
// the various store clerks scattered through out the game.

STR16 SKI_Text[ ] = 
{
	L"��������� ������",	//Header for the merchandise available
	L"���.",				//The current store inventory page being displayed
	L"����� ����",			//The total cost of the the items in the Dealer inventory area
	L"����� ��������",		//The total value of items player wishes to sell
	L"������",				//Button text for dealer to evaluate items the player wants to sell
	L"�������",				//Button text which completes the deal. Makes the transaction.
	L"����",				//Text for the button which will leave the shopkeeper interface.
	L"���� �������",		//The amount the dealer will charge to repair the merc's goods
	L"1 ���",				// SINGULAR! The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"%d �����",			// PLURAL!   The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"��������",			// Text appearing over an item that has just been repaired by a NPC repairman dealer
	L"��� ��� ������ ������ ����.",	//Message box that tells the user there is no more room to put there stuff
	L"%d �����",			// The text underneath the inventory slot when an item is given to the dealer to be repaired
	L"��������� ������� �� �����.",
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
	L"OK",					//Transfer the money
	L"�����",				//Take money from the player
	L"����",				//Give money to the player
	L"������",				//Cancel the transfer
	L"��������",			//Clear the money display
};


//Shopkeeper Interface
STR16	gzSkiAtmText[] = 
{	

	// Text on the bank machine panel that....
	L"�������� ���",			//tells the user to select either to give or take from the merc
	L"������� �����",			//Enter the amount to transfer
	L"��������� ������ �����",	//Giving money to the merc
	L"������� ������ � �����",	//Taking money from the merc
	L"������������ �������",	//Not enough money to transfer
	L"������",					//Display the amount of money the player currently has
};


STR16	SkiMessageBoxText[] =
{
	L"������� ����� �� ����� %s, ����� ������� �������?",
	L"������������ �������. �� ������� %s",
	L"������� ����� �� ����� %s, ����� �������� ������ ���������?",
	L"��������� �������� ������� �������",
	L"��������� �������� �������� ��������� ��������",
	L"��������� ������",
	L"������� ������",
};


//OptionScreen.c

STR16	zOptionsText[] = 
{
	//button Text
	L"���������",
	L"���������",
	L"�����",
	L">>",
	L"<<",
	L"������",

	//Text above the slider bars
	L"�����",
	L"����",
	L"������",

	//Confirmation pop when the user selects..
	L"����� �� ���� � ��������� � ������� ����?",

	L"���������� ������� ��� \"����\", ��� \"��������\"",
};


//SaveLoadScreen 
STR16			zSaveLoadText[] = 
{
	L"���������",
	L"���������",
	L"������",
	L"���������� �������",
	L"�������� �������",

	L"���� ������� ���������",
	L"������ ���������� ����!",
	L"���� ������� ���������",
	L"������ �������� ����!",

	L"��� ���������� ���� ������� ���� ������� ����. ������ �����, ��������� ��� �� �������. ��� ����� ����������?",
	L"�������� ����� ���������� ����������. ������� �� �������?",

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.
#ifdef JA2BETAVERSION
	L"������ ���������� ���� ���� ��������. ������ �������� ���� ��� ��������� ������� � �����-���� ������. �������� ���������?",
#else
	L"������� ��������� ���������� ���� ���������� ������. ������������� �������� ��� � ���������?",
#endif

	//Translators, the next two strings are for the same thing.  The first one is for beta version releases and the second one
	//is used for the final version.  Please don't modify the "#ifdef JA2BETAVERSION" or the "#else" or the "#endif" as they are
	//used by the compiler and will cause program errors if modified/removed.  It's okay to translate the strings though.
#ifdef JA2BETAVERSION
	L"������ ���� � ������ ���������� ���� ��������. ������ �������� ���� ��� ��������� ������� � �����-���� ������. �������� ���������?",
#else
	L"������� ��������� ���������� ���� ���������� ������. ������������� �������� ��� � ���������?",
#endif

	L"�� ������ �������� ���� �� ������������ ���������� #%d?",
	L"������ ��������� ���� �� ���������� #",


	//The first %d is a number that contains the amount of free space on the users hard drive,
	//the second is the recommended amount of free space.
	L"� ��� ������������� ��������� ����� �� ������� �����. ������ �������� %d ��, � ��������� %d �� ���������� ����� ��� JA.",

	L"��������...",		//When saving a game, a message box with this string appears on the screen

	L"����������",
	L"��������",
	L"���",
	L"��",

	L"�������� ����������",
	L"���������� �����",
	L"����������� ����� ���",
	L"����������",
	L"�������",
	L"��������",
	L"�� � �����",

	L"����������� ���� ���� ������ � ������ \"������ ���������\", ���� ����� �� ������� ��� ���������� ������ 640�480. �������� ���������� � ��������� ���� �����.",
	L"�������� ����, ������� � ������ \"������ ���������\", ����������. ���������� � Ja2.ini ������� ����� 'Data-1.13' � ��������� �������.",
};


//MapScreen
STR16		zMarksMapScreenText[] =
{
	L"������� �����",
	L"� ��� ��� ����������. ����� ��� ���������, ��� ����� �������� �� ���� ������� �������.",
	L"����� � �����",
	L"������� �����������", 
	L"%s �� ��������� � ������.", 
	L"%s �� ����� � �� ����� ���� �����.", 
	L"%s ������� � ��� �� ���������, ������ �������.",
	L"%s ����� ������.",
	L"����� �� ����� ���������, ����� ���� �� ��������� ����.",

	// stuff for contracts
	L"���� � ��� � ���� ������ �� ���������� ���������, �� �� �� ������, ����� �������� ��������� ��������.",
	L"%s: ��������� ��������� �������� %s �� %d �������������� ����. ������� ���������?",
	L"�������� � �������",
	L"����� �������� ������������.",
	
	// other items
	L"������", // people acting a field medics and bandaging wounded mercs 
	L"�������", // people who are being bandaged by a medic 
	L"������", // Continue on with the game after autobandage is complete 
	L"����", // Stop autobandaging of patients by medics now 
	L"��������, ���� ����� ���������� � ���������������� ������.", // informs player this option/button has been disabled in the demo 
	L"%s: ��� ������������.",
	L"%s: ��� �������.",
	L"����� ������������ ������������ ��� ����������.",
	L"� %s ������������ ���������� ����������.",
	L"� �������� ������������ ��������.", 
	L"�������� �������� �� �����������",
	L"�������������� �����",
};


STR16 pLandMarkInSectorString[] =
{
	L"����� %d ������� ����-�� � ������� %s.",
};

// confirm the player wants to pay X dollars to build a militia force in town
STR16 pMilitiaConfirmStrings[] =
{
	L"���������� ������ ���������� ����� ������ $", // telling player how much it will cost
	L"����������� ������?", // asking player if they wish to pay the amount requested
	L"�� �� ������ ���� ����� ���������.", // telling the player they can't afford to train this town
	L"���������� ���������� � %s (%s %d)?", // continue training this town?
	L"���� $", // the cost in dollars to train militia
	L"( �/� )",   // abbreviated yes/no
	L"",	// unused
	L"���������� ��������� � ������� %d ����� ������ $%d. %s", // cost to train sveral sectors at once
	L"� ��� ��� $%d, ����� ���������� � ���������� ���������.",
	L"%s: ��������� �� ����� %d ��������� ����������, ����� ���������� ���������� ���������.",
	L"������ �� �� ������ ����������� ��������� � %s.",
	L"� ��� ��� $%d ����� ����������� ����� ��������� �������������.",
	L"���������� ���������� ���������� ������������� � %s (%s %d)?",
	L"���������� ���������� ������������� � ������� %d �������� � $ %d. %s",
	L"���������� ���������� ������������� ���������� �������� � $",
};

//Strings used in the popup box when withdrawing, or depositing money from the $ sign at the bottom of the single merc panel
STR16	gzMoneyWithdrawMessageText[] = 
{
	L"�� ���� ��� �� ������ ����� �� ����� �� ����� $20 000.",
	L"�� ������ �������� %s �� ���� ����?",
};

STR16	gzCopyrightText[] = 
{
	L"��������� ����� (C) 1999 Sir-Tech Canada Ltd. ��� ����� ��������.",
};

//option Text
STR16		zOptionsToggleText[] = 
{
	L"����",
	L"���������� �����",
	L"��������",
	L"����� � ��������",
	L"������������� ���",
	L"����� � ����������", 
	L"�� ������� ����!",
	L"������ ����� ������", 
	L"�������� ���� ��������",
	L"�������� �������",
	L"���� � �������� �������",
	L"������������� ���/�������",
	L"����������� �������",
	L"���������� ��������� �����",
	L"������ �� ������",
	L"������ �� �����", 
	L"�������� �����",
	L"�������� ����� ��������",
	L"�������� �������",
	L"���������� ������",
	L"�������� ���� ���������",
	L"������ ������� ��� ������",
	L"��������� �����",	//Allow Enemy Taunts
	L"�������� �������� �������",
	L"�������� � �������� �������",
	L"����� �������� ����. ������",
	L"���� ��������� � ���������",
	L"��������� ������ � ������",
	L"��������� �������",
	L"��� �����",
	L"������",
	L"��������� ��� ���������",	//Show Soldier Tooltips
	L"�������������� ������ ���",
	L"���������� ����� ��������",
	L"������ �������� ����������",
	L"��������� �������� ���������",		//Enhanced Description Box
	L"������ ��������� �����",				// add forced turn mode
	L"���������� ����� � ���������",		//Stat Progress Bars	// Show progress towards stat increase
	L"�������� ������� ����",				// Show alternate bullet graphics (tracers)
	L"--��������� ���������--",				// TOPTION_CHEAT_MODE_OPTIONS_HEADER,
	L"�������� �������� ����� ���",			// force all pending Bobby Ray shipments
	L"-----------------",					// TOPTION_CHEAT_MODE_OPTIONS_END
	L"--��������� ���������� ������--",		// an example options screen options header (pure text)
	L"����� ���� ������� ��������",			// failsafe show/hide option to reset all options
	L"� ����� ���� ������ �����?",			// a do once and reset self option (button like effect)
	L"���������� ��������� �����",			//Debug Options in other builds		// allow debugging in release or mapeditor
	L"�������� ���������� ���������",		//DEBUG Render Option group	// an example option that will show/hide other options
	L"���������� Mouse Regions",		//Render Mouse Regions	// an example of a DEBUG build option
	L"-----------------",					// an example options screen options divider (pure text)

	// this is THE LAST option that exists (debug the options screen, doesnt do anything, except exist)
	L"���������_������_��������",	//THE_LAST_OPTION
};

//This is the help text associated with the above toggles.
STR16	zOptionsScreenHelpText[] =
{
	//speech
	L"�������� ��� ���������\n����� �� ����� ��������.",

	//Mute Confirmation
	L"�������� ��� ��������� �������\n������������� ���������� ��������.",

		//Subtitles
	L"�������� ��� ��������� �����������\n��������� �� ����� ��������.",

	//Key to advance speech
	L"���� �������� ��������, �������� ���� �����,\n����� ������ ��������� ������� ����������.",

	//Toggle smoke animation
	L"��������� �������� ����,\n���� �� ��������� ����.",

	//Blood n Gore
	L"��������� ���� �����, ���� ������� �����.",

	//Never move my mouse
	L"���� ���������, �� ������ ������������� ������������\n�� ������ ������������ ���� �������.", 

	//Old selection method
	L"���� ��������, �� ����� �������������� ������ ����� ������ ���������\n(��� ���, ��� ������ � ���������� ���������� ������ Jagged Alliance).",

	//Show movement path
	L"���� ��������, �� � ������ ��������� ������� ����� ������������ ���� ������������\n(���� ���������,  ������� |S|H|I|F|T, ����� ������� ����).",

	//show misses
	L"���� ��������, �� ������ ����� �����������\n���������� ����, ��������� ���� ����.",
	
	//Real Time Confirmation
	L"���� ��������, �� ��� ������� �� ������������ ����� �����������\n��������������, �������������� ������ ���� �� ����� ����������.",

	//Display the enemy indicator
	L"���� ��������, �� �� �������� ��������������,\n����� �������� ����� ����� ��� ���������.",

	//Use the metric system
	L"���� ��������, �� ������������ ����������� ������� ���,\n����� ����� ����������.",

	//Merc Lighted movement
	L"��� ������ ����� �������������� ������ ����� (|G).\n��������� ��� ��������� ��� ��������� ������������������ �������.",

	//Smart cursor
	L"���� ��������, �� ����������� ������� ����� ��������\n������������� �������� ���.",

	//snap cursor to the door
	L"���� ��������, �� ����������� ������� ����� �����\n������������� �������� ��� �� �����.",

	//glow items 
	L"���� ��������, �� ��� �������� ��������������. (|I)",

	//toggle tree tops
	L"���� ��������, �� ������������ ����� ��������. (|T)",

	//toggle wireframe
	L"���� ��������, �� � �����������\n������������� ������������ ������. (|W)",

	L"���� ��������, �� ������ ������������\n������������ � 3D. (|Home )",

	// Options for 1.13
	L"���� ��������, ���� ���������\n������������ ��� ��������.",
	L"���� ��������, ������� �� �����������\n���������� ������ �������� ���������.",
	L"���� ��������, ���� ������ ����� �������������� ���� ��������.",
	L"���� ��������, ���������� ������������ \n����� ��� ������� ����� � ��������� (|Q).",
	L"���� ��������, ���� �� ��������� � ��������� ����� \n��� ����������� ���������� (���� ���� ��� �� �����). \n������ ���� � ��������� ����� - |C|t|r+|X.",	//When ON, the turn based mode will not be entered when sneaking unnoticed and seeing an enemy unless pressing |C|t|r+|X.
	L"���� ��������, |�|�|�|�|�|� �������� ��������� �����.",
	L"���� ��������, ������������ ���� ��������� � ���������.",
	L"���� ��������, ��������� ������ \n������������ � ������� ���������.",
	L"���� ��������, ������������ ������ \n�������� � ��������� ���������.",	
	L"���� ��������, ����� ��� ����� �� ����� ��������.",
	L"���� ��������, ������ ������������ � ����.",
	L"���� ��������, ��� ������� ������ |A|l|t \n� ��������� ������� ���� �� ���������� ������� \n����� �������� �������������� ����������.",
	L"���� ��������, ���� ����� ������������� \n����������� ����� ������� ���� ������.",
	L"���� ��������, �������� �������\n�� ����� ��� ���������� ������������.",
	L"���� ��������, ���� ����� ������������\n������ ������������� �������.",
	L"���� ��������, ����� �������������\n��������� �������� ���������.",
	L"���� �������� � � ������� ������������ ����, \n��������� ����� ����� ������������ \n�� ������ �������� ������� (|C|T|R|L+|S|H|I|F|T+|A|L|T+|T).", // add forced turn mode
	L"���� ��������, �����, \n������� ������ ��������� ����� ���������.",
	L"���� ��������, ������� ���� ����� ����� ��������.",
	L"(text not rendered)TOPTION_CHEAT_MODE_OPTIONS_HEADER",
	L"���� ��������, \n���������� ���� � ����� ��� \n�������� ����������.",	//Force all pending Bobby Ray shipments
	L"(text not rendered)TOPTION_CHEAT_MODE_OPTIONS_END",
	L"(text not rendered)TOPTION_DEBUG_MODE_OPTIONS_HEADER",	// an example options screen options header (pure text)
	L"���� ��������, \n����������� ������� ��������� ����� �������������.",	// failsafe show/hide option to reset all options
	L"�������� ������ ��� ������������� ������ ������� ��������.",	// a do once and reset self option (button like effect)
	L"���� ��������, \n���������� ��������� ����� �������� ��� � ����, \n��� � � ��������� ����.",	// Allows debug options in release or mapeditor builds
	L"���� ��������, ���������� ��������� \n����� �������� � ����� ������.",	//Toggle to display debugging render options
	L"Attempts to display slash-rects around mouse regions",	// an example of a DEBUG build option
	L"(text not rendered)TOPTION_DEBUG_MODE_OPTIONS_END",	// an example options screen options divider (pure text)


	// this is THE LAST option that exists (debug the options screen, doesnt do anything, except exist)
	L"��������� ������ � ������ ��������.",
};


STR16	gzGIOScreenText[] =
{
	L"��������� ������ ����",
#ifdef JA2UB
	L"������� ������� �� �������",	//���� � ���, ��� ����� � ������������ ���� �� ������������� IMP ��������� �� Ja2 � � ����� ���� ��������� ������ ����-���� �� ���������� ��� ������, ������, ������� ������ ��������� ���� �� �������. ������ ����� ���� �������� ��� ��������� �������� ���������� ��������. (������������� �� ����� ������)
	L"���",
	L"��",
#else
	L"�������� ����������",
	L"���",
	L"����",
#endif	
	L"���������� �����",
	L"����������� ������ � ����",
	L"�� ���������",
	L"���� ��������",
	L"������� ���������",
	L"�����",	//�������
	L"�������",	//�������
	L"�������",	//�������
	L"��������",	//����������
	L"������ ����",
	L"������� ����",
	L"����������� ����������",
	L"� ����� �����",
	L"���� � ������",
	L"��������� � ����-������", 
	L"����������� ����� ���",
	L"�������",
	L"�������",
	L"��������",
	L"�� � �����",
	L"��������� / �������",
	L"NOT USED",
	L"NOT USED",
	L"���������",
	L"��������� ���� (��������� ������ �������� ���� �������)",
	// Added by SANDRO
	L"������ IMP ���������",
	L"������",
	L"�����",
	L"���������� IMP ����������",
	L"1",
	L"2",
	L"3",
	L"4",
	L"5",
	L"6",
	L"���� ��������� �� ����������",
	L"���",
	L"��",
#ifdef JA2UB
	L"���� ��� ���� ������",
	L"��������",
	L"��� �����",
#else
	L"����� �����������",
	L"���������",
	L"��� �����",
#endif
	L"���������� ������ ��������",	//Secret Weapon Caches
	L"���������",
	L"�� ���������",
	L"�������� ���������� ����������",	//Progress Speed of Item Choices
	L"����� ��������",
	L"��������",
	L"��������",
	L"������",
	L"����� ������",

	L"������ / ������",
	L"����� / ������",
	L"����� / �����",
};

STR16	gzMPJScreenText[] =
{
	L"������� ����",	//MULTIPLAYER
	L"��������������",	//Join
	L"������� ����",	//Host
	L"������",	//Cancel
	L"��������",	//Refresh
	L"��� ������",	//Player Name
	L"IP �������",	//Server IP
	L"����",	//Port
	L"��� �������",	//Server Name
	L"# Plrs",
	L"������",	//Version
	L"��� ����",	//Game Type
	L"Ping",
	L"������� ��� ������.",
	L"������� ���������� IP �����. \n(������ 84.114.195.239).",
	L"������� ���������� ���� ������� (����������� �������� �� 1 �� 65535).",
};

STR16	gzMPHScreenText[] =
{
	L"��������� ��������� �������",			//HOST GAME
	L"������ ����",					//Start
	L"������� ����",				//Cancel
	L"��� �������",					//Server Name
	L"��� ����",					//Game Type
	L"Deathmatch",
	L"Team Deathmatch",
	L"Co-operative",
	L"���-�� �������",				//Max Players
	L"������ � ������",				//Squad Size
	L"Merc Selection",
	L"��������� �����",				//Random Mercs
	L"����� �������",				//Hired by Player
	L"��������� ������",				//Starting Balance
	L"����� �������� ��� �� ������",		//Can Hire Same Merc
	L"��������� � ������� ������",			//Report Hired Mercs
	L"����� ��� ��������",				//Allow Bobby Rays
	L"������� �� ��������� �������",		//Randomise Starting Edge
	L"������� ��� �������",				//You must enter a server name
	L"���������� ������� ������ ���� � ��������� �� 2 �� 4",		//Max Players must be between 2 and 4
	L"���������� ������ � ������ ������ ���� �� 1-�� �� 6-�",		//Squad size must be between 1 and 6
	L"����� �������",							//Time of Day
	L"����� ������� ������ ���� � 24-� ������� ������� (��:��)",
	L"��������� ������ ������ ���� ����� ������",
	L"��������� �����",							//Damage Multiplier
	L"��������� ����� ������ ���������� � ���������� �� 0 �� 5.",		//Damage Multiplier must be a number between 0 and 5
	L"��������� ����� ����",						//Turn Timer Multiplier
	L"Turn Timer multiplier must be a number between 0 (no timed turns) and 200 (short timed turns)",
	L"������������ ����������� � CO-OP",		//Enable Civilians in CO-OP
	L"����� ������� ��������� (NIV)",
	L"Enforce Maximum AI Enemies",
	L"Sync. MP Clients Directory",
	L"MP Sync. Directory",
	L"������� ���������� ��� ������������� ������������ ������.",
	L"(��� ���������� ���������� ����������� '/' ������ '\\'.)",
	L"��������� ���������� ��� ������������� �� ����������.",
};

STR16 pDeliveryLocationStrings[] =
{
	L"�����",		//Austin, Texas, USA
	L"������",		//Baghdad, Iraq (Suddam Hussein's home)
	L"�������",		//The main place in JA2 that you can receive items.  The other towns are dummy names...
	L"�������",		//Hong Kong, Hong Kong
	L"������",		//Beirut, Lebanon	(Middle East)
	L"������",		//London, England
	L"���-��������",//Los Angeles, California, USA (SW corner of USA)
	L"������",		//Meduna -- the other airport in JA2 that you can receive items.
	L"��������",	//The island of Metavira was the fictional location used by JA1
	L"������",		//Miami, Florida, USA (SE corner of USA)
	L"������",		//Moscow, USSR
	L"���-����",	//New York, New York, USA
	L"������",		//Ottawa, Ontario, Canada -- where JA2 was made!
	L"�����",		//Paris, France
	L"�������",		//Tripoli, Libya (eastern Mediterranean)
	L"�����",		//Tokyo, Japan
	L"��������",	//Vancouver, British Columbia, Canada (west coast near US border)
};

STR16 pSkillAtZeroWarning[] =
{ //This string is used in the IMP character generation.  It is possible to select 0 ability
	//in a skill meaning you can't use it.  This text is confirmation to the player.
	L"�� �������? �������� 0 �������� ���������� ����� ������ ������.",
};

STR16 pIMPBeginScreenStrings[] =
{
	L"( �� 8 �������� )",
};

STR16 pIMPFinishButtonText[ 1 ]=
{
	L"������",
};

STR16 pIMPFinishStrings[ ]=
{
	L"�������, %s", //%s is the name of the merc
};

// the strings for imp voices screen
STR16 pIMPVoicesStrings[] =
{
	L"�����", 
};

STR16 pDepartedMercPortraitStrings[ ]=
{
	L"����� � ���",
	L"������",
	L"������",
};

// title for program
STR16 pPersTitleText[] =
{
	L"�����",
};

// paused game strings
STR16 pPausedGameText[] =
{
	L"����� � ����",
	L"���������� (|P|a|u|s|e)",
	L"����� (|P|a|u|s|e)",
};


STR16 pMessageStrings[] =
{
	L"����� �� ����?",
	L"��",
	L"��",
	L"���",
	L"������",
	L"������",
	L"�������",
	L"��� ��������.", //Save slots that don't have a description.
	L"���� ���������.",
	L"���� ���������.",
	L"QuickSave", //The name of the quicksave file (filename, text reference)
	L"SaveGame",	//The name of the normal savegame file, such as SaveGame01, SaveGame02, etc.
	L"sav",				//The 3 character dos extension (represents sav)
	L"..\\SavedGames", //The name of the directory where games are saved.
	L"����",
	L"����",
	L"��������� �����", //An empty save game slot
	L"����",				//Demo of JA2
	L"����� �����",				//State of development of a project (JA2) that is a debug build
	L"�����",			//Release build for JA2
	L"���",				//Abbreviation for Rounds per minute -- the potential # of bullets fired in a minute.
	L"���",					//Abbreviation for minute.
	L"�",					//One character abbreviation for meter (metric distance measurement unit).
	L"����",				//Abbreviation for rounds (# of bullets)
	L"��",					//Abbreviation for kilogram (metric weight measurement unit)
	L"����",				//Abbreviation for pounds (Imperial weight measurement unit)
	L"� ������",				//Home as in homepage on the internet.
	L"USD",					//Abbreviation to US dollars
	L"�/�",					//Lowercase acronym for not applicable.
	L"��������� ��� ���������� ��� �������� � ������ �����",		//Meanwhile
	L"%s: ������ � ������ %s%s",//30	Name/Squad has arrived in sector A9.  Order must not change without notifying
//SirTech
	L"������",
	L"������ ������ �������� ����",
	L"��� ������ ��������������� ��� �������� ����������, ������� ����� �������� � ����������� ����� ��� � ���������� �����, ����� ������� ALT+S.",
	L"��������",
	L"��������",
	L"� ��� ������������� ��������� �������� ������������. �� ����� ���� ����� %sM� ���������� �����, � ��� Jagged Alliance 2 ��������� %s M�.",
	L"�� A.I.M. ����� ���� %s.", 
	L"%s ����� %s.",		//'Merc name' has caught 'item' -- let SirTech know if name comes after item.
	L"%s ��������� ��������.", //'Merc name' has taken the drug
	L"%s: ����������� ������ � ��������.",//40	'Merc name' has no medical skill.

	//CDRom errors (such as ejecting CD while attempting to read the CD)
	L"�������� ����������� ���������.",
	L"������: CD-ROM ������.",

	//When firing heavier weapons in close quarters, you may not have enough room to do so.
	L"��� �����, ����� ����� ������ �����.",
	
	//Can't change stance due to objects in the way...
	L"������ ������ �������� ��������� ����.",

	//Simple text indications that appear in the game, when the merc can do one of these things.
	L"��������",
	L"�������",
	L"��������",

	L"%s ������� %s.", //"Item" passed to "merc".  Please try to keep the item %s before the merc %s, otherwise, must notify SirTech.
	L"�� ������� �����, ����� �������� %s %s.", //pass "item" to "merc".  Same instructions as above.

	//A list of attachments appear after the items.  Ex:  Kevlar vest ( Ceramic Plate 'Attached )'
	L" �����������]",			// 50

	//Cheat modes
	L"�� � ����� ���� ��� ����?",
	L"����������� ����� �����.",

	//Toggling various stealth modes
	L"����� ���� ����� �����.",
	L"����� ���� ������� �����.",
	L"%s ���� ����� �����.",
	L"%s ���� ������� �����.",

	//Wireframes are shown through buildings to reveal doors and windows that can't otherwise be seen in 
	//an isometric engine.  You can toggle this mode freely in the game.
	L"������ ������ ���.",
	L"������ ������ ����.",

	//These are used in the cheat modes for changing levels in the game.  Going from a basement level to
	//an upper level, etc.  
	L"������ ��������� � ����� ������...",
	L"��� ������ ������...",
	L"������ � ������. ������� %d...",
	L"�������� ������...",

	L".",		// used in the shop keeper inteface to mark the ownership of the item eg Red's gun
	L"����� ���������� ����.",
	L"����� ���������� ���.",
	L"3D ������ ����.",
	L"3D ������ ���.",
	L"������ %d-� �����.",
	L"�� ������� �����, ����� ��������� %s ���������� ������� %s",	//first %s is the mercs name, the seconds is a string containing the salary
	L"���",	//Skip
	L"%s �� ����� ���� � ��������.",
	L"���� ���������� ��� ������� ��� ��������� SaveGame99.sav. ���� ����������, ������������ ��� � SaveGame01 - SaveGame10 � �����, �� ������ �������� � ������ ����������.", 
	L"%s: �����(�) ������� %s.",
	L"������� ������� � �������.",
	L"%s �������� � ����� ���������� (������ %s) � %d� ����, �������� � %s.",		//first %s is mercs name, next is the sector location and name where they will be arriving in, lastely is the day an the time of arrival
	L"� ������ ��������� ������!",
	L"������� �� ������ ���������� ������ �������� ��������� (�������� �� �������� ��������)",
	L"������� �� ������ ���������� ������ ������� (�������� �� �������� �� ��������)",
	L"�������� ������� � ��������", // Changed from Drop All On (Enabled Soldier Tooltips)
	L"��������� ������� � ��������", // Changed from Drop All Off (Disabled Soldier Tooltips)
	L"����������� �������� ��� ������� �����",
	L"����������� �������� �������",
	// forced turn mode strings
    L"������ ��������� �����",
	L"����� ��������� �������",	//Normal turn mode
	L"����� �� ���������� ������",	//Exit combat mode
	L"������� ������ ��������� �����. �������� � ���!",	//Forced Turn Mode Active, Entering Combat
#ifdef JA2BETAVERSION
	L"���� ��������� � ���� ����-����������.",
#endif
	L"..\\SavedGames\\MP_SavedGames", //The name of the directory where games are saved.
	L"������",	//Client
	L"������ ������������ ���������� \"������\" ��������� � \"����� ������� �������\".",	//You cannot use the Old Inventory and the New Attachment System at the same time.
};


CHAR16 ItemPickupHelpPopup[][40] =
{
	L"�����",
	L"�����",
	L"������� ���",
	L"����",
	L"������",
};

STR16 pDoctorWarningString[] =
{
	L"%s ������� ������, ����� �����������.",
	L"���� ������ �� ����� ������� ������ ������ ���� �������.",
};

STR16 pMilitiaButtonsHelpText[] =
{
	L"��������� (����� ������)\n��������� (����� ������)\n����� �����������", // button help text informing player they can pick up or drop militia with this button 
	L"��������� (������ ������)\n��������� (����� ������)\n����� �������",
	L"��������� (������ ������)\n��������� (����� ������)\n����� ������� ������",
	L"���������� ������������\n���������� �� ���� ��������.",
};

STR16 pMapScreenJustStartedHelpText[] =
{
	L"������������� � A.I.M. � ������� ������ (*���������* - ��� � �������).", // to inform the player to hired some mercs to get things going
	L"����� ������ ������ ����������� � �������, �������� ������ ������� � ������ ������ ���� ������.", // to inform the player to hit time compression to get the game underway
};

STR16 pAntiHackerString[] = 
{
	L"������. �������� ��� �������� ����(�). ���� ���������� ������.",
};


STR16 gzLaptopHelpText[] =
{
	//Buttons:
	L"����������� �����",
	L"�������� �������� �����",
	L"����������� ���������� ������",
	L"����������� ������ ��������� �������",
	L"�������� ���������� � �������",
	L"����������� ���������� ������",
	L"������� ������",

	//Bottom task bar icons (if they exist):
	L"�������� ����� �����",
	L"�������� ����� ������",

	//Bookmarks:
	L"������������� ���������� ��������� A.I.M.",
	L"����� ��� - ����� ������ ����� ��������",
	L"�������� �������� �������� �������� I.M.P.",
	L"����� �������� M.E.R.C.",
	L"���������� ������ �������������",
	L"'����� �� ����� ����'",
	L"��������� ������ �� ���������� A.I.M.",
};


STR16	gzHelpScreenText[] =
{
	L"������� ���� ������",	
};

STR16 gzNonPersistantPBIText[] =
{
	L"���� ���. �� ������ ��������� ������ ����� ����������� �����.",
	L"����� � ������, ����� ���������� ���. (|E)",
	L"�������� ��� ������������� (|A).",
	L"�� ����� ����� ����� �������������� ����� �������� ������.",
	L"����� ���� ��� �� ������ � ������, �������������� ����� �������� ������.",
	L"����� �������� - �������������� ����� �������� ������.",
	L"����� ���������� ����������� - �������������� ����� �������� ������.",
	L"����� �����-������ - �������������� ����� �������� ������.",
	L"���� ���",
	L"������ �� �� ������ ���������.",
};

STR16 gzMiscString[] =
{
	L"���� ��������� ���������� ��� ��� ������ ���������...",
	L"������ ������ ������� �� ���������.",
	L"��������� ��� ����� �� %d%%.",
	L"%s ��������� ��� ��������� ��������.",
	L"�� �������� ����������� �������.",
};

STR16	gzIntroScreen[] = 
{
	L"�� ������� ����� ������������� ����������",
};

// These strings are combined with a merc name, a volume string (from pNoiseVolStr),
// and a direction (either "above", "below", or a string from pDirectionStr) to 
// report a noise.
// e.g. "Sidney hears a loud sound of MOVEMENT coming from the SOUTH."
STR16 pNewNoiseStr[] =
{
	L"%s ������ %s ���� %s.",
	L"%s ������ %s ���� �������� %s.",
	L"%s ������ %s �����, ������ %s.",
	L"%s ������ %s ���� �������� %s.",
	L"%s ������ %s ���� ����� %s.",
	L"%s ������ %s ���� ������ %s.",
	L"%s ������ %s ���� %s.",
	L"%s ������ %s ���� ����� %s.",
	L"%s ������ %s ���� ����� %s.",
	L"%s ������ %s ���� %s.",
	L"%s ������ %s ������ %s.",
};

STR16 wMapScreenSortButtonHelpText[] =
{
	L"���������� �� ����� (|F|1)",
	L"���������� �� ���� ������������ (|F|2)",
	L"���������� �� ��������� ��� (|F|3)",
	L"���������� �� ����� ���������� (|F|4)",
	L"���������� �� ����� ���������� (|F|5)",
	L"���������� �� ������� ��������� (|F|6)",
};



STR16		BrokenLinkText[] = 
{
	L"������ 404",
	L"���� �� ������.",
};


STR16 gzBobbyRShipmentText[] = 
{
	L"��������� �����������",
	L"����� �",
	L"����������",
	L"��������",
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
	L"������� ����������� ����", 				// Chris Camfield
	L"��������/���������",					// Shaun Lyng
	L"����������� �������������� ����� � ���������",	//Kris \"The Cow Rape Man\" Marnes
	L"��������/��������",					// Ian Currie
	L"��������/������ ����",				// Linda Currie
	L"��������",						// Eric \"WTF\" Cheng
	L"������������, ���������",				// Lynn Holowka
	L"������� ��������",					// Norman \"NRG\" Olsen
	L"������ �� �����",					// George Brooks
	L"�������� �������/��������",				// Andrew Stacey
	L"������� ��������/��������",				// Scot Loving
	L"������� �����������",					// Andrew \"Big Cheese Doddle\" Emmons
	L"�����������",						// Dave French
	L"����������� ��������� � ������� ����",		// Alex Meduna
	L"��������-����������",					// Joey \"Joeker\" Whelan",
};

STR16	gzCreditNameFunny[]=
{
	L"", 												// Chris Camfield
	L"(�� ��� ������ ������� ����������)",				// Shaun Lyng
	L"(\"������! �������� ������ ���� ���������.\")",	//Kris \"The Cow Rape Man\" Marnes
	L"(��� ������� ���� ��� ����� �����)",				// Ian Currie
	L"(����� �������� ��� Wizardry 8)",					// Linda Currie
	L"(��������� ����������� ��� ����� ���������)",		// Eric \"WTF\" Cheng
	L"(���� �� ��� � CFSA - ��������� �������...)",		// Lynn Holowka
	L"",							// Norman \"NRG\" Olsen
	L"",							// George Brooks
	L"(��������� ����� � ������ Dead Head)",			// Andrew Stacey
	L"(��� ��������� ��� ������)",						// Scot Loving
	L"(������������ ������������� �������)",			// Andrew \"Big Cheese Doddle\" Emmons
	L"(����� ����� �������� �����������)",				// Dave French
	L"(������� � ������ ��� Wizardry 8)",				// Alex Meduna
	L"(����� �������� � ����������� ������!)",			// Joey \"Joeker\" Whelan",
};

STR16 sRepairsDoneString[] =
{
	L"%s: �������� ������ ������ �����.",
	L"%s: �������� ������ ����� ������ � �����.",
	L"%s: �������� ������ ���� ���������� ������.",
	L"%s: �������� ������ ���� ������� ����� ������.",	//%s finished repairing everyone's large carried items
	L"%s: �������� ������ ���� ����� ����� ������.",	//%s finished repairing everyone's medium carried items
	L"%s: �������� ������ ���� ������ ����� ������.",	//%s finished repairing everyone's small carried items
	L"%s: �������� ������ ������������ ������ ������.",	//%s finished repairing everyone's LBE gear
};

STR16 zGioDifConfirmText[]=
{
	L"�� ������� ˨���� ������� ���������. ���� ����� ������������ ��� ���������� ������������ � Jagged Alliance. ��� ����� ��������� ��� ���� ����, ��� ��� ������ ���������. �� ������������� ������ ������ ���� � ���� ������?", 
	L"�� ������� ������� ������� ���������. ���� ����� ������������ ��� ���, ��� ������ � Jagged Alliance � ��������� ������. ��� ����� ��������� ��� ���� ����, ��� ��� ������ ���������. �� ������������� ������ ������ ���� � ���� ������?", 
	L"�� ������� ��ƨ��� ������� ���������. � ���� ������ ��� ����������� ������� ���� ���� � Jagged Alliance. ��� ����� ��������� ��� ���� ����, ��� ��� ������ ���������. �� ������������� ������ ������ ���� � ���� ������?", 
	L"�� ������� �������� ������� ���������. ������ � ���� - � ���� ������ ����������� �������� �������� �� ��������� ���������! �� ���� � ������� �� �� � �����, �� ��� ���� ����������. ��������?",
};

STR16 gzLateLocalizedString[] =
{
	L"%S ���� ��� �������� ������ �� ������...",

	//1-5
	L"����� �� ������ �������� ���� ������, ���� ���-������ �� ������� ����� ����������.",

	//This message comes up if you have pending bombs waiting to explode in tactical.
	L"������ ������ �������� ������ �������. ��������� ������!", 

	//'Name' refuses to move.
	L"%s ������������ �����������.",

	//%s a merc name
	L"%s: ������������ ����� �������� ��� ��������� ���������.",

	//A message that pops up when a vehicle runs out of gas.
	L"%s: ����������� �������. ������ �������� � %c%d.",

	//6-10

	// the following two strings are combined with the pNewNoise[] strings above to report noises
	// heard above or below the merc
	L"������",
	L"�����",

	//The following strings are used in autoresolve for autobandaging related feedback.
	L"����� �� ����� ��������� �� ����� ����������� �������.",
	L"����� ���������. �� � ���� �� ��������� ��� �������.",
	L"����� ���������� ���� ���������, �� ������� ������.",
	L"����� �� ����� ��������� �� ��������� � ���������.",
	L"������������� ������������ ������.",
	L"��� ���� �������� ����������.",

	//14
	L"�������",

	L"(�� �����)",

	L"��������: %d/%d",

	//In autoresolve if there were 5 mercs fighting 8 enemies the text would be "5 vs. 8"
	//"vs." is the abbreviation of versus.
	L"%d ������ %d",
	
	L"%s �����!",  //(ex "The ice cream truck is full")

	L"%s ��������� �� � ������ ������ ��� ���������, � � ��������� ������� �/��� ������.", 

	//20
	//Happens when you get shot in the legs, and you fall down.
	L"��-�� ������� � ���� %s ������ �� �����!",
	//Name can't speak right now.
	L"%s ������ �� ����� ��������",

	//22-24 plural versions @@@2 elite to veteran
	L"%d ���������� �� ��������� ����������� � ������� ������.",
	L"%d ���������� �� ��������� ����������� � �������.",
	L"%d ������� ��������� ����������� � ������� ������.",

	//25
	L"������",

	//26
	//Name has gone psycho -- when the game forces the player into burstmode (certain unstable characters)
	L"� %s ������� �������!",

	//27-28
	//Messages why a player can't time compress.
	L"������ ����������� �������� ������ ������� - � ��� ���� �������� � ������� %s.",
	L"������ ����������� �������� ������ ������� - � ��� ���� �������� � ������� � ������.",

	//29-31 singular versions @@@2 elite to veteran
	L"1 ���������� �� ��������� ���� ������� ��������.",
	L"1 ���������� �� ��������� ���� ������� ����������.",
	L"1 ������� ��������� ���� ������� ��������.",

	//32-34
	L"%s ������ �� �������.",
	L"��������� �� �����������?",
	L"(%d� �����)",

	//35
	//Ex: "Red has repaired Scope's MP5K".  Careful to maintain the proper order (Red before Scope, Scope before MP5K)
	L"%s ��������������(�) � %s %s",

	//36
	L"������",

	//37-38 "Name trips and falls"
	L"%s ����������� � ������.",
	L"���� ������� ������ ����� ����������.",

	//39
	L"���������� ����� �� ����� ���������. �������� � ������� ��������� ���������.",

	//40-43
	//%s is the name of merc.
	L"%s: ����������� �����������!",
	L"%s: ������������ ������� ��� �������.",
	L"%s: ���������� ��������� �����!",
	L"%s: ������������ ������� ��� �������.",

	//44-45
	L"����� �������",
	L"%s �� ����� ����� ��������.",

	//46-48
	L"%s: ���������� ��������� �������!",
	L"� ���� ������� ���������� ����� ����������� �� ����� %d �������.",	//No more than %d militia trainers are permitted in this sector.
	L"�� �������?",

	//49-50
	L"������ �������.",
	L"��� ������ �����.",

	//51-52 Fast help text in mapscreen.
	L"����������� ������ ������� (|�|�|�|�|�|�)",
	L"���������� ������ ������� (|E|s|c)",

	//53-54 "Magic has unjammed the Glock 18" or "Magic has unjammed Raven's H&K G11" 
	L"%s �������(�) %s",
	L"%s �������(�) %s (%s)",

	//55 
	L"������ �������� ������ ������� ��� ��������� ��������� � �������.",

	L"CD ������ ������ �� ������. ��������� ������� � ��.",

	L"�������� ������� ���������.",
	
	//58
	//Displayed with the version information when cheats are enabled.
	L"�������� ���� �������/����������� �����������: %d%%/%d%%",

	//59
	L"����������� ����� � ����?",
	
	//60
	L"������ ������.",

	L"%s ��������� ��� � ����������� ���-�� ��������!",
	L"%s �������� �� %d ������ ����!",
	L"%s �������� �� ���� ���� ������!",
};

STR16 gzCWStrings[] = 
{
	L"������� ������������ �� �������� �������� ��� %s?",
};

// WANNE: Tooltips
STR16 gzTooltipStrings[] =
{
	// Debug info
	L"%s|�����: %d\n",
	L"%s|�������: %d / %d\n",
	L"%s|��������� �� |����: %d\n",
	L"%s|I|D: %d\n",
	L"%s|�������: %d\n",
	L"%s|�������: %d\n",
	L"%s|������� |A|Ps: %d\n",
	L"%s|������� |��������: %d\n",
	// Full info
	L"%s|�����: %s\n",
	L"%s|�����: %s\n",
	L"%s|�����: %s\n",
	// Limited, Basic
	L"|�����: ",
	L"����� ",
	L"����� ",
	L"�����",
	L"����",
	L"��� �����",
	L"%s|�|�|�: %s\n",
	L"��� ���",
	L"%s|����������: %s\n",
	L"��� �����������",
	L"%s|������,|���� |1: %s\n",
	L"%s|������,|���� |2: %s\n",
	L"\n(� �������) ",
	L"%s|������: %s ",
	L"��� ������",
	L"��������",
	L"��������-�������",
	L"��������",
	L"������ �������",
	L"�����",
	L"���",
	L"������� ������",
	L"��� �����",
	L"��� �����������",
	L"��� �������",
	L"|�����: %s\n", 
	 // Added - SANDRO
	L"%s|����� 1: %s\n",	//%s|Skill 1: %s\n
	L"%s|����� 2: %s\n", 
	L"%s|����� 3: %s\n",
};

STR16 New113Message[] =
{
	L"�������� ����.",
	L"���� �����������.",
	L"������� �����.",
	L"����� ����������.",
	L"���������� ���������...",
	L"����� �� ����������!",	//suppression fire!
	L"*",			//BRST - ��������� �� ���������� ���������� ����
	L"***",			//AUTO - ������������ �������
	L"��",
	L"�� *",
	L"�� ***",
	L"�������!",
	L"���������� ��������� ������ ��-�� �������� �� �������.",
	L"����� ������� ����� ��������� ���������� � %s, ��� ��� ���������� ����� ������� %s ��������� �����������.",
	L"��������� ����.",
	L"��������� ��� ���� ��������� ������.",
	L"���� ������� ����������� ��������� �������.",
	L"������� ��� ���� ��������� ������.",
	L"������� ��� ������� ������ ����� ������.",	//You should check your goggles
	// Real Time Mode messages
	L"��� � ���.",	//In combat already
	L"� �������� ��������� ��� ������.",	//No enemies in sight
	L"�������� � ������ ��������� ������� ����.",	//Real-time sneaking OFF
	L"�������� � ������ ��������� ������� ���.",	//Real-time sneaking ON
	L"��������� ����!", // this should be enough - SANDRO
	L"%s ������� ��������� � ������!",	//%s was successful at stealing!
	L"� %s ��� ������������ ���������� ����� ��������, ����� ������� ��� ��������� ����.",	//%s did not have enough action points to steal all selected items.
	L"������ �������� ������������� �������� %s ����� ����������? (�� ������� ������������ ����� %i ��������).",	//Do you want to perform surgery on %s before bandaging? (You can heal about %i Health.)
	L"������ �������� ������������� �������� %s? (�� ������� ������������ ����� %i ��������).",	//Do you want to perform surgery on %s? (You can heal about %i Health.)
	L"������ ������� �������� ����������� ������������� ��������? (�������(�) - %i).",	//Do you wish to perform necessary surgeries first? (%i patient(s))
	L"������ �������� �������� ������� ����� ��������?",	//Do you wish to perform the surgery on this patient first?
	L"��������� ������ ������ � ������������� �������������� ��� ��� ����?",	//Apply first aid automatically with necessary surgeries or without them?
	L"%s ������� �������������(�).",	//Surgery on %s finished.
	L"%s ���������(�) ���� � ������� ������ � ������ ������� ������������� �������� ��������!",	//%s is hit in the chest and loses a point of maximum health!
	L"%s ���������(�) ���� � ������� ������ � ������ %d ������������� �������� ��������!",	//%s is hit in the chest and loses %d points of maximum health!
	L"%s �����������(�) ���� ������� ����������� %s.",	//%s has regained one point of lost %s
	L"%s �����������(�) %d ������ ����������� %s.",	//%s has regained %d points of lost %s
	L"���� ������ ������ ������� ������ ����������.",	//Your scouting skills prevented an ambush by the enemy!
	L"��������� ����� ������� ������ �� ������� �������� ������� � �������-�������!",	//Thanks to your scouting skills you have successfuly avoided a pack of bloodcats!
	L"%s �������� ���� � ��� � ������ �� ����� � ������ ����!",	//%s is hit to groin and falls down in pain!
};

STR16 New113HAMMessage[] = 
{
	// 0 - 5
	L"%s � ������ �������� ��������!",	//%s cowers in fear!	%s �������� �� ������!
	L"%s ������(�) � ����� ��������� �����!",	//%s is pinned down!
	L"%s ��������� ������ ����, ��� �������������!",	//%s fires more rounds than intended!
	L"�� �� ������ ����������� ��������� � ���� �������.",	//You cannot train militia in this sector.
	L"��������� �������� %s.",	//Militia picks up %s.
	L"���������� ����������� ��������� ����� � ������� ����!",	//Cannot train militia with enemies present!
	// 6 - 10
	L"%s ����� ������ ����� ���������, ����� ����������� ����������.",	//%s lacks sufficient Leadership score to train militia.
	L"� ���� ������� �� ����� ���� �������� ��������� ����� ������ %d.",	//No more than %d Mobile Militia trainers are permitted in this sector.
	L"��� ��������� ���� � %s ��� ������ ���� ��� ����� ��������� ������!",	//No room in %s or around it for new Mobile Militia!
	L"����� ����� �� %d ���������� � ������ ������������ ������� ������ %s, ������ ��� ����� ����� ����������� ��������� ������.",	//You need to have %d Town Militia in each of %s's liberated sectors before you can train Mobile Militia here.
	L"���������� �������� � ��������� ����������� ���� ���� � �������!",	//Can't staff a facility while enemies are present!
	// 11 - 15
	L"%s ����� ���� ��������, ����� �������� � ��������� �����������.",	//%s lacks sufficient Wisdom to staff this facility.
	L"����������� %s ��������� ��������������� ����������.",	//The %s is already fully-staffed.
	L"���� ��� ����� ����� ��������� �������� ��� � $%d. �������� ����������?",	//It will cost $%d per hour to staff this facility. Do you wish to continue?
        L"� ��� ������������ ����� ����� �������� ������ � ����������� �� �������. $%d ���������, ��� ����� $%d. ������� ��� �� �����������.", //You have insufficient funds to pay for all Facility work today. $%d have been paid, but you still owe $%d. The locals are not pleased.",
        L"� ��� ������������ ����� ����� ��������� ���������� ����� ���� �������. ������ ���� �������� $%d. ������� ��� �� �����������.",
	// 16 - 20
	L"������������ ���� ���������� $%d ��� ������ �����������, � ��� ����� ����� ��� ��������!",	//You have an outstanding debt of $%d for Facility Operation, and no money to pay it off!
	L"������������ ���� ���������� $%d ��� ������ �����������. �� �� ������ ��������� ����� �� ������ � ����������� ���� �� �������� �������������.",	//You have an outstanding debt of $%d for Facility Operation. You can't assign this merc to facility duty until you have enough money to pay off the entire debt.
	L"������������ ���� ���������� $%d ��� ������ �����������. ��������� ������ �� �������������?",	//You have an outstanding debt of $%d for Facility Operation. Would you like to pay it all back?
	L"�/� � ���� �������",	//N/A in this sector
	L"������� ������",
	// 21 - 25
	L"������������ ����� ����� ��������� ����� �������� ���������. %d ���������� ���� ���������� � ��������� �����.",	//Insufficient funds to pay all enlisted militia! %d militia have disbanded and returned home.
};

// WANNE: This are the email texts, when one of the 4 new 1.13 MERC mercs have levelled up, that Speck sends
// INFO: Do not replace the � characters. They indicate the <B2> (-> Newline) from the edt files
STR16	New113MERCMercMailTexts[] =
{
	// Gaston: Text from Line 39 in Email.edt
	L"����������, ������� � ��������, ��� � ���������� ������� ������� ������� ������������� ���������� ��������� ��� ����������������� ������. � � ���� �. ����� � ",
	// Stogie: Text from Line 43 in Email.edt
	L"����������, ������� � ��������, ��� ��������� ������ ������� ���������� ����� '������' ������ �� ����� ��������� ��� ��������. � � ���� �. ����� � ", 
	// Tex: Text from Line 45 in Email.edt
	L"����� ������� � ��������, ��� ������� ����� ��������� ��� ��������� ����� ��������� ������. ������� ��� ������� ��� ��������, ����� ��������������� ��� �������. � � ���� �. ����� � ",
	// Biggens: Text from Line 49 in Email.edt
	L"������ � �����������, ��� �������� ������ ���������� ��������� �������� ����������� ��������� � ���� ��������� ��������. ������������� ������� �������������� � �������� �������. � � ���� �. ����� � ",
};

//TODO.Translate
// WANNE: These are the missing skills from the impass.edt file
// INFO: Do not replace the � characters. They indicate the <B2> (-> Newline) from the edt files
STR16 MissingIMPSkillsDescriptions[] =
{
	// Sniper
	L"�������: � ��� ����� �������. � ��������� ����� �� ������������� ����������� �������� � ��� � ���������� 100 ������! � ",	//Sniper: Eyes of a hawk, you can shoot the wings from a fly at a hundred yards!
	// Camouflage
	L"����������: �� ����� ���� ����� �������� ��������������! � ",	//Camouflage: Beside you, even bushes look synthetic!
	// Ranger
	L"��������: ��� ��������� �� ������, �� ����� ���� �������� �����������! �� ������ ����������� �������� ����, ����� ���������� ��� �����, � ������ �������� �� ����� ������� ����� � ����. � ",	//Ranger: Those amateurs from Texas have nothing on you!
	// Gunslinger
	L"������: � ����� �����������, ���� � ����� - �� ��� �� ������ ��� ����� ���! � ",	//Gunslinger: With one handgun or two, you can be as lethal as Billy the Kid!
	// Squadleader
	L"��������: ����������� �����, ������� ������ ���������� ���! � ",	//Squadleader: A natural leader, your squadmates look to you for inspiration!
	// Technician
	L"�������: ����� ��������� �� ��������� � ���� ������ �����! ��������, ����������� ��� ���������� - �� �������������� ��� ������! � ",	//Technician: MacGyver's got nothing on you! Mechanical, electronic or explosive, you can fix it!
	// Doctor
	L"������: ���� �� �������� ��� �������� �����, ����� ��������� ��� �� ��������, ������� ����-������ - �� � �������� ���������� � ����� �������! � ",	//Doctor: From grazes to gutshot, to amputations, you can heal them all!
	// Athletics
	L"���������: ���� �������� � ������������ �������� ���������! � ",	//Athletics: Your speed and vitality are worthy of an Olympian!
	// Bodybuilding
	L"����������: �����? �� �� ������! �� � �������� �������� ��� ����� �����! � ",	//Bodybuilding: Arnie? What a wimp! You could beat him with one arm behind your back!
	// Demolitions
	L"���������: ����� �������, ��� ������ �� ����; ���������� ����, ��� �������� ������ - ����� � ������� 20 �����; � ����� ��������� �� ����� �����������... ��� ��, ���� ���� �� �����! � ",	//Demolitions: Sowing grenades like seeds, planting bombs, watching the limbs flying.. This is what you live for!
	// Scouting
	L"���������: ����� �� �������� �� ������ ������� �������! � ",	//Scouting: Nothing can escape your notice!
};

STR16 NewInvMessage[] = 
{
	L"� ������ ������ ������� ������ ������.",
	L"�� �� ������ ������������ ������ 2 �������.",
	L"�� �������� ���� ������...",
	L"����� ������� �������� ���� �� ����� �����.",
	L"�� �� ������ ������������� � �������� ��������.",
	L"�� ������� ��� ������ ������� ���� ���� ����� ������� ����������� ��������� �������?",
	L"�� ������� ��� ������ ��������� ���� ����, ���������� � ���� �������?",
	L"���������� ����� ���������� � ������ �������� �� �����. ����� ������?",
};

// WANNE - MP: Multiplayer messages
STR16 MPServerMessage[] =
{
	// 0
	L"����������� ������ RakNet...",
	L"������ �������, �������� �����������...",
	L"������ ��� ���� ������������ � �������, ����� '2'.",
	L"������ ��� �������.",
	L"�� ������� ��������� ������. ��������� ������.",
	// 5
	L"%d/%d �������� ������ � ������ ��������� �������.",
	L"������ ���������� � ��������� ���� ������.",
	L"������ �� �������.",
	L"��������� ����������, ������ ��� ��� �����������...",
	L"�� �� ������ �������� ���� ������� ����� ������� �������.",
	// 10
	L"�������� ����� '%S' - 100/100",	//Sent file '%S' - 100/100
	L"��������� �������� ������ ��� '%S'.",	//Finished sending files to '%S'.
	L"������ �������� ������ ��� '%S'.",	//Started sending files to '%S'.
};

STR16 MPClientMessage[] =
{
	// 0
	L"����������� ������ RakNet...",		
	L"����������� � IP: %S ...",
	L"�������� ��������� ����:",
	L"�� ��� ����������.",
	L"�� ��� �������������...",
	// 5
	L"������ �%d - '%S' ����� %s.",
	L"������ �%d - '%S' ����� ��� �����.",
	L"�� ������ � ��� (����� ������ = %d/%d).",
	L"�� �������� ���������� � ��� (����� ������ = %d/%d).",
	L"������ ������������� � ����� �����...",	//'Starting battle...'
	// 10
	L"������ �%d - '%S' ����� � ��� (����� ������ = %d/%d).",
	L"������ �%d - '%S' ������� ���������� � ��� (����� ������ = %d/%d).",
	L"������, �� ��� ������ � ���, ������, �������� ��������� ���������. (���� ������ �������� ������������ ����� ������, ������� ������ '��').",
	L"������ �� �����!",
	L"��� ������ ���� ���������� ��������� ������.",
	// 15
	L"���� �� ����� ���� ������, �� �� ������ �� ������ �����.",
	L"����, ����� ������ ���� ����� �� ������ � �������...",
	L"����������",			//Interrupted
	L"����������� ����� ���������",	//Finish from interrupt
	L"���������� �������:",		//Mouse Grid Coordinates
	// 20
	L"X: %d, Y: %d",
	L"����� ��������: %d",		//Grid Number
	L"�������� ���� ��� �������.",
	L"�������� ����� ������� ���� ������������� ���������:  ('1' - ������� ������/���� ������)  ('2' - ���������/��������� �������)  ('3' - �������������� ���������������� ���������)  ('4' - ��������� �����������)",
	L"Sector=%s, Max Clients=%d, Max Mercs=%d, Game_Mode=%d, Same Merc=%d, Damage Multiplier=%f, Timed Turns=%d, Secs/Tic=%d, Dis BobbyRay=%d, Dis Aim/Merc Equip=%d, Dis Morale=%d, Testing=%d",

	// 25
	L"�������� ���-������� '9' ��������.",
	L"����� �����: ������ �%d - '%S'.",
	L"�������: %d.",//not used any more
	L"%s (������ %d - '%S') ��� ���� %s (������ %d - '%S')",
	L"������ �%d - '%S' ������� �� ����.",
	// 30
	L"������������� ���� ��� �������: �1 - '%S' | �2 - '%S' | �3 - '%S' | �4 - '%S'",
	L"������� ��� ������� �%d",
	L"������ �������� � ����� ��������� �����...",
	L"������� � ����� ��������� �������.",
	L"������: ���-�� ����� �� ���, ��������� �������.",
	// 35
	L"������� ������ � �������? (������� ��� ��� ������ ������������?)",
	L"�������� ��� ������ ������ � �������. ����������� � ����� ������!",
	L"�����������.",
	L"������ �� ����� �������� ���� �������, �������� ���� �������.",
	L"�� ���������� �� ����������� �������, ������ ��� ��� �� ��������� � ������� ����.",
	// 40
	L"��� ���� ����� ���� �����!",
	L"������������� ����� ����������.",
	L"�� ��������� ���������!",
	L"��������, �������� �� ����� � ������� ���� ���������.",
	L"�� ������ %s.",
	// 45
	L"�� �� ������ �������� ����� ����� ������ �������.",
	L"����� �������� �� '%s'",
	L"������ '%s' ����������, ������� ��� �� ����.",
	L"�� ���� ��������� �� ����, ������������ � ������� ����.",
	L"������������ �� �������. ��������� ������� ����� 5 ������ (�������� %i �������)",
	//50
	L"������������ �� �������, ������...",
	L"�� �� ������ ������ ���� �� ����� ����������� ������ �������.",
	L"%s : %s",
	L"��������� ����",
	L"������ ���������",
	// 55
	L"�� ���� �������������� � ����. ���� ��� ��������.",
	L"%s (�������): %s",
	L"#%i - '%s'",
	L"%S - 100/100",
	L"%S - %i/100",
	// 60
	L"�� ������� �������� ��� ����������� �����.",
	L"'%S' ������� � ������� ���������.",
	L"'%S' ������ ������� � �������.",
	L"������ ������ ���� ���� ��� ������ �� ��������� ���� ������ �� �������.",
	L"��� ���� �� ���� ������� ���������� ������� ��������� ���������� �����, ������� ����������?",
	// 65
	L"������� '�����' ��� ����� �� ����������� �����.",
	L"�� ������ ������������. ������ ������ ������� (%S) ���������� �� ������ ������� (%S).",
	L"�� ����� ���������� �������.",
	L"������ ��������� ���� ������ ��� ��� ������� ����������.",
};

STR16 MPHelp[] =
{
	// 0
	L"�������� ������� ���� Jagged Alliance 2",
	L"������� F1 ��� ��������� ������.",
	L"���������� ������� ����� (�� �������������� ������)",
	L"* ������ ���������� ��������� � ����� ja2_mp.ini *",
	L"'1' - ��������� ������.", 
	// 5
	L"'2' - ������������ � �������.",
	L"'3' - ��� ������� - ������� ������, ��� ������� - ����� � ���.",
	L"'4' - ���������� ������� ��� �������.",
	L"'5' - ����� ��������� ��� ����� �� ����������� ������.",
	L"'7' - ����� ���� �������������� ��������� ��������� ���������.",
	// 10
	L"'F2' - �������� �������������� ������.",
	L"����� ��������� �������� �� ������� � ����� readme_mp.html",
	L"������: (�������, ��� ��������� � ja2_mp.ini �����)",
	L"* ��������� ��� ������ ������ ����� ���������� �������� CLIENT_NUM *",
	L"* � ����������� ���� �� ������������ ���������� � ����� ��� *",
	// 15
	L"* ���������� �� ������� ������ ����������� ����-����� � ������ ��������� *",
	L"'F1' - �������� �������� ������.",
};

STR16 gszMPEdgesText[] =
{
	L"�",	//N
	L"�",	//S
	L"�",	//E
	L"�",	//W
	L"�",	// "C"enter
};

STR16 gszMPTeamNames[] =
{
	L"��������",	//Foxtrot
	L"�����",	//Bravo
	L"������",	//Delta
	L"�����",	//Charlie
	L"�/�",		// Acronym of Not Applicable
};

STR16 gszMPMapscreenText[] =
{
	L"��� ����: ",		//Game Type: 
	L"�������: ",		//Players: 
	L"����� ������: ",	//Mercs each: 
	L"������ �������� ������� ������� ������ ����� �������� �������.",
	L"������ �������� ��� ������� ����� �������� �������.",
	L"����. �����: ",	//Random Mercs: 
	L"��",			//Y
	L"���������:",		//Difficulty:
	L"������ �������:",	//Server Version:
};

STR16 gzMPSScreenText[] =
{
	L"����� �����",		//Scoreboard
	L"����������",		//Continue
	L"������",		//Cancel
	L"�����",		//Player
	L"�����",		//Kills
	L"�������",		//Deaths
	L"����������� �����",	//Queen's Army
	L"���������",		//Hits
	L"�������",		//Misses
	L"��������",		//Accuracy
	L"��������� ����",	//Damage Dealt
	L"���������� ����",	//Damage Taken
	L"���������, ����������, ���� ������ ����� ������ '����������'."
};

STR16 gzMPCScreenText[] =
{
	L"������",						//Cancel
	L"����������� � �������...",				//Connecting to Server
	L"������� ��������� �� �������...",			//Getting Server Settings
	L"�������� ��������� �����...",				//Downloading custom files
	L"������� 'ESC' ��� ������ ��� 'Y' ����� ����� � ���.",	//Press 'ESC' to cancel or 'Y' to chat
	L"������� 'ESC' ��� ������",				//Press 'ESC' to cancel
	L"���������."						//Ready
};

STR16 gzMPChatToggleText[] =
{
	L"�������� ����",
	L"�������� ������ ���������",
};

STR16 gzMPChatboxText[] =
{
	L"��� ������� ���� Jagged Alliance 2 v1.13",
	L"�������: ������� |�|�|�|� ��� �������� ���������, |�|�|�|� ��� ������ �� ����.",
};

STR16 pSkillTraitBeginIMPStrings[] =
{
	// For old traits
	L"�� ��������� �������� ��� ����� ������� ���������������� ������ � ������������ �� �������������� ������ �������. �� ������ ������� �� ����� ���� ������ ������ ��� ���� � ������� �� � ������������.",
	L"����� ������� ����� ���� ����� ��� ������ �������� ��� ����. ����� ��� ����� ���� �������������� ����� ��� ��������� ��������� ����������. ��� �� �������� ���� ��������, ��� ����� ����������� � �������� � ���� ��� �� ����� ���� ����������.",
	// For new major/minor traits
	L"��������� ���� - ����� �������, ������� ��������� ������������� ������ �������. �� ������ �������� ����� ������� �� ���� �������� �������, ������� ��������� ���� ����� � ������. �� ������ - �������������� ������, �������������� ������ �������� �����.", 
	L"����� ����� ����� �� ����� ��� �������. ���, ���� �� �� ������� �������� �����, �� ����� ����� ��� ��������������. ���� �� �� ������� ��� �������� ������ (��� ���� ����������), �� ����� �������� ���� ���� ��������������...",  
};

STR16 sgAttributeSelectionText[] = 
{
	L"��������������� ���� ���������� ��������� �������� ����� �������� ������������. � �� ����� �� ��������.",
	L"I.M.P.: ��������� � ������.",	//I.M.P. Attributes and skills review.
	L"�����:",	//Bonus Pts.
	L"��� �������",	//Starting Level
	// New strings for new traits
	L"�� ��������� �������� ������� ���� ���������� ��������� � ������. \"���������� ���������\" - ��� ��������, ��������, �����������, ���� � ��������. ��� �� ����� ���� ���� %d.", 
	L"���������� \"������\", � ������� �� ���������� ����������, ����� ���� ����������� � ����, ��� �������� ���������� ���������������� � ������ ��������.", 
	L"���������� ��� ��������� ����������� �� �������. ��������, ��� ������� ��� ��������� ���������� ������������ ���������� ��������, � �� �� ������ �������� �� ��������.",
};

STR16 pCharacterTraitBeginIMPStrings[] =
{
	L"I.M.P.: ������ ������ �������",	//I.M.P. Character Analysis
	L"��������� ��� - ������ ����� ������ �������. �� ������ �������� ��� �� ����� ����� ��������� ������ ���� ���������. �������, ��� ��� ����� ���� ����������� ��������� �� ��������� ����, �� ������� ����� ���� ����. �������� ���� ����� ���� ���������� ���� ����� ���������.",
	L"�� ������ �������� ��� ����� ��������� ������ �����������, �������, ��������, ���� � ���. ���� ������ ���� ���������� � ������, �������� ���. ������ ��������� ������ ��� �������, ����� ����� ������������ ����� ������������� ������������� ����������� ���������� � ���.",
};

STR16 gzIMPAttitudesText[]=
{
	L"����������",	//Normal
	L"�����������",	//Friendly
	L"��������",	//Loner
	L"��������",	//Optimist
	L"���������",	//Pessimist
	L"�����������",	//Aggressive
	L"������������",	//Arrogant
	L"������",	//Big Shot
	L"�����",	//Asshole
	L"����",	//Coward
	L"I.M.P.: ��������� �������",	//I.M.P. Attitudes
};

STR16 gzIMPCharacterTraitText[]=
{
	L"�������",	//Neutral
	L"�����������",	//Sociable
	L"��������",	//Loner
	L"��������",	//Optimist
	L"�������������",	//Assertive
	L"����������",	//Intellectual
	L"����������",	//Primitive
	L"�����������",	//Aggressive
	L"������������",	//Phlegmatic
	L"�����������",	//Dauntless
	L"�����������",	//Pacifist
	L"�������",	//Malicious
	L"�������",	//Show-off
	L"I.M.P.: ���������� ��������",	//I.M.P. Character Traits
};

STR16 gzIMPColorChoosingText[] = 
{
	L"I.M.P.: ��������� � ������������",
	L"I.M.P.: ���������",
	L"�������� ��������������� ����� ����� ����, ����� � ������, � ��� �� ������� ���� ������������.",
	L"�������� ��������������� ����� ����� ����, ����� � ������.",
	L"�������� ����� ����� ��� �������� \n������ ������� ����� �����.",
	L"\n(�����: ��� ����������� �������� ��� ��� �����.)",
};

STR16 sColorChoiceExplanationTexts[]=
{
	L"���� �����",	//Hair Color
	L"���� ����",	//Skin Color
	L"���� �����",	//Shirt Color
	L"���� ������",	//Pants Color
	L"���������� ������������",	//Normal Body
	L"����������� ������������",	//Big Body
};

STR16 gzIMPDisabilityTraitText[]=
{
	L"�������",	//No Disability
	L"��������������� ����",		//Heat Intolerant
	L"�������",		//Nervous
	L"�����������",	//Claustrophobic
	L"�� ������� �������",	//Nonswimmer
	L"������ ���������",	//Fear of Insects
	L"����������",		//Forgetful
	L"��������",		//Psychotic
	L"I.M.P.: ����������",	//I.M.P. Disabilities
};

// HEADROCK HAM 3.6: Error strings for assigning a merc to a facility
STR16 gzFacilityErrorMessage[]=
{
	L"%s �� ������� ���� ����� ��������� ��� ��������.",
	L"%s �� ������� �������� ����� ��������� ��� ��������.",
	L"%s �� ������� ����������� ����� ��������� ��� ��������.",
	L"%s �� ������� �������� ����� ��������� ��� ��������..",
	L"%s �� ������� �������� ����� ��������� ��� ��������.",
	L"%s �� ������� �������� ����� ��������� ��� ��������.",
	// 6 - 10
	L"%s �� ���������� ������ ����������� �����, ����� ��������� ��� ��������.",
	L"%s �� ���������� ������ ����� ��������, ����� ��������� ��� ��������.",
	L"%s �� ���������� ������� ���������, ����� ��������� ��� ��������.",
	L"%s �� ���������� ������ ����� ����������, ����� ��������� ��� ��������.",
	L"%s �� ���������� �����, ����� ��������� ��� ��������.",
	// 11 - 15
	L"� %s ������� ������ ������ ���, ����� ��������� ��� ��������",
	L"%s ������� �����(�), ����� ��������� ��� ��������.",
	L"� ������ %s ��� ���� �� ��������. ������� ������������ ��������� ���� ������.",
	L"������� ����� ����� ��� �������� � %s.",
	L"������� ����� ����� ��� ��������� ��� ������ � %s.",
	// 16 - 20
	L"%s �� ����� ����� ����, ������� ��������� � �������.",
	L"%s �������(�) ����� %s ���� ������� � ������� %s!",
	L"%s �������(�) ����� %s ���� ������� ��� %s � %s!",
	L"%s �������(�) ������ ���� �������(�) � ������� %s, � ������� ���������������� ����������� ������!",
	L"%s �������(�) ������ ���� �������(�) ��� %s � %s, � ������� ���������������� ����������� ������!",
	// 21 - 25
	L"%s �������(�) ������ ���� �������(�) � ������� %s. ������ ��������������.",
	L"%s �������(�) ������ ���� �������(�) ��� %s � %s. ������ ��������������.",
	L"������ ������ %s ���������� ���, ��� %s ��������� � �� ������.",
	L"������ ������ %s ���������� ������� %s � %s.",
	L"%s � ������� %s ������ ���������� ������� ��������� �� ��� �������!",
	// 26 - 30
	L"%s ������� ��� %s � %s �����(�) � ��������� ��������� �� ��� �������!",
	L"%s ����(�).",
	L"%s �������(�) � ������� %s, � ��������(�) �������� ������� ������.",
	L"%s �������(�) � �� ����� ���������� ������ ��� %s � %s.",
	L"%s �������(�) ������ � ������� %s.",
	L"%s �������(�) ��������� ������ � ������� %s.",


};

STR16 gzFacilityRiskResultStrings[]=
{
	L"����",	//Strength
	L"�����������",	//Agility
	L"��������",	//Dexterity
	L"���������",	//Wisdom
	L"��������",	//Health
	L"��������",	//Marksmanship
	// 5-10
	L"���������",	//Leadership
	L"��������",	//Mechanical skill
	L"��������",	//Medical skill
	L"����������",	//Explosives skill
};

STR16 gzFacilityAssignmentStrings[]=
{
	L"AMBIENT",
	L"����",	//Staff
	L"�����",
	L"������ �����",
	L"������ %s", // Vehicle name inserted here
	L"������ ������",
	// 6-10
	L"������",
	L"�������",
	L"������� ����",
	L"������� ��������",
	L"������� �����������",
	L"������� ��������",
	// 11-15
	L"������� ��������",
	L"������� ��������",
	L"������� ��������",
	L"������� ���������",
	L"������� ����������",
	// 16-20
	L"������ �� ����",
	L"������ �� ��������",
	L"������ �� �����������",
	L"������ �� ��������",
	L"������ �� ��������",
	// 21-25
	L"������ �� ��������",
	L"������ �� ��������",
	L"������ �� ���������",
	L"������ �� ����������",
	L"������ �� ����",
	// 26-30
	L"������ �� ��������",
	L"������ �� �����������",
	L"������ �� ��������",
	L"������ �� ��������",
	L"������ �� ��������",
	// 30-35
	L"������ �� ��������",
	L"������ �� ���������",
	L"������ �� ����������",
};

STR16 Additional113Text[]=
{
	L"��� ������� Jagged Alliance 2 v1.13 � ������� ������ ��������� ���������� 16-������ �������� ������������� ������",
};


STR16 sEnemyTauntsFireGun[]=
{
	L"Suck on this!",
	L"Say hello to my lil' friend!",
	L"Come get some!",
	L"You're mine!",
	L"Die!",
	L"You scared, motherfucker?",
	L"This will hurt!",
	L"Come on you bastard!",
	L"Come on! I don't got all day!",
	L"Come to daddy!",
	L"You'll be six feet under in no time!",
	L"Gonna send ya home in a pine box, loser!",
	L"Hey, wanna play?",
	L"You should have stayed home, bitch!",
	L"Sucker!",
};

STR16 sEnemyTauntsFireLauncher[]=
{

	L"Barbecue time!",
	L"I got a present for ya!",
	L"Bam!",
	L"Smile!",
};

STR16 sEnemyTauntsThrow[]=
{
	L"Catch!",
	L"Here ya go!",
	L"Pop goes the weasel.",
	L"This one's for you.",
	L"Muahaha!",
	L"Catch this, swine!",
	L"I like this.",
};

STR16 sEnemyTauntsChargeKnife[]=
{
	L"Gonna scalp ya, sucker!",
	L"Come to papa.",
	L"Show me your guts!",
	L"I'll rip you to pieces!",
	L"Motherfucker!",
};

STR16 sEnemyTauntsRunAway[]=
{
	L"We're in some real shit...",
	L"They said join the army. Not for this shit!",
	L"I've had enough!",
	L"Oh my God!",
	L"They ain't paying us enough for this shit..",
	L"Mommy!",
	L"I'll be back! With friends!",

};

STR16 sEnemyTauntsSeekNoise[]=
{
	L"I heard that!",
	L"Who's there?",
	L"What was that?",
	L"Hey! What the...",

};

STR16 sEnemyTauntsAlert[]=
{
	L"They're here!",
	L"Now the fun can start!",
	L"I hoped this would never happen..",

};

STR16 sEnemyTauntsGotHit[]=
{
	L"Aaaggh!",
	L"Ugh!",
	L"This.. hurts!",
	L"You fuck!",
	L"You will regret.. uhh.. this.",
	L"What the..!",
	L"Now you have.. pissed me off.",

};

STR16	gzNewLaptopMessages[]=
{
	L"����������� ���� ����. �����������!",
	L"�������� ����������",
	L"This special press preview of Jagged Alliance 2: Unfinished Business contains the only first 6 sector maps. The final version of the game will feature many more - please see the included readme file for details.",
};

STR16	zNewTacticalMessages[]=
{
	L"���������� ��������� � ������ ��������.",
	L"�� �� ������ ������ %s",
	L"����������� ��������� ������������ ����� � ��������� ��������� ����� �� ��� ������, ���� �� ��� �� �������� ������������, ������������� ����.",
	L"������� %s - ���� ����������� ���������������� '���� ����� �� ���'. �� ����� ��������� �������� ��� ������������ ����������.",
	L"�������",
	L"� ������� ���-�� ����...",
	L"�������� �������",
	L"����� �������",
	L"����� �������� �� ����� ���������� �����.",
	L"��� ��� ��� ������� ������� �������, �� �� �� ������� ������ ����� ���������. ��������, ������ ��� ����� ��������� ���� �� ����������� ���, ��� ������ ���� ������!",
	L"%s ������ ������������� ����� ��� ����� ������. �������, ��� ��� ������� ������� ������ ��������.",  //the %s is the name of a merc.  @@@  Modified
	L"����� ��������� �������, ����������� ���������� ��������� �������, %s �����, ��� �� ��� ��� ��������. � ������� ���������� ���������� ������� ������� ��� ������� �� ��� �����. ����� ����, ��� ����� ������� ���������� ����� �������� ����.",
	L"������ ������ ����������, %s ��������, ��� ���������� ���� ����� ��������, � ����� ������ ��������� ��� ����.  %s �� ���������� �������, � ������ ����� ������� ������ ����������. ������, ��� ����� ������� ������ ��� ����...",
	L"� ������ ���� �� ������� ����� \"�������� ����\" � ������ �� ������ ������������ �� ����� ���.",
	L"(������ ����������� �� ����� ���)",
	L"������� �������� ������� 30 ��������.",
	L"������� �������� �� �������.",
	L"��������: �� ��������� ( %S )",
	L"��������: %S",
	L"�� ������� �������� %S. ��� �������� �������� ������������ ������������ �������� Unfinished Business. �� �������, ��� ������ ������ �������� %S?",
	L"����� ��������������� ����������, ������� �������� �� ��������� �� ������.",
};

#endif //RUSSIAN
