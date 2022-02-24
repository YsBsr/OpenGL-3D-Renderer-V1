#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::VertexBuffer(const OBJpolygon& polygon)
{
	vertexes = polygon;
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &buffer_id);
}

void VertexBuffer::evaluatePosAttribFromShader(const std::string& attribname, unsigned int program)
{
	positionAttrib = glGetAttribLocation(program, attribname.c_str());

	if (positionAttrib == -1) {
		std::cout << "Attrib name '" << attribname << "' could have defined but it is has not used as an input." << std::endl;
	}
}

void VertexBuffer::evaluateTexAttribFromShader(const std::string& attribname, unsigned int program)
{
	textureAttrib = glGetAttribLocation(program, attribname.c_str());

	if (textureAttrib == -1) {
		std::cout << "Attrib name '" << attribname << "' could have defined but it is has not used as an input." << std::endl;
	}
}

void VertexBuffer::evaluateNormalAttribFromShader(const std::string& attribname, unsigned int program)
{
	normalAttrib = glGetAttribLocation(program, attribname.c_str());

	if (normalAttrib == -1) {
		std::cout << "Attrib name '" << attribname << "' could have defined but it is has not used as an input." << std::endl;
	}
}

void VertexBuffer::setPosAttribs(int read_size, int stride, int offset)
{
	p_read_size = read_size;
	this->stride = stride;
	p_offset = offset;
}

void VertexBuffer::setTexAttribs(int read_size, int stride, int offset)
{
	t_read_size = read_size;
	this->stride = stride;
	t_offset = offset;
}

void VertexBuffer::setNormalAttribs(int read_size, int stride, int offset)
{
	n_read_size = read_size;
	this->stride = stride;
	n_offset = offset;
}

void VertexBuffer::assignBuffer()
{
	glBufferData(GL_ARRAY_BUFFER, vertexes.edge * stride * sizeof(float), &vertexes.buffer[0], GL_STATIC_DRAW);
}

void VertexBuffer::assignPosAttribPointer()
{
	glVertexAttribPointer(positionAttrib, p_read_size, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (const void*)(p_offset * sizeof(float)));
	glEnableVertexAttribArray(positionAttrib);
}

void VertexBuffer::assignTexAttribPointer()
{
	glVertexAttribPointer(textureAttrib, t_read_size, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (const void*)(t_offset * sizeof(float)));
	glEnableVertexAttribArray(textureAttrib);
}

void VertexBuffer::assignNormalAttribPointer()
{
	glVertexAttribPointer(normalAttrib, n_read_size, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (const void*)(n_offset * sizeof(float)));
	glEnableVertexAttribArray(normalAttrib);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
