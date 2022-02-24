#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glew.h>
#include <glfw3.h>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {

private:
	const char* shd_filepath;
	std::string shader;
	

	static unsigned int total_shader_obj;
	unsigned int shader_id = 0;

public:
	Shader(const std::string& filepath);
	~Shader();
	
	unsigned int program;

	void releseShaderProgram();
	void Unbind();
	void Bind();

private:
	ShaderProgramSource ParseShader();
	unsigned int CompileVertexShader(const std::string& vertexShader);
	unsigned int CompileFragmentShader(const std::string& fragmentShader);
};