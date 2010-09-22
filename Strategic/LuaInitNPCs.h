#ifndef _UNDERGROUNDINIT_H
#define _UNDERGROUNDINIT_H

#include "Types.h"

extern BOOLEAN LetLuaGameInit(UINT8 Init);

#ifdef JA2UB
extern BOOLEAN LuaInitStrategicLayer(UINT8 Init);
extern BOOLEAN LetLuaMakeBadSectorListFromMapsOnHardDrive(UINT8 Init);
#endif

//Intro
extern BOOLEAN LuaIntro(UINT8 Init, UINT32 uiCurrentVideo, INT8 bIntroType, UINT32 iStringToUse);

#endif
