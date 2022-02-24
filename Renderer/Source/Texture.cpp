#pragma once

#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(const std::string& filepath, bool is_flipped) : 
    tex_filepath(filepath.c_str()), width(0), height(0), bits_per_color(0)
{
    unsigned int id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    //texture_id = id;

    if (is_flipped) {
        stbi_set_flip_vertically_on_load(1);
    }

    unsigned char* imagebuffer = stbi_load(tex_filepath, &width, &height, &bits_per_color, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagebuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (&imagebuffer) {
        stbi_image_free(imagebuffer);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_id);
}

void Texture::Bind(unsigned int slot) 
{
    tex_slot = slot;
    glActiveTexture(GL_TEXTURE0 + tex_slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::Unbind() 
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setTexSlotNum(unsigned int slot)
{
    tex_slot = slot;
}

int Texture::getUnifrom1iLocation(const std::string& uniforname, unsigned int program)
{
    uniform_name = uniforname;
    shader_tex_uniform = glGetUniformLocation(program, uniforname.c_str());
    return shader_tex_uniform;
}

void Texture::setUnifrom1i()
{
    glUniform1i(shader_tex_uniform, tex_slot);
}

