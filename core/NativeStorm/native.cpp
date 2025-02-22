#include <cstdlib>
#include "native.hpp"

using string = std::string;

static string Error = "";

STORMAPI void Storm_SetError (std::string err) {
  Error = err;
}

STORMAPI void Storm_Free (void* ptr) {
  free (ptr);
}

STORMAPI const char* Storm_GetError() {
  char* buf = new char[Error.length() + 1];
  memcpy (buf, Error.c_str(), Error.length() + 1);
  return buf;
}
