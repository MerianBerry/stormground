#pragma once

#include "sg.h"

enum {
  SG_NOHOLD  = 0,
  SG_PRESS   = 1,
  SG_RELEASE = 2,
  SG_HOLD    = 3,
  SG_REPEAT  = 4,
};

void sgInputOpenLibs (lua_State* L);

/* void sgJoystickCallback(int jid, int event); */

int sgNumActiveGamepads();

int sgRealGamepadID (int fakeID);

void sgAdvanceInputs();