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

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall --debug")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# the list of source files
set(SRC_FILES
    model/basic_editor.cpp
    model/noisyheight_editor.cpp
    model/heightnoise.cpp
    model/mesh.cpp
    model/advanced_editor.cpp
    view/shader.cpp
    view/trackball.cpp
    view/camera.cpp
    view/viewer.cpp
    main.cpp
)

set(HEADERS
    include/heightnoise.h
    include/basic_editor.h
    include/noisyheight_editor.h
    include/shape.h
    include/editor.h
    include/mesh.h
    include/shader.h
    include/trackball.h
    include/viewer.h
    include/camera.h
    include/common.h
    include/opengl.h
    include/advanced_editor.h
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
