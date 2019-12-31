#pragma once
#include <glad/glad.h>

class Shader
{
public:
	static int Program()
	{
		auto vertexShader = Shader::vertexShader();
		auto fragmentShader = Shader::fragmentShader();
		
		int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// TODO: error check linking

		// Cleanup - the shaders can be deleted once they're compiled and linked
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	
		return shaderProgram;
	}
	
private:
	static int vertexShader()
	{
		// GLSL code
		// We simply use the position in the incoming vertex attributes,
		// as they're already in the normalised device co-ordinates
		const char* vertexShaderSource =
			"#version 460 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		// TODO: error checking

		return vertexShader;
	}

	static int fragmentShader()
	{
		const char* fragmentShaderSource =
			"#version 460 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		// TODO: error checking

		return fragmentShader;
	}
};
