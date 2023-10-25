#pragma once

#include <Windows.h>
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!(x)) DebugBreak();
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

 void GLClearError();
 bool GLLogCall(const char* function, const char* file, int line);