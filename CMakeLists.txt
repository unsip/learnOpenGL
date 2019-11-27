cmake_minimum_required(VERSION 3.15)

project(
    learnOpenGL
    VERSION 0.1.0
    DESCRIPTION "Small OpenGL projects for study purpose"
    HOMEPAGE_URL "https://github.com/unsip/learnOpenGL"
    LANGUAGES CXX
  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# GLFW3
find_package(glfw3 REQUIRED)

# Always prefer vendor-neutral GL lib.
set(OpenGL_GL_PREFERENCE GLVND)
# OpenGL
find_package(OpenGL REQUIRED)

add_subdirectory(src)
