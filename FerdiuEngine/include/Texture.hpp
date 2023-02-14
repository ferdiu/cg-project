
#pragma once

#include <iostream>
#include <string>
#include <GL/gl.h>
#include "utils/BitMapFile.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Texture
{
public:
    FERDIU_ENGINE_EXPORT Texture(std::string path, GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);

    FERDIU_ENGINE_EXPORT void ReBind();

    FERDIU_ENGINE_EXPORT int getWidth();
    FERDIU_ENGINE_EXPORT int getHeight();
    FERDIU_ENGINE_EXPORT unsigned int getId();

private:
    std::string filepath;
    int width = 0;
    int height = 0;
    unsigned int id = 0;

    void Load(GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);
    void Bind(BitMapFile image, GLenum filtering = GL_NEAREST, GLenum wrap = GL_REPEAT);
};

}
