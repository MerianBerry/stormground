
set(SG_SOURCES
  "sg.c"
  "sg_cli.c"
  "sg_lua.c"
  "sg_event.c"
  "sg_render.c"
  "sg_log.c"
  "../scl.c")
add_executable(sg "resource.rc" ${SG_SOURCES})
add_dependencies(sg luajit_target)
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
# "SDL3_shadercross-static" "spirv-cross-c-shared" "dxcompiler"
set(SDL_LIBS "SDL3-static")
set(SDL_DEPS kernel32 user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32)
else()
# "SDL3_shadercross" "spirv-cross-c-shared" "dxcompiler"
set(SDL_LIBS "SDL3" )
set(SDL_DEPS "m")
endif()
target_link_libraries(sg PRIVATE ${SDL_LIBS} ${SDL_DEPS} libluajit)
get_target_property(SG_SG_COMPILE_FLAGS sg COMPILE_FLAGS)
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/core" VERSION ${SG_VERSION} COMPILE_FLAGS "${SG_COMPILE_FLAGS}")
createVersionH(sg)
clangdConfigure(sg)

add_custom_command(TARGET sg PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_SHARED} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

