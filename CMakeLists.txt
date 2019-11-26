cmake_minimum_required(VERSION 3.15)

project(learnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Always prefer vendor-neutral GL lib.
set(OpenGL_GL_PREFERENCE "GLVND")
set(GLAD_DIR "lib")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

add_subdirectory(src)
