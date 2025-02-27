
function(genHeader list in)
  cmake_path(GET in STEM outStem)
  set(out ${CMAKE_BINARY_DIR}/generated/${outStem}.h)
  set(${list} "${${list}};${out}" CACHE STRING "${list}" FORCE)
  #list(APPEND ${list} ${out})
  add_custom_command(OUTPUT ${out}
    COMMAND ${PYTHON_CMD}
    ${CMAKE_SOURCE_DIR}/build_scripts/headerfy.py
    ${in}
    ${out}
    ${outStem})
  #add_dependencies(${target} ${out})
  message(STATUS "Added header generator: ${in} -> ${out}")
endfunction(genHeader)

function(target_genHeader target in)
  cmake_path(GET in STEM outStem)
  cmake_path(GET in EXTENSION outExt)
  string(REPLACE "." "_" outFixExt ${outExt})
  set(out ${CMAKE_BINARY_DIR}/generated/${outStem}.h)
  #set(${list} "${${list}};${out}" CACHE STRING "${list}" FORCE)
  #list(APPEND ${list} ${out})
  add_custom_command(TARGET ${target} PRE_BUILD
    COMMAND ${PYTHON_CMD}
    ${CMAKE_SOURCE_DIR}/build_scripts/headerfy.py
    ${in}
    ${out}
    "${outStem}${outFixExt}")
  #add_dependencies(${target} ${out})
  message(STATUS "Added header generator: ${in} -> ${out}")
endfunction(target_genHeader)
