#include "Renderer.hpp"

#include "iostream"
#include <cstdlib>
#include <GL/glu.h>

static void glCheckError(const char* operation) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error during " << operation << ": " << gluErrorString(error) << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


Renderer::Renderer(GLFWwindow* window, const World& world, const Camera& camera)
    :
    window(window),
    world(world),
    camera(camera)
{
    compileShaders();
}

Renderer::~Renderer()
{
    glDeleteProgram(shaderProgram);
}

void Renderer::compileShaders()
{
    const char* vertexShaderSource = "src/shaders/vertexShader.glsl";
    const char* fragmentShaderSource = "src/shaders/fragmentShader.glsl";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glCheckError("glCreateShader");
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCheckError("glShaderSource");
    glCompileShader(vertexShader);
    glCheckError("glCompileShader");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glCheckError("glCreateShader");
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCheckError("glShaderSource");
    glCompileShader(fragmentShader);
    glCheckError("glCompileShader");

    shaderProgram = glCreateProgram();
    glCheckError("glCreateShaderProgram");
    glAttachShader(shaderProgram, vertexShader);
    glCheckError("glAttachVertexShader");
    glAttachShader(shaderProgram, fragmentShader);
    glCheckError("glAttachFragmentShader");
    glLinkProgram(shaderProgram);
    glCheckError("glLinkShaderProgram");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "shaders compiling complete successfully\n";
}

void Renderer::render()
{
    std::vector<glm::vec3> vertices = world.getVertices();

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glCheckError("glGenBuffers");
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError("glBindBuffer");
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glCheckError("glBufferData");

    glUseProgram(shaderProgram);

    GLint cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosLoc, 1, &(camera.getPos())[0]);

    GLint cameraDirLoc = glGetUniformLocation(shaderProgram, "cameraDir");
    glUniform3fv(cameraDirLoc, 1, &(camera.getDir())[0]);

    GLint viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &camera.getViewMatrix()[0][0]);

    GLint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &camera.getProjectionMatrix()[0][0]);

    GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}