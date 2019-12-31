// Hides the console in Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "shader.h"
#include "vao.h"
#include "window.h"

void render(Window* window);

int main()
{
	const auto window = new Window();

	glUseProgram(Shader::Program());
	glBindVertexArray(VAO::Triangle());
	
	// The render loop
	while (window->isRunning())
	{
		render(window);
	}

	return 0;
}

// The render loop
void render(Window* window)
{
	// OpenGL is a state machine - this is a state setting function - we define
	// the colour to use for all future clears
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	// And then we do the clearing - this will use whatever clear colour is
	// currently in state This function wants to know the buffer we want to clear
	// - we're clearing the colour buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// OpenGL uses double buffers - we display the "front" frame whilst creating
	// the back frame Once the back frame is complete (ie, now), we swap them
	// around
	glfwSwapBuffers(window->glfwWindow);
}


