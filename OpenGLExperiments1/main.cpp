// Hides the console in Windows
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "shader.h"
#include "Renderer/Scene/Examples/SpinningCubes.h"
#include "window.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void render(Window* window, Shader* shader);

int main()
{
	const auto window = new Window();

	glEnable(GL_DEPTH_TEST);

	Shader shader("../../vertex.shader", "../../fragment.shader");
	shader.AddTexture("../../container.jpg");
	shader.AddTexture("../../thinking.png", GL_RGBA, GL_TEXTURE1);

	// The render loop
	while (window->isRunning())
	{
		render(window, &shader);
	}

	return 0;
}

// The render loop
void render(Window* window, Shader* shader)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
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
		
	shader->setMatrix("model", glm::value_ptr(model));
	shader->setMatrix("view", glm::value_ptr(view));
	shader->setMatrix("projection", glm::value_ptr(projection));

	shader->Use();
	SpinningCubes::Draw(shader, window);
	
	glfwSwapBuffers(window->glfwWindow);
}
