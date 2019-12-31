// Hides the console in Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initialiseWindow();
void initialiseGLAD();
int initialiseShader();
unsigned int initialiseVAO();
void render(GLFWwindow* window);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	const auto window = initialiseWindow();
	initialiseGLAD();

	glUseProgram(initialiseShader());
	glBindVertexArray(initialiseVAO());
	
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

int initialiseShader()
{
	// GLSL code
	// We simply use the position in the incoming vertex attributes,
	// as they're already in the normalised device co-ordinates
	const char* vertexShaderSource =
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource =
		"#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	// Compile the vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	// TODO: error check shader compilation

	// Compile the fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	// TODO: error check shader compilation

	// Link the shaders into a new program
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// TODO: error check linking

	// Cleanup - the shaders can be deleted once they're compiled and linked
	glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	
	return shaderProgram;
}

unsigned int initialiseVAO()
{
	// OpenGL uses normalised (x, y, z) device coordinates in the [-1, 1] range
	// (0, 0) is the centre of the screen
	// We have the same z co-ordinate / depth for each vertex, to simulate a 2D triangle
	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

	// A vertex array object stores references to vertex data and buffer
	// it remembers the values passed to so if we rebind this VAO in the future,
	// we don't have to re-invoke vertex buffer specific functions like glVertexAttribPointer
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	// Vertex buffer objects are how we send vertices to the GPU
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Create and initialises the buffer object's data store
	// GL_STATIC_DRAW allows the GPU to optimise this buffer on the basis it will rarely change
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// TODO: explain EBOs
	unsigned int elementBufferObject;
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(
		0, // The attribute being configured - this maps to location = 0 in the vertex shader
		3, // The number of elements in each vertex - we're using a vec3
		GL_FLOAT, // The type of each element
		GL_FALSE, // Whether we need them normalised when accessed - we don't
		3*sizeof(float), // The space between verts
		(void*)0 // The offset of where the position data begins - our position data is at the start
	);

	// Enable the vertex attribute, using the index we set (maps to the 1st arg of glVertexAttribPointer)
	glEnableVertexAttribArray(0);

	// the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object
	// so we can unbind our VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// we can NOT unbind the EBO while a VAO is active as the bound EBO is stored in the VAO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbinding the VAO so other VAO calls won't modify it
	glBindVertexArray(0);

	return vertexArrayObject;
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
