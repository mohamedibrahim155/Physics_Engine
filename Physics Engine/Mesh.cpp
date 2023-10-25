#include "Mesh.h"


void MeshData::SetupMesh()
{
    // create buffers/arrays
   // glGenVertexArrays(1, &VAO);

    //glBindVertexArray(VAO);
    // load data into vertex buffers
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
   
     VA = new VertexArray();
    void* pVertices = static_cast<void*>(&Vertices[0]);
    unsigned int size = Vertices.size() * sizeof(Vertex);
     VB = new VertexBuffer(pVertices, size);
     layout = new VertexBufferLayout();
     layout->Push<float>(3);
     layout->Push<float>(3);
     layout->Push<float>(2);
     layout->Push<float>(3);

     VA->AddBuffer(*VB, *layout);

 // glGenBuffers(1, &VBO);
 // glBindBuffer(GL_ARRAY_BUFFER, VBO);
 // glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

   
     IBO = new IndexBufferObject(&Indices[0], Indices.size());

  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
 //   glEnableVertexAttribArray(0);
 //   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
 //   glEnableVertexAttribArray(1);
 //   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vNormals));
    // vertex texture coords
 //   glEnableVertexAttribArray(2);
 //   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vTextureCoordinates));
   
 //   glEnableVertexAttribArray(3);
 //   glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vRGB));
   
}


void  MeshData::DeleteVAOandVBO (/*ShaderClass& shader*/)
{
    
    // draw mesh
   // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
   // glDeleteBuffers(1, &EBO);
    VA->Unbind();
    VB->Unbind();
    IBO->Unbind();
  //  delete VB;
    
}


