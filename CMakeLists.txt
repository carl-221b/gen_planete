project(gen_planet_pdp)

cmake_minimum_required(VERSION 3.2.0)

add_subdirectory(ext/glfw)
add_subdirectory(ext/glbinding)

include_directories(ext/glfw/include)
include_directories(ext/glbinding/include)
include_directories(ext/eigen3)
include_directories(ext/)

include_directories(include/)

set (CMAKE_CXX_STANDARD 11)

set(SRC_FILES
    ext/ObjFormat/ObjFormat.cpp
    ext/ObjFormat/ObjUtil.cpp

    src/main.cpp

    #Interface
    src/shader.cpp
    src/camera.cpp
    src/renderer.cpp
    src/window.cpp

    include/opengl.h
    include/shader.h
    include/camera.h
    include/renderer.h
    include/window.h

    #Geometry
    src/face.cpp
    src/vertex.cpp
    src/geometry.cpp
    src/icosphere.cpp

    include/face.h
    include/vertex.h
    include/geometry.h
    include/icosphere.h

    #Editors
    src/planet.cpp
    src/editor.cpp
    src/basiceditor.cpp

    include/planet.h
    include/editor.h
    include/basiceditor.h

)

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")

add_executable(gen ${SRC_FILES})

target_link_libraries(gen glfw ${GLFW_LIBRARIES} glbinding)

function(IndicateExternalFile _target)
    foreach(_file IN ITEMS ${ARGN})
        if ((IS_ABSOLUTE "${_file}" AND EXISTS "${_file}") OR
            (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_file}"))
            target_sources(${_target} PRIVATE "${_file}")
        endif()
    endforeach()
endfunction()

file(GLOB SHADERS "data/shaders/*.vert" "data/shaders/*.frag")
IndicateExternalFile("gen" ${SHADERS})

