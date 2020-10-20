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
		SpinningCamera camera;
		Shader shader("../../Renderer/Shader/vertex.shader", "../../Renderer/Shader/fragment.shader");
	    shader.AddTexture("../../Renderer/Texture/container.jpg");
	    shader.AddTexture("../../Renderer/Texture/thinking.png", GL_RGBA, GL_TEXTURE1);
		shader.setMatrix("view", glm::value_ptr(camera.view));
		shader.setMatrix("projection", glm::value_ptr(camera.projection));

		SpinningCubesGeometrySet geo;

		shader.Use();
		geo.Draw(&shader);
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
