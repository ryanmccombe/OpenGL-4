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
	ShaderGroup(Shader* _shader, GeometrySet* _geo)
	{
		shader = _shader;
		geo = _geo;
	}
	void Render()
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
	virtual void Render(double mousePos[3])
	{
		if(!ShaderGroups.empty())
		{
			// TODO: render all groups
			ShaderGroups[0].Render();
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
