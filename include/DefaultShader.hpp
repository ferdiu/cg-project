
#pragma once

#include "Components/Component.hpp"
#include <FerdiuEngine.hpp>

// TODO explaing this class
class DefaultShader : public FerdiuEngine::Component
{
public:
    void awake() override;
    void update() override;

private:
    FerdiuEngine::Material *material = nullptr;
    FerdiuEngine::Shader *shader = nullptr;
};
