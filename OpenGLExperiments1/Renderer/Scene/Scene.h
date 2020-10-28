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
		std::cout << "Destructed ShaderGroup" << std::endl;
	}
	void Render(std::vector<double> mousePos)
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
	Scene(Window& window) : Camera { FPSCamera { window }} {}
	~Scene()
	{
		std::cout << "Destructed Scene" << std::endl;
	}
	virtual void Render(std::vector<double>& mousePos)
	{
		if(!ShaderGroups.empty())
		{
			// TODO: render all groups
			ShaderGroups[0]->Render(mousePos);
		} else {
			// TODO: implement logging system
			std::cout << "Render Sets size is " << ShaderGroups.size() << std::endl;
		}
		Camera.Update(mousePos);
	}

	std::vector<ShaderGroup*> ShaderGroups;

	// TODO: use standard camera by default
	FPSCamera Camera;
};
