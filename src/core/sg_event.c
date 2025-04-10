#include "sg_event.h"
#include "sg_lua.h"
#include "scl.h"
#include <stdlib.h>

#define sg_luaSetKeyI(ind, k, i) \
  lua_pushstring (L, k);         \
  lua_pushinteger (L, i);        \
  lua_settable (L, ind - 2)

#define ikey(k, i) sg_luaSetKeyI (-1, k, i)

#define sk(k)      (k - SDLK_CAPSLOCK + SDLK_PLUSMINUS + 1)

static int sgl_onTick (lua_State *L) {
  if (!lua_testtype (L, 1, LUA_TFUNCTION)) {
    sg_throwLuaError (L, "expected function argument");
    return 1;
  }
  lua_getglobal (L, "sg");
  lua_getfield (L, -1, "_tickCBs");
  int n = lua_objlen (L, -1);
  lua_pushinteger (L, (lua_Integer)n + 1);
  lua_pushvalue (L, -4);
  lua_rawset (L, -3);

  n = lua_objlen (L, -1);

  lua_pop (L, 3);
  return 0;
}

static int sgl_getScreen (lua_State *L) {
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  int w, h;
  SDL_GetWindowSize (sg->win, &w, &h);
  lua_pushinteger (L, w);
  lua_pushinteger (L, h);
  return 2;
}

static int sgl_getCursor (lua_State *L) {
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  lua_pushinteger (L, sg->cx);
  lua_pushinteger (L, sg->cy);
  return 2;
}

static int sgl_getScroll (lua_State *L) {
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  lua_pushinteger (L, sg->cw);
  return 1;
}

static int sgl_getKey (lua_State *L) {
  if (!lua_testtype (L, 1, LUA_TSTRING)) {
    sg_throwLuaError (L, "expected string argument");
    return 1;
  }
  char const *k = lua_tostring (L, 1);
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  int key = (int)(intptr_t)scl_htabget (sg->mappings, k);
  if (key <= 0 || key >= SDL_LAST_KEY) {
    lua_pushnil (L);
    return 1;
  }
  switch (sg->keys[key]) {
  case SG_KEY_NONE:
    lua_pushnil (L);
    return 1;
  case SG_KEY_PRESSED:
    lua_pushstring (L, "pressed");
    return 1;
  case SG_KEY_RELEASED:
    lua_pushstring (L, "released");
    return 1;
  case SG_KEY_HELD:
    lua_pushstring (L, "held");
    return 1;
  }
  lua_pushnil (L);
  return 1;
}

static int sgl_getButton (lua_State *L) {
  if (!lua_testtype (L, 1, LUA_TSTRING)) {
    sg_throwLuaError (L, "expected string argument");
    return 1;
  }
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  char const *b     = lua_tostring (L, 1);
  char        state = 0;
  if (!strcmp (b, "left"))
    state = sg->buttons[SDL_BUTTON_LEFT];
  else if (!strcmp (b, "right"))
    state = sg->buttons[SDL_BUTTON_RIGHT];
  else if (!strcmp (b, "middle"))
    state = sg->buttons[SDL_BUTTON_MIDDLE];
  switch (state) {
  case SG_KEY_NONE:
    lua_pushnil (L);
    return 1;
  case SG_KEY_PRESSED:
    lua_pushstring (L, "pressed");
    return 1;
  case SG_KEY_RELEASED:
    lua_pushstring (L, "released");
    return 1;
  case SG_KEY_HELD:
    lua_pushstring (L, "held");
    return 1;
  }
  lua_pushnil (L);
  return 1;
}

int sg_loadEventLib (lua_State *L) {
  lua_getglobal (L, "sg");

  sg_setcfunfield (L, -1, onTick);

  sg_setcfunfield (L, -1, getScreen);
  sg_setcfunfield (L, -1, getCursor);
  sg_setcfunfield (L, -1, getScroll);
  sg_setcfunfield (L, -1, getKey);
  sg_setcfunfield (L, -1, getButton);
  lua_pop (L, 1);
  return 0;
}

#define kkey(n, k) scl_htabset (sg->basemap, n, (void *)(intptr_t)k)

void sg_loadMappings (SG *sg) {
  sg->basemap = scl_htabnew();

  char buf[4] = {0, 0};
  for (char c = '0'; c <= (char)'9'; c++) {
    buf[0] = c;
    kkey (buf, c);
  }
  for (char c = 'a'; c <= (char)'z'; c++) {
    buf[0] = c;
    kkey (buf, c);
  }
  buf[0] = 'F';
  for (int i = 1; i <= 12; i++) {
    sprintf (buf + 1, "%d", i);
    kkey (buf, sk (SDLK_F1 + i - 1));
  }
  kkey ("escape", SDLK_ESCAPE);
  kkey ("backspace", SDLK_BACKSPACE);
  kkey ("tab", SDLK_TAB);
  kkey ("space", SDLK_SPACE);
  kkey ("comma", SDLK_COMMA);
  kkey ("minus", SDLK_MINUS);
  kkey ("period", SDLK_PERIOD);
  kkey ("slash", SDLK_SLASH);
  kkey ("semicolon", SDLK_SEMICOLON);
  kkey ("equals", SDLK_EQUALS);
  kkey ("lbracket", SDLK_LEFTBRACKET);
  kkey ("backslash", SDLK_BACKSLASH);
  kkey ("rightbracket", SDLK_RIGHTBRACKET);
  kkey ("grave", SDLK_GRAVE);
  kkey ("lbrace", SDLK_LEFTBRACE);
  kkey ("rbrace", SDLK_RIGHTBRACE);
  kkey ("delete", SDLK_DELETE);

  kkey ("insert", sk (SDLK_INSERT));
  kkey ("home", sk (SDLK_HOME));
  kkey ("pageup", sk (SDLK_PAGEUP));
  kkey ("end", sk (SDLK_END));
  kkey ("pagedown", sk (SDLK_PAGEDOWN));
  kkey ("right", sk (SDLK_RIGHT));
  kkey ("left", sk (SDLK_LEFT));
  kkey ("down", sk (SDLK_DOWN));
  kkey ("up", sk (SDLK_UP));
  kkey ("lctrl", sk (SDLK_LCTRL));
  kkey ("lshift", sk (SDLK_LSHIFT));
  kkey ("lalt", sk (SDLK_LALT));
  kkey ("rctrl", sk (SDLK_RCTRL));
  kkey ("rshift", sk (SDLK_RSHIFT));
  kkey ("ralt", sk (SDLK_RALT));

  sg->mappings = scl_htabcopy (sg->basemap);
}

int sg_processEvent (SG *sg, SDL_Event *e) {
  switch (e->type) {
  case SDL_EVENT_QUIT:
    sg->runstate = 0;
    return 1;
  case SDL_EVENT_KEY_DOWN: {
    if (e->key.repeat == 1)
      break;
    SDL_Keycode k = e->key.key;
    k             = (k & SDLK_SCANCODE_MASK) ? sk (k) : k;
    sg->keys[k]   = SG_KEY_PRESSED;
    break;
  }
  case SDL_EVENT_KEY_UP: {
    SDL_Keycode k = e->key.key;
    k             = (k & SDLK_SCANCODE_MASK) ? sk (k) : k;
    sg->keys[k]   = SG_KEY_RELEASED;
    break;
  }
  case SDL_EVENT_MOUSE_BUTTON_DOWN: {
    if (e->button.button < 8)
      sg->buttons[e->button.button] = SG_KEY_PRESSED;
    break;
  }
  case SDL_EVENT_MOUSE_BUTTON_UP: {
    if (e->button.button < 8)
      sg->buttons[e->button.button] = SG_KEY_RELEASED;
    break;
  }
  case SDL_EVENT_MOUSE_MOTION: {
    sg->cx = e->motion.x;
    sg->cy = e->motion.y;
    break;
  }
  case SDL_EVENT_MOUSE_WHEEL: {
    sg->cw = e->wheel.y;
    break;
  }
  }
  return 0;
}

void sg_advanceInputs (SG *sg) {
  for (int i = 0; i < SDL_LAST_KEY; i++) {
    if (sg->keys[i] == SG_KEY_PRESSED)
      sg->keys[i] = SG_KEY_HELD;
    else if (sg->keys[i] == SG_KEY_RELEASED)
      sg->keys[i] = SG_KEY_NONE;
  }
  for (int i = 0; i < sizeof (sg->buttons); i++) {
    if (sg->buttons[i] == SG_KEY_PRESSED)
      sg->buttons[i] = SG_KEY_HELD;
    else if (sg->buttons[i] == SG_KEY_RELEASED)
      sg->buttons[i] = SG_KEY_NONE;
  }
}
