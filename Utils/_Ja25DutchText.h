#ifndef _JA25ENGLISHTEXT__H_
#define _JA25ENGLISHTEXT__H_

extern	STR16 gzIMPSkillTraitsText[];

enum
{
	IMM__IRON_MAN_MODE_WARNING_TEXT,
};
extern	STR16	gzIronManModeWarningText[];

// display cover message (for tactical usually, seperated)
// display cover terrain type info (used in cover information)
enum
{
	DC_MSG__COVER_INFORMATION,
	DC_MSG__GUN_RANGE_INFORMATION,
	DC_MSG__COVER_DRAW_OFF,
	DC_MSG__COVER_DRAW_MERC_VIEW,
	DC_MSG__COVER_DRAW_ENEMY_VIEW,
	DC_TTI__WOOD,
	DC_TTI__URBAN,
	DC_TTI__DESERT,
	DC_TTI__SNOW,
	DC_TTI__WOOD_AND_DESERT,
	DC_TTI__UNKNOWN
};
extern STR16 gzDisplayCoverText[];

#endif


