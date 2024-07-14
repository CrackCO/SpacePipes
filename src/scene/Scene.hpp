#pragma once

#include "World.hpp"
#include "Camera.hpp"
#include <app/Definitions.hpp>


class Scene {
public:
    Scene(const World& world, Camera& camera);
    ~Scene() = default;

    const World& world;
    Camera& camera;
};