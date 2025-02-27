function(createVersionH target)
get_target_property(version ${target} VERSION)
get_target_property(dir ${target} CMAKE_SOURCE_DIR)

add_custom_command(TARGET ${target} PRE_BUILD
  COMMAND ${PYTHON_CMD}
  ${CMAKE_SOURCE_DIR}/build_scripts/versionh.py
  ${target}
  ${version}
  "${dir}/${target}_version.h")
endfunction()