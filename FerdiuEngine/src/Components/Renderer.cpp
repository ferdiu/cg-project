
#include <list>
#include <string>
#include <optional>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../../include/Material.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Components/Renderer.hpp"

namespace FerdiuEngine
{

Renderer::Renderer(Material material)
{
    this->material = material;

    PrivateInit();
    Init();
    FinalizeInit();
}

void Renderer::Draw()
{
    material->use();
    glBindVertexArray(this->vao);

    _Draw();

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

// ------------------------------ protected -----------------------------------

void Renderer::Init()
{
    std::cout << "error: Initialization step not overriden in concrete Renderer" << std::endl;
    exit(1);
};

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
