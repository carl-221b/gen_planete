project(pdp_planet)

cmake_minimum_required(VERSION 3.1)

add_subdirectory(ext/glfw)
add_subdirectory(ext/glbinding)
add_subdirectory(ext/libnoise)

include_directories(ext/glfw/include)
include_directories(ext/glbinding/include)
include_directories(ext/eigen3)
include_directories(ext/libnoise)
include_directories(ext/libnoise/include)
include_directories(ext)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall --debug")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# the list of source files
set(SRC_FILES
    src/shader.cpp
    src/mesh.cpp
    src/trackball.cpp
    src/camera.cpp
    src/viewer.cpp
    src/main.cpp
    src/basic_editor.cpp
    src/noisyheight_editor.cpp
    src/heightnoisegen.cpp
    src/noisemap.cpp
)

set(HEADERS
    src/basic_editor.h
    src/noisyheight_editor.h
    src/camera.h
    src/common.h
    src/editor.h
    src/mesh.h
    src/opengl.h
    src/shader.h
    src/shape.h
    src/trackball.h
    src/viewer.h

    src/noisegenerator.h
    src/heightnoisegen.h
    src/noisemap.h
    )

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")

add_executable(gen_planet ${SRC_FILES} ${HEADERS})

target_link_libraries(gen_planet glfw ${GLFW_LIBRARIES} glbinding libnoise)

function(IndicateExternalFile _target)
    foreach(_file IN ITEMS ${ARGN})
        if ((IS_ABSOLUTE "${_file}" AND EXISTS "${_file}") OR
            (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_file}"))
            target_sources(${_target} PRIVATE "${_file}")
        endif()
    endforeach()
endfunction()

file(GLOB SHADERS "data/shaders/*.vert" "data/shaders/*.frag")
IndicateExternalFile("gen_planet" ${SHADERS})
