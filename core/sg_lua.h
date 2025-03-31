#ifndef SG_LUA_H
#define SG_LUA_H

#include "sg.h"
#include "scl.h"
#include "sg_log.h"

#define lua_testtype(L, narg, t) (lua_type (L, narg) == t)

#define sg_setcfunfield(L, i, name)    \
  lua_pushcfunction ((L), sgl_##name); \
  lua_setfield ((L), (i) - 1, #name)

#define sg_throwLuaError(L, msg)                    \
  {                                                 \
    const char *s__  = sg_luaTrace (L);             \
    const char *fmsg = scl_fmt ("%s %s", s__, msg); \
    sg_echoError (fmsg);                            \
    lua_pushstring (L, fmsg);                       \
    lua_error (L);                                  \
    free ((void *)fmsg);                            \
  }

char const *sg_luaTrace (lua_State *L);

int sg_luaInit (SG *sg);

int sg_loadLibs (SG *sg);

int sg_runInit (SG *sg, char const *dir);

int sg_runTicks (SG *sg);
#endif