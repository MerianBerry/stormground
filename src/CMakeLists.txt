#[[set(SG_MOBDEBUG_PATH "${CMAKE_BINARY_DIR}/generated/mobdebug.h")

add_custom_command(OUTPUT ${SG_MOBDEBUG_PATH}
  COMMAND python
          ${CMAKE_SOURCE_DIR}/build_scripts/headerfy.py
          ${CMAKE_SOURCE_DIR}/third_party/mobdebug/src/mobdebug.lua
          ${SG_MOBDEBUG_PATH}
          mobdebuglua)
add_custom_target(sg_mobdebug_h ALL DEPENDS ${SG_MOBDEBUG_PATH})
]]

add_executable(test "test.c")
#add_dependencies(test luasocket)
target_link_libraries(test PUBLIC libluajit luasocket mxml)
target_include_directories(test PRIVATE "${CMAKE_BINARY_DIR}/generated" "${CMAKE_SOURCE_DIR}/third_party/luasocket/src")
target_compile_definitions(test PRIVATE SG_INCLUDE_GENERATED=1)
clangdConfigure(test)

target_genHeader(test ${CMAKE_SOURCE_DIR}/third_party/mobdebug/src/mobdebug.lua)
target_genHeader(test ${CMAKE_SOURCE_DIR}/third_party/luasocket/src/socket.lua)