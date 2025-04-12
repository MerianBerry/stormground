# Stormgrounds build system, Amp
set(AMP_SOURCES
  "amp.c"
  "../scl.c")

add_library(amp SHARED ${AMP_SOURCES})
set_target_properties(amp PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")
clangdConfigure(amp)
createVersionH(amp)
