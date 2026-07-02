cmake_minimum_required(VERSION 3.22)

project(sg LANGUAGES C)

include(buildconf/headerGenerator.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl/include 
  ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/external
  ${CMAKE_CURRENT_BINARY_DIR}/generated)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(SDL_CAMERA OFF)
set(SDL_GPU OFF)
set(SDL_RENDER OFF)
set(SDL_TRAY OFF)
set(SDL_FILESYSTEM OFF)
set(SDL_SENSOR OFF)
set(SDL_POWER OFF)
set(SDL_HAPTIC OFF)
set(SDL_DIRECTX OFF)
set(SDL_VULKAN OFF)
add_subdirectory(external/sdl)

set(SOURCES
  src/cJSON.c
  src/scl.c
  src/sg.c
  src/sgapi.c
  src/sgcli.c
  src/sgimage.c
  src/sginput.c
  src/sgrender.c
  src/sgshader.c
  external/glad/src/gl.c
)

genheader(SOURCES src/shaders/blit.frag)
genheader(SOURCES src/shaders/blit.vert)
genheader(SOURCES src/shaders/main.frag)
genheader(SOURCES src/shaders/main.vert)

add_executable(sg ${SOURCES})
target_link_directories(sg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux)
target_link_libraries(sg PRIVATE SDL3-static)
#target_link_libraries(sg PRIVATE glfw3 GL pthread X11 Xrandr Xi dl m)
