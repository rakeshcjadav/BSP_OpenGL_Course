cmake_minimum_required(VERSION 3.0.0)

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

include_directories(STB Dependencies/stb/include)

add_executable(BSP_OpenGL_Course ${SOURCES})

if(UNIX)
    target_link_libraries(BSP_OpenGL_Course PRIVATE  glfw ${GLFW_LIBRARIES} GLEW::GLEW GL)
else(WIN32)
    target_link_libraries(BSP_OpenGL_Course PRIVATE GLFW3 GLEW::GLEW)
endif (UNIX)