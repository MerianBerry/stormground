

if (WIN32)
set(MONO_DIR "C:/Program Files/Mono")
endif()

set(SG_SOURCES
  "sg.cpp"
  "NetHost/NetHost.cpp")

add_executable(sg "resource.rc" ${SG_SOURCES})
if (MSVC)
#target_compile_options(sg PRIVATE "/fsanitize=address")
endif()
target_compile_definitions(sg PRIVATE SG_INCLUDE_GENERATED=1)
target_include_directories(sg PRIVATE "${CMAKE_BINARY_DIR}/generated")
target_link_libraries(sg PRIVATE "SDL3-shared" "slang")
#target_link_libraries(sg PRIVATE "SDL3-static")
set_target_properties(sg PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/core" VERSION ${SG_VERSION})
createVersionH(sg)
clangdConfigure(sg)

set(NATIVE_SOURCES "NativeStorm/native.cpp")
set(NATIVE_LIBS "")

#[==[
if (WIN32)
list(APPEND NATIVE_SOURCES "NativeStorm/GPUDevice/DirectDevice.cpp")
list(APPEND NATIVE_LIBS "d3d11" "dxgi" "SDL3-shared")
endif()
]==]

add_library(NativeStorm SHARED ${NATIVE_SOURCES})
target_link_libraries(NativeStorm PRIVATE ${NATIVE_LIBS})

add_custom_target(engine)
enginebuild(engine debug)


#[==[set(GLUE_SOURCES
  "glue/sdlglu.cpp")
add_library(sglu SHARED ${GLUE_SOURCES})
#target_link_libraries(sglu PRIVATE "SDL3-static")
set_target_properties(sglu PROPERTIES CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/core/glue" VERSION ${SG_VERSION})
createVersionH(sglu)
]==]
