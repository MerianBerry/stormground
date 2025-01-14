cmake_minimum_required(VERSION "3.22")

project(SG2 LANGUAGES C)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(SG_VERSION "2.0-beta")
set(CMAKE_SKIP_INSTALL_RULES ON)

include(build_scripts/clangdConfig.cmake)
include(build_scripts/headerGenerator.cmake)
include(build_scripts/versionH.cmake)

if (MSVC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
else()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()


include_directories("${CMAKE_SOURCE_DIR}/third_party/SDL3/include" "${CMAKE_SOURCE_DIR}/third_party" "${CMAKE_SOURCE_DIR}/third_party/luajit/src")

add_subdirectory(src)

#add_subdirectory(third_party/luajit)
set(SDL_STATIC ON)
#add_subdirectory(third_party/SDL3)

set(SLANG_LIB_TYPE STATIC)
set(SLANG_ENABLE_SLANGD OFF)
set(SLANG_ENABLE_SLANGC OFF)
set(SLANG_ENABLE_GFX OFF)
set(SLANG_ENABLE_TESTS OFF)
set(SLANG_ENABLE_EXAMPLES OFF)

#add_subdirectory(third_party/slang)

set(SOCKET_DIR "third_party/luasocket/src")
set(SOCKET_SRCS "${SOCKET_DIR}/luasocket.c" "${SOCKET_DIR}/timeout.c" "${SOCKET_DIR}/buffer.c" "${SOCKET_DIR}/io.c" "${SOCKET_DIR}/auxiliar.c" "${SOCKET_DIR}/compat.c" "${SOCKET_DIR}/options.c" "${SOCKET_DIR}/inet.c" "${SOCKET_DIR}/except.c" "${SOCKET_DIR}/except.c" "${SOCKET_DIR}/select.c" "${SOCKET_DIR}/tcp.c" "${SOCKET_DIR}/udp.c")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  list(APPEND SOCKET_SRCS "${SOCKET_DIR}/wsocket.c")
else()
  
endif()
  
add_library(luasocket STATIC ${SOCKET_SRCS})
target_include_directories(luasocket PRIVATE third_party/luajit/src)
target_link_libraries(luasocket PRIVATE libluajit "Ws2_32")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  target_compile_definitions(luasocket PRIVATE "WIN32" NDEBUG _WINDOWS _CRT_SECURE_NO_WARNINGS LUASOCKET_NODEBUG)
  #set_target_properties(luasocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/socket OUTPUT_NAME "core")
  #target_link_options(luasocket PRIVATE "//SUBSYSTEM:WINDOWS" "//OPT:REF" "//OPT:ICF")
else()
  
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_target_properties(minilua buildvm buildvm_arch_h lj_gen_folddef lj_gen_headers lj_gen_vm_s lj_luajit_h libluajit luajit PROPERTIES FOLDER luajit)
set_target_properties(luasocket PROPERTIES FOLDER "libs")
#set_target_properties(slang compiler-core copy_slang_headers core slang-common-objects slang-glslang slang-rt PROPERTIES FOLDER slang)

#add_subdirectory(third_party/luajit-cmake)

#add_custom_target(luaj make -C "${CMAKE_SOURCE_DIR}/third_party/luaj" -j12 BYPRODUCTS "luajit.lib" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/third_party/luaj")