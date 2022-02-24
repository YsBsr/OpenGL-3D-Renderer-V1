#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
}

VertexArrayObject::VertexArrayObject(VertexBuffer* vb, IndexBuffer* ib) : vertex_buffer(vb), index_buffer(ib)
{
	glGenVertexArrays(1, &vertex_array_obj_id);
	glBindVertexArray(vertex_array_obj_id);
    glBindVertexArray(0);
}

VertexArrayObject::VertexArrayObject(VertexBuffer* vb, IndexBuffer* ib, Texture* tex) : vertex_buffer(vb), index_buffer(ib), texture(tex)
{
	glGenVertexArrays(1, &vertex_array_obj_id);
	glBindVertexArray(vertex_array_obj_id);
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	Unbind();
	delete vertex_buffer;
	delete index_buffer;
	glDeleteVertexArrays(1, &vertex_array_obj_id);
}

void VertexArrayObject::addBuffer()
{
	Bind();
	vertex_buffer->Bind();
    vertex_buffer->assignBuffer();
	vertex_buffer->assignPosAttribPointer();
	vertex_buffer->assignTexAttribPointer();
	vertex_buffer->assignNormalAttribPointer();

	index_buffer->Bind();
	if (index_buffer->edge_num == 4) index_buffer->setDataBuferRect();
	else if (index_buffer->edge_num == 3) index_buffer->setDataBufferTriangle();
	else std::cout << "Unavailable edge num in index buffer class" << std::endl;

    Unbind();
    vertex_buffer->Unbind();
    index_buffer->Unbind();
}

void VertexArrayObject::drawTeture(unsigned int tex_slot_num)
{
	texture->Unbind();
	texture->Bind(tex_slot_num);
	texture->setUnifrom1i();
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(vertex_array_obj_id);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::changeTexture(Texture* tex)
{
	texture = tex;
}

float* VertexArrayObject::getVertex(int index)
{
	float* getVertice = new float[3];

	int offset = vertex_buffer->stride;

	getVertice[0] = vertex_buffer->vertexes.buffer[offset * index + 0];
	getVertice[1] = vertex_buffer->vertexes.buffer[offset * index + 1];
	getVertice[2] = vertex_buffer->vertexes.buffer[offset * index + 2];

	return getVertice;
}
