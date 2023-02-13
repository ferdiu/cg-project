
#pragma once

#include <list>
#include <string>
#include <optional>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../Texture.hpp"
#include "../Material.hpp"

namespace FerdiuEngine
{

class Renderer
{
public:
    Renderer(Material material);

    void Draw();

    void setTexture(std::string filepath, GLenum texEnum = GL_TEXTURE0);
    void setTexture(Texture tex, GLenum texEnum = GL_TEXTURE0);

protected:
    virtual void Init();
    virtual void _Draw();

private:
    std::optional<Material> material;
    std::optional<Texture> texture = {};

    GLuint vao;

    void PrivateInit();
    void FinalizeInit();
};

}
