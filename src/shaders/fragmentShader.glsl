#version 330 core

in vec3 position;
in float diffuse;

out vec4 fragColor;

void main()
{
    if (diffuse == 0.0)
    {
        fragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
    else
    {
        vec3 color = vec3(diffuse);

        fragColor = vec4(color, 1.0);
    }
}
