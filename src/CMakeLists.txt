#[[add_executable(test "test.c" "hydrogen.c")
#add_dependencies(test luasocket)
target_link_libraries(test PUBLIC libluajit luasocket mxml)
target_include_directories(test PRIVATE "${CMAKE_SOURCE_DIR}/src" "${CMAKE_BINARY_DIR}/generated" "${CMAKE_SOURCE_DIR}/third_party/luasocket/src")
target_compile_definitions(test PRIVATE SG_INCLUDE_GENERATED=1)
clangdConfigure(test)

target_genHeader(test ${CMAKE_SOURCE_DIR}/third_party/mobdebug/src/mobdebug.lua)
target_genHeader(test ${CMAKE_SOURCE_DIR}/third_party/luasocket/src/socket.lua)
]]

if (WIN32)
set(MONO_DIR "C:/Program Files/Mono")
endif()

set(SG_SOURCES
  "sg.c"
  "sg_cli.c"
  "sgsharp.c"
  "macl.c")

add_executable(sg "resource.rc" "hydrogen.c" ${SG_SOURCES})
target_compile_definitions(sg PRIVATE SG_INCLUDE_GENERATED=1)
target_include_directories(sg PRIVATE "${CMAKE_BINARY_DIR}/generated" "${MONO_DIR}/include/mono-2.0")
target_link_directories(sg PRIVATE "${MONO_DIR}/lib")
target_link_libraries(sg libmono-static-sgen)
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)

target_genHeader(sg ${CMAKE_SOURCE_DIR}/third_party/mobdebug/src/mobdebug.lua)
target_genHeader(sg ${CMAKE_SOURCE_DIR}/third_party/luasocket/src/socket.lua)