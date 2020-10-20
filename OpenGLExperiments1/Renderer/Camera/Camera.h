#pragma once
#include <glm/mat4x4.hpp>

class Camera
{
public:
	virtual void Update() {};
	glm::mat4 view;
	glm::mat4 projection;
};
