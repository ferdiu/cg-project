
#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Transform : public Component
{
public:
    // constructor
    FERDIU_ENGINE_EXPORT Transform(glm::vec3 pos = glm::vec3(1), glm::vec3 scale = glm::vec3(1), glm::vec3 rot = glm::vec3(0));

    // ------- GETTERS-SETTERS -------
    // position
    FERDIU_ENGINE_EXPORT glm::vec3 getPosition();
    FERDIU_ENGINE_EXPORT void setPosition(glm::vec3 v);

    // scale
    FERDIU_ENGINE_EXPORT glm::vec3 getScale();
    FERDIU_ENGINE_EXPORT void setScale(glm::vec3 v);

    // rotation
    FERDIU_ENGINE_EXPORT glm::vec3 getRotation();
    FERDIU_ENGINE_EXPORT void setRotation(glm::vec3 v);

private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

}
