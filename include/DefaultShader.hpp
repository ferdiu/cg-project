
#pragma once

#include "Components/Component.hpp"
#include <FerdiuEngine.hpp>

// TODO explaing this class
class DefaultShader : public FerdiuEngine::Component
{
public:
    void awake() override;
    void update() override;

    void setLight(FerdiuEngine::Light *l);
    FerdiuEngine::Light *getLight();

    void setColor(glm::vec4 const& c);
    glm::vec4 getColor();

    void setTexture(FerdiuEngine::Texture const& t);
    void setTexture(std::string const& t);
    void unsetTexture();

private:
    glm::vec4 color = glm::vec4(1);

    FerdiuEngine::Renderer *renderer = nullptr;
    FerdiuEngine::Material *material = nullptr;
    FerdiuEngine::Shader *shader = nullptr;
    FerdiuEngine::Light *light = nullptr;
};
