#include "Renderer.hpp"
#include "shader/Shader.hpp"
#include "scene/Mesh.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scene/Pipe.hpp"

Mesh generateStraight(unsigned int quality, float radius);
Mesh generateBent(u32 quality, float radius);

Renderer::Renderer(GLFWwindow* window, const Scene& scene)
    :
    window(window),

    shader(),
    scene(scene)
{
    shader.Compile();
}

void Renderer::Render() {
    shader.Bind();

    shader.SetVec3( "cameraPos", scene.camera.GetPos());
    shader.SetVec3( "cameraDir", scene.camera.GetDir());
    shader.SetMat4( "viewMatrix", scene.camera.GetViewMatrix());
    shader.SetMat4( "projectionMatrix", scene.camera.GetProjectionMatrix());
    shader.SetFloat("time", 0.0f); //glfwGetTime() / 16.0f);

    for (int i = 0; i < scene.world.pipes.size(); ++i) {
        glBindVertexArray(scene.world.pipes[i].mesh.VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(scene.world.pipes[i].mesh.indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Renderer::Cleanup() {
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

Renderer::~Renderer()
{ Cleanup(); }
