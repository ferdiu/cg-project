
#pragma once

#include <list>
#include <string>
#include <optional>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/mat4x4.hpp>

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

    FERDIU_ENGINE_EXPORT std::optional<Material*> getMaterial();

    FERDIU_ENGINE_EXPORT void setTexture(std::string filepath, GLenum texEnum = GL_TEXTURE0);
    FERDIU_ENGINE_EXPORT void setTexture(Texture tex, GLenum texEnum = GL_TEXTURE0);

    FERDIU_ENGINE_EXPORT glm::mat4 *getModelMatrix();
    FERDIU_ENGINE_EXPORT void setModelMatrix(glm::mat4 const& m);

protected:
    void init();
    virtual void Init() = 0;
    virtual void _draw() = 0;

private:
#ifdef DEBUG
    bool initialized = false;
#endif
    glm::mat4 *_modelMatrix = new glm::mat4(1);

    std::optional<Material> material = {};
    std::optional<Texture> texture = {};

    GLuint vao;

    void PreInit();
    void PostInit();
};

}
