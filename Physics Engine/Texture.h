#pragma once

#include "OpenGL_Common.h"

#include "stb_image.h"
#include <iostream>
class Texture
{
public:
	Texture();
	Texture(const char* filePath);
	~Texture() {}
	unsigned int textureId;
	const char* path;	
	const char* type;
	void LoadTexture(const char* filePath, const char* _type);
private:
	unsigned int loadTexture(char const* path);
};
