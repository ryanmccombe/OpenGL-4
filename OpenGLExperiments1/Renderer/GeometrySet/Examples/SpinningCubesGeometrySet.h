#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Shader/shader.h"
#include "../../../Window/window.h"
#include "../../Mesh/Examples/Cube.h"
#include "../GeometrySet.h"

class SpinningCubesGeometrySet : public GeometrySet
{
public:
	SpinningCubesGeometrySet()
	{
		std::cout << "Constructing SpinningCubesGeometrySet" << std::endl;
	}
	~SpinningCubesGeometrySet()
	{
		std::cout << "Destructing SpinningCubesGeometrySet" << std::endl;
	}
	void Draw(Shader& shader) override
	{
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

		ExampleCube.Bind();

		glm::mat4 identityTransform = glm::mat4(1.0f);
		glm::mat4 spinnyTransform = glm::rotate(identityTransform, float(glfwGetTime()), glm::vec3(0.0, 0.0, 1.0));

		// TODO: instance this instead of 10 draw calls
		for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMatrix("model", glm::value_ptr(model));
			shader.setMatrix("transformation", value_ptr(spinnyTransform));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
	}
	Cube ExampleCube;
};
