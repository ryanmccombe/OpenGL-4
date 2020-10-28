#pragma once
class GeometrySet
{
public:
	GeometrySet()
	{
		std::cout << "Constructing GeometrySet" << std::endl;
	}
	~GeometrySet()
	{
		std::cout << "Destructing GeometrySet" << std::endl;
	}
	virtual void Draw(Shader* shader) {};
};