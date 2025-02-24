cmake_minimum_required(VERSION "3.22")

project(SG2 LANGUAGES C CXX)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(SG_VERSION "2.0-alpha")
set(CMAKE_SKIP_INSTALL_RULES ON)

include(build_scripts/clangdConfig.cmake)
include(build_scripts/headerGenerator.cmake)
include(build_scripts/versionH.cmake)
include(build_scripts/enginebuild.cmake)

if (MSVC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(DYLIB_PREFIX "")
set(DYLIB_EXTENSION "dll")
else()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

make_directory("${CMAKE_SOURCE_DIR}/third_party/SDL")
execute_process(COMMAND "python" "${CMAKE_SOURCE_DIR}/build_scripts/build_SDL.py" "${CMAKE_BINARY_DIR}/SDL3" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/third_party/SDL")

file(GLOB SDL_SHARED "${CMAKE_BINARY_DIR}/SDL3/${DYLIB_PREFIX}*.${DYLIB_EXTENSION}")

link_directories("${CMAKE_BINARY_DIR}/SDL3")
include_directories("${CMAKE_BINARY_DIR}/SDL3/" "${CMAKE_SOURCE_DIR}/third_party")
add_subdirectory(core)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_target_properties(SDL_uclibc SDL3_test SDL3-shared PROPERTIES FOLDER SDL3)
#set_target_properties(slang slang-rt compiler-core copy_slang_headers core slang-glslang PROPERTIES FOLDER slang)