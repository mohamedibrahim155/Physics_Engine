

#include "Model.h"

#include"Renderer.h"








void ModelLoad:: processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ListofMeshesInthisModel.push_back(ProcessMesh(mesh, scene));
       // ConvertinFileToData(mesh, scene);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

//void ModelLoad::ConvertinFileToData(aiMesh* mesh, const aiScene* scene)
//{
//    std::vector<Vertex> meshVertexData;
//    std::vector<unsigned int> meshIndicesData;
//    std::vector<Texture> meshTextureData;
//
//    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//    {
//        Vertex vertex;
//        glm::vec3 vector;
//        // positions
//        vector.x = mesh->mVertices[i].x;
//        vector.y = mesh->mVertices[i].y;
//        vector.z = mesh->mVertices[i].z;
//        vertex.vPos = vector;
//        // normals
//        if (mesh->HasNormals())
//        {
//            vector.x = mesh->mNormals[i].x;
//            vector.y = mesh->mNormals[i].y;
//            vector.z = mesh->mNormals[i].z;
//            vertex.vNormals = vector;
//        }
//        // texture coordinates
//        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
//        {
//            glm::vec2 vec;
//            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
//            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
//            vec.x = mesh->mTextureCoords[0][i].x;
//            vec.y = mesh->mTextureCoords[0][i].y;
//            vertex.vTextureCoordinates = vec;
//            // tangent
//          //  vector.x = mesh->mTangents[i].x;
//            //vector.y = mesh->mTangents[i].y;
//            //vector.z = mesh->mTangents[i].z;
//            //vertex.Tangent = vector;
//            //// bitangent
//            //vector.x = mesh->mBitangents[i].x;
//            //vector.y = mesh->mBitangents[i].y;
//            //vector.z = mesh->mBitangents[i].z;
//            //vertex.Bitangent = vector;
//        }
//        else
//        {
//            vertex.vTextureCoordinates = glm::vec2(0, 0);
//            vertex.vRGB = glm::vec3(1.0f, 1.0f, 1.0f); // declaring white color
//        }
//        
//        meshVertexData.push_back(vertex);
//    }
//    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
//    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//        // retrieve all indices of the face and store them in the indices vector
//        for (unsigned int j = 0; j < face.mNumIndices; j++)
//        {
//
//            meshIndicesData.push_back(face.mIndices[j]);
//        }
//    }
//
//    //setting material
//    //if (diffuseTexture.path==nullptr)
//    //{
//    //    diffuseTexture.LoadTexture(defaultDiffusePath,"DIFFUSE");
//    //}
//    //if (specularTexture.path == nullptr)
//    //{
//    //    specularTexture.LoadTexture(defaultSpecularPath,"SPECULAR");
//    //}
//    material.diffuseMap = diffuseTexture;
//    material.diffuseMap = diffuseTexture;
//    material.specularMap = specularTexture;
//    material.specularMapPath = specularTexture.path;
//
//
//    meshTextureData.push_back(diffuseTexture);
//    meshTextureData.push_back(specularTexture);
//    MeshData currentMesh;
//    currentMesh.Vertices = meshVertexData;
//    currentMesh.Indices = meshIndicesData;
//    currentMesh.textures = meshTextureData;
//    currentMesh.SetupMesh();
//    ListofMeshesInthisModel.push_back(currentMesh);
//
//
// 
//}



MeshData   ModelLoad::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> meshVertexData;
    std::vector<unsigned int> meshIndicesData;
    std::vector<Texture> meshTextureData;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.vPos = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.vNormals = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.vTextureCoordinates = vec;
            // tangent
          //  vector.x = mesh->mTangents[i].x;
            //vector.y = mesh->mTangents[i].y;
            //vector.z = mesh->mTangents[i].z;
            //vertex.Tangent = vector;
            //// bitangent
            //vector.x = mesh->mBitangents[i].x;
            //vector.y = mesh->mBitangents[i].y;
            //vector.z = mesh->mBitangents[i].z;
            //vertex.Bitangent = vector;
        }
        else
        {
            vertex.vTextureCoordinates = glm::vec2(0, 0);
            vertex.vRGB = glm::vec3(1.0f, 1.0f, 1.0f); // declaring white color
        }

        meshVertexData.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {

            meshIndicesData.push_back(face.mIndices[j]);
        }
    }





    material.diffuseMap = diffuseTexture;
    material.diffuseMapPath = diffuseTexture.path;
    material.specularMap = specularTexture;
    material.specularMapPath = specularTexture.path;


    meshTextureData.push_back(material.diffuseMap);
    meshTextureData.push_back(material.specularMap);



    return MeshData(meshVertexData, meshIndicesData, meshTextureData);
}

std::vector<Texture> ModelLoad::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::cout << " Texture file path : " << str.C_Str() << std::endl;
        //if (this->isTextureFlipped)
        //{
        //    stbi_set_flip_vertically_on_load(true);

        //}
        //else
        //{
        //    stbi_set_flip_vertically_on_load(false);

        //}

        //bool skip = false;
        //for (unsigned int j = 0; j < textures_loaded.size(); j++)
        //{
        //    if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
        //    {
        //        textures.push_back(textures_loaded[j]);
        //        skip = true;
        //        break;
        //    }
        //}
        //if (!skip)
        //{
        //    Texture texture;
        //    texture.id = TextureFromFile(str.C_Str(), this->directory);
        //    texture.type = typeName;
        //    std::cout << "Texture Loaded: " << texture.type << std::endl;
        //    texture.path = str.C_Str();
        //    textures.push_back(texture);
        //    textures_loaded.push_back(texture);
        //}
    }

    return textures;
}

void ModelLoad:: LoadModel(std::string modelFilePath)
{
    modelPath = modelFilePath;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std:: endl;
        return;
    }
    // retrieve the directory path of the filepath
    std:: string directory = modelFilePath.substr(0, modelFilePath.find_last_of('/'));
    processNode(scene->mRootNode, scene);
    std::cout << " Loaded  Model file  : " << modelFilePath << " Mesh count : " << scene->mNumMeshes << std::endl;
    std::cout << "List of meshes the model " + modelFilePath << " is : " << ListofMeshesInthisModel.size() << std::endl;
}


    void ModelLoad::DrawMeshes(ShaderClass &shader)
    {
        
        glm::mat4 matModel = transform.getModelMatrix();
        shader.SetMat4("model", matModel);
      
        if (isVisible)
        {


            for (int i = 0; i < ListofMeshesInthisModel.size(); i++)
            {
                ListofMeshesInthisModel[i].isWireFrame = this->isWireFrame;
                ListofMeshesInthisModel[i].DrawMesh(shader);

            }
        }

    }

void ModelLoad::DeleteVBO()
{
    for (int i = 0; i < ListofMeshesInthisModel.size(); i++)
    {
        MeshData temp = ListofMeshesInthisModel[i];
        temp.DeleteVAOandVBO();
        
    }
}


void ModelLoad::SetPosition(glm::mat4& model, const  glm::vec3& position)
{

    model = glm::translate(model, position); // translate it down so it's at the center of the scene

}

void ModelLoad::SetScale(glm::mat4& model, const  glm::vec3& scale)
{

    model = glm::scale(model, scale); // translate it down so it's at the center of the scene
}

void ModelLoad::SetRotation(glm::mat4& model, const  glm::vec3& rotation)
{   
    // translate it down so it's at the center of the scene

    glm::mat4  modelX = glm::rotate(glm::mat4(1.0f), this->rotationAxis.x, glm::vec3(1.0f, 0.0, 0.0f));

    glm::mat4  modelY = glm::rotate(glm::mat4(1.0f), this->rotationAxis.y, glm::vec3(0.0f, 1.0, 0.0f));

    glm::mat4  modelZ = glm::rotate(glm::mat4(1.0f), this->rotationAxis.z, glm::vec3(0.0f, 0.0, 1.0f));

   model = model * modelX;
   model = model * modelY;
   model = model * modelZ;

}

void ModelLoad::SetTransform(glm::mat4& model, const  glm::vec3& position, const  glm::vec3& rotation,  float angle, const glm::vec3& scale)
{
    SetPosition(model ,position);
    SetRotation(model, rotation);
    SetScale(model, scale);

}

ModelLoad::ModelLoad()
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scale = glm::vec3(1.0f);
    this->rotationAngle = 0;
    this->isWireFrame = false;
    this->isVisible = true;
   // transform = new Transform();
    //transformmodelMatrix = glm::mat4(1.0f);
}




