#pragma once

#include "Shader.h"

unsigned int Shader::total_shader_obj = 0;

Shader::Shader(const std::string& filepath) : shd_filepath(filepath.c_str()), shader_id(total_shader_obj++)
{
    ShaderProgramSource shader = ParseShader();
    program = glCreateProgram();
    
    int result = CompileVertexShader(shader.VertexSource);

    if (!result) {
        std::cout << "Shader object not created. Error in Fragment shader compile" << std::endl;
        Shader::~Shader();
        return;
    }

    result = CompileFragmentShader(shader.FragmentSource);

    if (!result) {
        std::cout << "Shader object not created. Error in Fragment shader compile" << std::endl;
        Shader::~Shader();
        return;
    }

    glLinkProgram(program);
    glValidateProgram(program);

    /*glAttachShader(program, 0);
    glAttachShader(program, 0);*/

    glUseProgram(program);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::releseShaderProgram()
{
    glDeleteProgram(program);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::Bind()
{
    glUseProgram(program);
}

ShaderProgramSource Shader::ParseShader()
{
    std::ifstream stream(shd_filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileVertexShader(const std::string& vertexShader)
{
    unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);

    const char* vsrc = vertexShader.c_str();

    glShaderSource(vertexshader, 1, &vsrc, nullptr);
    glCompileShader(vertexshader);

    int result;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        int length;
        glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];

        glGetShaderInfoLog(vertexshader, length, &length, message);

        std::cout << "Vertex Shader Compiling Error. Error message: " << message << std::endl;

        delete[] message;
        glDeleteShader(vertexshader);

        return 0;
    }

    glAttachShader(program, vertexshader);
    glDeleteShader(vertexshader);

	return 1;
}

unsigned int Shader::CompileFragmentShader(const std::string& fragmentShader)
{
    unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fsrc = fragmentShader.c_str();

    glShaderSource(fragmentshader, 1, &fsrc, nullptr);
    glCompileShader(fragmentshader);

    int result;
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        int length;
        glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];

        glGetShaderInfoLog(fragmentshader, length, &length, message);

        std::cout << "Vertex Shader Compiling Error. Error message: " << message << std::endl;

        delete[] message;
        glDeleteShader(fragmentshader);

        return 0;
    }

    glAttachShader(program, fragmentshader);
    glDeleteShader(fragmentshader);

	return 1;
}
