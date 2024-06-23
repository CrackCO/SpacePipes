#include "Scene.hpp"

Scene::Scene(const World& world, const Camera& camera)
    :
    world  ( world  ),
    camera ( camera )
{}

const World&  Scene::getWorld  () const { return world;  }
const Camera& Scene::getCamera () const { return camera; }