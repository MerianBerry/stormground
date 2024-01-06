#define _XOPEN_SOURCE 700
#include "sgapi.h"

#include <stdio.h>
#include <stdlib.h>
#include "sgcallbacks.h"
#include "sgimage.h"

#include "lua-5.4.6/src/luaconf.h"
#include "lua-5.4.6/src/lauxlib.h"
#include "lua-5.4.6/src/lua.h"
#include "lua-5.4.6/src/lualib.h"

int strToKeyCode (char const* str) {
  unsigned int hash = str_hash (str);
  switch (hash) {
  case 177638:
  case 177670: /* A a */ return GLFW_KEY_A;
  case 177639:
  case 177671: /* B b */ return GLFW_KEY_B;
  case 177640:
  case 177672: /* C c */ return GLFW_KEY_C;
  case 177641:
  case 177673: /* D d */ return GLFW_KEY_D;
  case 177642:
  case 177674: /* E e */ return GLFW_KEY_E;
  case 177643:
  case 177675: /* F f */ return GLFW_KEY_F;
  case 177644:
  case 177676: /* G g */ return GLFW_KEY_G;
  case 177645:
  case 177677: /* H h */ return GLFW_KEY_H;
  case 177646:
  case 177678: /* I i */ return GLFW_KEY_I;
  case 177647:
  case 177679: /* J j */ return GLFW_KEY_J;
  case 177648:
  case 177680: /* K k */ return GLFW_KEY_K;
  case 177649:
  case 177681: /* L l */ return GLFW_KEY_L;
  case 177650:
  case 177682: /* M m */ return GLFW_KEY_M;
  case 177651:
  case 177683: /* N n */ return GLFW_KEY_N;
  case 177652:
  case 177684: /* O o */ return GLFW_KEY_O;
  case 177653:
  case 177685: /* P p */ return GLFW_KEY_P;
  case 177654:
  case 177686: /* Q q */ return GLFW_KEY_Q;
  case 177655:
  case 177687: /* R r */ return GLFW_KEY_R;
  case 177656:
  case 177688: /* S s */ return GLFW_KEY_S;
  case 177657:
  case 177689: /* T t */ return GLFW_KEY_T;
  case 177658:
  case 177690: /* U u */ return GLFW_KEY_U;
  case 177659:
  case 177691: /* V v */ return GLFW_KEY_V;
  case 177660:
  case 177692: /* W w */ return GLFW_KEY_W;
  case 177661:
  case 177693: /* X x */ return GLFW_KEY_X;
  case 177662:
  case 177694: /* Y y */ return GLFW_KEY_Y;
  case 177663:
  case 177695: /* Z z */ return GLFW_KEY_Z;
  case 177621: /* 0 */ return GLFW_KEY_0;
  case 177622: /* 1 */ return GLFW_KEY_1;
  case 177623: /* 2 */ return GLFW_KEY_2;
  case 177624: /* 3 */ return GLFW_KEY_3;
  case 177625: /* 4 */ return GLFW_KEY_4;
  case 177626: /* 5 */ return GLFW_KEY_5;
  case 177627: /* 6 */ return GLFW_KEY_6;
  case 177628: /* 7 */ return GLFW_KEY_7;
  case 177629: /* 8 */ return GLFW_KEY_8;
  case 177630: /* 9 */ return GLFW_KEY_9;
  case 203947599: /* lshift */ return GLFW_KEY_LEFT_SHIFT;
  case 438759957: /* rshift */ return GLFW_KEY_RIGHT_SHIFT;
  case 4147334258: /* lcontrol */ return GLFW_KEY_LEFT_CONTROL;
  case 2159954360: /* rcontrol */ return GLFW_KEY_RIGHT_CONTROL;
  case 2090464114: /* lalt */ return GLFW_KEY_LEFT_ALT;
  case 2090679736: /* ralt */ return GLFW_KEY_RIGHT_ALT;
  case 2957236621: /* lbracket */ return GLFW_KEY_LEFT_BRACKET;
  case 969856723: /* rbracket */ return GLFW_KEY_RIGHT_BRACKET;
  case 274667089: /* space */ return GLFW_KEY_SPACE;
  case 3580823138: /* backspace */ return GLFW_KEY_BACKSPACE;
  case 193506620: /* tab */ return GLFW_KEY_TAB;
  case 258013091: /* enter */ return GLFW_KEY_ENTER;
  case 267314769: /* minus */ return GLFW_KEY_MINUS;
  case 258121853: /* equal */ return GLFW_KEY_EQUAL;
  case 5863882: /* up */ return GLFW_KEY_UP;
  case 2090192221: /* down */ return GLFW_KEY_DOWN;
  case 2090468272: /* left */ return GLFW_KEY_LEFT;
  case 273236323: /* right */ return GLFW_KEY_RIGHT;
  case 255669810: /* comma */ return GLFW_KEY_COMMA;
  case 344245928: /* period */ return GLFW_KEY_PERIOD;
  case 4224779062: /* escape */ return GLFW_KEY_ESCAPE;
  case 274523872: /* slash */ return GLFW_KEY_SLASH;
  case 3580679921: /* backslash */ return GLFW_KEY_BACKSLASH;
  case 1051985198: /* semicolon */ return GLFW_KEY_SEMICOLON;
  case 4169368696: /* delete */ return GLFW_KEY_DELETE;
  case 2600365223: /* page up */ return GLFW_KEY_PAGE_UP;
  case 1413671802: /* page down */ return GLFW_KEY_PAGE_DOWN;
  case 2090335630: /* home */ return GLFW_KEY_HOME;
  case 193490716: /* end */ return GLFW_KEY_END;
  case 81003162: /* insert */ return GLFW_KEY_INSERT;

  default: return -1;
  }
}

int strToButtonCode (char const* str) {
  unsigned int hash = str_hash (str);
  switch (hash) {
  case 2090468272: /* left */ return GLFW_MOUSE_BUTTON_LEFT;
  case 273236323: /* right */ return GLFW_MOUSE_BUTTON_RIGHT;
  case 231074772: /* middle */ return GLFW_MOUSE_BUTTON_MIDDLE;
  case 2498432466: /* button1 */ return GLFW_MOUSE_BUTTON_1;
  case 2498432467: /* button2 */ return GLFW_MOUSE_BUTTON_2;
  case 2498432468: /* button3 */ return GLFW_MOUSE_BUTTON_3;
  case 2498432469: /* button4 */ return GLFW_MOUSE_BUTTON_4;
  case 2498432470: /* button5 */ return GLFW_MOUSE_BUTTON_5;
  case 2498432471: /* button6 */ return GLFW_MOUSE_BUTTON_6;
  case 2498432472: /* button7 */ return GLFW_MOUSE_BUTTON_7;
  case 2498432473: /* button8 */ return GLFW_MOUSE_BUTTON_8;
  default: return -1;
  }
}

char* sgStateToString (char state) {
  switch (state) {
  case SG_PRESS: return str_cpy ("pressed", npos);
  case SG_RELEASE: return str_cpy ("released", npos);
  case SG_HOLD: return str_cpy ("held", npos);
  case SG_NOHOLD: return str_cpy ("not pressed", npos);
  default: return NULL;
  }
}

int sgRealGamepadID (SGstate* sgs, int fakeID) {
  int i;
  int n = 0;
  for (i = 0; i < GLFW_JOYSTICK_LAST + 1; ++i) {
    if (sgs->gpads[i].connected) {
      ++n;
      if (n == fakeID)
        return i;
    }
  }
  return -1;
}

void sgPushAndSetGPButton (lua_State* L, Gamepad gp, int tbind, int glfwID,
                           char const* name) {
  char* str = sgStateToString (gp.buttons[glfwID]);
  if (!str) {
    lua_pushnil (L);
  } else {
    lua_pushstring (L, str);
    free (str);
  }
  lua_setfield (L, tbind, name);
}

#define CommonAPIHeader(state)                          \
  lua_getglobal ((state), "__SGSTATE");                 \
  SGstate* sgs = (SGstate*)lua_tointeger ((state), -1); \
  lua_pop ((state), 1)

/*           INPUT API           */

int l_getDelta (lua_State* L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, sgs->delta);
  return 1;
}

int l_getTime (lua_State* L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, sgs->time);
  return 1;
}

int l_getCursor (lua_State* L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->curx);
  lua_pushnumber (L, (double)sgs->cury);
  return 2;
}

int l_getKey (lua_State* L) {
  CommonAPIHeader (L);
  if (lua_type (L, -1) != LUA_TSTRING) {
    errorf ("Argument to getKey is not a string\n");
    lua_pushstring (L, "Argument to getButton is not a string");
    lua_error (L);
    return 1;
  }
  char const* str = lua_tostring (L, -1);
  lua_pop (L, 1);
  int code = strToKeyCode (str);
  if (code >= 0) {
    char  state = sgs->keys[code];
    char* str   = sgStateToString (state);
    if (str) {
      lua_pushstring (L, str);
      free (str);
      return 1;
    } else {
      lua_pushnil (L);
      return 1;
    }
  }
  lua_pushnil (L);
  return 1;
}

int l_getButton (lua_State* L) {
  CommonAPIHeader (L);
  if (lua_type (L, -1) != LUA_TSTRING) {
    lua_pushstring (L, "Argument to getButton is not a string");
    lua_error (L);
    return 1;
  }
  char const* str = lua_tostring (L, -1);
  lua_pop (L, 1);
  int code = strToButtonCode (str);
  if (code >= 0) {
    char  state = sgs->buttons[code];
    char* str   = sgStateToString (state);
    if (str) {
      lua_pushstring (L, str);
      free (str);
      return 1;
    } else {
      lua_pushnil (L);
      return 1;
    }
  }
  lua_pushnil (L);
  return 1;
}

int l_getGamepad (lua_State* L) {
  CommonAPIHeader (L);
  if (lua_type (L, -1) != LUA_INT_TYPE) {
    lua_pushstring (
        L, "stormground.getGamepad expects an integer type argument\n");
    lua_error (L);
    return 1;
  }
  float id = lua_tonumber (L, -1);
  lua_pop (L, 1);
  if ((int)id < 0 || (int)id > sgNumActiveGamepads()) {
    id = -1;
  }
  int     realid = (id < 0) ? -1 : sgRealGamepadID (sgs, (int)id);
  Gamepad gp     = (realid < 0) ? (Gamepad){0} : sgs->gpads[realid];
  lua_createtable (L, 0, 1); /* gamepad */

  lua_createtable (L, 0, 1); /* axes */

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
  lua_setfield (L, -2, "leftY");

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
  lua_setfield (L, -2, "leftX");

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
  lua_setfield (L, -2, "rightY");

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
  lua_setfield (L, -2, "rightX");

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
  lua_setfield (L, -2, "leftTrigger");

  lua_pushnumber (L, (double)gp.gstate.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
  lua_setfield (L, -2, "rightTrigger");

  lua_setfield (L, -2, "axes"); /* end axes */

  lua_createtable (L, 0, 1); /* buttons */

  /* right hand side buttons */
  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_A, "a");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_B, "b");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_X, "x");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_Y, "y");

  /* bumpers */

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
                        "leftBumper");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
                        "rightBumper");

  /* special */

  sgPushAndSetGPButton(L, gp, -2, GLFW_GAMEPAD_BUTTON_BACK, "back");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_START, "start");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_GUIDE, "guide");

  
  /* joystick buttons */

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_LEFT_THUMB, "leftThumb");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
                        "rightThumb");

  /* Dpad */

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_DPAD_UP, "dpadUp");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, "dpadRight");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_DPAD_DOWN, "dpadDown");

  sgPushAndSetGPButton (L, gp, -2, GLFW_GAMEPAD_BUTTON_DPAD_LEFT, "dpadLeft");


  lua_setfield (L, -2, "buttons"); /* end buttons */

  return 1; /* end gamepad */
}

int l_getScreen (lua_State* L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->width);
  lua_pushnumber (L, (double)sgs->height);
  return 2;
}

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
    if (lua_type (L, -1) != LUA_INT_TYPE) {
      lua_pushstring (L,
                      "Expected 2 integer types as arguments to "
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

/*            DRAWING API            */

int l_drawTriangle (lua_State* L) {
  CommonAPIHeader (L);
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
    vs[i] = (vs[i]);
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

int l_drawRectangle (lua_State* L) {
  CommonAPIHeader (L);
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
  vs[3]                              = (vs[1] + vs[3]);
  vs[0]                              = (vs[0]);
  vs[1]                              = (vs[1]);
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

int l_setColor (lua_State* L) {
  CommonAPIHeader (L);
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

  CommonAPIFun (L, -2, getScreen);

  CommonAPIFun (L, -2, getKey);

  CommonAPIFun (L, -2, getButton);

  CommonAPIFun (L, -2, getGamepad);

  /* OUTPUT API */

  CommonAPIFun (L, -2, close);

  CommonAPIFun (L, -2, setScreen);

  /* DRAWING API */

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
    return SG_API_BAD_GLOBAL;
  }
  if (lua_pcall (script->L, 0, 0, 0) != 0) {
    errorf ("Failed to call global function %s:\n\t%s\n", name,
            lua_tostring (script->L, -1));
    return SG_API_BAD_CALL;
  }
  return SG_API_OK;
}