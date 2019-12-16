#include "shaders.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

namespace {

constexpr auto DX = 1920;
constexpr auto DY = 1400;
void printCompileStatus(GLuint vertexShader)
{
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLint infoLogCap = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogCap);
        std::vector<char> infoLog(infoLogCap, '\0');
        GLsizei copied = 0;
        glGetShaderInfoLog(vertexShader, infoLogCap, &copied, infoLog.data());
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILIED\n"
            << std::string_view(infoLog.data(), copied) << std::endl;
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

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Initialize and bind Vertex Array Object (VAO), Vertex Buffer Object
    // (VBO), Elements Buffer Object (EBO).
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vertData = Shaders::Vert.data();
    glShaderSource(vs, 1, &vertData, nullptr);
    glCompileShader(vs);
    printCompileStatus(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragData = Shaders::Frag.data();
    glShaderSource(fs, 1, &fragData, nullptr);
    glCompileShader(fs);
    printCompileStatus(fs);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    // Free memory from shader objects left by glCreateShader().
    glDeleteShader(vs);
    glDeleteShader(fs);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw in wireframe mode.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free memory from buffer objects.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return EXIT_SUCCESS;
}
