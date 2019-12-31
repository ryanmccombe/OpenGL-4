#pragma once
#include <glad/glad.h>

class VAO
{
public:
	static unsigned int Square()
	{
		// OpenGL uses normalised (x, y, z) device coordinates in the [-1, 1] range
		// (0, 0) is the centre of the screen
		// We have the same z co-ordinate / depth for each vertex, to simulate a 2D triangle
		float vertices[] = {
			0.5f, 0.5f, 0.0f, // top right
			0.5f, -0.5f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f, 0.5f, 0.0f // top left 
		};
		unsigned int indices[] = {
			0, 1, 3, // first Triangle
			1, 2, 3 // second Triangle
		};

		// A vertex array object stores references to vertex data and buffer
		// it remembers the values passed to so if we rebind this VAO in the future,
		// we don't have to re-invoke vertex buffer specific functions like glVertexAttribPointer
		unsigned int vertexArrayObject;
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		// Vertex buffer objects are how we send vertices to the GPU
		unsigned int vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

		// Create and initialises the buffer object's data store
		// GL_STATIC_DRAW allows the GPU to optimise this buffer on the basis it will rarely change
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// TODO: explain EBOs
		unsigned int elementBufferObject;
		glGenBuffers(1, &elementBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0, // The attribute being configured - this maps to location = 0 in the vertex shader
			3, // The number of elements in each vertex - we're using a vec3
			GL_FLOAT, // The type of each element
			GL_FALSE, // Whether we need them normalised when accessed - we don't
			3 * sizeof(float), // The space between verts
			static_cast<void*>(nullptr)
			// The offset of where the position data begins - our position data is at the start
		);

		// Enable the vertex attribute, using the index we set (maps to the 1st arg of glVertexAttribPointer)
		glEnableVertexAttribArray(0);

		// the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object
		// so we can unbind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// we can NOT unbind the EBO while a VAO is active as the bound EBO is stored in the VAO
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Unbinding the VAO so other VAO calls won't modify it
		glBindVertexArray(0);

		return vertexArrayObject;
	}
};
