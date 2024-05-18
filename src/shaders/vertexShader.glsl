#version 330 core

in vec3 position;

uniform vec3 cameraPos;
uniform vec3 cameraDir;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out float diffuse;

void main()
{
    vec4 viewPos = viewMatrix * vec4(position, 1.0);

    vec3 viewDir = normalize(viewPos.xyz - cameraPos);

    diffuse = max(0.0, dot(viewDir, cameraDir));

    gl_Position = projectionMatrix * viewPos;
}
