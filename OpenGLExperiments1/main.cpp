// Hides the console in Windows
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "shader.h"
#include "vao.h"
#include "window.h"
#include <vector>

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
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto object : objectsToRender)
	{
		// object.Shader.Use();
		glBindVertexArray(object.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// OpenGL uses double buffers - we display the "front" frame whilst creating
	// the back frame Once the back frame is complete (ie, now), we swap them
	// around
	glfwSwapBuffers(window->glfwWindow);
}
