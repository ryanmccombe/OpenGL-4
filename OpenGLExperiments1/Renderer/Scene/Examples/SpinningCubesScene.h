#pragma once
#include "../../Camera/Camera.h"
#include "../../Shader/shader.h"
#include "../../Mesh/Mesh.h"
#include "../../GeometrySet/Examples/SpinningCubesGeometrySet.h"
#include "../Scene.h"

class SpinningCubesScene : public Scene
{
public:
	SpinningCubesScene(Window& window) :
		Scene { window },
		window { window },
		shader { Shader { "../../Renderer/Shader/vertex.shader", "../../Renderer/Shader/fragment.shader" } },
		geo { SpinningCubesGeometrySet {} },
		shaderGroup { ShaderGroup { shader, geo } }
	{
		std::cout << "Constructed SpinningCubesScene" << std::endl;
		// TODO: create default example shader
	    shader.AddTexture("../../Renderer/Texture/container.jpg");
	    shader.AddTexture("../../Renderer/Texture/thinking.png", GL_RGBA, GL_TEXTURE1);
		UpdateShaderFromCamera();

		// TODO: better way of initialising this?
		std::cout << "Populating ShaderGroup" << std::endl;
		ShaderGroups.assign(1, &shaderGroup);
	}

	~SpinningCubesScene()
	{
		std::cout << "Destructed SpinningCubesScene" << std::endl;
	}

	void Render(std::vector<double>& mousePos) override
	{
		Scene::Render(mousePos);
		Camera.ProcessInput(window);
		UpdateShaderFromCamera();
	}

	void UpdateShaderFromCamera()
	{
		shader.setMatrix("view", glm::value_ptr(Camera.view));
		shader.setMatrix("projection", glm::value_ptr(Camera.projection));
	}

	Window& window;
	Shader shader;
	SpinningCubesGeometrySet geo;
	ShaderGroup shaderGroup;
};
