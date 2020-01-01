#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec3 vertexPosition;
out vec2 TexCoord;

uniform float xOffset;

void main()
{
    gl_Position = vec4(position.x + xOffset, position.y, position.z, 1.0);
	vertexColor = color;
	vertexPosition = position;
	TexCoord = aTexCoord;
}