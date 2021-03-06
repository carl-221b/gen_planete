project(pdp_planet)

cmake_minimum_required(VERSION 3.1)

###################
#Exterior library

add_subdirectory(ext/glfw)
add_subdirectory(ext/glbinding)
add_subdirectory(ext/libnoise)
add_subdirectory(ext/googletest)
add_subdirectory(ext/pugixml)

###################
#Include

include_directories(ext/glfw/include)
include_directories(ext/glbinding/include)
include_directories(ext/eigen3)
include_directories(ext/libnoise)
include_directories(ext/libnoise/include)
include_directories(ext/pugixml)
include_directories(ext/pugixml/src)
include_directories(ext)

include_directories(ext/googletest)
include_directories(ext/googletest/include)

include_directories(include)

###################
#Compil flags

#Debug
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g --debug")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

###################
#Sources

set(SRC_FILES
    model/aleatorymode.cpp
    model/thresholdtable.cpp
    model/random_editor.cpp
    model/noisyheight_editor.cpp
    model/noiserandom.cpp
    model/icosphere.cpp
    model/xmlgenerator.cpp
    view/shader.cpp
    view/trackball.cpp
    view/camera.cpp
    view/viewer.cpp
    view/rendering_opengl.cpp
    repository/shape_repository.cpp
)

set(HEADERS
    include/aleatorymode.h
    include/thresholdtable.h
    include/noiserandom.h
    include/random_editor.h
    include/noisyheight_editor.h
    include/shape.h
    include/editor.h
    include/icosphere.h
    include/shader.h
    include/trackball.h
    include/viewer.h
    include/camera.h
    include/common.h
    include/opengl.h
    include/rendering.h
    include/rendering_opengl.h
    include/shape_repository.h
    include/generator.h
    include/xmlgenerator.h
)

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")
add_executable(gen_planet main.cpp ${SRC_FILES} ${HEADERS})
target_link_libraries(gen_planet glfw ${GLFW_LIBRARIES} glbinding libnoise pugixml)

###################
#Test

ENABLE_TESTING()
set(TESTS
    tests/test_main.cpp
    tests/test_geometry.cpp
    tests/test_editor.cpp
    tests/test_save_load.cpp
    tests/test_time_generation.cpp
    tests/test_generator.cpp
    tests/test_common.cpp
    tests/test_treshold.cpp
    tests/test_random.cpp
    tests/test_performances.cpp
)
add_executable(unit_tests ${TESTS} ${SRC_FILES} ${HEADERS})
target_link_libraries( unit_tests glbinding libnoise gtest pugixml)
add_test( NAME unit_tests COMMAND unit_tests)

###################
#External files

function(IndicateExternalFile _target)
    foreach(_file IN ITEMS ${ARGN})
        if ((IS_ABSOLUTE "${_file}" AND EXISTS "${_file}") OR
            (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_file}"))
            target_sources(${_target} PRIVATE "${_file}")
        endif()
    endforeach()
endfunction()

file(GLOB SHADERS "data/shaders/*.vert" "data/shaders/*.frag")
file(GLOB PARAMS "data/generators/*.xml")
IndicateExternalFile("gen_planet" ${SHADERS})
IndicateExternalFile("gen_planet" ${PARAMS})
