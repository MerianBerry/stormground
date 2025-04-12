#ifndef AMP_CACHE_H
#define AMP_CACHE_H
#include "amp.h"

typedef struct amp_cached {
  char const *in;
  char const *out;
  long        iwtime;
  long        owtime;
} amp_cached;

typedef struct amp_rule {
  char const *from;
  char const *to;
  char const *dump;
} amp_rule;

typedef struct amp_cache {
  scl_page  mem;
  scl_htab *caches;
} amp_cache;

int amp_loadcache (lua_State *L, amp_cache *ac);
#endif