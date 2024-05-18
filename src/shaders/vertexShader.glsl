#version 330 core

in vec3 position;

uniform vec3 cameraPos;
uniform vec3 cameraDir;

out vec3 fragPosition;

void main() {
    vec3 cameraUpVector = vec3(0.0, 1.0, 0.0);
    vec3 cameraRightVector = cross(cameraDir, cameraUpVector);
    vec3 cameraUpVectorNormalized = cross(cameraRightVector, cameraDir);

    mat4 viewMatrix = mat4(
        vec4(cameraRightVector, 0.0),
        vec4(cameraUpVectorNormalized, 0.0),
        vec4(-cameraDir, 0.0),
        vec4(-cameraPos, 1.0)
    );

    vec4 viewPosition = viewMatrix * vec4(vertexPosition, 1.0);

    fragPosition = vertexPosition;

    gl_Position = viewPosition;
}
