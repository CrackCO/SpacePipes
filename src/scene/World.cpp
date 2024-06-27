#include "World.hpp"

std::vector<glm::vec3> World::GetVertices() const {
    std::vector<glm::vec3> vertices = {
        glm::vec3(-0.732f, 1.293f, 0.146f),
        glm::vec3(-0.605f, 1.122f, 0.439f),
        glm::vec3(-0.260f, 1.195f, 0.695f),
        glm::vec3(0.269f, 1.341f, 0.557f),
        glm::vec3(0.659f, 1.171f, 0.196f),
        glm::vec3(0.548f, 0.976f, -0.240f),
        glm::vec3(0.158f, 0.901f, -0.596f),
        glm::vec3(-0.390f, 1.098f, -0.639f),
        glm::vec3(-0.781f, 1.268f, -0.234f),
        glm::vec3(-0.292f, 0.806f, 0.457f),
        glm::vec3(0.146f, 0.951f, 0.796f),
        glm::vec3(0.631f, 1.098f, 0.572f),
        glm::vec3(0.964f, 0.927f, 0.040f),
        glm::vec3(0.698f, 0.707f, -0.463f),
        glm::vec3(0.098f, 0.585f, -0.817f),
        glm::vec3(-0.598f, 0.829f, -0.765f),
        glm::vec3(-1.016f, 0.976f, -0.137f),
        glm::vec3(-0.490f, 0.474f, 0.294f),
        glm::vec3(0.098f, 0.651f, 0.798f),
        glm::vec3(0.760f, 0.834f, 0.485f),
        glm::vec3(1.049f, 0.634f, -0.117f),
        glm::vec3(0.572f, 0.381f, -0.708f),
        glm::vec3(-0.117f, 0.276f, -0.933f),
        glm::vec3(-0.858f, 0.536f, -0.649f),
        glm::vec3(-1.196f, 0.708f, 0.058f)
    };

    return vertices;
}