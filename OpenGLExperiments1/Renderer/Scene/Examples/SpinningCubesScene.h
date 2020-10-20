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
		// TODO: create default example shader
	    shader.AddTexture("../../Renderer/Texture/container.jpg");
	    shader.AddTexture("../../Renderer/Texture/thinking.png", GL_RGBA, GL_TEXTURE1);
		UpdateShaderFromCamera();

		// TODO: better way of initialising this?
		ShaderGroups.assign(1, ShaderGroup(&shader, &geo));
	}

	void Render() override
	{
		Scene::Render();
		UpdateShaderFromCamera();
	}

	void UpdateShaderFromCamera()
	{
		shader.setMatrix("view", glm::value_ptr(Camera.view));
		shader.setMatrix("projection", glm::value_ptr(Camera.projection));
	}

	// TODO: better way of initialising this?
	Shader shader = Shader("../../Renderer/Shader/vertex.shader", "../../Renderer/Shader/fragment.shader");
	SpinningCubesGeometrySet geo;
};
