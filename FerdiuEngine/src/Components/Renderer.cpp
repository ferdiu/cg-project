
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
    PreInit();
    Init();
    PostInit();

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

#ifdef DEBUG_RENDERING
    Debug::indent();
    Debug::Log("start->draw");
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

    glutPostRedisplay();

#ifdef DEBUG_RENDERING
    Debug::Log("finish->draw");
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

glm::mat4 *Renderer::getModelMatrix()
{
    return this->_modelMatrix;
}

void Renderer::setModelMatrix(glm::mat4 const& m)
{
    GLMatrix::copy(*this->_modelMatrix, m);
}

// ------------------------------ private -------------------------------------
void Renderer::PreInit()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(this->vao);
}

void Renderer::PostInit()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
