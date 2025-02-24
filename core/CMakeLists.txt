
set(NATIVE_SOURCES
  "NativeStorm/native.cpp")
set(NATIVE_LIBS "")

add_library(NativeStorm SHARED ${NATIVE_SOURCES})
target_link_libraries(NativeStorm PRIVATE ${NATIVE_LIBS})

set(SG_SOURCES
  "sg.cpp"
  "CLIHandler.cpp"
  "NetHost/NetHost.cpp"
  "NetHost/StormProcs.cpp")
add_executable(sg "resource.rc" ${SG_SOURCES})
if (MSVC)
#target_compile_options(sg PRIVATE "/fsanitize=address")
endif()
target_link_libraries(sg PRIVATE NativeStorm "SDL3-shared" "slang")
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/core" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)


add_custom_target(engine)
enginebuild(engine debug)
