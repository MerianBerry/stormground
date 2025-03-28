#include "sg_lua.h"
#include "scl.h"
#include "sg_log.h"
#include "luajit/src/lualib.h"
#include "luajit/src/lauxlib.h"
#include "luajit/src/lj_tab.h"

static lua_State *baseInit (SG *sg) {
  lua_State *L = luaL_newstate();
  luaL_openlibs (L);

  lua_getglobal (L, "os");
  lua_pushnil (L);
  lua_setfield (L, -2, "exit");
  lua_pop (L, 1);
  lua_pushnil (L);
  lua_setglobal (L, "assert");
  return L;
}

int sg_luaInit (SG *sg) {
  lua_State *L = baseInit (sg);

  lua_pushinteger (L, (intptr_t)sg);
  lua_setglobal (L, "_SG");

  lua_createtable (L, 0, 1);

  lua_setglobal (L, "sg");


  sg->L = L;
  return 1;
};

int sg_runBuild (SG *sg, SG_BuildInfo *bi) {
  memset (bi, 0, sizeof (SG_BuildInfo));
  bi->depv = malloc (sizeof (char *) * SG_MAX_DEPS);
  memset (bi->depv, 0, sizeof (char *) * SG_MAX_DEPS);

  lua_State  *L      = baseInit (sg);
  char const *script = scl_fmt ("%s/build.lua", sg->wdir);

  if (!scl_exists (script)) {
    free ((void *)script);
    sg_echoError ("build.lua does not exist in working directory");
    return 1;
  }

  luaL_dofile (L, script);
  free ((void *)script);

  if (!lua_testtype (L, -1, LUA_TTABLE)) {
    sg_echoError ("build.lua does not return a table");
    return 1;
  }

  lua_getfield (L, -1, "plugins");

  if (lua_testtype (L, -1, LUA_TTABLE)) {
    int n = lua_objlen (L, -1);
    for (int i = 1; i <= n; i++) {
      // plugins table element
      lua_rawgeti (L, -1, i);
      // element is a simple plugin string
      if (lua_testtype (L, -1, LUA_TSTRING)) {
        char const *s        = lua_tostring (L, -1);
        bi->depv[bi->depc++] = scl_strcopy (s);
        sg_logInfof ("sg", "found plugin %s", s);
      }
      // pop the plugin table element
      lua_pop (L, 1);
    }
  }

  lua_close (L);
  return 0;
}
