#include "Material.h"

void Material::ConfigureTexture()
{
	/*Texture diffuse(diffuseMapPath);
	diffuseMap = diffuse;

	Texture specular(specularMapPath);
	diffuseMap = specular;*/
}

Material::~Material()
{
	//diffuseMap = nullptr;
	//specularMap = nullptr;
	//delete diffuseMap;
	//delete specularMap;
}

Material::Material()
{

	this->shininess =10.f;
	this-> ambient = glm::vec3(0.5f);
	this-> diffuse = glm::vec3(1.0f);
	this-> specular= glm::vec3(1.0f);
}