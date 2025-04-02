function(createVersionH target)
get_target_property(version ${target} VERSION)
#get_target_property(dir ${target} CMAKE_SOURCE_DIR)
set(dir "${CMAKE_BINARY_DIR}/generated")

execute_process(COMMAND ${PYTHON_CMD} "${CMAKE_SOURCE_DIR}/build_scripts/versionh.py" "${target}" "${version}" "${dir}/${target}_version.h")
#[[add_custom_command(TARGET ${target} PRE_BUILD
  COMMAND ${PYTHON_CMD}
  ${CMAKE_SOURCE_DIR}/build_scripts/versionh.py
  ${target}
  ${version}
  "${dir}/${target}_version.h")]]
endfunction()