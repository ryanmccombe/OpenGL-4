#pragma once
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../Camera.h"
#include <iostream>
#include <cmath>

class FPSCamera : public Camera
{
public:
	FPSCamera()
	{
		std::cout << "Constructed spinning camera" << std::endl;
		// Update(std::pair<double, double>{0, 0});
	}

	const Window* window;

	void ProcessInput(const Window* _window)
	{
		window = _window;

		// Camera speed needs normalised to frame rate
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		const float cameraSpeed = 4.0f * deltaTime;

		if (glfwGetKey(window->glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window->glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window->glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window->glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void Update(std::vector<double> mousePos) {
		double xpos = mousePos[0];
		double ypos = mousePos[1];
		double scrollYOffset = mousePos[2];
		// std::cout << xpos << " | " << ypos << " | " << scrollYOffset << std::endl;
		
		float xoffset = (xpos - lastX);
		float yoffset = (lastY - ypos); // reversed since y-coordinates range from bottom to top
		lastX = xpos;
		lastY = ypos;

		const float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw   += xoffset;
		pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

		glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);



		zoom = (10.f * (1.0 - scrollYOffset)) + (90.f * scrollYOffset);

		// std::cout << scrollYOffset << " | " << zoom << std::endl;
		
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(glm::radians(zoom), 800.0f / 600.0f, 0.1f, 100.0f);
	}

	bool firstMouse = true;
	float lastX = 0.f;
	float lastY = 0.f;
	float lastFrame = 0.0f;
	float yaw = -90.f;
	float pitch = 0.f;
	float zoom = 45.f;
	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
};
