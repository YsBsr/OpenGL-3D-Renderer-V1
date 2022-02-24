#pragma once
#include <glew.h>
#include <glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class VertexArrayObject {

private:
	unsigned int vertex_array_obj_id;
	VertexBuffer* vertex_buffer;
	IndexBuffer* index_buffer;
	Texture* texture;
	//float* getVertice;

public:
	VertexArrayObject();
	VertexArrayObject(VertexBuffer* vb, IndexBuffer* ib);
	VertexArrayObject(VertexBuffer* vb, IndexBuffer* ib, Texture* tex);
	~VertexArrayObject();

	void addBuffer();

	void drawTeture(unsigned int tex_slot_num);
	void changeTexture(Texture* tex);
	float* getVertex(int index);

	void Bind();
	void Unbind();
};