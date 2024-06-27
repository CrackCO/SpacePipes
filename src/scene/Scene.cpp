#include "Scene.hpp"

Scene::Scene(const World& world, const Camera& camera)
    : world(world),
    camera(camera)
{}

const World& Scene::GetWorld() const
{ return world;  }

const Camera& Scene::GetCamera() const
{ return camera; }