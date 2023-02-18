
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../include/Components/Component.hpp"
#include "../../include/Components/Transform.hpp"
#include "../../include/Components/Camera.hpp"
#include "../../include/GameObject.hpp"
#include "../../include/utils/Math.hpp"

namespace FerdiuEngine
{

// constructor
Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot)
{
    this->position = pos;
    this->scale = scale;
    this->rotation = rot;
}
Transform::~Transform()
{
    // TODO: DESTROY
}


// ------- GETTERS-SETTERS -------
// position
glm::vec3 Transform::getPosition() const
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
glm::vec3 Transform::getScale() const
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
glm::vec3 Transform::getRotation() const
{
    return this->rotation;
}
void Transform::setRotation(glm::vec3 v)
{
    this->rotation.x = v.x;
    this->rotation.y = v.y;
    this->rotation.z = v.z;
}

// model matrix
glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1);
    apply(model);
    return model;
}

void Transform::apply(Transform const& t, glm::mat4& mat)
{
    mat = Math::convert(t, mat);
}

void Transform::apply(glm::mat4& mat) const
{
    apply(*getOwner().getTransform(), mat);
}

void Transform::copyFrom(Transform const& t)
{
    this->setPosition(t.getPosition());
    this->setRotation(t.getRotation());
    this->setScale(t.getScale());
}
void Transform::copyFrom(Transform *t)
{
    this->setPosition(t->getPosition());
    this->setRotation(t->getRotation());
    this->setScale(t->getScale());
}

}
