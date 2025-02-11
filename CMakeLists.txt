cmake_minimum_required(VERSION 3.20)
project(openglTut)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(opengltut)

set_target_properties(opengltut PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

target_sources(opengltut
    PUBLIC
    src/main.cpp
    src/utils.cpp
)

target_include_directories(opengltut
    PUBLIC
    src/headers
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

find_library(SOIL2 soil2-debug)
# find_library(SOIL_LIBRARY soil-debug)


if(glfw3_FOUND)
    target_link_libraries(opengltut glfw)
endif()

if(OpenGL_FOUND)
    target_link_libraries(opengltut OpenGL::GL)
    # link_libraries(OpenGL::GL)
endif()

if(GLEW_FOUND)
    target_link_libraries(opengltut GLEW::GLEW)
endif()

target_link_libraries(opengltut SOIL)
