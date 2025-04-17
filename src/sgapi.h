#pragma once

#include "sg.h"

enum {
  SG_API_OK = 0,
  SG_API_BAD_GLOBAL,
  SG_API_BAD_CALL,
};

lua_State* sgNewScript (SGstate* sgs);
