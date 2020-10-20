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
#include "Renderer/Camera/Examples/SpinningCamera.h"

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

	SpinningCamera Camera;
		
	shader->setMatrix("view", glm::value_ptr(Camera.view));
	shader->setMatrix("projection", glm::value_ptr(Camera.projection));

	shader->Use();
	SpinningCubes::Draw(shader, window);
	
	glfwSwapBuffers(window->glfwWindow);
}
