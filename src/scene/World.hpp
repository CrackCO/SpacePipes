#pragma once

#include <glm/glm.hpp>

class World {
public:
    World();
    ~World();

    std::vector<glm::vec3> getVertices() const;
};