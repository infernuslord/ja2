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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SANDRO - New STOMP laptop strings
//these strings match up with the defines in IMP Skill trait.cpp
STR16 gzIMPSkillTraitsText[]=
{
	// made this more elegant
	L"Взлом замков",
	L"Рукопашный бой",
	L"Электроника",
	L"Ночные операции",
	L"Метание",
	L"Инструктор",
	L"Тяжелое оружие",
	L"Автоматическое оружие",
	L"Скрытность",
	L"Ловкач",
	L"Холодное оружие",
	L"Снайпер",
	L"Камуфляж",
	L"Боевые искусства",

	L"Нет",
	L"I.M.P.: Специализация",
	L"(эксперт)",
};

//added another set of skill texts for new major traits
STR16 gzIMPSkillTraitsTextNewMajor[]=
{
	L"Автоматчик",	//Auto Weapons
	L"Гренадёр",	//Heavy Weapons
	L"Стрелок",	//Marksman
	L"Охотник",	//Hunter
	L"Ковбой",	//Gunslinger
	L"Боксёр",	//Hand to Hand
	L"Старшина",	//Deputy
	L"Механик-электронщик",	//Technician
	L"Санитар",	//Paramedic

	L"Нет",
	L"I.M.P.: Основные навыки",	//I.M.P. Major Traits
	// second names
	L"Пулемётчик",	//Machinegunner
	L"Артиллерист",	//Bombardier
	L"Снайпер",	//Sniper
	L"Лесничий",	//Ranger
	L"Пистолетчик",	//Gunfighter
	L"Боевые искусства",	//Martial Arts
	L"Командир",	//Squadleader
	L"Инженер",	//Engineer
	L"Доктор",	//Doctor
};

//added another set of skill texts for new minor traits
STR16 gzIMPSkillTraitsTextNewMinor[]=
{
	L"Ловкач",	//Ambidextrous
	L"Мастер клинка",	//Melee
	L"Мастер по метанию",	//Throwing
	L"Человек ночи",	//Night Ops
	L"Бесшумный убийца",	//Stealthy
	L"Спортсмен",	//Athletics
	L"Культурист",	//Bodybuilding
	L"Подрывник",	//Demolitions
	L"Инструктор",	//Teaching
	L"Разведчик",	//Scouting

	L"Нет",
	L"I.M.P.: Дополнительные навыки",	//I.M.P. Minor Traits
};

//these texts are for help popup windows, describing trait properties
STR16 gzIMPMajorTraitsHelpTextsAutoWeapons[]=
{
	L"+%d%s Chance to Hit with Assault Rifles\n",
	L"+%d%s Chance to Hit with SMGs\n",
	L"+%d%s Chance to Hit with LMGs\n",
	L"-%d%s APs needed to fire with LMGs on autofire or burst mode\n",
	L"-%d%s APs needed to ready light machine guns\n",
	L"Auto fire/burst chance to hit penalty is reduced by %d%s\n",
	L"Reduced chance for shooting unwanted bullets on autofire\n",

};
STR16 gzIMPMajorTraitsHelpTextsHeavyWeapons[]=
{
	L"-%d%s APs needed to fire grenade launchers\n",
	L"-%d%s APs needed to fire rocket launchers\n",
	L"+%d%s chance to hit with grenade launchers\n",
	L"+%d%s chance to hit with rocket launchers\n",
	L"-%d%s APs needed to fire mortar\n",
	L"Reduce penalty for mortar CtH by %d%s\n",
	L"+%d%s damage to tanks with heavy weapons, grenades and explosives\n",
	L"+%d%s damage to other targets with heavy weapons\n",

};
STR16 gzIMPMajorTraitsHelpTextsSniper[]=
{
	L"+%d%s Chance to Hit with Sniper Rifles\n",
	L"-%d%s effective range to target with all weapons\n",
	L"+%d%s aiming bonus per aim click (except for handguns)\n",
	L"+%d%s damage on shot",
	L" plus",
	L" per every aim click",
	L" after first",
	L" after second",
	L" after third",
	L" after fourth",
	L" after fifth",
	L" after sixth",
	L" after seventh",
	L"-%d%s APs needed to chamber a round with bolt-action rifles \n",
	L"Adds one more aim click for rifle-type guns\n",
	L"Adds %d more aim clicks for rifle-type guns\n",

};
STR16 gzIMPMajorTraitsHelpTextsRanger[]=
{
	L"+%d%s Chance to Hit with Rifles\n",
	L"+%d%s Chance to Hit with Shotguns\n",
	L"-%d%s APs needed to pump Shotguns\n",
	L"+%d%s group travelling speed between sectors if traveling by foot\n",
	L"+%d%s group travelling speed between sectors if traveling in vehicle (except helicopter)\n",
	L"-%d%s less energy spent for travelling between sectors\n",
	L"-%d%s weather penalties\n",
	L"+%d%s camouflage effectiveness\n",
	L"-%d%s worn out speed of camouflage by water or time\n",

};
STR16 gzIMPMajorTraitsHelpTextsGunslinger[]=
{
	L"-%d%s APs needed to fire with pistols and revolvers\n",
	L"+%d%s effective range with pistols and revolvers\n",
	L"+%d%s chance to hit with pistols and revolvers\n",
	L"+%d%s chance to hit with machine pistols",
	L" (on single shots only)",
	L"+%d%s aiming bonus per click with pistols, machine pistols and revolvers\n",
	L"-%d%s APs needed to ready pistols and revolvers\n",
	L"-%d%s APs needed to reload pistols, machine pistols and revolvers\n",
	L"Adds %d more aim click for pistols, machine pistols and revolvers\n",
	L"Adds %d more aim clicks for pistols, machine pistols and revolvers\n",

};
STR16 gzIMPMajorTraitsHelpTextsMartialArts[]=
{
	L"-%d%s AP cost of hand to hand attacks(bare hands or with brass knuckles)\n",
	L"+%d%s chance to hit with hand to hand attacks with bare hands\n",
	L"+%d%s chance to hit with hand to hand attacks with brass knuckles\n",
	L"+%d%s damage of hand to hand attacks(bare hands or with brass knuckles)\n",
	L"+%d%s breath damage of hand to hand attacks(bare hands or with brass knuckles)\n",
	L"Enemy knocked out due to your HtH attacks takes slightly longer to recuperate\n",
	L"Enemy knocked out due to your HtH attacks takes longer to recuperate\n",
	L"Enemy knocked out due to your HtH attacks takes much longer to recuperate\n",
	L"Enemy knocked out due to your HtH attacks takes very long to recuperate\n",
	L"Enemy knocked out due to your HtH attacks takes extremely long to recuperate\n",
	L"Enemy knocked out due to your HtH attacks takes long hours to recuperate\n",
	L"Enemy knocked out due to your HtH attacks probably never stand up\n",
	L"Focused (aimed) punch deals +%d%s more damage\n",
	L"Your special spinning kick deals +%d%s more damage\n",
	L"+%d%s change to dodge hand to hand attacks\n",
	L"+%d%s on top chance to dodge HtH attacks with bare hands",
	L" or brass knuckles",
	L" (+%d%s with brass knuckles)",
	L"+%d%s on top chance to dodge HtH attacks with brass knuckles\n",
	L"+%d%s chance to dodge attacks by any melee weapon\n",
	L"-%d%s APs needed to steal weapon from enemy hands\n",
	L"-%d%s APs needed to change stance (stand, crouch, lie down), turn around, climb on/off roof and jump obstacles\n",
	L"-%d%s APs needed to change stance (stand, crouch, lie down)\n",
	L"-%d%s APs needed to turn around\n",
	L"-%d%s APs needed to climb on/off roof and jump obstacles\n",
	L"+%d%s chance to kick doors in\n",
	L"You gain special animations for hand to hand combat\n",

};
STR16 gzIMPMajorTraitsHelpTextsSquadleader[]=
{
	L"+%d%s APs per round of other mercs in vicinity\n",
	L"+%d effective exp level of other mercs in vicinity, which have lesser level than the %s\n",
	L"+%d effective exp level to count as a standby when counting friends' bonus for suppression\n",
	L"+%d%s total suppression tolerance for other mercs in the vicinity and %s himself\n",
	L"+%d morale gain for other mercs in the vicinity\n",
	L"-%d morale loss for other mercs in the vicinity\n",
	L"The vicinity for bonuses is %d tiles",
	L" (%d tiles with extended ears)",
	L"(Max simultaneous bonuses for one soldier is %d)\n",
	L"+%d%s fear resistence of %s\n",
	L"Drawback: %dx morale loss for %s's death for all other mercs\n",

};
STR16 gzIMPMajorTraitsHelpTextsTechnician[]=
{
	L"+%d%s to repairing speed\n",
	L"+%d%s to lockpicking (normal/electronic locks)\n",
	L"+%d%s to disarming electronic traps\n",
	L"+%d%s to attaching special items and combining things\n",
	L"+%d%s to unjamming a gun in combat\n",
	L"Reduce penalty to repair electronic items by %d%s\n",
	L"Increased chance to detect traps and mines (+%d detect level)\n",
	L"+%d%s CtH of robot controlled by the %s\n",
	L"%s trait grants you the ability to repair the robot\n",
	L"Reduced penalty to repair speed of the robot by %d%s\n",
};
STR16 gzIMPMajorTraitsHelpTextsDoctor[]=
{
	L"Has ability to perform surgical intervention by using medical bag on wounded soldier\n",
	L"Surgery instantly returns %d%s of lost health back.",
	L" (This drains the medical bag a lot.)",
	L"Can heal lost stats (from critical hits) by the",
	L" surgery or",
	L" doctor assignment.\n",
	L"+%d%s effectiveness on doctor-patient assignment\n",
	L"+%d%s bandaging speed\n",
	L"+%d%s natural regeneration speed for all soldiers in the same sector",
	L" (max %d of these bonuses per sector stack)",

};
STR16 gzIMPMajorTraitsHelpTextsNone[]=
{
	L"Нет преимуществ",	//No bonuses
};

STR16 gzIMPMinorTraitsHelpTextsAmbidextrous[]=
{
	L"Reduce penalty to shoot dual weapons by %d%s\n",
	L"+%d%s speed of reloading guns with magazines\n",
	L"+%d%s speed of reloading guns with loose rounds\n",
	L"-%d%s APs needed to pickup items\n",
	L"-%d%s APs needed to work backpack\n",
	L"-%d%s APs needed to handle doors\n",
	L"-%d%s APs needed to plant/remove bombs and mines\n",
	L"-%d%s APs needed to attach items\n",
};
STR16 gzIMPMinorTraitsHelpTextsMelee[]=
{
	L"-%d%s APs needed to attack by blades\n",
	L"+%d%s chance to hit with blades\n",
	L"+%d%s chance to hit with blunt melee weapons\n",
	L"+%d%s damage with blades\n",
	L"+%d%s damage with blunt melee weapons\n",
	L"Aimed attack with any melee weapon deals +%d%s damage\n",
	L"+%d%s chance to dodge attack by melee blades\n",
	L"+%d%s on top chance to dodge melee blades if holding a blade\n",
	L"+%d%s chance to dodge attack by blunt melee weapons\n",
	L"+%d%s on top chance to dodge blunt melee weapons if holding a blade\n",

};
STR16 gzIMPMinorTraitsHelpTextsThrowing[]=
{
	L"-%d%s basic APs needed to throw blades\n",
	L"+%d%s max range when throwing blades\n",
	L"+%d%s chance to hit when throwing blades\n",
	L"+%d%s chance to hit when throwing blades per aim click\n",
	L"+%d%s damage with throwing blades\n",
	L"+%d%s damage with throwing blades per aim click\n",
	L"+%d%s chance to inflict critical hit with throwing blade if not seen or heard\n",
	L"+%d critical hit with throwing blade multiplier\n",
	L"Adds %d more aim click for throwing blades\n",
	L"Adds %d more aim clicks for throwing blades\n",

};
STR16 gzIMPMinorTraitsHelpTextsNightOps[]=
{
	L"+%d to effective sight range in the dark\n",
	L"+%d to general effective hearing range\n",
	L"+%d additional hearing range in the dark\n",
	L"+%d to interrupts modifier in the dark\n",
	L"-%d need to sleep\n",

};
STR16 gzIMPMinorTraitsHelpTextsStealthy[]=
{
	L"-%d%s APs needed to move quietly\n",
	L"+%d%s chance to move quietly\n",
	L"+%d%s stealth (being 'invisible' if unnoticed)\n",
	L"Reduced cover penalty for movement by %d%s\n",

};
STR16 gzIMPMinorTraitsHelpTextsAthletics[]=
{
	L"-%d%s APs needed for moving (running, walking, squatting, crawling, swimming, etc.)\n",
	L"-%d%s energy spent for movement, roof-climbing, obstacle-jumping, swimming, etc.\n",
};
STR16 gzIMPMinorTraitsHelpTextsBodybuilding[]=
{
	L"Has %d%s damage resistance\n",
	L"+%d%s effective strength for carrying weight capacity \n",
	L"Reduced energy lost when hit by HtH attack by %d%s\n",
	L"Increased damage needed to fall down if hit to legs by %d%s\n",

};
STR16 gzIMPMinorTraitsHelpTextsDemolitions[]=
{
	L"-%d%s APs needed to throw grenades\n",
	L"+%d%s max range when throwing grenades\n",
	L"+%d%s chance to hit when throwing grenades\n",
	L"+%d%s damage of set bombs and mines\n",
	L"+%d%s to attaching detonators check\n",
	L"+%d%s to planting/removing bombs check\n",
	L"Decreases chance enemy will detect your bombs and mines (+%d bomb level)\n",
	L"Increased chance shaped charge will open the doors (damage multiplied by %d)\n",

};
STR16 gzIMPMinorTraitsHelpTextsTeaching[]=
{
	L"+%d%s bonus to militia training speed\n",
	L"+%d%s bonus to effective leadership for determining militia training\n",
	L"+%d%s bonus to teaching other mercs\n",
	L"Skill value counts to be +%d higher for being able to teach this skill to other mercs\n",
	L"+%d%s bonus to train stats through self-practising assignment\n",

};
STR16 gzIMPMinorTraitsHelpTextsScouting[]=
{
	L"+%d to effective sight range with scopes on weapons\n",
	L"+%d to effective sight range with binoculars (and scopes separated from weapons)\n",
	L"-%d tunnel vision with binoculars (and scopes separated from weapons)\n",
	L"If in sector, adjacent sectors will show exact number of enemies\n",
	L"If in sector, adjacent sectors will show presence of enemies, if any\n",
	L"Prevents enemy ambushes on your squad\n",
	L"Prevents bloodcat ambushes on your squad\n",

};
STR16 gzIMPMinorTraitsHelpTextsNone[]=
{
	L"Нет преимуществ",	//No bonuses
};

STR16 gzIMPOldSkillTraitsHelpTexts[]=
{
	L"+%d%s bonus to lockpicking\n",
	L"+%d%s hand to hand chance to hit\n",
	L"+%d%s hand to hand damage\n",
	L"+%d%s chance to dodge hand to hand attacks\n",
	L"Eliminates the penalty to repair and handle\nelectronic things (locks, traps, rem. detonators, robot, etc.)\n",
	L"+%d to effective sight range in the dark\n",
	L"+%d to general effective hearing range\n",
	L"+%d extra hearing range in the dark\n",
	L"+%d to interrupts modifier in the dark\n",
	L"-%d need to sleep\n",
	L"+%d%s max range when throwing anything\n",
	L"+%d%s chance to hit when throwing anything\n",
	L"+%d%s chance to instantly kill by throwing knife if not seen or heard\n",
	L"+%d%s bonus to militia training and other mercs instructing speed\n",
	L"+%d%s effective leadership for militia training calculations\n",
	L"+%d%s chance to hit with rocket/greande launchers and mortar\n",
	L"Auto fire/burst chance to hit penalty is divided by %d\n",
	L"Reduced chance for shooting unwanted bullets on autofire\n",
	L"+%d%s chance to move quietly\n",
	L"+%d%s stealth (being 'invisible' if unnoticed)\n",
	L"Eliminates the CtH penalty when firing two weapons at once\n",
	L"+%d%s chance to hit with melee blades\n",
	L"+%d%s chance to dodge attacks by melee blades if having blade in hands\n",
	L"+%d%s chance to dodge attacks by melee blades if having anything else in hands\n",
	L"+%d%s chance to dodge hand to hand attacks if having blade in hands\n",
	L"-%d%s effective range to target with all weapons\n",
	L"+%d%s aiming bonus per aim click\n",
	L"Provides permanent camouflage\n",
	L"+%d%s hand to hand chance to hit\n",
	L"+%d%s hand to hand damage\n",
	L"+%d%s chance to dodge hand to hand attacks if having empty hands\n",
	L"+%d%s chance to dodge hand to hand attacks if not having empty hands\n",
	L"+%d%s chance to dodge attacks by melee blades\n",
	L"Can perform spinning kick attack on weakened enemies to deal double damage\n",
	L"You gain special animations for hand to hand combat\n",
	L"Нет преимуществ",	//No bonuses
};

STR16 gzIMPNewCharacterTraitsHelpTexts[]=
{
//I.M.P. Character Traits help text
//Neutral
	L"плюсы: Нет преимуществ.\n \nминусы: Без изъян.",
//Sociable
	L"плюсы: Лучше работает в команде.\n \nминусы: Боевой дух не растёт, когда наёмник работает один.",
//Loner
	L"плюсы: Лучше работает в одиночестве.\n \nминусы: Боевой дух не растёт в присутствии других бойцов.",
//Optimist
	L"плюсы: Боевой дух растет быстрее, а снижается медленнее обычного.\n \nминусы: Шанс обнаружить мины и ловушки ниже среднего.",
//Assertive
	L"плюсы: Лучше ладит с людьми и тренирует ополчение.\n \nминусы: Действия других бойцов не влияют на его боевой дух.",
//Intellectual
	L"плюсы: Немного быстрее обучается.\n \nминусы: Обладает меньшим сопротивлением страху и подавлению.",
//Primitive
	L"плюсы: Устаёт медленнее других, если не работает как врач, ремонтник, тренер или ученик.\n \nминусы: Его мудрость, лидерство, взрывное дело, механика и медицина растут медленнее обычного.",
//Aggressive
	L"плюсы: Имеет бонус к стрельбе очередями и урону в рукопашной. \nПри убийстве врага боевой дух растёт больше, чем у других.\n \nминусы: Хуже исполняет обязанности, для которых требуется терпение: \nремонт, вскрытие замков, снятие ловушек, лечение, тренировка ополчения.",
//Phlegmatic
	L"плюсы: Лучше исполняет обязанности, требующие терпения: \nремонт, вскрытие замков, снятие ловушек, лечение, тренировка ополчения.\n \nминусы: Имеет меньший шанс перехватить ход врага.",
//Dauntless
	L"плюсы: Имеет повышенное сопротивление подавлению и страху. \nБоевой дух при ранениях и гибели товарищей понижается медленнее, чем у других.\n \nминусы: Может быть с большей вероятностью поражен во время движения.",
//Pacifist
	L"плюсы: Боевой дух повышается при выполнении небоевых заданий (кроме тренировки ополчения).\n \nминусы: Убийство врагов не повышает боевой дух.",
//Malicious
	L"плюсы: Имеет больший шанс нанести болезненные раны и травмы, приводящие к ухудшению параметров.\n \nминусы: Имеет проблемы в общении и быстро теряет боевой дух, если не сражается.",
//Show-off
	L"плюсы: Лучше работает в компании представителей противоположного пола.\n \nминусы: Боевой дух бойцов того же пола в его присутствии растёт медленнее.",
};

STR16 gzIMPDisabilitiesHelpTexts[]=
{
	L"Никакого влияния.",
	L"Уменьшается работоспособность и возникают проблемы с дыханием \nесли находится в пустынной или тропической местности.",
	L"Может впасть в панику если оставить одного в определённых ситуациях.",
	L"Понижается работоспособноть в замкнутых помещениях, подземельях.",
	L"При попытке плыть может с лёгкостью утонуть.",
	L"При виде больших насекомых может впасть в крайности и наворотить дел... \nНахождение в тропических лесах так же понижает его работоспособность.",
	L"Иногда забывает приказы, из-за чего теряет \nнекоторое количество Очков Действия во время боя.",
	L"Иногда бывают приступы помутнения рассудка. \nВ такие моменты он расстреливает весь магазин до последней пули. \nПадает духом, если его оружие этого не позволяет.",
};


STR16 gzIMPProfileCostText[]=
{
	L"Составление вашей харрактеристики стоит %d$. Подтвердить оплату? ",
};

STR16 zGioNewTraitsImpossibleText[]=
{
	L"Нельзя выбрать новые умения IMP персонажа с отключенным PROFEX. Проверьте значение файла настроек JA2_Options.ini, ключ: READ_PROFILE_DATA_FROM_XML.",	//You cannot choose the New Trait System with PROFEX utility deactivated. Check your JA2_Options.ini for entry: READ_PROFILE_DATA_FROM_XML.
};

//@@@:  New string as of March 3, 2000.
STR16	gzIronManModeWarningText[]=
{
	L"Ваш выбор позволит сохраняться лишь в \"мирное время\". Проходить игру станет гораздо сложнее, так как сохраняться вы сможете только между боями. После старта игры изменить эту настройку нельзя. Вы уверены, что готовы расстаться с возможностью сохраняться в бою?",
};

STR16 gzDisplayCoverText[]=
{
	L"Местность: %d/100 %s, Освещённость: %d/100",
	L"Дальнобойность оружия: %d/%d ед., шанс попасть: %d/100",
	L"Отключено выделение видимых зон наёмника и врага",
	L"Видимые зоны наёмнка",
	L"Опасные зоны для наёмника",
	L"Джунгли", //Wood //wanted to use jungle , but wood is shorter in german too (dschungel vs wald)
	L"Город",
	L"Пустыня",
	L"Снег",	//NOT USED!!!
	L"Лес и пустыня",
	L"" // yes empty for now
};


#endif
