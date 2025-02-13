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
else()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

include_directories("${CMAKE_SOURCE_DIR}/third_party/SDL3/include" "${CMAKE_SOURCE_DIR}/third_party")

add_subdirectory(core)

set(SDL_SHARED TRUE)
set(SDL_STATIC FALSE)
add_subdirectory(third_party/SDL3)

set(SLANG_LIB_TYPE STATIC)
set(SLANG_ENABLE_SLANGD OFF)
set(SLANG_ENABLE_SLANGC OFF)
set(SLANG_ENABLE_GFX OFF)
set(SLANG_ENABLE_TESTS OFF)
set(SLANG_ENABLE_EXAMPLES OFF)

#add_subdirectory(third_party/slang)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_target_properties(slang compiler-core copy_slang_headers core slang-common-objects slang-glslang slang-rt PROPERTIES FOLDER slang)