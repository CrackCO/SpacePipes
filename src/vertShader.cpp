#include "Shader.hpp"

const char* Shader::vertSrc = R"(
    #version 330 core

    in vec3 position;

    uniform vec3 cameraPos;
    uniform vec3 cameraDir;

    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    uniform float time;

    out float diffuse;

    void main() {
        float angle = time * 2.0 * 3.14159;

        mat4 rotationMatrix = mat4(
            vec4(cos(angle), 0.0, sin(angle), 0.0),
            vec4(0.0, 1.0, 0.0, 0.0),
            vec4(-sin(angle), 0.0, cos(angle), 0.0),
            vec4(0.0, 0.0, 0.0, 1.0)
        );

        vec4 rotatedPosition = rotationMatrix * vec4(position, 1.0);
        vec4 viewPos = viewMatrix * rotatedPosition;
        vec3 viewDir = normalize(viewPos.xyz - cameraPos);
        diffuse = max(0.0, dot(viewDir, cameraDir));
        gl_Position = projectionMatrix * viewPos;
    }
)";