#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "World.hpp"
#include "Camera.hpp"

class Renderer {
private:
    GLFWwindow* window;
    const World& world;
    const Camera& camera;
    GLuint shaderProgram;

public:
    Renderer(GLFWwindow* window, const World& world, const Camera& camera);
    ~Renderer();

private:
    void compileShaders();

public:
    void render();
};