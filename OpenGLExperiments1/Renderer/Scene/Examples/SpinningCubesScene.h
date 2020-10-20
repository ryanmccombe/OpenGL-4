#pragma once
#include "../../Camera/Camera.h"
#include "../../Shader/shader.h"
#include "../../Mesh/Mesh.h"
#include "../../GeometrySet/Examples/SpinningCubesGeometrySet.h"
#include "../Scene.h"

class SpinningCubesScene : public Scene
{
public:
	SpinningCubesScene()
	{
		Shader shader("../../Renderer/Shader/vertex.shader", "../../Renderer/Shader/fragment.shader");
	    shader.AddTexture("../../Renderer/Texture/container.jpg");
	    shader.AddTexture("../../Renderer/Texture/thinking.png", GL_RGBA, GL_TEXTURE1);
		shader.setMatrix("view", glm::value_ptr(camera.view));
		shader.setMatrix("projection", glm::value_ptr(camera.projection));

		SpinningCubesGeometrySet geo;

		std::cout << "GeoSet created" << std::endl;

		ShaderGroups.assign(1, ShaderGroup(&shader, &geo));
	}

	void Hello() {};

	void Render()
	{
		// std::cout << "rendering in spinning cubes scene" << std::endl;
		if(ShaderGroups.size() == 1)
		{
			ShaderGroups[0].Render();
		} else {
			std::cout << "Render Sets size is " << ShaderGroups.size() << std::endl;
		}
		
	}

	SpinningCamera camera;
};