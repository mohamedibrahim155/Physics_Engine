
#pragma once
#include"Renderer.h"
class VertexBuffer
{
public:
	//VertexBuffer() { }
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind();
	void Unbind();

private:
	unsigned int m_RendererID;

};

