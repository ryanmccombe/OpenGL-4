#pragma once
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera()
	{
		
	}
	glm::mat4 view;
	glm::mat4 projection;
};
