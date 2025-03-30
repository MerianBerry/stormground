#include "sg_event.h"
#include "sg_lua.h"

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
  lua_pushinteger (L, n + 1);
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
  lua_getglobal (L, "_SG");
  SG *sg = (SG *)(intptr_t)lua_tointeger (L, -1);
  lua_pop (L, 1);
  lua_getglobal (L, "sg");
  lua_getfield (L, -1, "mappings");
  lua_pushvalue (L, 1);
  lua_gettable (L, -2);
  if (!lua_testtype (L, -1, LUA_TNUMBER)) {
    lua_pop (L, 3);
    lua_pushnil (L);
    return 1;
  }
  int key = lua_tointeger (L, -1);
  lua_pop (L, 3);
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

  lua_newtable (L);

  char buf[4] = {0, 0};
  for (char c = '0'; c <= (char)'9'; c++) {
    buf[0] = c;
    ikey (buf, c);
  }
  for (char c = 'a'; c <= (char)'z'; c++) {
    buf[0] = c;
    ikey (buf, c);
  }
  buf[0] = 'F';
  for (int i = 1; i <= 12; i++) {
    itoa (i, buf + 1, 10);
    ikey (buf, sk (SDLK_F1 + i - 1));
  }
  ikey ("escape", SDLK_ESCAPE);
  ikey ("backspace", SDLK_BACKSPACE);
  ikey ("tab", SDLK_TAB);
  ikey ("space", SDLK_SPACE);
  ikey ("comma", SDLK_COMMA);
  ikey ("minus", SDLK_MINUS);
  ikey ("period", SDLK_PERIOD);
  ikey ("slash", SDLK_SLASH);
  ikey ("semicolon", SDLK_SEMICOLON);
  ikey ("equals", SDLK_EQUALS);
  ikey ("lbracket", SDLK_LEFTBRACKET);
  ikey ("backslash", SDLK_BACKSLASH);
  ikey ("rightbracket", SDLK_RIGHTBRACKET);
  ikey ("grave", SDLK_GRAVE);
  ikey ("lbrace", SDLK_LEFTBRACE);
  ikey ("rbrace", SDLK_RIGHTBRACE);
  ikey ("delete", SDLK_DELETE);

  ikey ("insert", sk (SDLK_INSERT));
  ikey ("home", sk (SDLK_HOME));
  ikey ("pageup", sk (SDLK_PAGEUP));
  ikey ("end", sk (SDLK_END));
  ikey ("pagedown", sk (SDLK_PAGEDOWN));
  ikey ("right", sk (SDLK_RIGHT));
  ikey ("left", sk (SDLK_LEFT));
  ikey ("down", sk (SDLK_DOWN));
  ikey ("up", sk (SDLK_UP));
  ikey ("lctrl", sk (SDLK_LCTRL));
  ikey ("lshift", sk (SDLK_LSHIFT));
  ikey ("lalt", sk (SDLK_LALT));
  ikey ("rctrl", sk (SDLK_RCTRL));
  ikey ("rshift", sk (SDLK_RSHIFT));
  ikey ("ralt", sk (SDLK_RALT));
  lua_setfield (L, -2, "basemap");

  // Copy the mappings table
  luaL_dostring (L, "sg.mappings = sg.basemap");

  sg_setcfunfield (L, -1, onTick);

  sg_setcfunfield (L, -1, getScreen);
  sg_setcfunfield (L, -1, getCursor);
  sg_setcfunfield (L, -1, getScroll);
  sg_setcfunfield (L, -1, getKey);
  sg_setcfunfield (L, -1, getButton);
  lua_pop (L, 1);
  return 0;
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
