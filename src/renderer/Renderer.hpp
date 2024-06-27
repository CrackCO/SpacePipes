#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <limits>

#include <scene/Scene.hpp>
#include "shader/Shader.hpp"


class Renderer {
public:
    Renderer(GLFWwindow* window, const Scene& scene);

    void Render();

    ~Renderer();

private:
    void InitMesh();
    void Cleanup();

private:
    GLFWwindow* window = nullptr;

    /* OpenGL cannot generate buffer with index 0 */
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    Shader shader;

    const Scene& scene;
};