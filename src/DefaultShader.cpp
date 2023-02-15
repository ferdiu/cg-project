
#include <climits>
#include <iostream>
#include <optional>

#include "../include/DefaultShader.hpp"

using namespace FerdiuEngine;

void DefaultShader::awake()
{
    renderer = getGameObject()->renderer().has_value() ?
        getGameObject()->renderer().value() : nullptr;

    if (nullptr != renderer && renderer->getMaterial().has_value())
        this->material = getGameObject()->renderer().value()->getMaterial().value();

#ifdef DEBUG
    if (nullptr == this->material)
        std::cerr << "warning: DefaultShader placed on an object with no Renderer or Material!" << std::endl;
#endif

    if (nullptr != this->material)
        this->shader = this->material->getShader();

    if (nullptr != this->shader)
    {
        shader->use();
        shader->setUniform("tex", 0);
    }

#ifdef DEBUG
    if (nullptr == light)
        std::cerr << "warning: no light set in DefaultShader in object " <<
        this->getOwner()->getName() << std::endl;
#endif
    Component::awake();
}

void DefaultShader::update()
{
    shader->use();
    // TODO: space for optimization here:
    //   not all uniforms need to be updated at every refresh
    Camera *camera = Camera::getCurrent();

#ifdef DEBUG
    // Debug::indent();
    // Debug::Log("MATRICES:");
    // Debug::Log("--- proj ---");
    // fprint(*camera->getPorjectionMatrix());
    // Debug::Log("--- view---");
    // fprint(*camera->getViewMatrix());
    // Debug::Log("--- model ---");
    // fprint(*renderer->getModelMatrix());
    // Debug::Log("");
    // Debug::unindent();
#endif

    shader->setUniform("projMat", *camera->getPorjectionMatrix());
    shader->setUniform("viewMat", *camera->getViewMatrix());
    shader->setUniform("modelMat", *renderer->getModelMatrix());

    shader->setUniform("color", color);

    shader->setUniform("viewPos", camera->getOwner()->getTransform()->getPosition());
    shader->setUniform("light0", *light);
    shader->setUniform("material", *material);
}

void DefaultShader::setLight(Light *l)
{
    this->light = l;
}
Light *DefaultShader::getLight()
{
    return this->light;
}

void DefaultShader::setColor(glm::vec4 const& c)
{
    this->color[0] = c[0];
    this->color[1] = c[1];
    this->color[2] = c[2];
    this->color[3] = c[3];
}
glm::vec4 DefaultShader::getColor()
{
    return glm::vec4(this->color);
}

void DefaultShader::setTexture(std::string const& t)
{
    renderer->setTexture(t);
    shader->setUniform("useTex", true);
}
void DefaultShader::setTexture(FerdiuEngine::Texture const& t)
{
    renderer->setTexture(t);
    shader->setUniform("useTex", true);
}
void DefaultShader::unsetTexture()
{
    shader->setUniform("useTex", false);
}
