#ifndef _DISPLAY_COVER__H_
#define _DISPLAY_COVER__H_

void DisplayRangeToTarget( SOLDIERTYPE *pSoldier, INT32 sTargetGridNo );
void DisplayCover(const BOOLEAN& forceUpdate = FALSE);

void SwitchToMercView();
void SwitchToEnemyView();
void SwitchViewOff();

void ToggleMercView();
void ToggleEnemyView();

void SwitchCoverDrawMode();

#endif
