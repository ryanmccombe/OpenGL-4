#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec3 vertexPosition;
out vec2 TexCoord;

uniform mat4 transformation;

void main()
{
    gl_Position = transformation * vec4(position, 1.0);
	vertexColor = color;
	vertexPosition = position;
	TexCoord = aTexCoord;
}