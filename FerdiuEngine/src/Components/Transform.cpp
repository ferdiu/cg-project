
#include <glm/glm.hpp>

#include "../../include/Components/Component.hpp"
#include "../../include/Components/Transform.hpp"

namespace FerdiuEngine
{

// constructor
Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot)
{
    this->position = pos;
    this->scale = scale;
    this->rotation = rot;
}

// ------- GETTERS-SETTERS -------
// position
glm::vec3 Transform::getPosition()
{
    return this->position;
}
void Transform::setPosition(glm::vec3 v)
{
    this->position.x = v.x;
    this->position.y = v.y;
    this->position.z = v.z;
}

// scale
glm::vec3 Transform::getScale()
{
    return this->scale;
}
void Transform::setScale(glm::vec3 v)
{
    this->scale.x = v.x;
    this->scale.y = v.y;
    this->scale.z = v.z;
}

// rotation
glm::vec3 Transform::getRotation()
{
    return this->rotation;
}
void Transform::setRotation(glm::vec3 v)
{
    this->rotation.x = v.x;
    this->rotation.y = v.y;
    this->rotation.z = v.z;
}

}
