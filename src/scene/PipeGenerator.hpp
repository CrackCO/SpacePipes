#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Pipe.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PipeGenerator {
public:
    #define PIPE_LENGTH (2.0f)
    static Mesh generateStraight(unsigned int quality, float radius);

    static Mesh generateBent(u32 quality, float radius);

    #define QUALITY (16)
    #define RADIUS (0.5f)
    static Mesh generateMesh(pipeType type);

    static glm::mat4 generateRotation(pipeType type);

    static Pipe generatePipe(pipeType type, glm::vec3 pos, glm::vec3 color);
};