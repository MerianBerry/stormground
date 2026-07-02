
find_package(Python3 COMPONENTS Interpreter REQUIRED)

function(genheader list in)
  cmake_path(GET in STEM outStem)
  cmake_path(GET in EXTENSION outExt)
  string(REPLACE "." "_" outFixExt ${outExt})
  set(out ${CMAKE_BINARY_DIR}/generated/${outStem}${outFixExt}.h)
  set(${list} "${${list}};${out}" PARENT_SCOPE)
  #set(${list} "${${list}};${out}" CACHE STRING "${list}" FORCE)
  #list(APPEND ${list} ${out})
  add_custom_command(OUTPUT "${out}"
    COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_LIST_DIR}/buildconf/headerfy.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/${in}"
    "${out}"
    "${outStem}${outFixExt}"
    DEPENDS ${in})
  #add_dependencies(${target} ${out})
  message(STATUS "Added header generator: ${in} -> ${out}")
endfunction(genheader)

function(target_genheader target in out_var)
  cmake_path(GET in STEM outStem)
  cmake_path(GET in EXTENSION outExt)
  string(REPLACE "." "_" outFixExt ${outExt})
  set(out ${CMAKE_BINARY_DIR}/generated/${outStem}${outFixExt}.h)
  #set(${list} "${${list}};${out}" CACHE STRING "${list}" FORCE)
  #list(APPEND ${list} ${out})
  add_custom_command(OUTPUT "${out}"
    COMMAND ${Python3_EXECUTABLE}
    "${CMAKE_CURRENT_LIST_DIR}/buildconf/headerfy.py"
    "${in}"
    "${out}"
    "${outStem}${outFixExt}"
    DEPENDS ${in})
  message(STATUS "Added header generator: ${in} -> ${out}")
endfunction(target_genheader)
