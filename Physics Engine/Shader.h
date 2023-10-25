#pragma once
#ifndef SHADER_HEADER
#define SHADER_HEADER
#include "OpenGL_Common.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 

class ShaderClass
{
public:
    ShaderClass(const char* vertexShaderPath, const char* fragmentShaderPath);

    unsigned int ID;

    // Utility uniform functions
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, glm::vec2 value);
    void SetVec3(const std::string& name, glm::vec3 value);
    void SetVec4(const std::string& name, glm::vec4 value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    void UseProgram();
    void Unbind();

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};




#endif // !SHADER_HEADER
