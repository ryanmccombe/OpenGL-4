#pragma once
#include "../Camera/Camera.h"
#include "../Shader/shader.h"
#include "../Mesh/Mesh.h"

class ShaderGroup
{
public:
	Shader Shader;
	// GeometrySet Geo;
	void Render()
	{
		Shader.Use();
		// GeometrySet.Draw();
	}
};

class Scene
{
public:
	void Render()
	{
		
	}

	std::vector<ShaderGroup> RenderSets;
	Camera Camera;
};
