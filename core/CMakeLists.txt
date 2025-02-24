
set(NATIVE_SOURCES
  "NativeStorm/native.cpp"
  "NativeStorm/Shader.cpp")
set(NATIVE_LIBS "")

add_library(NativeStorm SHARED ${NATIVE_SOURCES})
target_link_libraries(NativeStorm PRIVATE ${NATIVE_LIBS} SDL3_shadercross-static)

#add_custom_command(TARGET NativeStorm PRE_BUILD COMMAND "python" "${CMAKE_SOURCE_DIR}/build_scripts/build_SDL.py" WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/SDL3")

set(SG_SOURCES
  "sg.cpp"
  "CLIHandler.cpp"
  "NetHost/NetHost.cpp"
  "NetHost/StormProcs.cpp")
add_executable(sg "resource.rc" ${SG_SOURCES})
if (MSVC)
#target_compile_options(sg PRIVATE "/fsanitize=address")
endif()
target_link_libraries(sg PRIVATE NativeStorm "SDL3")
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/core" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)

add_custom_command(TARGET sg PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_SHARED} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_custom_target(engine)
enginebuild(engine debug)
