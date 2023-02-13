
#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"

namespace FerdiuEngine
{

class Transform : public Component
{
public:
    // constructor
    Transform(glm::vec3 pos = glm::vec3(1), glm::vec3 scale = glm::vec3(1), glm::vec3 rot = glm::vec3(0));

    // ------- GETTERS-SETTERS -------
    // position
    glm::vec3 getPosition();
    void setPosition(glm::vec3 v);

    // scale
    glm::vec3 getScale();
    void setScale(glm::vec3 v);

    // rotation
    glm::vec3 getRotation();
    void setRotation(glm::vec3 v);

private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

}
