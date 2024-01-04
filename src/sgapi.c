#define _XOPEN_SOURCE 700
#include "sgapi.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __LONG_LONG_MAX__
#else
#  error "No good chief"
#endif

#include "lua-5.4.6/src/luaconf.h"
#include "lua-5.4.6/src/lauxlib.h"
#include "lua-5.4.6/src/lua.h"
#include "lua-5.4.6/src/lualib.h"

int l_getdelta (lua_State* L) {
  lua_getglobal (L, "__SGSTATE");
  SGstate* sgs = (SGstate*)lua_tointeger (L, -1);
  lua_pop (L, 1);
  lua_pushnumber (L, sgs->delta);
  return 1;
}

int l_gettime (lua_State* L) {
  lua_getglobal (L, "__SGSTATE");
  SGstate* sgs = (SGstate*)lua_tointeger (L, -1);
  lua_pop (L, 1);
  lua_pushnumber (L, sgs->time);
  return 1;
}

int l_drawtriangle (lua_State* L) {
  lua_getglobal (L, "__SGSTATE");
  SGstate* sgs = (SGstate*)lua_tointeger (L, -1);
  lua_pop (L, 1);
  int   i;
  float vs[6] = {0};
  for (i = 1; i <= 6; ++i) {
    if (lua_type (L, -1) != LUA_INT_TYPE) {
      errorf (
          "Expected 6 integer types as arguments to "
          "stormground.drawTriangle\n");
      lua_pushnil (L);
      return 1;
    }
    vs[6 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  float xmid = (float)sgs->width / 2.f;
  float ymid = (float)sgs->height / 2.f;
  for (i = 0; i < 6; i += 2) {
    vs[i] = (vs[i]);
  }
  for (i = 1; i < 6; i += 2) {
    vs[i] = sgs->height - (vs[i]);
  }
  SGprimitive t                      = {0};
  t.t                                = SG_PRIMITIVE_TRIANGLE;
  t.c[0]                             = (float)sgs->col.r / 255.f;
  t.c[1]                             = (float)sgs->col.g / 255.f;
  t.c[2]                             = (float)sgs->col.b / 255.f;
  t.p1.x                             = vs[0];
  t.p1.y                             = vs[1];
  t.p2.x                             = vs[2];
  t.p2.y                             = vs[3];
  t.p3.x                             = vs[4];
  t.p3.y                             = vs[5];
  sgs->ssbo->primv[sgs->ssbo->primc] = t;
  ++sgs->ssbo->primc;
  return 0;
}

int l_drawrectangle (lua_State* L) {
  lua_getglobal (L, "__SGSTATE");
  SGstate* sgs = (SGstate*)lua_tointeger (L, -1);
  lua_pop (L, 1);
  int   i;
  float vs[4] = {0};
  for (i = 1; i <= 4; ++i) {
    if (lua_type (L, -1) != LUA_INT_TYPE) {
      errorf (
          "Expected 4 integer types as arguments to "
          "stormground.drawRectangle\n");
      lua_pushnil (L);
      return 1;
    }
    vs[4 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  float xmid = (float)sgs->width / 2.f;
  float ymid = (float)sgs->height / 2.f;
  /*vs[2] += .001;
  vs[3] += .001;*/
  vs[2]                              = (vs[0] + vs[2]);
  vs[3]                              = (float)sgs->height - (vs[1] + vs[3]);
  vs[0]                              = (vs[0]);
  vs[1]                              = ((float)sgs->height - vs[1]);
  SGprimitive r                      = {0};
  r.t                                = SG_PRIMITIVE_RECT;
  r.c[0]                             = (float)sgs->col.r / 255.f;
  r.c[1]                             = (float)sgs->col.g / 255.f;
  r.c[2]                             = (float)sgs->col.b / 255.f;
  r.p1.x                             = vs[0];
  r.p1.y                             = vs[1];
  r.p2.x                             = vs[2];
  r.p2.y                             = vs[3];
  sgs->ssbo->primv[sgs->ssbo->primc] = r;
  ++sgs->ssbo->primc;
  return 0;
}

int l_setcolor (lua_State* L) {
  lua_getglobal (L, "__SGSTATE");
  SGstate* sgs = (SGstate*)lua_tointeger (L, -1);
  lua_pop (L, 1);
  int i;
  int cs[3] = {0};
  for (i = 1; i <= 3; ++i) {
    if (lua_type (L, -i) != LUA_INT_TYPE) {
      errorf (
          "Expected 3 integer types as arguments to stormground.setColor\n");
      lua_pushnil (L);
      return 1;
    }
    cs[3 - i] = (int)lua_tonumber (L, -i);
  }
  SGcolor c = {(uint8_t)cs[0], (uint8_t)cs[1], (uint8_t)cs[2], (uint8_t)255};
  sgs->col  = c;
  return 0;
}

int sgPrepState (SGscript* script, SGstate* sgs) {
  script->L = luaL_newstate();
  luaL_openlibs (script->L);

  lua_getglobal (script->L, "os");
  lua_pushnil (script->L);
  lua_setfield (script->L, -2, "execute");
  lua_pushnil (script->L);
  lua_setfield (script->L, -2, "exit");
  lua_pop (script->L, 1);
  lua_pushnil (script->L);
  lua_setglobal (script->L, "assert");

  lua_createtable (script->L, 0, 1);

  lua_pushinteger (script->L, (intptr_t)sgs);
  lua_setglobal (script->L, "__SGSTATE");

  lua_pushcfunction (script->L, l_getdelta);
  lua_setfield (script->L, -2, "getDelta");

  lua_pushcfunction (script->L, l_gettime);
  lua_setfield (script->L, -2, "getTime");

  lua_pushcfunction (script->L, l_drawtriangle);
  lua_setfield (script->L, -2, "drawTriangle");

  lua_pushcfunction (script->L, l_drawrectangle);
  lua_setfield (script->L, -2, "drawRectangle");

  lua_pushcfunction (script->L, l_setcolor);
  lua_setfield (script->L, -2, "setColor");

  lua_setglobal (script->L, "stormground");
  return SG_API_OK;
}

int sgDoFile (SGscript* script, SGstate* sgs, char const* path) {
  if (!script->L)
    sgPrepState (script, sgs);

  if (luaL_dofile (script->L, path)) {
    errorf ("Failed to call file:\n\t%s\n", lua_tostring (script->L, -1));
    return SG_API_BAD_CALL;
  }
  return SG_API_OK;
}

int sgCallGlobal (SGscript* script, char const* name) {
  lua_getglobal (script->L, name);
  if (lua_isnil (script->L, -1)) {
    lua_pop (script->L, 1);
    return SG_API_BAD_GLOBAL;
  }
  if (lua_pcall (script->L, 0, 0, 0) != 0) {
    errorf ("Failed to call global function %s:\n\t%s\n", name,
            lua_tostring (script->L, -1));
    return SG_API_BAD_CALL;
  }
  return SG_API_OK;
}