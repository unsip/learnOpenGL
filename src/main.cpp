#include "shaders.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <string>
#include <iostream>

namespace {

constexpr auto DX = 1920;
constexpr auto DY = 1400;

void printCompileStatus(GLuint vertexShader)
{
    int success;
    std::string infoLog;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog.data());
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILIED\n"
            << infoLog << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

}                                                           // anonymous namespace

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(DX, DY, "Hello OpenGL!", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to initialize GLFW window." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // Setting OpenGL viewport rendering on resize.
    glViewport(0, 0, DX, DY);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.7f, 0.2f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Array of vertices for triangle.
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
        };

        // Initialize and bind Vertex Buffer Object
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        const char* data = Shaders::Vert.data();
        glShaderSource(vs, 1, &data, nullptr);
        glCompileShader(vs);
        printCompileStatus(vs);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
