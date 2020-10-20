#pragma once
#include <glm/mat4x4.hpp>

class Camera
{
public:
	glm::mat4 view;
	glm::mat4 projection;
};
