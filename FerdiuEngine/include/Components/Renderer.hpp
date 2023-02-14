
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

    FERDIU_ENGINE_EXPORT void Draw();

    FERDIU_ENGINE_EXPORT void setTexture(std::string filepath, GLenum texEnum = GL_TEXTURE0);
    FERDIU_ENGINE_EXPORT void setTexture(Texture tex, GLenum texEnum = GL_TEXTURE0);

protected:
    virtual void Init();
    virtual void _Draw() = 0;

private:
    std::optional<Material> material = {};
    std::optional<Texture> texture = {};

    GLuint vao;

    void PrivateInit();
    void FinalizeInit();
};

}
