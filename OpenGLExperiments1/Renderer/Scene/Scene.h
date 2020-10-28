#pragma once
#include "../Shader/shader.h"
#include "../GeometrySet/GeometrySet.h"
#include "../Camera/Examples/SpinningCamera.h"
#include "../Camera/Examples/FPSCamera.h"

// TODO: move ShaderGroup to own file
class ShaderGroup
{
public:
	// TODO: remove unnecessary constructor
	ShaderGroup(Shader* shader, GeometrySet* geo) : shader { shader }, geo { geo} { }
	void Render(std::vector<double> mousePos)
	{
		shader->Use();
		geo->Draw(shader);
	}

    Shader* shader = nullptr;
	GeometrySet* geo = nullptr;
};

class Scene
{
public:
	Scene(Window& window) : Camera { FPSCamera { window }} {}
	virtual void Render(std::vector<double>& mousePos)
	{
		if(!ShaderGroups.empty())
		{
			// TODO: render all groups
			ShaderGroups[0].Render(mousePos);
		} else {
			// TODO: implement logging system
			std::cout << "Render Sets size is " << ShaderGroups.size() << std::endl;
		}
		Camera.Update(mousePos);
	}

	std::vector<ShaderGroup> ShaderGroups;

	// TODO: use standard camera by default
	FPSCamera Camera;
};
