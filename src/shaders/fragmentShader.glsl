#version 330 core

in vec3 fragPosition;

out vec4 fragColor;

void main() {
    vec3 softGreenColor = vec3(0.5, 0.8, 0.5);
    fragColor = vec4(softGreenColor, 1.0);
}
