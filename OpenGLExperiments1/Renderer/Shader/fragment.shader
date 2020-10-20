#version 460 core
out vec4 FragColor;
  
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 background = mix(texture(texture1, TexCoord), vec4(vertexColor, 1.0f), 0.2f);
	vec4 darkBackground = mix(background, vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.0f);
    FragColor = mix(darkBackground, texture(texture2, TexCoord), texture(texture2, TexCoord).a);
}