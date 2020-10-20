// Hides the console in Windows
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Renderer/Shader/shader.h"
#include "Renderer/Scene/Examples/SpinningCubesScene.h"
#include "Window/window.h"
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Renderer/Camera/Examples/SpinningCamera.h"

void render(Window*, Scene*);

int main()
{
	const auto window = new Window();
	SpinningCubesScene Scene;

	glEnable(GL_DEPTH_TEST);

	while (window->isRunning())
	{
		render(window, &Scene);
	}
	system("pause");
	return 0;
}

void render(Window* window, Scene* scene)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// std::cout << "rendering in main" << std::endl;

	scene->Render();
	
	glfwSwapBuffers(window->glfwWindow);
}
