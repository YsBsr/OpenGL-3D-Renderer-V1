#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glew.h>
#include <glfw3.h>
#include "OBJFileReader.h"

class VertexBuffer {

public:
	int stride;
	int p_read_size, p_offset;
	int t_read_size, t_offset;
	int n_read_size, n_offset;
	OBJpolygon vertexes;

private:
	unsigned int buffer_id;
	int positionAttrib;
	int textureAttrib;
	int normalAttrib;
	
public:
	VertexBuffer();
	VertexBuffer(const OBJpolygon& polygon);
	~VertexBuffer();

	void evaluatePosAttribFromShader(const std::string& attribname, unsigned int program);
	void evaluateTexAttribFromShader(const std::string& attribname, unsigned int program);
	void evaluateNormalAttribFromShader(const std::string& attribname, unsigned int program);
	
	void setPosAttribs(int read_size, int stride, int offset);
	void setTexAttribs(int read_size, int stride, int offset);
	void setNormalAttribs(int read_size, int stride, int offset);

	void assignBuffer();
	void assignPosAttribPointer();
	void assignTexAttribPointer();
	void assignNormalAttribPointer();

	void Bind();  
	void Unbind();
};