#include "Shader.hpp"

const char* Shader::fragSrc = R"(
    #version 330 core

    out vec4 FragColor;

    in float diffuse;

    void main() {
        FragColor = vec4(diffuse, diffuse, diffuse, 1.0);
    }
)";