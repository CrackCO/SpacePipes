#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "World.hpp"
#include "Camera.hpp"

class Renderer {
private:
    GLFWwindow* window;
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;

    const World& world;
    const Camera& camera;

public:
    Renderer(GLFWwindow* window, const World& world, const Camera& camera);
    ~Renderer();

private:
    GLuint compileShader(GLuint type, const char* src);
    void initShaders();
    void initMesh();
    void cleanup();

public:
    void render();

};