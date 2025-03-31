#include "sg_lua.h"
#include "sg_event.h"

char const *sg_luaTrace (lua_State *L) {
  luaL_dostring (L,
    "return string.format('at %s():%s:%d',"
    "debug.getinfo(2, 'n').name,"
    "debug.getinfo(3, 'S').short_src,"
    "debug.getinfo(3, 'l').currentline)");
  char const *s__ = lua_tostring (L, -1);
  return s__;
}

static lua_State *baseInit (SG *sg) {
  lua_State *L = luaL_newstate();
  sg->L        = L;
  luaL_openlibs (L);

  lua_getglobal (L, "os");
  lua_pushnil (L);
  lua_setfield (L, -2, "exit");
  lua_pop (L, 1);
  lua_pushnil (L);
  lua_setglobal (L, "assert");

  lua_pushinteger (L, (intptr_t)sg);
  lua_setglobal (L, "_SG");

  lua_newtable (L);

  lua_newtable (L);
  lua_setfield (L, -2, "_tickCBs");

  lua_setglobal (L, "sg");
  return L;
}

int sg_luaInit (SG *sg) {
  lua_State *L = luaL_newstate();
  sg->L        = L;
  luaL_openlibs (L);

  lua_getglobal (L, "os");
  lua_pushnil (L);
  lua_setfield (L, -2, "exit");
  lua_pop (L, 1);
  lua_pushnil (L);
  lua_setglobal (L, "assert");

  lua_pushinteger (L, (intptr_t)sg);
  lua_setglobal (L, "_SG");

  lua_newtable (L);

  lua_newtable (L);
  lua_setfield (L, -2, "_tickCBs");

  lua_setglobal (L, "sg");
  return 0;
};

int sg_loadLibs (SG *sg) {
  sg_loadEventLib (sg->L);
  return 0;
}

int sg_runInit (SG *sg, char const *dir) {
  lua_State  *L      = sg->L;
  char const *script = scl_fmt ("%s/init.lua", dir);

  if (!scl_exists (script)) {
    free ((void *)script);
    sg_echo (1);
    sg_logErrorf ("sg", "init.lua does not exist in %s", dir);
    sg_echo (0);
    return 1;
  }

  if (luaL_dofile (L, script)) {
    char const *err = lua_tostring (L, -1);
    printf ("%s\n", err);
  }
  free ((void *)script);

  return 0;
}

int sg_runTicks (SG *sg) {
  lua_State *L = sg->L;

  lua_getglobal (L, "sg");
  lua_getfield (L, -1, "_tickCBs");
  int n = lua_objlen (L, -1);
  for (int i = 0; i < n; i++) {
    lua_rawgeti (L, -1, i + 1);
    if (!lua_testtype (L, -1, LUA_TFUNCTION)) {
      lua_pop (L, 3);
      sg_throwLuaError (L, "unexpected non-function tick callback");
      return 1;
    }
    lua_pcall (L, 0, 0, 0);
  }
  lua_pop (L, 2);
  return 0;
}
