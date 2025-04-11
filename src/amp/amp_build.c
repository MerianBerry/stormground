#include "scl.h"
#include <stdio.h>
#include "SDL3/SDL_thread.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

/* TODO, logging api from core */

// Hold an array of source patterns.
// When a rule is added, attempt to match it to every
// pattern available. If there was a match, an identical
// or overlapping pattern exists, and that is an error.
// If not, add it like usual.

// Every rule will contain a timestamp of the write time of build.lua file that
// made it. If a cache file is ever older than it's rule's timestamp, that file
// must be remade.

// Mark the configure cache with the timestamp of the end of the configure time.
// Still check ever build.lua file, and if any is newer than that timestamp,
// a reconfigure must occur. This event still preserves compiled cache.

// During building, iterate over every rule, and matching its pattern
// on every workspace. Next, check its output rule, to check if the output
// is up to date (its write time is the same time or after the write time of the
// source). If it is not up to date, apply the rule's build function. If the
// rule's build function returns nil, make sure all successive builds, until a
// reconfigure, skips that source file.

#define lua_testtype(L, narg, t) (lua_type (L, narg) == t)

static void checkSGDir (char const *dir) {
  char const *sgdir = scl_fmt ("%s/.sg", dir);
  if (!scl_exists (sgdir)) {
    scl_mkdir (sgdir);
  }
}

/* Use cached data and functions to build files */
/* File packing is handled by the core */
static int l_build (lua_State *L) {
}

/* Prepares the build system for user projects */
/* Aqcuire external dependencies, and cache user functions */
static int l_configure (lua_State *L) {
  if (!lua_testtype (L, 1, LUA_TSTRING)) {
  }
  char const *wdir   = lua_tostring (L, 1);
  char const *script = scl_fmt ("%s/build.lua", wdir);

  // Only make the .sg dir in the main working directory
  checkSGDir (wdir);

  if (!scl_exists (script)) {
    return 0;
  }

  luaL_dofile (L, script);
}

int luaopen_amp (lua_State *L) {
  return 0;
}
