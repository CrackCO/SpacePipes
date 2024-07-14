#pragma once

#include "Mesh.hpp"

enum pipeType {
    /* straight */
    X_ALIGNED, /* basic */
    Y_ALIGNED,
    Z_ALIGNED,

    /* bent */
    POS_X_TO_POS_Y,
    POS_X_TO_NEG_Y, /* basic */ 
    POS_X_TO_POS_Z, 
    POS_X_TO_NEG_Z, /* POSitive X TO NEGative Z */

    NEG_X_TO_POS_Z,
    NEG_X_TO_NEG_Z,
    NEG_X_TO_POS_Y,
    NEG_X_TO_NEG_Y,

    POS_Y_TO_POS_Z,
    POS_Y_TO_NEG_Z,

    NEG_Y_TO_POS_Z,
    NEG_Y_TO_NEG_Z
};

class Pipe {
public:
    pipeType type;
    Mesh mesh; /* The field will be removed in the future for optimization */
    glm::mat4 transformation;
    glm::vec3 color;

    Pipe(pipeType type, Mesh mesh, glm::mat4 transformation, glm::vec3 color);
    Pipe() = default;
    ~Pipe() = default;

    Pipe& operator=(const Pipe& other);
};