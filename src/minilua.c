#define LUA_IMPL
#include "minilua.h"
#include "scl.h"

int main (int argc, char **argv) {
  if (argc < 2)
    return 1;
  if (!scl_exists (argv[1])) {
    fprintf (stderr, "could not open %s\n", argv[1]);
    return 1;
  }

  lua_State *L = luaL_newstate();
  luaL_openlibs (L);

  int i;
  for (i = 2; i < argc && argv[i]; i++) {
    lua_pushstring (L, argv[i]);
  }

  if (luaL_dofile (L, argv[1])) {
    char const *err = lua_tostring (L, -1);
    fprintf (stderr, "lua error: %s\n", err);
    return 1;
  }

  lua_close (L);
  return 0;
}