#pragma once

#include "World.hpp"
#include "Camera.hpp"
#include <app/Definitions.hpp>


class Scene {
public:
    Scene(const World& world, const Camera& camera);

    SP_NODISCARD const World& GetWorld() const;
    SP_NODISCARD const Camera& GetCamera() const;

    ~Scene() = default;

private:
    const World& world;
    const Camera& camera;
};