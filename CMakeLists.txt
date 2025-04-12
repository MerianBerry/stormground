cmake_minimum_required(VERSION "3.22")

project(SG2 LANGUAGES C)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(SG_VERSION "2.0-alpha")
set(CMAKE_SKIP_INSTALL_RULES ON)

include(build_scripts/clangdConfig.cmake)
include(build_scripts/headerGenerator.cmake)
include(build_scripts/versionH.cmake)

if (MSVC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(DYLIB_PREFIX "")
set(DYLIB_EXTENSION "dll")
set(PYTHON_CMD "python")
set(SG_COMPILE_FLAGS "-std=c11")
else()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(DYLIB_PREFIX "lib")
set(DYLIB_EXTENSION "so")
set(PYTHON_CMD "python3")
set(SG_COMPILE_FLAGS "-std=c11")
endif()

include(build_scripts/sdl.cmake)
include(build_scripts/luajit.cmake)

include_directories(
  "${CMAKE_BINARY_DIR}/generated"
  "${CMAKE_SOURCE_DIR}/third_party"
  "${CMAKE_SOURCE_DIR}/src")

add_subdirectory(src/core)
add_subdirectory(src/amp)

