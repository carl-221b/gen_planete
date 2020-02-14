project(icosphere_geo)

cmake_minimum_required(VERSION 3.1)

add_subdirectory(ext/glfw)
add_subdirectory(ext/glbinding)

include_directories(ext/glfw/include)
include_directories(ext/glbinding/include)
include_directories(ext/eigen3)
include_directories(ext)

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
)

add_definitions(-DDATA_DIR="${PROJECT_SOURCE_DIR}/data")

add_executable(tp_si ${SRC_FILES})

target_link_libraries(tp_si glfw ${GLFW_LIBRARIES} glbinding)
