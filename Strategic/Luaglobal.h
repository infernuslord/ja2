#ifndef _LUAGLOBAL_H
#define _LUAGLOBAL_H

#include "Types.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

void  IniGlobalGameSetting(lua_State *L);

#endif
