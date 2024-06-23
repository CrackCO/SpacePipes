#pragma once

#include "World.hpp"
#include "Camera.hpp"

class Scene {
private:
    const World& world;
    const Camera& camera;

public:
    Scene(const World& world, const Camera& camera);
    ~Scene() = default;

    const World& getWorld() const;
    const Camera& getCamera() const;
};