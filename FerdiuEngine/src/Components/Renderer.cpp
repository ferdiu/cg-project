
#include <list>
#include <string>
#include <optional>
#include <iostream>
#ifdef DEBUG
#include <stdexcept>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../../include/Material.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Components/Renderer.hpp"
#include "../../include/Components/Camera.hpp"

namespace FerdiuEngine
{

Renderer::Renderer(Material material)
{
    this->material = material;
}

void Renderer::init()
{
    PrivateInit();
    Init();
    FinalizeInit();

#ifdef DEBUG
    initialized = true;
#endif
}

void Renderer::draw()
{
#ifdef DEBUG
    if (!initialized)
        throw std::invalid_argument("init function not called in contructor of derived Renderer");
#endif
    Camera *c = Camera::getCurrent();

    if (nullptr == c)
        return;

    material->use();
    glBindVertexArray(this->vao);

    _draw();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::setTexture(std::string filepath, GLenum texEnum)
{
    glBindVertexArray(this->vao);
    glActiveTexture(texEnum);

    texture = Texture(filepath);

    glBindVertexArray(0);
    glActiveTexture(0);
}
void Renderer::setTexture(Texture tex, GLenum texEnum)
{
    glBindVertexArray(this->vao);
    glActiveTexture(texEnum);

    tex.ReBind();

    glBindVertexArray(0);
    glActiveTexture(0);
}

// ------------------------------ private -------------------------------------
void Renderer::PrivateInit()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(this->vao);
}

void Renderer::FinalizeInit()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
