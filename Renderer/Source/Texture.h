#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glew.h>
#include <glfw3.h>

#include "stb_image/stb_image.h"

class Texture {

private:
	const char* tex_filepath;
	unsigned int texture_id;
	int width, height, bits_per_color;
	int shader_tex_uniform, tex_slot;
	std::string uniform_name;

public:
	Texture();
	Texture(const std::string& filepath, bool is_flipped = false);
	~Texture();

	void Bind(unsigned int slot);
	void Unbind();

	void setTexSlotNum(unsigned int slot);

	int getUnifrom1iLocation(const std::string& uniforname, unsigned int program);
	void setUnifrom1i();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};