# Filling templates with shaders code.
file(READ simple.vert SIMPLE_VERT)
file(READ simple.frag SIMPLE_FRAG)
configure_file(shaders.cpp.in shaders.cpp)
configure_file(shaders.hpp ${CMAKE_CURRENT_BINARY_DIR})

add_executable(
    hello_gl
    shaders.hpp
    ${CMAKE_CURRENT_BINARY_DIR}/shaders.cpp
    main.cpp
    )

target_include_directories(hello_gl PRIVATE "${GLAD_DIR}/include")

target_link_libraries(
    hello_gl
    PRIVATE
        glad
        ${OPENGL_LIBRARY}
        ${GLFW_LIBRARIES}
)
