#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
public:
	GLFWwindow* glfwWindow;
	
	Window()
	{
		glfwInit();

		// Which version of OpenGL are we using?
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		// Which profile?  CORE has a smaller subset of open GL features, without
		// legacy support
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Starting dimensions of the window
		const auto window =
			glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Experiments", nullptr, nullptr);

		// Window can be resized by user, so we register a callback for when that
		// happens
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		// Make this window the main context on the current thread
		glfwMakeContextCurrent(window);

		glfwWindow = window;

		initialiseGLAD();
	}

	bool isRunning()
	{
		// Check for any events (eg, resize, keyboard input) and invoke appropriate
		// callbacks
		glfwPollEvents();
		
		processInput();

		if (glfwWindowShouldClose(glfwWindow))
		{
			glfwTerminate();
			return false;
		}
		
		return true;
	}

private:
	void processInput()
	{
		if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(glfwWindow, true);
	}

	// This gets called when the window is first created, and every time it is
	// subsequently resized
	static void framebufferSizeCallback(GLFWwindow* window, const int width,
	                                    const int height)
	{
		// First 2 arguments - (0, 0) - defines where the bottom left corner of the
		// rendering view is, within the parent window Second 2 arguments are the
		// width and height, ie, the top right will be (0 + width, 0 + height)
		glViewport(0, 0, width, height);
	}

	// GLAD manages function pointers for OpenGL - this is OS-specific
	static void initialiseGLAD()
	{
		// glfwGetProcAddress defines the correct function based on the OS we're
		// compiling for
		const auto loadProc = GLADloadproc(glfwGetProcAddress);
		if (!gladLoadGLLoader(loadProc))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
}
};
