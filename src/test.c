#include "luasocket.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mxml/mxml.h"

extern char const mobdebug_lua[];
extern char const socket_lua[];

#ifdef SG_INCLUDE_GENERATED
#  include "mobdebug.h"
#  include "socket.h"
#else
#endif

#define preload(L, modname, str)                                            \
  {                                                                         \
    int _size = snprintf (                                                  \
        NULL, 0, "package.preload[" #modname "]=function()\n%send\n", str); \
    if (_size > 0) {                                                        \
      char* prebuf = (char*)malloc ((size_t)_size + 2);                     \
      memset (prebuf, 0, (size_t)_size + 2);                                \
      snprintf (prebuf, (size_t)_size + 1,                                  \
                "package.preload[" #modname "]=function()\n%send\n", str);  \
      if (luaL_dostring (L, prebuf)) {                                      \
        fprintf (stderr, "%s\n", lua_tostring (L, -1));                     \
        return 1;                                                           \
      }                                                                     \
      free (prebuf);                                                        \
    }                                                                       \
  }

int main() {
  /*lua_State* L = luaL_newstate();
  luaL_openlibs (L);

  lua_getglobal (L, "package");
  lua_getfield (L, -1, "preload");
  lua_pushcfunction (L, luaopen_socket_core);
  lua_setfield (L, -2, "socket.core");
  lua_pop (L, 1);

  preload (L, "socket", socket_lua);

  preload (L, "mobdebug", mobdebug_lua);

  if (luaL_dostring (L, "require(\"mobdebug\").start()")) {
    fprintf (stderr, "%s\n", lua_tostring (L, -1));
    return 1;
  }
  lua_close (L);*/

  return 0;
}