#include "sginput.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minilua.h"

static SGstate *sgstate;

#define CommonAPIHeader(state)                           \
  lua_getglobal ((state), "__SGSTATE");                  \
  SGstate *sgs = (SGstate *)lua_tointeger ((state), -1); \
  lua_pop ((state), 1)

#define kkey(k, c) scl_htabset (sgstate->mappings, k, (void *)(intptr_t)(c))
#define kbut(b, c) scl_htabset (sgstate->bmaps, b, (void *)(intptr_t)(c))

static char const *sgStateToString (char state) {
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

static int l_getDelta (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, sgs->delta);
  return 1;
}

static int l_getTime (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, sgs->time);
  return 1;
}

static int l_getCursor (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->curx);
  lua_pushnumber (L, (double)sgs->cury);
  return 2;
}

static int l_getRealCursor (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->fakeCurX);
  lua_pushnumber (L, (double)sgs->fakeCurY);
  return 2;
}

static int l_getScroll (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->scrolly);
  return 1;
}

static int l_getScreen (lua_State *L) {
  CommonAPIHeader (L);
  lua_pushnumber (L, (double)sgs->width);
  lua_pushnumber (L, (double)sgs->height);
  return 2;
}

static int l_getKey (lua_State *L) {
  CommonAPIHeader (L);
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const *str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (sgs->mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushstring (L, sgStateToString (sgs->keys[k]));
  else
    lua_pushnil (L);
  return 1;
}

static int l_keyIsTyped (lua_State *L) {
  CommonAPIHeader (L);
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const *str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (sgs->mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushboolean (L, sgs->keys[k] == SG_PRESS || sgs->keys[k] == SG_REPEAT);
  else
    lua_pushnil (L);
  return 1;
}

static int l_keyIsDown (lua_State *L) {
  CommonAPIHeader (L);
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const *str = lua_tostring (L, 1);
  int         k   = (intptr_t)scl_htabget (sgs->mappings, str);
  lua_pop (L, 1);
  if (k)
    lua_pushboolean (L, sgs->keys[k] == SG_HOLD || sgs->keys[k] == SG_PRESS ||
                            sgs->keys[k] == SG_REPEAT);
  else
    lua_pushnil (L);
  return 1;
}

static int l_getButton (lua_State *L) {
  CommonAPIHeader (L);
  if (lua_type (L, 1) != LUA_TSTRING)
    return lua_pushnil (L), 1;
  char const *str = lua_tostring (L, 1);
  int         b   = (intptr_t)scl_htabget (sgs->bmaps, str);
  lua_pop (L, 1);
  if (b)
    lua_pushstring (L, sgStateToString (sgs->buttons[b]));
  else
    lua_pushnil (L);
  return 1;
}

#define kgpbut(gp, n, id)                                   \
  lua_pushstring (L, sgStateToString ((gp).buttons[(id)])); \
  lua_setfield (L, -2, n)

#define kgpax(gp, n, id)                                        \
  lua_pushstring (L, sgStateToString ((gp).gstate.axes[(id)])); \
  lua_setfield (L, -2, n)

static int l_getGamepad (lua_State *L) {
  CommonAPIHeader (L);
  if (lua_type (L, 1) != LUA_INT_TYPE)
    return lua_pushnil (L), 1;
  float id = lua_tonumber (L, 1);
  lua_pop (L, 1);
  if ((int)id < 0 || (int)id > sgNumActiveGamepads()) {
    id = -1;
  }
  int realid = (id < 0) ? -1 : sgRealGamepadID (sgs, (int)id);
  if (realid < 0)
    return lua_pushnil (L), 1;
  Gamepad gp = (realid < 0) ? (Gamepad){0} : sgs->gpads[realid];
  lua_newtable (L); /* gamepad */

  lua_newtable (L); /* axes */

  kgpax (gp, "ly", GLFW_GAMEPAD_AXIS_LEFT_Y);
  kgpax (gp, "lx", GLFW_GAMEPAD_AXIS_LEFT_X);
  kgpax (gp, "ry", GLFW_GAMEPAD_AXIS_RIGHT_Y);
  kgpax (gp, "rx", GLFW_GAMEPAD_AXIS_RIGHT_X);
  kgpax (gp, "ltrigger", GLFW_GAMEPAD_AXIS_LEFT_TRIGGER);
  kgpax (gp, "rtrigger", GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER);

  lua_setfield (L, -2, "axes"); /* end axes */

  lua_newtable (L); /* buttons */

  /* right hand side buttons */
  kgpbut (gp, "a", GLFW_GAMEPAD_BUTTON_A);
  kgpbut (gp, "b", GLFW_GAMEPAD_BUTTON_B);
  kgpbut (gp, "x", GLFW_GAMEPAD_BUTTON_X);
  kgpbut (gp, "y", GLFW_GAMEPAD_BUTTON_Y);

  /* bumpers */

  kgpbut (gp, "lbumper", GLFW_GAMEPAD_BUTTON_LEFT_BUMPER);
  kgpbut (gp, "rbumper", GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER);

  /* special */

  kgpbut (gp, "back", GLFW_GAMEPAD_BUTTON_BACK);
  kgpbut (gp, "start", GLFW_GAMEPAD_BUTTON_START);
  kgpbut (gp, "guide", GLFW_GAMEPAD_BUTTON_GUIDE);

  /* joystick buttons */

  kgpbut (gp, "lstick", GLFW_GAMEPAD_BUTTON_LEFT_THUMB);
  kgpbut (gp, "rstick", GLFW_GAMEPAD_BUTTON_RIGHT_THUMB);

  /* Dpad */

  kgpbut (gp, "up", GLFW_GAMEPAD_BUTTON_DPAD_UP);
  kgpbut (gp, "down", GLFW_GAMEPAD_BUTTON_DPAD_DOWN);
  kgpbut (gp, "left", GLFW_GAMEPAD_BUTTON_DPAD_LEFT);
  kgpbut (gp, "right", GLFW_GAMEPAD_BUTTON_DPAD_RIGHT);

  lua_setfield (L, -2, "buttons"); /* end buttons */

  return 1; /* end gamepad */
}

static int l_getInputMethod (lua_State *L) {
  CommonAPIHeader (L);
  if (sgs->usage == SG_USAGE_MANDK) {
    lua_pushstring (L, "m&k");
    return 1;
  } else if (sgs->usage == SG_USAGE_GAMEPAD) {
    lua_pushstring (L, "gamepad");
    return 1;
  }
  lua_pushnil (L);
  return 1;
}

static const luaL_Reg libfuncs[] = {
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

void sgInputOpenLibs (lua_State *L) {
  char buf[4];
  char c;
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
  kkey ("lshift", GLFW_KEY_LEFT_SHIFT);
  kkey ("rshift", GLFW_KEY_RIGHT_SHIFT);
  kkey ("lcontrol", GLFW_KEY_LEFT_CONTROL);
  kkey ("rcontrol", GLFW_KEY_RIGHT_CONTROL);
  kkey ("lalt", GLFW_KEY_LEFT_ALT);
  kkey ("ralt", GLFW_KEY_RIGHT_ALT);
  kkey ("lbracket", GLFW_KEY_LEFT_BRACKET);
  kkey ("rbracket", GLFW_KEY_RIGHT_BRACKET);
  kkey ("space", GLFW_KEY_SPACE);
  kkey ("backspace", GLFW_KEY_BACKSPACE);
  kkey ("tab", GLFW_KEY_TAB);
  kkey ("enter", GLFW_KEY_ENTER);
  kkey ("minus", GLFW_KEY_MINUS);
  kkey ("equal", GLFW_KEY_EQUAL);
  kkey ("up", GLFW_KEY_UP);
  kkey ("down", GLFW_KEY_DOWN);
  kkey ("left", GLFW_KEY_LEFT);
  kkey ("right", GLFW_KEY_RIGHT);
  kkey ("comma", GLFW_KEY_COMMA);
  kkey ("period", GLFW_KEY_PERIOD);
  kkey ("escape", GLFW_KEY_ESCAPE);
  kkey ("slash", GLFW_KEY_SLASH);
  kkey ("backslash", GLFW_KEY_BACKSLASH);
  kkey ("semicolon", GLFW_KEY_SEMICOLON);
  kkey ("delete", GLFW_KEY_DELETE);
  kkey ("page up", GLFW_KEY_PAGE_UP);
  kkey ("page down", GLFW_KEY_PAGE_DOWN);
  kkey ("home", GLFW_KEY_HOME);
  kkey ("end", GLFW_KEY_END);
  kkey ("insert", GLFW_KEY_INSERT);

  kbut ("left", GLFW_MOUSE_BUTTON_LEFT);
  kbut ("right", GLFW_MOUSE_BUTTON_RIGHT);
  kbut ("middle", GLFW_MOUSE_BUTTON_MIDDLE);
  kbut ("button1", GLFW_MOUSE_BUTTON_1);
  kbut ("button2", GLFW_MOUSE_BUTTON_2);
  kbut ("button3", GLFW_MOUSE_BUTTON_3);
  kbut ("button4", GLFW_MOUSE_BUTTON_4);
  kbut ("button5", GLFW_MOUSE_BUTTON_5);
  kbut ("button6", GLFW_MOUSE_BUTTON_6);
  kbut ("button7", GLFW_MOUSE_BUTTON_7);
  kbut ("button8", GLFW_MOUSE_BUTTON_8);

  lua_getglobal (L, "sg");
  luaL_setfuncs (L, libfuncs, 0);
  lua_setglobal (L, "sg");
}

void sgSetInputState (SGstate *state) {
  sgstate = state;
}

void sgFramebufSizeCallback (GLFWwindow *win, int width, int height) {
  glViewport (0, 0, width, height);
}

void sgMouseButtonCallback (GLFWwindow *win, int button, int action, int mods) {
  if (action == GLFW_PRESS && sgstate->buttons[button] == SG_NOHOLD ||
      sgstate->buttons[button] == SG_RELEASE) {
    sgstate->buttons[button] = SG_PRESS;
  } else if (action == GLFW_RELEASE && sgstate->buttons[button] == SG_HOLD ||
             sgstate->buttons[button] == SG_PRESS) {
    sgstate->buttons[button] = SG_RELEASE;
  }
}

void sgCursorPosCallback (GLFWwindow *win, double x, double y) {
  if (x != sgstate->realCurX || y != sgstate->realCurY) {
    sgstate->usage    = SG_USAGE_MANDK;
    sgstate->fakeCurX = x;
    sgstate->fakeCurY = y;
  }
  sgstate->realCurX = x;
  sgstate->realCurY = y;
}

void sgKeyCallback (GLFWwindow *win, int key, int scancode, int action,
                    int mods) {
  switch (action) {
  case GLFW_PRESS:
    sgstate->keys[key] = SG_PRESS;
    break;
  case GLFW_RELEASE:
    sgstate->keys[key] = SG_RELEASE;
    break;
  case GLFW_REPEAT:
    sgstate->keys[key] = SG_REPEAT;
  }
}

void sgScrollCallback (GLFWwindow *win, double x, double y) {
  sgstate->scrollx = x;
  sgstate->scrolly = y;
}

#if 0
void sgJoystickCallback (int jid, int event) {
  if (!sgstate)
    return;
  if (event == GLFW_CONNECTED && glfwJoystickIsGamepad (jid)) {
    sgstate->gpads[jid].connected = 1;
    sgstate->gpads[jid].id        = jid;
    sgstate->gpads[jid].name      = (char *)glfwGetJoystickName (jid);
    notef ("Connected joystick %s on id %i\n", sgstate->gpads[jid].name, jid);
  } else if (event == GLFW_DISCONNECTED) {
    sgstate->gpads[jid].connected = 0;
    sgstate->gpads[jid].id        = 0;
    notef ("Connected joystick %s on id %i\n", sgstate->gpads[jid].name, jid);
  }
}
#endif

int sgNumActiveGamepads() {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (sgstate->gpads[i].connected)
      ++n;
  }
  return n;
}

int sgRealGamepadID (SGstate *sgs, int fakeID) {
  int i;
  int n = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    int activeID = sgs->activeGpads[i];
    if (sgs->gpads[activeID].connected) {
      ++n;
      if (n == fakeID)
        return activeID;
    }
  }
  return -1;
}

char sgMandKInUse (SGstate *sgs) {
  int i = 0;
  for (i = 0; i < GLFW_KEY_LAST + 1; ++i) {
    if (sgs->keys[i] == SG_PRESS) {
      return 1;
    }
  }
  for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; ++i) {
    if (sgs->buttons[i] == SG_PRESS) {
      return 1;
    }
  }
  return 0;
}

char sgGamepadInUse (SGstate *sgs) {
  int i  = 0;
  int ii = 0;
  for (i = 1; i <= SG_GAMEPAD_LAST; ++i) {
    int realid = sgRealGamepadID (sgs, i);
    if (realid < 0)
      continue;
    Gamepad gp = sgs->gpads[i];
    for (ii = 0; ii < GLFW_GAMEPAD_AXIS_LAST + 1; ++ii) {
      if (gp.gstate.axes[ii] > 0.1) {
        return i;
      }
    }
    for (ii = 0; ii < GLFW_GAMEPAD_BUTTON_LAST + 1; ++ii) {
      if (gp.buttons[ii] == SG_PRESS) {
        return i;
      }
    }
  }
  return -1;
}

void sgInsertActiveGamepad (SGstate *sgs, int id) {
  int i = 0;
  for (i = SG_GAMEPAD_LAST; i > 0; --i) {
    sgs->activeGpads[i] = sgs->activeGpads[i - 1];
  }
  sgs->activeGpads[0] = id;
}

int sgCheckCurrentInputMethod (SGstate *sgs) {
  if (sgMandKInUse (sgs)) {
    /* if (sgs->usage == SG_USAGE_GAMEPAD) {
      notef ("Usage: Mouse & Keyboard\n");
    } */
    sgs->usage = SG_USAGE_MANDK;
    return SG_USAGE_MANDK;
  }
  int id = sgGamepadInUse (sgs);
  if (id > -1) {
    /* sgInsertActiveGamepad (sgs, id); */
    /* if (sgs->usage == SG_USAGE_MANDK) {
      notef ("Usage: Gamepad\n");
    } */
    sgs->usage = SG_USAGE_GAMEPAD;
    return SG_USAGE_GAMEPAD;
  }
  return sgs->usage;
}

void sgAdvanceInputs() {
  int i;
  int ii;
  sgCheckCurrentInputMethod (sgstate);
  for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; ++i) {
    if (sgstate->buttons[i] == SG_PRESS || sgstate->buttons[i] == SG_REPEAT)
      sgstate->buttons[i] = SG_HOLD;
    else if (sgstate->buttons[i] == SG_RELEASE)
      sgstate->buttons[i] = SG_NOHOLD;
  }
  for (i = 0; i < GLFW_KEY_LAST + 1; ++i) {
    if (sgstate->keys[i] == SG_PRESS) {
      sgstate->keys[i] = SG_HOLD;
    } else if (sgstate->keys[i] == SG_RELEASE)
      sgstate->keys[i] = SG_NOHOLD;
  }
  sgstate->scrollx = 0;
  sgstate->scrolly = 0;
  for (i = 0; i < SG_GAMEPAD_LAST + 1; ++i) {
    if (glfwJoystickPresent (i) && glfwJoystickIsGamepad (i)) {
      sgstate->gpads[i].connected = 1;
      if (!sgstate->gpads[i].name) {
        sgstate->gpads[i].name = (char *)glfwGetGamepadName (i);
        /*notef ("Gamepad \"%s\" was connected on id %i\n",
               sgstate->gpads[i].name, i);*/
        sgInsertActiveGamepad (sgstate, i);
      }
      glfwGetGamepadState (i, &sgstate->gpads[i].gstate);
      for (ii = 0; ii < GLFW_GAMEPAD_BUTTON_LAST + 1; ++ii) {
        char  action   = sgstate->gpads[i].gstate.buttons[ii];
        char  oldstate = sgstate->gpads[i].buttons[ii];
        char *sgbutton = (char *)sgstate->gpads[i].buttons + ii;
        if (oldstate == SG_PRESS) {
          (*sgbutton) = SG_HOLD;
        } else if (oldstate == SG_RELEASE) {
          (*sgbutton) = SG_NOHOLD;
        }
        if (action == GLFW_PRESS &&
            (oldstate == SG_NOHOLD || oldstate == SG_RELEASE)) {
          (*sgbutton) = SG_PRESS;
        } else if (action == GLFW_RELEASE &&
                   (oldstate == SG_HOLD || oldstate == SG_PRESS)) {
          (*sgbutton) = SG_RELEASE;
        }
      }

    } else {
      sgstate->gpads[i].connected = 0;
      if (sgstate->gpads[i].name) {
        /*notef ("Gamepad \"%s\" was disconnected on id %i\n",
               sgstate->gpads[i].name, i);*/
      }

      sgstate->gpads[i].name = NULL;
    }
  }
}
