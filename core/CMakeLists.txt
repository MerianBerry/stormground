
set(SG_SOURCES
  "sg.cpp"
  "api.cpp"
  "Shader.cpp"
  "CLIHandler.cpp"
  "NetHost/NetHost.cpp"
  "NetHost/StormProcs.cpp")
add_executable(sg "resource.rc" ${SG_SOURCES})
if (MSVC)
#target_compile_options(sg PRIVATE "/fsanitize=address")
set(SDL_DEPS kernel32 user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32)
endif()
target_link_libraries(sg PRIVATE "SDL3-static" "SDL3_shadercross-static" "spirv-cross-c-shared" "dxcompiler" ${SDL_DEPS})
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/core" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)

add_custom_command(TARGET sg PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_SHARED} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_custom_target(engine)
enginebuild(engine debug)
