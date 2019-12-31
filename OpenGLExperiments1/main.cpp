// Hides the console in Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "vao.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initialiseWindow();
void initialiseGLAD();
void render(GLFWwindow* window);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	const auto window = initialiseWindow();
	initialiseGLAD();

	glUseProgram(Shader::Program());
	glBindVertexArray(VAO::Square());
	
	// The render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		render(window);
	}

	// Cleanup
	glfwTerminate();
	return 0;
}

// Create a GLFW window
GLFWwindow* initialiseWindow()
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

	return window;
}

// GLAD manages function pointers for OpenGL - this is OS-specific
void initialiseGLAD()
{
	// glfwGetProcAddress defines the correct function based on the OS we're
	// compiling for
	const auto loadProc = GLADloadproc(glfwGetProcAddress);
	if (!gladLoadGLLoader(loadProc))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

// The render loop
void render(GLFWwindow* window)
{
	// OpenGL is a state machine - this is a state setting function - we define
	// the colour to use for all future clears
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	// And then we do the clearing - this will use whatever clear colour is
	// currently in state This function wants to know the buffer we want to clear
	// - we're clearing the colour buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// OpenGL uses double buffers - we display the "front" frame whilst creating
	// the back frame Once the back frame is complete (ie, now), we swap them
	// around
	glfwSwapBuffers(window);

	// Check for any events (eg, resize, keyboard input) and invoke appropriate
	// callbacks
	glfwPollEvents();
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// This gets called when the window is first created, and every time it is
// subsequently resized
void framebufferSizeCallback(GLFWwindow* window, const int width,
                             const int height)
{
	// First 2 arguments - (0, 0) - defines where the bottom left corner of the
	// rendering view is, within the parent window Second 2 arguments are the
	// width and height, ie, the top right will be (0 + width, 0 + height)
	glViewport(0, 0, width, height);
}
