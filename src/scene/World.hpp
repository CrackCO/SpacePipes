#pragma once

#include <glm/glm.hpp>

#include <app/Definitions.hpp>
#include "scene/Pipe.hpp"
#include "scene/PipeGenerator.hpp"

class World {
public:
    std::vector<Pipe> pipes;

    World()
    {
        //pipes.push_back(PipeGenerator::generatePipe(X_ALIGNED, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
        pipes.push_back(Pipe(X_ALIGNED, PipeGenerator::generateStraight(16, 1), glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
    }

    ~World() = default;
};