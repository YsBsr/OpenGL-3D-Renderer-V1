#include "IndexBuffer.h"

unsigned int IndexBuffer::indices_for_rect[6] = {
	0, 1, 2, 2, 3, 0
};

unsigned int IndexBuffer::indices_for_triangle[3] = {
	0, 1, 2
};

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::IndexBuffer(int edges_number_of_polygon) : edge_num(edges_number_of_polygon)
{
	glGenBuffers(1, &index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &index_buffer_id);
}

void IndexBuffer::setDataBuferRect()
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices_for_rect, GL_STATIC_DRAW);
}

void IndexBuffer::setDataBufferTriangle()
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices_for_triangle, GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
