//#pragma setlocale("CHINESE")
#ifdef PRECOMPILEDHEADERS
	#include "Utils All.h"
	#include "_Ja25Englishtext.h"
#else
	#include "Language Defines.h"
	#ifdef CHINESE
		#include "text.h"
		#include "Fileman.h"
	#endif
#endif

//suppress : warning LNK4221: no public symbols found; archive member will be inaccessible
void this_is_the_Ja25ChineseText_public_symbol(void){;}

#ifdef CHINESE

// VERY TRUNCATED FILE COPIED FROM JA2.5 FOR ITS FEATURES FOR JA2 GOLD

//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	L"开锁",	//"Lock picking",
	L"徒手格斗", //"Hand to hand combat",
	L"电子",	//"Electronics",
	L"夜战",	//"Night operations",
	L"投掷",	//"Throwing",
	L"教学",	//"Teaching",
	L"重武器",	//"Heavy Weapons",
	L"自动武器",	//"Auto Weapons",
	L"潜行",	//"Stealth",
	L"双手武器",	//"Ambidextrous",
	L"刀技",	//"Knifing",
	L"狙击手",	//"Sniper",
	L"伪装",	//"Camouflage",
	L"武术",	//"Martial Arts",

	L"无",	//"None",
	L"I.M.P 专属技能",	//"I.M.P. Specialties",
};
//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
//	L"You have chosen IRON MAN mode. This setting makes the game considerably more challenging as you will not be able to save your game when in a sector occupied by enemies. This setting will affect the entire course of the game.  Are you sure want to play in IRON MAN mode?",
	L"你选择了铁人模式。这将会游戏变得相当有挑战性，因为你无法在敌人占据的分区存档。 这个设置会影响游戏的整个进程。你确认你要在铁人模式下进行游戏吗?",
};

STR16 gzDisplayCoverText[]=
{
	L"隐蔽程度: %d/100 %s, 光亮度: %d/100",
	L"武器射程: %d/%d 格, 命中率: %d/100",
	L"关闭隐蔽程度显示",
	L"显示佣兵的视线",
	L"显示佣兵的隐蔽程度",
	L"树林", //本想用丛林, 但树林这词在德文中更短 (dschungel vs wald) // wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"城市",
	L"沙漠",
	L"雪地", // NOT USED!!!
	L"树林和沙漠",
	L"" // yes empty for now
};


#endif
