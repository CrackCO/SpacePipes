#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.hpp"

#include "scene/Scene.hpp"

class Renderer {
private:
    GLFWwindow* window;

    GLuint VAO, VBO, EBO;
    Shader shader;

    const Scene& scene;

public:
    Renderer(GLFWwindow* window, const Scene& scene);
    ~Renderer();

private:
    void initMesh();
    void cleanup();

public:
    void render();
};