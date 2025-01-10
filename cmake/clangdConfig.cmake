
function(clangdConfigure target)
get_target_property(inc_dirs ${target} INCLUDE_DIRECTORIES)
message(STATUS "DIRS: ${inc_dirs}")
set(CLANGD_INCLUDE_DIRS "")

foreach(dir ${inc_dirs})
set(CLANGD_INCLUDE_DIRS "${CLANGD_INCLUDE_DIRS}, -I${dir}")
endforeach()

file(WRITE "${CMAKE_CURRENT_LIST_DIR}/.clangd" "If:
  PathMatch: [.*\.hpp, .*\.h, .*\.cpp, .*\.c]
  PathExclude: third_party/*
CompileFlags:
  Add: [-Wno-deprecated-declarations, -Wno-unused-includes${CLANGD_INCLUDE_DIRS}]")

endfunction()

