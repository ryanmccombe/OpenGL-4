#pragma once
#include "../../Log.h"

class GeometrySet
{
public:
	GeometrySet()
	{
		LOG_INFO("Constructing GeometrySet");
	}
	~GeometrySet()
	{
		LOG_INFO("Destructing GeometrySet");
	}
	virtual void Draw(Shader& shader) {};
};
