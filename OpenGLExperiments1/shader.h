#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			CompileVertexShader(vShaderStream.str().c_str());
			CompileFragmentShader(fShaderStream.str().c_str());
			BuildShaderProgram();
			Use();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
	}

	void Use() const
	{
		// std::cout << "Using " << ID << std::endl;
		glUseProgram(ID);
	}

	void setVec4(const std::string &name, float x, float y, float z, float w) const
	{ 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }

	void setFloat(const std::string &name, float x) const
	{ 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), x); 
    }

private:
	unsigned int vertexShader;
	unsigned int fragmentShader;

	void CompileVertexShader(const char* code)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &code, nullptr);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");
	}

	void CompileFragmentShader(const char* code)
	{
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &code, nullptr);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");
	}

	void BuildShaderProgram()
	{
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
					"\n -- --------------------------------------------------- -- " << std::endl;
			}
			else
			{
				std::cout << "Successfully compiled " << type << " shader" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
					"\n -- --------------------------------------------------- -- " << std::endl;
			}
			else
			{
				std::cout << "Successfully linked program" << std::endl;
			}
		}
	}
};
