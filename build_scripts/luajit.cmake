if (NOT DEFINED LJBUILD_DIR)
set(LJBUILD_DIR ${CMAKE_BINARY_DIR}/luajit)
endif()

cmake_path(GET LJBUILD_DIR PARENT_PATH LJCMAKE_DIR)
set(LJCMAKE_DIR "${LJCMAKE_DIR}/luajit-cmake")

# Clone luajit repos

if (NOT EXISTS ${LJBUILD_DIR})
execute_process(COMMAND "git" "clone" "https://github.com/LuaJIT/LuaJIT.git" "${LJBUILD_DIR}")
endif()
if (NOT EXISTS ${LJCMAKE_DIR} AND MSVC)
execute_process(COMMAND "git" "clone" "https://github.com/zhaozg/luajit-cmake.git" "${LJCMAKE_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND}
  "."
  "-B" "${LJBUILD_DIR}/build"
  "-DBUILD_SHARED_LIBS=TRUE"
  "-DLUAJIT_DIR=${LJBUILD_DIR}" 
  "-DCMAKE_BUILD_TYPE=Release"
  WORKING_DIRECTORY ${LJCMAKE_DIR})
endif()

include_directories("${LJBUILD_DIR}/src")

if (MSVC)
# Use luajit-cmake because there is no way in hell i am doing it manually
set(LJLIB_PATH "${LJBUILD_DIR}/build/Release/libluajit.dll")
add_custom_command(OUTPUT ${LJLIB_PATH}
                  COMMAND ${CMAKE_COMMAND} "--build" "." "--config" "Release"
                  WORKING_DIRECTORY "${LJBUILD_DIR}/build")
add_custom_target("luajit_target" DEPENDS "${LJLIB_PATH}")
link_directories("${LJBUILD_DIR}/build/Release")
set(LUAJIT_LIB ${LUAJIT_PATH})
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
# Just use make, and make it compilable from cmake
set(LJLIB_PATH "${LJBUILD_DIR}/src/libluajit.so")
add_custom_command(OUTPUT "${LJLIB_PATH}"
COMMAND "make" "-C" "src" "libluajit.so" "-j8"
WORKING_DIRECTORY "${LJBUILD_DIR}")
add_custom_target("luajit_target" DEPENDS "${LJLIB_PATH}")
link_directories("${LJBUILD_DIR}/src")
set(LUAJIT_LIB ${LUAJIT_PATH})
endif()

cmake_path(GET LJLIB_PATH FILENAME LJLIB_FILE)
add_custom_command(TARGET luajit_target POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  "-E" "copy_if_different"
  "${LJLIB_PATH}"
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${LJLIB_FILE}")
