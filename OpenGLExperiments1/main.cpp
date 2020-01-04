// Hides the console in Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "shader.h"
#include "vao.h"
#include "window.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct RenderObject
{
	Shader Shader;
	unsigned int VAO;
};

template <std::size_t array_size>
void render(Window* window, RenderObject (&objectsToRender)[array_size]);

int main()
{
	const auto window = new Window();

	const Shader shader("../../vertex.shader", "../../fragment.shader");
	shader.AddTexture("../../container.jpg");
	shader.AddTexture("../../thinking.png", GL_RGBA, GL_TEXTURE1);

	RenderObject objects[]
	{
		{
			shader,
			VAO::Square()
		}
	};

	glEnable(GL_DEPTH_TEST);

	// The render loop
	while (window->isRunning())
	{
		render(window, objects);
	}

	return 0;
}

// The render loop
template <std::size_t array_size>
void render(Window* window, RenderObject (&objectsToRender)[array_size])
{
	// OpenGL is a state machine - this is a state setting function - we define
	// the colour to use for all future clears
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	// And then we do the clearing - this will use whatever clear colour is
	// currently in state This function wants to know the buffer we want to clear
	// - we're clearing the colour buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto object : objectsToRender)
	{
		// TODO: this is experimental matrix transformation code
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		// camera
		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		
		object.Shader.setMatrix("model", glm::value_ptr(model));
		object.Shader.setMatrix("view", glm::value_ptr(view));
		object.Shader.setMatrix("projection", glm::value_ptr(projection));
		// TODO: end of test code

		object.Shader.Use();
		// glBindVertexArray(object.VAO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		VAO::DrawTestCubes(&object.Shader, window);
	}

	// OpenGL uses double buffers - we display the "front" frame whilst creating
	// the back frame Once the back frame is complete (ie, now), we swap them
	// around
	glfwSwapBuffers(window->glfwWindow);
}
