cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(mpcdemo VERSION 0.1.0)

#SET(CMAKE_CXX_FLAGS "-std=gnu++2a")
SET(CMAKE_CXX_STANDARD 20)

SET(OpenGL_GL_PREFERENCE GLVND)

SET(EXECUTABLE_OUTPUT_PATH .)

file(GLOB SOURCES BSP_OpenGL_Course/*.cpp)

if(UNIX)
    find_package(OpenGL REQUIRED)
endif (UNIX)

find_package(GLEW REQUIRED)

FIND_PACKAGE(Boost 1.54 COMPONENTS log REQUIRED)
FIND_PACKAGE(Threads)

include_directories(STB Dependencies/stb/include)
include_directories(${Boost_INCLUDE_DIR})

add_executable(BSP_OpenGL_Course ${SOURCES})

if(UNIX)
    target_link_libraries(BSP_OpenGL_Course PRIVATE  glfw ${GLFW_LIBRARIES} ${Boost_LOG_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} GLEW::GLEW GL)
else(WIN32)
    target_link_libraries(BSP_OpenGL_Course PRIVATE GLFW3 GLEW::GLEW)
endif (UNIX)