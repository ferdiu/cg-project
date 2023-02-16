
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../include/utils/BitMapFile.hpp"
#include "../include/Texture.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------

Texture::Texture(std::string path, bool bind, GLenum filtering, GLenum wrap) : bmp(path)
{
    filepath = path;
    width = bmp.width();
    height = bmp.height();

    Load(bind, filtering, wrap);
}

void Texture::ReBind()
{
    Bind();
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

void Texture::Load(bool bind, GLenum filtering, GLenum wrap)
{
    // generate
    glGenTextures(1, &id);

    // bind texture object
    glBindTexture(GL_TEXTURE_2D, this->id);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bmp.width(), bmp.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, bmp.getData());

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

    // unbind eventually
    if (!bind)
        glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    // bind texture object
    glBindTexture(GL_TEXTURE_2D, this->id);
}

}
