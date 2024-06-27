#include "renderer/shader/Shader.hpp"

std::string Shader::fragSrc = R"(
    #version 330 core

    out vec4 FragColor;

    in float diffuse;

    void main() {
        FragColor = vec4(diffuse, diffuse, diffuse, 1.0);
    }
)";