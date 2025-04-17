//#define _XOPEN_SOURCE 700
#include "sgapi.h"

#include <stdio.h>
#include <stdlib.h>
#include "sginput.h"
#include "sgimage.h"
#include <string.h>

#include "minilua.h"

void dr (SGstate* sg, float x, float y, float w, float h, char hollow) {
  SGprimitive r = {0};
  r.t           = SG_PRIMITIVE_RECT;
  r.c[0]        = (float)sg->col.r / 255.f;
  r.c[1]        = (float)sg->col.g / 255.f;
  r.c[2]        = (float)sg->col.b / 255.f;
  r.p1.x        = x;
  r.p1.y        = y;
  r.p2.x        = w;
  r.p2.y        = h;
  r.p3.x        = hollow;
  if (sg->ssbo->primc >= 0xffff - 1)
    return;
  sg->ssbo->primv[sg->ssbo->primc] = r;
  ++sg->ssbo->primc;
}

char toUpper (char c) {
  if (c >= 0x61 && c <= 0x7a) {
    return c - 32;
  }
  return c;
}

/* Hi youtube id like to make an apology... */
static unsigned char hexass[] =
    "$\x82\x01 Z\x00\x03 UU\x03 <\x9e\x03 R\xa5\x03 *\xab\x03 $\x00\x01 "
    ")\"\x03 \"J\x03 \x0A\xA8\x03 \x05\xD0\x03 \x00\x12\x01 \x01\xC0\x03 "
    "\x00\x02\x01 \x12\xA4\x03 +j\x03 ,\x97\x03 b\xa7\x03 b\x8e\x03 )\xd2\x03 "
    "\x79\x8E\x03 )\xaa\x03 r\x92\x03 *\xaa\x03 *\xca\x03 \x04\x10\x01 "
    "\x04\x12\x01 \x05\x10\x03 \x0e\x38\x03 \x04P\x03 \"\x82\x03 \xff\xff\x03 "
    "\x2B\xED\x03 \x6B\xAE\x03 \x39\x23\x03 \x6B\x6E\x03 \x79\xA7\x03 "
    "\x79\xA4\x03 \x39\x2B\x03 \x5B\xED\x03 \x74\x97\x03 \x32\x6A\x03 "
    "\x4B\xAD\x03 \x49\x27\x03 \x5F\x6D\x03 \x7B\x6D\x03 \x7B\x6F\x03 "
    "\x6B\xA4\x03 \x2B\x59\x03 \x6B\xAD\x03 \x38\x8E\x03 \x74\x92\x03 "
    "\x5B\x6A\x03 \x5B\x52\x03 \x5B\x7D\x03 \x5A\xAD\x03 \x5A\x92\x03 "
    "\x72\xA7\x03 \x69\x26\x03 \x48\x89\x03 \x32\x4B\x03 \x2A\x00\x03 "
    "\x00\x07\x03 \x00\x00\x00 \x35\x93\x03 \x24\x92\x01 \x64\xD6\x03 "
    "\x0C\x98\x03";

int sgDrawStr (SGstate* sg, char* str, float _x, float _y, float size) {
  unsigned int i;
  int          ii;
  if (!str)
    return -1;
  unsigned int l = strlen (str);
  if (l < 1)
    return -1;

  float rx = _x;
  for (i = 0; i < l; ++i) {
    int o = toUpper (str[i]);
    if (o >= 0x7b && o <= 0x7e)
      o -= 26;
    o -= 32;
    if (o < 0 || o > 69) {
      continue;
    }
    if (o == 0) {
      rx += 4.f;
      continue;
    }
    o -= 1;
    int  hex = hexass[o * 4] << 8 | hexass[o * 4 + 1];
    char s   = hexass[o * 4 + 2];
    rx       = rx - ((3 - s) / 2) * size;

    for (ii = 14; ii >= 0; --ii) {
      char bit = (hex >> ii) & 0b1;
      int  p   = 14 - ii;
      char x   = (p % 3);
      char y   = (p / 3);
      if (bit) {
        float __x = (float)rx + (float)x * size;
        float __y = (float)_y + (float)y * size;
        dr (sg, __x, __y, __x + 1 * (size - 1), __y + 1 * (size - 1), 0);
      }
    }
    rx += 4.f * size - ((3 - s) / 2) * size;
  }
  return 1;
}

#define CommonAPIHeader(state)                          \
  lua_getglobal ((state), "__SGSTATE");                 \
  SGstate* sgs = (SGstate*)lua_tointeger ((state), -1); \
  lua_pop ((state), 1)

/*           INPUT API           */

/*            OUTPUT API             */

int l_close (lua_State* L) {
  CommonAPIHeader (L);
  sgs->runstate = SG_RUNSTATE_STOP;
  return 0;
}

int l_setScreen (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  float vs[2] = {0};
  for (i = 1; i <= 2; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushstring (L,
                      "Expected 2 number types as arguments to "
                      "stormground.setScreen\n");
      lua_error (L);
      return 1;
    }
    vs[2 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  vs[0]      = clampf (vs[0], 6.f, 960.f);
  vs[1]      = clampf (vs[1], 6.f, 540.f);
  sgs->mon.w = (int)vs[0];
  sgs->mon.h = (int)vs[1];
  sgRegenerateTexture (&sgs->mon);
  sgBindTexture (sgs->mon, GL_READ_WRITE);
  sgs->width  = (int)vs[0];
  sgs->height = (int)vs[1];
  return 0;
}

int l_setCursor (lua_State* L) {
  int i = 0;
  CommonAPIHeader (L);
  float vs[2];
  for (i = 1; i <= 2; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushstring (
          L, "stormground.getGamepad expects two numbers as arguments\n");
      lua_error (L);
      return 1;
    }
    vs[2 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  sgs->fakeCurX = vs[0];
  sgs->fakeCurY = vs[1];
  return 0;
}

/*            DRAWING API            */

int l_drawText (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  float vs[3] = {0};
  for (i = 1; i <= 3; ++i) {
    if (lua_type (L, i) != LUA_TNUMBER) {
      lua_pushstring (
          L, "Expected 3 number arguments first for stormground.drawText");
      lua_error (L);
      return 1;
    }
    vs[i - 1] = lua_tonumber (L, i);
  }
  if (lua_type (L, 4) != LUA_TSTRING) {
    lua_pushstring (L,
                    "Expected a string argument after first 3 number arguments "
                    "for stormground.drawText");
    lua_error (L);
    return 1;
  }
  char* str = (char*)lua_tostring (L, 4);
  sgDrawStr (sgs, str, vs[0], vs[1], vs[2]);
  return 0;
}

int l_drawLine (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  int   t     = lua_gettop (L);
  float vs[4] = {0};
  if (t < 4) {
    lua_pushfstring (L,
                     "Expected at least 4 number types as arguments to "
                     "stormground.drawRectangle, but %i were passed\n",
                     t);
    lua_error (L);
    return 1;
  }
  for (i = 1; i <= 4; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushfstring (
          L,
          "Expected at least 4 number types as arguments to "
          "stormground.drawRectangle, but type \"%s\" was passed\n",
          lua_typename (L, lua_type (L, -1)));
      lua_error (L);
      return 1;
    }
    vs[4 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  SGprimitive p = {0};
  p.t           = SG_PRIMITIVE_LINE;
  p.c[0]        = (float)sgs->col.r / 255.f;
  p.c[1]        = (float)sgs->col.g / 255.f;
  p.c[2]        = (float)sgs->col.b / 255.f;
  p.p1.x        = vs[0];
  p.p1.y        = vs[1];
  p.p2.x        = vs[2];
  p.p2.y        = vs[3];
  if (p.p2.x < p.p1.x || (p.p1.x == p.p2.x && p.p2.y < p.p1.y)) {
    h_vec2 pt = p.p1;
    p.p1      = p.p2;
    p.p2      = pt;
  }
  if (sgs->ssbo->primc >= 0xffff - 1)
    return 0;
  sgs->ssbo->primv[sgs->ssbo->primc] = p;
  ++sgs->ssbo->primc;
  return 0;
}

int l_drawCircle (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  int   t     = lua_gettop (L);
  float vs[4] = {0};
  if (t < 3) {
    lua_pushstring (L,
                    "Expected at least 3 number types as arguments to "
                    "stormground.drawCircle\n");
    lua_error (L);
    return 1;
  }
  if (t == 4) {
    if (lua_isnumber (L, -1)) {
      vs[3] = lua_tonumber (L, -1);
      lua_pop (L, 1);
    } else if (!lua_isnil (L, -1)) {
      lua_pushstring (
          L,
          "Argument \"innerDiameter\" for stormground.drawCircle is "
          "expected to be a number or nil\n");
      lua_error (L);
      return 1;
    }
  }
  for (i = 1; i <= 3; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushstring (L,
                      "Expected 3 number types as arguments to "
                      "stormground.drawCircle\n");
      lua_error (L);
      return 1;
    }
    vs[3 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  SGprimitive r = {0};
  r.t           = SG_PRIMITIVE_CIRCLE;
  r.c[0]        = (float)sgs->col.r / 255.f;
  r.c[1]        = (float)sgs->col.g / 255.f;
  r.c[2]        = (float)sgs->col.b / 255.f;
  r.p1.x        = vs[0];
  r.p1.y        = vs[1];
  r.p2.x        = vs[2];
  r.p2.y        = vs[3];
  if (sgs->ssbo->primc >= 0xffff - 1)
    return 0;
  sgs->ssbo->primv[sgs->ssbo->primc] = r;
  ++sgs->ssbo->primc;
  return 0;
}

int l_drawTriangle (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  float vs[6] = {0};
  for (i = 1; i <= 6; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushstring (L,
                      "Expected 6 integer types as arguments to "
                      "stormground.drawTriangle\n");
      lua_error (L);
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
    vs[i] = (vs[i]);
  }
  SGprimitive t = {0};
  t.t           = SG_PRIMITIVE_TRIANGLE;
  t.c[0]        = (float)sgs->col.r / 255.f;
  t.c[1]        = (float)sgs->col.g / 255.f;
  t.c[2]        = (float)sgs->col.b / 255.f;
  t.p1.x        = vs[0];
  t.p1.y        = vs[1];
  t.p2.x        = vs[2];
  t.p2.y        = vs[3];
  t.p3.x        = vs[4];
  t.p3.y        = vs[5];
  if (sgs->ssbo->primc >= 0xffff - 1)
    return 0;
  sgs->ssbo->primv[sgs->ssbo->primc] = t;
  ++sgs->ssbo->primc;
  return 0;
}

int l_drawRectangle (lua_State* L) {
  CommonAPIHeader (L);
  int   i;
  int   t     = lua_gettop (L);
  float vs[5] = {0};
  if (t < 4) {
    lua_pushfstring (L,
                     "Expected at least 4 number types as arguments to "
                     "stormground.drawRectangle, but %i were passed\n",
                     t);
    lua_error (L);
    return 1;
  }
  if (t == 5) {
    if (lua_isboolean (L, -1) || lua_isnil (L, -1)) {
      vs[4] = (float)lua_toboolean (L, -1);
      lua_pop (L, 1);
    } else {
      lua_pushstring (L,
                      "Argument \"isHollow\" for stormground.drawRectangle is "
                      "expected to be a boolean or nil\n");
      lua_error (L);
      return 1;
    }
  }
  for (i = 1; i <= 4; ++i) {
    if (lua_type (L, -1) != LUA_TNUMBER) {
      lua_pushfstring (
          L,
          "Expected at least 4 number types as arguments to "
          "stormground.drawRectangle, but type \"%s\" was passed\n",
          lua_typename (L, lua_type (L, -1)));
      lua_error (L);
      return 1;
    }
    vs[4 - i] = lua_tonumber (L, -1);
    lua_pop (L, 1);
  }
  float x2 = vs[0] + vs[2] - 1.f;
  float y2 = vs[1] + vs[3] - 1.f;
  vs[2]    = maxf (vs[0], x2);
  vs[3]    = maxf (vs[1], y2);
  vs[0]    = minf (vs[0], x2);
  vs[1]    = minf (vs[1], y2);
  dr (sgs, vs[0], vs[1], vs[2], vs[3], vs[4]);
  return 0;
}

int l_setColor (lua_State* L) {
  CommonAPIHeader (L);
  int i;
  int cs[3] = {0};
  for (i = 1; i <= 3; ++i) {
    if (lua_type (L, -i) != LUA_INT_TYPE) {
      lua_pushstring (
          L, "Expected 3 integer types as arguments to stormground.setColor\n");
      lua_error (L);
      return 1;
    }
    cs[3 - i] = (int)lua_tonumber (L, -i);
  }
  SGcolor c = {(uint8_t)cs[0], (uint8_t)cs[1], (uint8_t)cs[2], (uint8_t)255};
  sgs->col  = c;
  return 0;
}

#define CommonAPIFun(L, i, name)     \
  lua_pushcfunction ((L), l_##name); \
  lua_setfield ((L), (i), #name)

int sgPrepState (SGscript* script, SGstate* sgs) {
  script->L    = luaL_newstate();
  lua_State* L = script->L;
  luaL_openlibs (L);

  lua_getglobal (L, "os");
  lua_pushnil (L);
  lua_setfield (L, -2, "execute");
  lua_pushnil (L);
  lua_setfield (L, -2, "exit");
  lua_pop (L, 1);
  lua_pushnil (L);
  lua_setglobal (L, "assert");

  lua_createtable (L, 0, 1);

  lua_pushinteger (L, (intptr_t)sgs);
  lua_setglobal (L, "__SGSTATE");

  /* INPUT API */
  CommonAPIFun (L, -2, getDelta);

  CommonAPIFun (L, -2, getTime);

  CommonAPIFun (L, -2, getCursor);

  CommonAPIFun (L, -2, getRealCursor);

  CommonAPIFun (L, -2, getScroll);

  CommonAPIFun (L, -2, getScreen);

  CommonAPIFun (L, -2, getKey);

  CommonAPIFun (L, -2, keyIsTyped);

  CommonAPIFun (L, -2, keyIsDown);

  CommonAPIFun (L, -2, getButton);

  CommonAPIFun (L, -2, getGamepad);

  CommonAPIFun (L, -2, getInputMethod);

  /* OUTPUT API */

  CommonAPIFun (L, -2, close);

  CommonAPIFun (L, -2, setScreen);

  CommonAPIFun (L, -2, setCursor);

  /* DRAWING API */

  CommonAPIFun (L, -2, drawText);

  CommonAPIFun (L, -2, drawLine);

  CommonAPIFun (L, -2, drawCircle);

  CommonAPIFun (L, -2, drawTriangle);

  CommonAPIFun (L, -2, drawRectangle);

  CommonAPIFun (L, -2, setColor);

  lua_setglobal (L, "stormground");
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
    errorf ("Global %s does not exist\n", name);
    return SG_API_BAD_GLOBAL;
  }
  if (lua_pcall (script->L, 0, 0, 0) != 0) {
    errorf ("Failed to call global function %s:\n\t%s\n", name,
            lua_tostring (script->L, -1));
    return SG_API_BAD_CALL;
  }
  return SG_API_OK;
}