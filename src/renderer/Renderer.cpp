#include "Renderer.hpp"

#include "shader/Shader.hpp"

Renderer::Renderer(GLFWwindow* window, const World& world, const Camera& camera)
    :
    window(window),
    VAO(0), VBO(0), EBO(0),
    shader(),
    world(world),
    camera(camera)
{
    shader.compile();
    initMesh();
}

Renderer::~Renderer()
{
    cleanup();
}


void Renderer::initMesh() {
    GLfloat vertices[] = {
        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f
    };

    GLuint indices[] = {
        0, 1, 2, 
        2, 3, 0, 
        4, 5, 6, 
        6, 7, 4, 
        0, 4, 7, 
        7, 3, 0, 
        1, 5, 6, 
        6, 2, 1, 
        3, 2, 6, 
        6, 7, 3, 
        0, 1, 5, 
        5, 4, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::render() {
    glfwPollEvents();

    shader.bind();

    shader.setVec3( "cameraPos",        camera.getPos              ());
    shader.setVec3( "cameraDir",        camera.getDir              ());
    shader.setMat4( "viewMatrix",       camera.getViewMatrix       ());
    shader.setMat4( "projectionMatrix", camera.getProjectionMatrix ());
    shader.setFloat("time", 0.0f); //glfwGetTime() / 16.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
}
