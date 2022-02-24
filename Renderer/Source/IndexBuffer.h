#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glew.h>
#include <glfw3.h>

class IndexBuffer {

public:
	unsigned int edge_num;

private:
	static unsigned int indices_for_rect[6];
	static unsigned int indices_for_triangle[3];

	unsigned int index_buffer_id;

public:
	IndexBuffer();
	IndexBuffer(int faces);
	~IndexBuffer();

	void setDataBuferRect();
	void setDataBufferTriangle();

	void Bind();
	void Unbind();
};