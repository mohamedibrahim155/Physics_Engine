#pragma once
#include "stb_image.h"
#include"Texture.h"
#include<glm/glm.hpp>



class Material
{
public:
	Material();
	~Material();

	const char* diffuseMapPath;
	const char* specularMapPath;
	Texture diffuseMap;
	Texture specularMap;
	float shininess;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	void ConfigureTexture();

private:

};

