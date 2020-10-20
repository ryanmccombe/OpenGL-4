#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "window.h"
#include "Renderer/Mesh/Cube.h"

class VAO
{
public:
	static unsigned int DrawTestCubes(Shader* shader, Window* window)
	{
		Cube testCube;

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(2.0f, 5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f, 3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f, 2.0f, -2.5f),
			glm::vec3(1.5f, 0.2f, -1.5f),
			glm::vec3(-1.3f, 1.0f, -1.5f)
		};

		unsigned int vertexArrayObject;
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		unsigned int vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

		glBufferData(GL_ARRAY_BUFFER, sizeof(testCube.vertices), testCube.vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glm::mat4 identityTransform = glm::mat4(1.0f);
		glm::mat4 spinnyTransform = glm::rotate(identityTransform, float(glfwGetTime()), glm::vec3(0.0, 0.0, 1.0));

		for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->setMatrix("model", glm::value_ptr(model));
			shader->setMatrix("transformation", value_ptr(
				glfwGetKey(window->glfwWindow, GLFW_KEY_SPACE) == GLFW_RELEASE
				? spinnyTransform
				: identityTransform));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
		
		return vertexArrayObject;
	}
};
