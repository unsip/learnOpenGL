# Filling templates with shaders code.
file(READ simple.vert SIMPLE_VERT)
file(READ simple.frag SIMPLE_FRAG)
configure_file(shaders.cpp.in shaders.cpp @ONLY)

add_executable(
    hello_gl
    shaders.hpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/shaders.cpp
  )

target_compile_options(
    hello_gl
    PRIVATE
        -Wall
        -Wextra
  )

target_include_directories(
    hello_gl
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(
    hello_gl
    PRIVATE
        OpenGL::GL
        # NOTE GLFW library provides an awkward CMake support:
        # the imported target declared out of any namespace!
        # TODO Send a patch to upstream.
        glfw
  )
