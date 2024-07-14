#pragma once
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

typedef unsigned int u32;

struct Vertex {
    glm::vec3 pos;

};


class Mesh {
public:
    std::vector<Vertex>  vertices;
    std::vector<u32>     indices;
    u32 VAO;
private:
    u32 VBO, EBO;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<u32> indices);
    Mesh() = default;
    ~Mesh();

    void bind();

    Mesh& operator=(const Mesh& other);
};