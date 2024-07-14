#include "Pipe.hpp"

#include "Mesh.hpp"
#include "Pipe.hpp"


Pipe::Pipe(pipeType type, Mesh mesh, glm::mat4 transformation, glm::vec3 color)
    : type(type), mesh(mesh), transformation(transformation), color(color)
{}


Pipe& Pipe::operator=(const Pipe& other) {
    if (this == &other) {
        return *this;
    }

    type = other.type;
    mesh = other.mesh;
    transformation = other.transformation;
    color = other.color;

    return *this;
}