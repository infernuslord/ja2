#ifndef _UNDERGROUNDINIT_H
#define _UNDERGROUNDINIT_H

#include "Types.h"

extern BOOLEAN LetLuaBuildUndergroundSectorInfoList();
extern BOOLEAN locationStringToCoordinates(std::string loc, UINT8* x, UINT8* y, UINT8* z);

#endif
