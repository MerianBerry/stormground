

if (WIN32)
set(MONO_DIR "C:/Program Files/Mono")
endif()

set(SG_SOURCES
  "sg.cpp"
  "NetHost/NetHost.cpp")

add_executable(sg "resource.rc" ${SG_SOURCES})
if (MSVC)
#target_compile_options(sg PRIVATE "/fsanitize=address")
endif()
target_compile_definitions(sg PRIVATE SG_INCLUDE_GENERATED=1)
target_include_directories(sg PRIVATE "${CMAKE_BINARY_DIR}/generated")
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)
