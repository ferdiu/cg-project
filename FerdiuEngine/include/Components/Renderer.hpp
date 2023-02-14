
#pragma once

#include <list>
#include <string>
#include <optional>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../Texture.hpp"
#include "../Material.hpp"
#include "Component.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Renderer : public Component
{
public:
    FERDIU_ENGINE_EXPORT Renderer(Material material);

    FERDIU_ENGINE_EXPORT void draw();

    FERDIU_ENGINE_EXPORT void setTexture(std::string filepath, GLenum texEnum = GL_TEXTURE0);
    FERDIU_ENGINE_EXPORT void setTexture(Texture tex, GLenum texEnum = GL_TEXTURE0);

protected:
    void init();
    virtual void Init() = 0;
    virtual void _draw() = 0;

private:
#ifdef DEBUG
    bool initialized = false;
#endif

    std::optional<Material> material = {};
    std::optional<Texture> texture = {};

    GLuint vao;

    void PrivateInit();
    void FinalizeInit();
};

}
