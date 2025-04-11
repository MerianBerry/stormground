#ifndef AMP_H
#define AMP_H
#include "scl.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define amp_logInfo(L, msg)          \
  {                                  \
    lua_pushstring (L, "amp");       \
    lua_pushstring (L, msg);         \
    lua_getglobal (L, "sg");         \
    lua_getfield (L, -1, "logInfo"); \
    lua_pcall (L, 2, 0, 0);          \
  }

#endif