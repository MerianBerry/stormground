if(NOT DEFINED SDL_TAG)
set(SDL_TAG "release-3.2.4")
endif()
if(NOT DEFINED SDL_WORKING_DIR)
set(SDL_WORKING_DIR "${CMAKE_BINARY_DIR}/SDL3")
endif()

set(SDL_SOURCE_DIR "${SDL_WORKING_DIR}/source/SDL")
make_directory(${SDL_SOURCE_DIR})

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
set(SDL_BUILD_DIR "${SDL_SOURCE_DIR}\\build\\Release")
set(SDL_LIBNAME "SDL3-static.lib")
set(SDL_BUILD_FLAGS "--config Release" INTERNAL)
set(SDL_DEPS kernel32 user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32)

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
set(SDL_BUILD_DIR "${SDL_SOURCE_DIR}/build")
set(SDL_LIBNAME "libSDL3.a")
set(SDL_BUILD_FLAGS "-j4")
set(SDL_DEPS m)
endif()

set(SDL_LIBPATH ${SDL_WORKING_DIR}/${SDL_LIBNAME})
set(SDL_FULLLIB ${SDL_BUILD_DIR}/${SDL_LIBNAME})

if (NOT EXISTS ${SDL_LIBPATH})
message("Cloning SDL...")
execute_process(WORKING_DIRECTORY ${SDL_SOURCE_DIR}
COMMAND "git" "clone" "https://github.com/libsdl-org/SDL" ".")

message("Resetting SDL to ${SDL_TAG}...")
execute_process(WORKING_DIRECTORY ${SDL_SOURCE_DIR}
COMMAND "git" "fetch" "origin")

execute_process(WORKING_DIRECTORY ${SDL_SOURCE_DIR}
COMMAND "git" "reset" "--hard" ${SDL_TAG})

message("Configuring SDL...")
execute_process(WORKING_DIRECTORY ${SDL_SOURCE_DIR}
COMMAND ${CMAKE_COMMAND} "-Bbuild" "-S." "-DSDL_SHARED=OFF" "-DSDL_STATIC=ON" "-DSDL_TEST_LIBRARY=OFF" "-DSDL_POWER_DEFAULT=OFF" "-DSDL_SENSOR_DEFAULT=OFF" "-DSDL_DIALOG_DEFAULT=OFF" "-DSDL_CAMERA_DEFAULT=OFF" "-DCMAKE_BUILD_TYPE=Release")

message("Copying SDL headers...")
file(GLOB SDL_HEADERS "${SDL_SOURCE_DIR}/include/SDL3/*.h")
file(COPY ${SDL_HEADERS} DESTINATION ${SDL_WORKING_DIR}/include/SDL3)
endif()

# Check if the sdl source path is under the working dir
string(REGEX MATCH "${SDL_WORKING_DIR}/.+" SDL_SOURCE_CHECK ${SDL_SOURCE_DIR})
message("source check ${SDL_SOURCE_CHECK}")
# If the sdl lib exists, and the source still exists, and the source path is under
# the working dir, delete the source
if (EXISTS ${SDL_LIBPATH} AND EXISTS ${SDL_SOURCE_DIR}/CMakeLists.txt AND NOT ${SDL_SOURCE_CHECK} STREQUAL "")
file(REMOVE_RECURSE ${SDL_SOURCE_DIR})
endif()

include_directories(${SDL_WORKING_DIR}/include)

add_custom_command(OUTPUT ${SDL_LIBPATH}
WORKING_DIRECTORY ${SDL_SOURCE_DIR}
COMMAND ${CMAKE_COMMAND} "--build" "build" ${SDL_BUILD_FLAGS}
COMMAND ${CMAKE_COMMAND} "-E" "copy_if_different" ${SDL_FULLLIB} ${SDL_LIBPATH})
add_custom_target(sdl_target DEPENDS "${SDL_LIBPATH}")


add_library(sdl3 STATIC IMPORTED)
add_dependencies(sdl3 sdl_target)
set_target_properties(sdl3 PROPERTIES
IMPORTED_LOCATION ${SDL_LIBPATH})

set(SDL_LIBS sdl3 ${SDL_DEPS})
message(${SDL_LIBS})