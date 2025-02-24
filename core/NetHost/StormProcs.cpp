#include "StormProcs.hpp"
#include "../NativeStorm/native.hpp"

StormProcs::StormProcs (NetHost* host) {
  if (!host)
    throw NetException ("NetHost is null");
  EntryFromCore = (EntryFromCore_fn)host->CreateDelegate ("Storm",
    "Storm.Core.Main",
    "EntryFromCore");
  BuildFromCore = (BuildFromCore_fn)host->CreateDelegate ("Storm",
    "Storm.Core.Main",
    "BuildFromCore");
  if (!EntryFromCore || !BuildFromCore)
    throw NetException ("Failed to create core delegates");
  Storm_LogInfo ("NativeHost", "Found all core procs");
}
