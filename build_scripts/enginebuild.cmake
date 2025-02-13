function(enginebuild target mode)
add_custom_command(TARGET ${target} POST_BUILD
  COMMAND python
  ${CMAKE_SOURCE_DIR}/build_scripts/enginebuild.py
  ${mode}
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
  ${CMAKE_SOURCE_DIR}
  "SG.Core"
  "SDL3.Core")
endfunction()