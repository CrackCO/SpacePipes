#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
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
    void Cleanup();

private:
    GLFWwindow* window = nullptr;

    /* OpenGL cannot generate buffer with index 0 */
    Shader shader;

    const Scene& scene;
};