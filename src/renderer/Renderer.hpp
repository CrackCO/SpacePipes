#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene/World.hpp"
#include "scene/Camera.hpp"
#include "shader/Shader.hpp"

class Renderer {
private:
    GLFWwindow* window;
    GLuint VAO, VBO, EBO;
    Shader shader;

    const World& world;
    const Camera& camera;

public:
    Renderer(GLFWwindow* window, const World& world, const Camera& camera);
    ~Renderer();

private:
    void initMesh();
    void cleanup();

public:
    void render();

};