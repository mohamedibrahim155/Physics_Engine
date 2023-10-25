#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Shader.h"
#include "Texture.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

struct Vertex
{
	glm::vec3 vPos;
	glm::vec3 vNormals;
	glm::vec2 vTextureCoordinates;
	glm::vec3 vRGB;
};

class MeshData
{
public:

	bool isWireFrame;
	MeshData(std::vector<Vertex> vertices, std::vector<unsigned int > indices, std::vector<Texture> textures)
	{
		this->Vertices = vertices;
		this->Indices = indices;
		this->textures = textures;
		SetupMesh();
	}

	/*MeshData()
	{

	}*/
	~MeshData()
	{
		/*delete VB;
		delete IBO;*/
	}
	std::vector<Vertex> Vertices;
	std::vector<unsigned int >Indices;
	std::vector<Texture> textures;
	unsigned int VAO;
	void DrawMesh(ShaderClass& shader) 
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			GLCALL(glActiveTexture(GL_TEXTURE0 + i)); // active proper texture unit before binding
			
			std ::string number;
			std::string name = textures[i].type;
			if (name =="DIFFUSE")
			{
				shader.SetInt("material.diffuse", 0);    // location of  light shader-> material.diffuse

			}
			if (name == "SPECULAR")
			{
				shader.SetInt("material.specular", 1);
			}
			
			//glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
			// and finally bind the texture
			GLCALL(glBindTexture(GL_TEXTURE_2D, textures[i].textureId));
		}

		// draw mesh
		VA->Bind();
		IBO->Bind();

		if (isWireFrame)
		{
			GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		else
		{
			GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
		
		GLCALL(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Indices.size()), GL_UNSIGNED_INT, 0));
		VA->Unbind();
		GLCALL(glActiveTexture(GL_TEXTURE0));
	
	}
	void SetupMesh();
	void DeleteVAOandVBO();
	unsigned int VBO, EBO;
	VertexBuffer* VB;
	IndexBufferObject* IBO;
	VertexArray* VA;
	VertexBufferLayout* layout;

private:

};








#endif // MESH_H

