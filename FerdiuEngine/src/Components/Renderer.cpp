
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

#include "../../include/utils/Debug.hpp"
#include "../../include/Material.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Components/Renderer.hpp"
#include "../../include/Components/Camera.hpp"
#include "../../include/utils/GLMatrices.hpp"

namespace FerdiuEngine
{

Renderer::Renderer(Material material)
{
    this->material = material;
}

void Renderer::init()
{
#ifdef DEBUG_RENDERING
    Debug::indent();
    Debug::Log("[Renderer] start->init");
#endif

    preInit();
    Init();
    postInit();

#ifdef DEBUG
    initialized = true;
#endif

#ifdef DEBUG_RENDERING
    Debug::Log("[Renderer] start->init");
    Debug::unindent();
#endif
}

void Renderer::draw()
{
#ifdef DEBUG
    if (!initialized)
        throw std::invalid_argument("init function not called in contructor of derived Renderer");
#endif

#ifdef DEBUG_RENDERING
    Debug::indent();
    Debug::Log("[Renderer] start->draw");
#endif

    Camera *c = Camera::getCurrent();

    if (nullptr == c)
        return;

    material->use();
    glBindVertexArray(this->vao);

    if (texture.has_value())
        glBindTexture(GL_TEXTURE_2D, texture.value().getId());

    _draw();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glutPostRedisplay();

#ifdef DEBUG_RENDERING
    Debug::Log("[Renderer] finish->draw");
    Debug::unindent();
#endif
}

std::optional<Material*> Renderer::getMaterial()
{
    return this->material.has_value() ? &(this->material.value()) : nullptr;
}

void Renderer::setTexture(std::string filepath, GLenum texEnum)
{
    glBindVertexArray(this->vao);
    glActiveTexture(texEnum);

    texture = Texture(filepath, true);

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

glm::mat4 *Renderer::getModelMatrix()
{
    return this->_modelMatrix;
}

void Renderer::setModelMatrix(glm::mat4 const& m)
{
    GLMatrix::copy(*this->_modelMatrix, m);
}

// ------------------------------ private -------------------------------------
void Renderer::preInit()
{
#ifdef DEBUG_RENDERING
    Debug::indent();
    Debug::Log("[Renderer] start->preInit");
#endif

    glGenVertexArrays(1, &vao);
    glBindVertexArray(this->vao);

#ifdef DEBUG_RENDERING
    Debug::Log("[Renderer] finish->preInit");
    Debug::unindent();
#endif
}

void Renderer::postInit()
{
#ifdef DEBUG_RENDERING
    Debug::indent();
    Debug::Log("[Renderer] start->postInit");
#endif

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#ifdef DEBUG_RENDERING
    Debug::Log("[Renderer] finish->postInit");
    Debug::unindent();
#endif
}

void Renderer::bind()
{
    material->use();
    glBindVertexArray(this->vao);
}

void Renderer::unbind()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
