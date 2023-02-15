
#include <iostream>
#include <optional>

#include "../include/DefaultShader.hpp"

using namespace FerdiuEngine;

void DefaultShader::awake()
{
    Renderer *r = getGameObject()->renderer().has_value() ?
        getGameObject()->renderer().value() : nullptr;

    if (nullptr != r && r->getMaterial().has_value())
        this->material = getGameObject()->renderer().value()->getMaterial().value();

#ifdef DEBUG
    if (nullptr == this->material)
        std::cerr << "warning: DefaultShader placed on an object with no Renderer or no Material!" << std::endl;
#endif

    if (nullptr != this->material)
        this->shader = this->material->getShader();
}

void DefaultShader::update()
{
    // TODO: update all shader uniforms
    // shader->setUniform("projMat", );
    // shader->setUniform("viewMat", );
    // shader->setUniform("modelMat", );
}
