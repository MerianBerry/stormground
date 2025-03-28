#ifndef SG_LUA_H
#define SG_LUA_H

#include "sg.h"

#define lua_testtype(L, narg, t) (lua_type (L, narg) == t)

typedef struct SG_BuildInfo {
  char const **depv;
  uint32_t     depc;
} SG_BuildInfo;

int sg_luaInit (SG *sg);

int sg_runBuild (SG *sg, SG_BuildInfo *bi);
#endif