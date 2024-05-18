#include "Camera.hpp"

Camera::Camera(const glm::vec3& pos, const glm::vec3& dir)
    :
    pos(pos),
    dir(dir)
{}

glm::vec3 Camera::getPos() const {
    return pos;
}

glm::vec3 Camera::getDir() const {
    return dir;
}