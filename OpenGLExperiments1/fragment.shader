#version 460 core
out vec4 FragColor;
in vec3 vertexColor;
in vec3 vertexPosition;

void main()
{
    FragColor = vec4(vertexPosition, 1.0f);
}