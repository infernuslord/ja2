#pragma setlocale("RUSSIAN")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25RussianText.h"
#else
	#include "Language Defines.h"
	#ifdef RUSSIAN
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25RussianText_public_symbol(void){;}

#ifdef RUSSIAN

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"����� ������",
	L"���������� ���",
	L"�����������",
	L"������ ��������",
	L"�������",
	L"����������",
	L"������� ������",
	L"�������������� ������",
	L"����������",
	L"�������� � ���� ���",
	L"�������� ������",
	L"�������",
	L"��������",
	L"������ ���������",

	L"���",
	L"I.M.P.: �������������",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"�� ������� ����� \"�������� ����\". ��������� ���� ������ ������� �������, ��� ��� �� �� ������� ��������� ����, ����� ���� �������� ����� ���������� � ����� ������� � �����������. �� ����� ���� ���� ����� ������ ����� ���������. �� �������, ��� ������� ������ � ������ \"�������� ����\"?",
};

STR16 gzDisplayCoverText[]=
{
	L"���������: %d/100 %s, ������������: %d/100",			//Cover: %d/100 %s, Brightness: %d/100
	L"�������������� ������: %d/%d ��., ���� �������: %d/100",	//Gun Range: %d/%d tiles, Chance to hit: %d/100
	L"��������� ��������� ������� ��� ������� � �����",		//Disabling cover display
	L"������� ���� ������",					//Showing mercenary view
	L"������� ���� ��� �������",				//Showing danger zones for mercenary
	L"�������", //Wood //wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"�����",	//Urban
	L"�������",	//Desert
	L"����", //Snow //NOT USED!!!
	L"��� � �������",	//Wood and Desert
	L"" // yes empty for now
};


#endif
