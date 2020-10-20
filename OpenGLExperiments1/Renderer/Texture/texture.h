#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture
{
public:
	unsigned int ID;
	Texture(char const* path, GLenum dataType = GL_RGB, GLenum textureUnit = GL_TEXTURE0, GLenum wrapping = GL_REPEAT)
	{
		// OpenGL expects 0.0 to be at the bottom of the y-axis; image formats usually have that at the top
		stbi_set_flip_vertically_on_load(true);

		// Textures are referenced by ID like most things in OpenGL
		glGenTextures(1, &ID);

		// We can bind multiple textures at once - we just need to assign them to different texture units
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, ID);
		
		// Wrapping Options in both directions
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

		// Filtering options can be set seperately for when magnifying or minifying
		// We generate mipmaps (later) for use when minifying
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// Load and generate texture - these are all variables written to by the stbi loader
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			std::cout << "Loaded texture" << std::endl;

			// Load the image data into the texture, and generate mipmaps
			glTexImage2D(GL_TEXTURE_2D, 0, dataType, width, height, 0, dataType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		// Free the image memory
		stbi_image_free(data);
	}
};
