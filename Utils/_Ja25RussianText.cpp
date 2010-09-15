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
	L"Взлом замков",
	L"Рукопашный бой",
	L"Электроника",
	L"Ночные операции",
	L"Метание",
	L"Инструктор",
	L"Тяжелое оружие",
	L"Автоматическое оружие",
	L"Скрытность",
	L"Стрельба с двух рук",
	L"Холодное оружие",
	L"Снайпер",
	L"Камуфляж",
	L"Боевые искусства",

	L"Нет",
	L"I.M.P.: Специализация",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Вы выбрали режим \"Стальная воля\". Проходить игру станет гораздо сложнее, так как вы не сможете сохранять игру, когда ваши наемники будут находиться в одном секторе с противником. Во время игры этот режим нельзя будет отключить. Вы уверены, что желаете играть в режиме \"Стальная воля\"?",
};

STR16 gzDisplayCoverText[]=
{
	L"Местность: %d/100 %s, Освещённость: %d/100",			//Cover: %d/100 %s, Brightness: %d/100
	L"Дальнобойность оружия: %d/%d ед., шанс попасть: %d/100",	//Gun Range: %d/%d tiles, Chance to hit: %d/100
	L"Отключено выделение видимых зон наёмника и врага",		//Disabling cover display
	L"Видимые зоны наёмнка",					//Showing mercenary view
	L"Опасные зоны для наёмника",				//Showing danger zones for mercenary
	L"Джунгли", //Wood //wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Город",	//Urban
	L"Пустыня",	//Desert
	L"Снег", //Snow //NOT USED!!!
	L"Лес и пустыня",	//Wood and Desert
	L"" // yes empty for now
};


#endif
