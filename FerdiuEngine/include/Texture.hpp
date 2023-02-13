
#pragma once

#include <iostream>
#include <string>
#include <GL/gl.h>
#include "utils/BitMapFile.hpp"

namespace FerdiuEngine
{

class Texture
{
public:
    Texture(std::string path, GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);

    void ReBind();

    int getWidth();
    int getHeight();
    unsigned int getId();

private:
    std::string filepath;
    int width = 0;
    int height = 0;
    unsigned int id = 0;

    void Load(GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);
    void Bind(BitMapFile image, GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);
};

}
