#pragma once
#include "../Shader/shader.h"
#include "../GeometrySet/GeometrySet.h"
#include "../Camera/Examples/FPSCamera.h"

// TODO: move ShaderGroup to own file
class ShaderGroup
{
public:
	// TODO: remove unnecessary constructor
	ShaderGroup(Shader& shader, GeometrySet& geo) : shader { shader }, geo { geo} { }
	~ShaderGroup()
	{
		LOG_INFO("Destructed ShaderGroup");
	}
	void Render()
	{
		shader.Use();
		geo.Draw(shader);
	}

    Shader& shader;
	GeometrySet& geo;
};

class Scene
{
public:
	Scene(Window& window) : Camera { FPSCamera { window }}
	{
		LOG_INFO("Constructed Scene");
	}
	~Scene()
	{
		LOG_INFO("Destructed Scene");
	}
	virtual void Render(std::vector<double>& mousePos)
	{
		if(!ShaderGroups.empty())
		{
			// TODO: render all groups
			ShaderGroups[0]->Render();
		} else {
			// TODO: implement logging system
			LOG_WARN("Render Sets size is {0}", ShaderGroups.size());
		}
		Camera.Update(mousePos);
	}

	std::vector<ShaderGroup*> ShaderGroups;

	// TODO: use standard camera by default
	FPSCamera Camera;
};
