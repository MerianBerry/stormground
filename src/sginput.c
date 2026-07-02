#include "sginput.h"

#include "sgapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minilua.h"

#define kkey(k, c) scl_htabset (_state.mappings, k, (void*)(intptr_t)(c))
#define kbut(b, c) scl_htabset (_state.bmaps, b, (void*)(intptr_t)(c))

static char const* sgStateToString (char state) {
  switch (state) {
  case SG_PRESS:
    return "pressed";
  case SG_RELEASE:
    return "released";
  case SG_HOLD:
    return "held";
  case SG_NOHOLD:
    return "not pressed";
  case SG_REPEAT:
    return "repeated";
  default:
    return NULL;
  }
}

static int l_getDelta (lua_State* L) {
  lua_pushnumber (L, _state.delta);
  return 1;
}

static int l_getTime (lua_State* L) {
  lua_pushnumber (L, _state.time);
  return 1;
}

static int l_getCursor (lua_State* L) {
  lua_pushnumber (L, (double)_state.curx);
  lua_pushnumber (L, (double)_state.cury);
  return 2;
}

static int l_getRealCursor (lua_State* L) {
  lua_pushnumber (L, (double)_state.realCurX);
  lua_pushnumber (L, (double)_state.realCurY);
  return 2;
}

static int l_getScroll (lua_State* L) {
  lua_pushnumber (L, (double)_state.scrolly);
  return 1;
}

static int l_getScreen (lua_State* L) {
  lua_pushnumber (L, (double)_state.width);
  lua_pushnumber (L, (double)_state.height);
  return 2;
}

static int l_getKey (lua_State* L) {
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const* str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (_state.mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushstring (L, sgStateToString (_state.keys[k]));
  else
    lua_pushnil (L);
  return 1;
}

static int l_keyIsTyped (lua_State* L) {
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const* str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (_state.mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushboolean (L,
                     _state.keys[k] == SG_PRESS || _state.keys[k] == SG_REPEAT);
  else
    lua_pushnil (L);
  return 1;
}

static int l_keyIsDown (lua_State* L) {
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const* str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (_state.mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushboolean (L, _state.keys[k] == SG_HOLD ||
                            _state.keys[k] == SG_PRESS ||
                            _state.keys[k] == SG_REPEAT);
  else
    lua_pushnil (L);
  return 1;
}

static int l_getButton (lua_State* L) {
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const* str = lua_tostring (L, 1);
  int         b   = (intptr_t)scl_htabget (_state.bmaps, str);
  lua_pop (L, 1);
  if (b)
    lua_pushstring (L, sgStateToString (_state.buttons[b]));
  else
    lua_pushnil (L);
  return 1;
}

#define kgpbut(gp, n, id)                                   \
  lua_pushstring (L, sgStateToString ((gp).buttons[(id)])); \
  lua_setfield (L, -2, n)

#define kgpax(gp, n, ax)               \
  lua_pushnumber (L, (gp).axes[(ax)]); \
  lua_setfield (L, -2, n)

static int l_getGamepad (lua_State* L) {
  if (lua_type (L, 1) != LUA_INT_TYPE)
    return lua_pushnil (L), 1;
  int id = (int)lua_tonumber (L, 1);
  lua_pop (L, 1);
  if (id < 0 || id > sgNumActiveGamepads()) {
    id = -1;
  }
  int realid = (id < 0) ? -1 : sgRealGamepadID (id);
  if (realid < 0)
    return lua_pushnil (L), 1;
  Gamepad gp = (realid < 0) ? (Gamepad){0} : _state.gpads[realid];
  lua_newtable (L); /* gamepad */

  lua_newtable (L); /* axes */

  kgpax (gp, "ly", SDL_GAMEPAD_AXIS_LEFTX);
  kgpax (gp, "lx", SDL_GAMEPAD_AXIS_LEFTY);
  kgpax (gp, "ry", SDL_GAMEPAD_AXIS_RIGHTX);
  kgpax (gp, "rx", SDL_GAMEPAD_AXIS_RIGHTY);
  kgpax (gp, "ltrigger", SDL_GAMEPAD_AXIS_LEFT_TRIGGER);
  kgpax (gp, "rtrigger", SDL_GAMEPAD_AXIS_RIGHT_TRIGGER);

  lua_setfield (L, -2, "axes"); /* end axes */

  lua_newtable (L); /* buttons */

  /* right hand side buttons */
  kgpbut (gp, "a", SDL_GAMEPAD_BUTTON_LABEL_A);
  kgpbut (gp, "b", SDL_GAMEPAD_BUTTON_LABEL_B);
  kgpbut (gp, "x", SDL_GAMEPAD_BUTTON_LABEL_X);
  kgpbut (gp, "y", SDL_GAMEPAD_BUTTON_LABEL_Y);

  /* bumpers */

  kgpbut (gp, "lbumper", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
  kgpbut (gp, "rbumper", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);

  /* special */

  kgpbut (gp, "back", SDL_GAMEPAD_BUTTON_BACK);
  kgpbut (gp, "start", SDL_GAMEPAD_BUTTON_START);
  kgpbut (gp, "guide", SDL_GAMEPAD_BUTTON_GUIDE);

  /* joystick buttons */

  kgpbut (gp, "lstick", SDL_GAMEPAD_BUTTON_LEFT_STICK);
  kgpbut (gp, "rstick", SDL_GAMEPAD_BUTTON_RIGHT_STICK);

  /* Dpad */

  kgpbut (gp, "up", SDL_GAMEPAD_BUTTON_DPAD_UP);
  kgpbut (gp, "down", SDL_GAMEPAD_BUTTON_DPAD_DOWN);
  kgpbut (gp, "left", SDL_GAMEPAD_BUTTON_DPAD_LEFT);
  kgpbut (gp, "right", SDL_GAMEPAD_BUTTON_DPAD_RIGHT);

  lua_setfield (L, -2, "buttons"); /* end buttons */

  return 1; /* end gamepad */
}

static int l_getInputMethod (lua_State* L) {
  if (_state.usage == SG_USAGE_MANDK) {
    lua_pushstring (L, "m&k");
    return 1;
  } else if (_state.usage == SG_USAGE_GAMEPAD) {
    lua_pushstring (L, "gamepad");
    return 1;
  }
  lua_pushnil (L);
  return 1;
}

static luaL_Reg const libfuncs[] = {
    {"getDelta",       l_getDelta      },
    {"getTime",        l_getTime       },
    {"getCursor",      l_getCursor     },
    {"getRealCursor",  l_getRealCursor },
    {"getScroll",      l_getScroll     },
    {"getScreen",      l_getScreen     },
    {"getKey",         l_getKey        },
    {"keyIsTyped",     l_keyIsTyped    },
    {"keyIsDown",      l_keyIsDown     },
    {"getButton",      l_getButton     },
    {"getGamepad",     l_getGamepad    },
    {"getInputMethod", l_getInputMethod},
    {NULL,             NULL            },
};

void sgInputOpenLibs (lua_State* L) {
  char buf[4];
  char c;

  luaL_setfuncs (L, libfuncs, 0);

  buf[1] = 0;
  for (c = 'A'; c <= (char)'Z'; c++) {
    buf[0] = c;
    kkey (buf, c);
    buf[0] += 32;
    kkey (buf, c + 32);
  }
  for (c = '0'; c <= (char)'0'; c++) {
    buf[0] = c;
    kkey (buf, c);
  }
  kkey ("lshift", SGK_LSHIFT);
  kkey ("rshift", SGK_RSHIFT);
  kkey ("lcontrol", SGK_LCTRL);
  kkey ("rcontrol", SGK_RCTRL);
  kkey ("lalt", SGK_LALT);
  kkey ("ralt", SGK_RALT);
  kkey ("lbracket", SGK_LEFTBRACKET);
  kkey ("rbracket", SGK_RIGHTBRACKET);
  kkey ("space", SGK_SPACE);
  kkey ("backspace", SGK_BACKSPACE);
  kkey ("tab", SGK_TAB);
  kkey ("enter", SGK_RETURN);
  kkey ("minus", SGK_MINUS);
  kkey ("equal", SGK_EQUALS);
  kkey ("up", SGK_UP);
  kkey ("down", SGK_DOWN);
  kkey ("left", SGK_LEFT);
  kkey ("right", SGK_RIGHT);
  kkey ("comma", SGK_COMMA);
  kkey ("period", SGK_PERIOD);
  kkey ("escape", SGK_ESCAPE);
  kkey ("slash", SGK_SLASH);
  kkey ("backslash", SGK_BACKSLASH);
  kkey ("semicolon", SGK_SEMICOLON);
  kkey ("delete", SGK_DELETE);
  kkey ("page up", SGK_PAGEUP);
  kkey ("page down", SGK_PAGEDOWN);
  kkey ("home", SGK_HOME);
  kkey ("end", SGK_END);
  kkey ("insert", SGK_INSERT);

  kbut ("left", SDL_BUTTON_LEFT);
  kbut ("right", SDL_BUTTON_RIGHT);
  kbut ("middle", SDL_BUTTON_MIDDLE);
  kbut ("button1", SDL_BUTTON_X1);
  kbut ("button2", SDL_BUTTON_X2);
}

#if 0
void sgJoystickCallback (int jid, int event) {
  if (!_state)
    return;
  if (event == GLFW_CONNECTED && glfwJoystickIsGamepad (jid)) {
    _state.gpads[jid].connected = 1;
    _state.gpads[jid].id        = jid;
    _state.gpads[jid].name      = (char *)glfwGetJoystickName (jid);
    notef ("Connected joystick %s on id %i\n", _state.gpads[jid].name, jid);
  } else if (event == GLFW_DISCONNECTED) {
    _state.gpads[jid].connected = 0;
    _state.gpads[jid].id        = 0;
    notef ("Connected joystick %s on id %i\n", _state.gpads[jid].name, jid);
  }
}
#endif

int sgNumActiveGamepads() {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (_state.gpads[i].connected)
      ++n;
  }
  return n;
}

int sgRealGamepadID (int fakeID) {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    int activeID = _state.activeGpads[i];
    if (_state.gpads[activeID].connected) {
      ++n;
      if (n == fakeID)
        return activeID;
    }
  }
  return -1;
}

char sgMandKInUse() {
  int i = 0;
  for (i = 0; i < SG_KEY_LAST + 1; ++i) {
    if (_state.keys[i] == SG_PRESS) {
      return 1;
    }
  }
  for (i = 0; i < SG_BUTTON_LAST + 1; ++i) {
    if (_state.buttons[i] == SG_PRESS) {
      return 1;
    }
  }
  return 0;
}

char sgGamepadInUse() {
  int i  = 0;
  int ii = 0;
  for (i = 1; i <= SG_GAMEPAD_LAST; ++i) {
    int realid = sgRealGamepadID (i);
    if (realid < 0)
      continue;
    Gamepad gp = _state.gpads[i];
    for (ii = 0; ii < SDL_GAMEPAD_AXIS_COUNT; ++ii) {
      if (fabsf (gp.axes[ii]) > 0.1)
        return i;
    }
    for (ii = 0; ii < SDL_GAMEPAD_BUTTON_COUNT; ++ii) {
      if (gp.buttons[ii] == SG_PRESS)
        return i;
    }
  }
  return -1;
}

void sgInsertActiveGamepad (int id) {
  int i = 0;
  for (i = SG_GAMEPAD_LAST; i > 0; --i)
    _state.activeGpads[i] = _state.activeGpads[i - 1];
  _state.activeGpads[0] = id;
}

int sgCheckCurrentInputMethod() {
  if (sgMandKInUse()) {
    /* if (_state.usage == SG_USAGE_GAMEPAD) {
      notef ("Usage: Mouse & Keyboard\n");
    } */
    _state.usage = SG_USAGE_MANDK;
    return SG_USAGE_MANDK;
  }
  int id = sgGamepadInUse();
  if (id > -1) {
    /* sgInsertActiveGamepad (_state, id); */
    /* if (_state.usage == SG_USAGE_MANDK) {
      notef ("Usage: Gamepad\n");
    } */
    _state.usage = SG_USAGE_GAMEPAD;
    return SG_USAGE_GAMEPAD;
  }
  return _state.usage;
}

void sgAdvanceInputs() {
  int i;
  int ii;
  sgCheckCurrentInputMethod();
  for (i = 0; i < SG_BUTTON_LAST + 1; ++i) {
    if (_state.buttons[i] == SG_PRESS || _state.buttons[i] == SG_REPEAT)
      _state.buttons[i] = SG_HOLD;
    else if (_state.buttons[i] == SG_RELEASE)
      _state.buttons[i] = SG_NOHOLD;
  }
  for (i = 0; i < SG_KEY_LAST + 1; ++i) {
    if (_state.keys[i] == SG_PRESS) {
      _state.keys[i] = SG_HOLD;
    } else if (_state.keys[i] == SG_RELEASE)
      _state.keys[i] = SG_NOHOLD;
  }
  _state.scrollx = 0;
  _state.scrolly = 0;
#if 0
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (glfwJoystickPresent (i) && glfwJoystickIsGamepad (i)) {
      _state.gpads[i].connected = 1;
      if (!_state.gpads[i].name) {
        _state.gpads[i].name = (char*)glfwGetGamepadName (i);
        /*notef ("Gamepad \"%s\" was connected on id %i\n",
               _state.gpads[i].name, i);*/
        sgInsertActiveGamepad (i);
      }
      glfwGetGamepadState (i, &_state.gpads[i].gstate);
      for (ii = 0; ii < SDL_GAMEPAD_BUTTON_COUNT; ++ii) {
        char  action   = _state.gpads[i].gstate.buttons[ii];
        char  oldstate = _state.gpads[i].buttons[ii];
        char* sgbutton = (char*)_state.gpads[i].buttons + ii;
        if (oldstate == SG_PRESS) {
          (*sgbutton) = SG_HOLD;
        } else if (oldstate == SG_RELEASE) {
          (*sgbutton) = SG_NOHOLD;
        }
        if (action == SG_PRESS &&
            (oldstate == SG_NOHOLD || oldstate == SG_RELEASE)) {
          (*sgbutton) = SG_PRESS;
        } else if (action == SG_RELEASE &&
                   (oldstate == SG_HOLD || oldstate == SG_PRESS)) {
          (*sgbutton) = SG_RELEASE;
        }
      }

    } else {
      _state.gpads[i].connected = 0;
      if (_state.gpads[i].name) {
        /*notef ("Gamepad \"%s\" was disconnected on id %i\n",
               _state.gpads[i].name, i);*/
      }

      _state.gpads[i].name = NULL;
    }
  }
#endif
}
