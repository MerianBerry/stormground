#pragma once

#include "sg.h"

#define CommonAPIHeader(state)                          \
  lua_getglobal ((state), "__SGSTATE");                 \
  SGstate* sgs = (SGstate*)lua_tointeger ((state), -1); \
  lua_pop ((state), 1)

enum {
  SG_API_OK = 0,
  SG_API_BAD_GLOBAL,
  SG_API_BAD_CALL,
};

lua_State* sgNewScript (SGstate* sgs);
