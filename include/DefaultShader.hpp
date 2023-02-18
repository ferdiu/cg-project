
#pragma once

#include "Components/Component.hpp"
#include <FerdiuEngine.hpp>

// TODO explaing this class
class DefaultShader : public FerdiuEngine::Component
{
public:
    ~DefaultShader() override;

    void awake() override;
    void draw() override;

    void setLight(FerdiuEngine::Light *l);
    FerdiuEngine::Light *getLight();

    void setColor(glm::vec4 const& c);
    glm::vec4 getColor();

    void setTexture(FerdiuEngine::Texture const& t);
    void setTexture(std::string const& t);
    void unsetTexture();

    void updateShader();

private:
    glm::vec4 color = glm::vec4(1);
    bool useTex = false;

    FerdiuEngine::Renderer *renderer = nullptr;
    FerdiuEngine::Material *material = nullptr;
    FerdiuEngine::Shader *shader = nullptr;
    FerdiuEngine::Light *light = nullptr;
};
