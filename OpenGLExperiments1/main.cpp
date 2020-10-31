// Hides the console in Windows
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Renderer/Scene/Examples/SpinningCubesScene.h"
#include "Window/window.h"

// TODO: move to texture.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Log.h"

// xpos, ypos, YScrollOffset
std::vector<double> mousePos = {0,0,0.5f};

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	LOG_TRACE("mouse callback");
	mousePos[0] = xpos;
	mousePos[1] = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float zoomSensitivity = .04f;
    mousePos[2] += yoffset * zoomSensitivity;
	if (mousePos[2] > 1.f) mousePos[2] = 1.f;
	if (mousePos[2] < 0.f) mousePos[2] = 0.f;
}

void render(Window& window, Scene& scene)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.Render(mousePos);
	
	glfwSwapBuffers(window.glfwWindow);
}

int main()
{
	Log::Init();
	LOG_INFO("Logger Initialised");
	Window window {};
	SpinningCubesScene Scene { window };

	glfwFocusWindow(window.glfwWindow);
	glfwSetWindowPos(window.glfwWindow, 800, 300);
	
	glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window.glfwWindow, mouse_callback);
	glfwSetScrollCallback(window.glfwWindow, scroll_callback); 
	glfwSetCursorPos(window.glfwWindow, 0,0);
	
	glEnable(GL_DEPTH_TEST);
	while (window.isRunning())
	{
		render(window, Scene);
	}
	
	return 0;
}
