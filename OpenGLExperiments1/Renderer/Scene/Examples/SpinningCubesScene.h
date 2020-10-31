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
		LOG_INFO("Constructed SpinningCubesScene");
		// TODO: create default example shader
	    shader.AddTexture("../../Renderer/Texture/container.jpg");
	    shader.AddTexture("../../Renderer/Texture/thinking.png", GL_RGBA, GL_TEXTURE1);
		UpdateShaderFromCamera();

		// TODO: better way of initialising this?
		LOG_INFO("Populating ShaderGroup");
		ShaderGroups.assign(1, &shaderGroup);
	}

	~SpinningCubesScene()
	{
		LOG_INFO("Destructed SpinningCubesScene");
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
