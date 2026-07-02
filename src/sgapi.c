// #define _XOPEN_SOURCE 700
#include "sgapi.h"

#include <stdio.h>
#include <stdlib.h>
#include "sginput.h"
#include "sgrender.h"

#define LUA_IMPL
#include "minilua.h"

int l_close (lua_State* L) {
  _state.runstate = SG_RUNSTATE_STOP;
  return 0;
}

int l_setScreen (lua_State* L) {
  int t = lua_gettop (L);
  if (t < 2)
    return lua_pushnil (L), 1;
  _state.width  = clampf (lua_tonumber (L, 1), 6.f, SG_MAX_MONWIDTH);
  _state.height = clampf (lua_tonumber (L, 2), 6.f, SG_MAX_MONHEIGHT);
  return 0;
}

int l_setCursor (lua_State* L) {
  int t = lua_gettop (L);
  if (t < 2)
    return lua_pushnil (L), 1;
  _state.fakeCurX = lua_tonumber (L, 1);
  _state.fakeCurY = lua_tonumber (L, 2);
  return 0;
}

static luaL_Reg const libfuncs[] = {
    {"close",     l_close    },
    {"setScreen", l_setScreen},
    {"setCursor", l_setCursor},
    {NULL,        NULL       },
};

lua_State* sgNewScript() {
  lua_State* L = luaL_newstate();
  luaL_openlibs (L);

  lua_getglobal (L, "os");
  lua_pushnil (L);
  lua_setfield (L, -2, "execute");
  lua_pop (L, 1);

  lua_newtable (L);

  luaL_setfuncs (L, libfuncs, 0);
  sgInputOpenLibs (L);
  sgRenderOpenLibs (L);

  lua_setglobal (L, "stormground");
  return L;
}
