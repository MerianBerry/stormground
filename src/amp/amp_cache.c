#include "amp_cache.h"
#include <stdlib.h>
#include <string.h>

int amp_loadcache (lua_State *L, amp_cache *ac) {
  if (!scl_exists ("cache.xml")) {
    amp_logInfo (L, "Cache file does not exist");
    return 0;
  }
  xml_doc *doc = xml_load_file ("cache.xml");
  if (!doc) {
    amp_logInfo (L, "Failed to open cache.xml");
    return 1;
  }

  /* Until xpath is working, manually verify and traverse */
  if (!strcmp (xml_tag (doc), "cache")) {
    amp_logInfo (L, "Cache is invalid");
    // Delete cached.xml
    return 1;
  }

  ac->caches = scl_htabnew();

  xml_elem *e = doc->child;
  while (e) {
    char const *tag = xml_tag (e);
    if (!strcmp (tag, "t")) { // Transform in->out cache
      amp_cached cached;
      xml_attr  *in  = xml_find_attribute (e, "in");
      xml_attr  *out = xml_find_attribute (e, "out");
      cached.in      = scl_strcopy (xml_data (in));
      cached.out     = scl_strcopy (xml_data (out));
      cached.iwtime  = scl_wtime (cached.in);
      cached.owtime  = scl_wtime (cached.out);
      amp_cached *C  = scl_pagealloc (&ac->mem, sizeof (cached));
      memcpy (C, &cached, sizeof (cached));
      scl_htabset (ac->caches, cached.in, C);
    } else if (!strcmp (tag, "b")) { // Build func cache
      char const *dump = xml_data (e);
    } else {
      amp_logInfo (L, "unknown type cache entry");
    }
  }

  xml_free_doc (doc);
  return 0;
}