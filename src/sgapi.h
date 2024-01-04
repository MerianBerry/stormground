#pragma once

#include "sg.h"

enum {
  SG_API_OK = 0,
  SG_API_BAD_GLOBAL,
  SG_API_BAD_CALL,
};

int sgPrepState(SGscript* script, SGstate* sgs);

int sgDoFile(SGscript* script, SGstate* sgs, const char* path);

int sgCallGlobal(SGscript* script, const char* name);