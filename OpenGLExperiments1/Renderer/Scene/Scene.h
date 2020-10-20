#pragma once
#include "../Shader/shader.h"
#include "../Mesh/Mesh.h"
#include "../GeometrySet/GeometrySet.h"
#include "../Camera/Examples/SpinningCamera.h"

class ShaderGroup
{
public:
	ShaderGroup(Shader* _shader, GeometrySet* _geo)
	{
		std::cout << "constructing shadergroup" << std::endl;
		shader = _shader;
		geo = _geo;
	}
	void Render()
	{
		// std::cout << "rendering in shadergroup" << std::endl;
		if (shader == nullptr)
		{
			std::cout << "shader is null" << std::endl;
		} else
		{
			shader->Use();
		}
		
		if (geo == nullptr || shader == nullptr)
		{
			std::cout << "geo is null" << std::endl;
		} else
		{
			geo->Draw(shader);
			geo->Hello();
		}
	}

    Shader* shader = nullptr;
	GeometrySet* geo = nullptr;
};

class Scene
{
public:
	virtual void Render()
	{
		
	}

	std::vector<ShaderGroup> ShaderGroups;
	SpinningCamera Camera;
};
