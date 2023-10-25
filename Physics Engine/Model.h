#ifndef MODEL_H
#define MODEL_H



#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Mesh.h";
#include "Material.h"
#include "Transform.h"

class ModelLoad
{
public:
	ModelLoad();
	~ModelLoad(){}
	std::vector<MeshData> ListofMeshesInthisModel;
	Texture diffuseTexture;
	Texture specularTexture;
	Material material;
	bool isWireFrame;
	bool isVisible;
	std::string modelPath;
	const char* defaultDiffusePath = "Images/Default_Textures/Diffuse_Default.png";
	const char* defaultSpecularPath = "Images/Default_Textures/Specular_Default.png";
	void LoadModel(std::string modelFilePath);
	void  DrawMeshes(ShaderClass& shader);
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float rotationAngle;
	glm::vec3 scale;
	bool HasTexture=false;
	void SetPosition(glm::mat4& model, const  glm::vec3& position = glm::vec3(0));
	void SetScale(glm::mat4& model, const glm::vec3& scale = glm::vec3(1));
	void SetRotation(glm::mat4& model, const  glm::vec3& rotation = glm::vec3(0.f, 0.f, 1.f));
	void SetTransform(glm::mat4& model, const  glm::vec3& position = glm::vec3(0), const  glm::vec3& rotation = glm::vec3(0.f,0.f,1.f), float angle = 0, const glm::vec3& scale = glm::vec3(1));
	void DeleteVBO();
	MeshData ProcessMesh(aiMesh* mesh, const aiScene* scene);
	Transform transform;
	std::string modelName;

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	
private:
	void processNode(aiNode* node, const aiScene* scene);
	void ConvertinFileToData(aiMesh* mesh, const aiScene* scene);
	
};


#endif // !MODEL_H
