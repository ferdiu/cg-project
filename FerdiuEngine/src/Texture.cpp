
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../include/utils/BitMapFile.hpp"
#include "../include/Texture.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------

Texture::Texture(std::string path, GLenum filtering, GLenum wrap)
{
    filepath = path;
    Load(filtering, wrap);
}

void Texture::ReBind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

int Texture::getWidth()
{
    return width;
}
int Texture::getHeight()
{
    return height;
}
unsigned int Texture::getId()
{
    return id;
}

//------------------------- private -------------------------------

void Texture::Load(GLenum filtering, GLenum wrap)
{
    BitMapFile bmp = BitMapFile(filepath);

    width = bmp.width();
    height = bmp.height();

    // generate
    glGenTextures(1, &id);

    // bind
    Bind(bmp, filtering, wrap);

    // unbind
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(BitMapFile image, GLenum filtering, GLenum wrap)
{
    // Activate texture object
    glBindTexture(GL_TEXTURE_2D, this->id);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, image.getData());

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
}

}
