#ifndef STORM_PROCS
#define STORM_PROCS
#include "NetHost.hpp"

class StormProcs {
 public:
  using EntryFromCore_fn = void (*) (char const *, char const *);
  using BuildFromCore_fn = void (*) (char const *);
  EntryFromCore_fn EntryFromCore;
  BuildFromCore_fn BuildFromCore;


  StormProcs (NetHost *host);
};

#endif
