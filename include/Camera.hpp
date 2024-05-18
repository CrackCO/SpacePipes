#pragma once

#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 pos;
    glm::vec3 dir;

public:
    Camera(const glm::vec3& pos, const glm::vec3& dir);

    glm::vec3 getPos() const;
    glm::vec3 getDir() const;
};