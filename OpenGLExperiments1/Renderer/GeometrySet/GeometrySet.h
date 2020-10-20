#pragma once
class GeometrySet
{
public:
	virtual void Draw(Shader* shader)
	{
		std::cout << "drawing from base geoset" << std::endl;
	};
	virtual void Hello() { std::cout << "hello from base" << std::endl; };
};