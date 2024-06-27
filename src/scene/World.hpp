#pragma once

#include <glm/glm.hpp>

#include <app/Definitions.hpp>


class World {
public:
    World() = default;

    SP_NODISCARD std::vector<glm::vec3> GetVertices() const;

    ~World() = default;
};