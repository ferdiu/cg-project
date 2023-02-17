
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../include/Components/Component.hpp"
#include "../../include/Components/Transform.hpp"
#include "../../include/Components/Camera.hpp"
#include "GameObject.hpp"

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
    glm::vec3 const& rot = t.getRotation();
    // https://gamedev.stackexchange.com/questions/138358/what-is-the-transformation-order-when-using-the-transform-class
    // https://community.khronos.org/t/correct-order-of-transformations/75448/2
    glm::mat4 matRX = glm::rotate(mat, glm::radians(rot[0]), glm::vec3(1.0, 0.0, 0.0)); // x
    glm::mat4 matRY = glm::rotate(mat, glm::radians(rot[1]), glm::vec3(0.0, 1.0, 0.0)); // y
    glm::mat4 matRZ = glm::rotate(mat, glm::radians(rot[2]), glm::vec3(0.0, 0.0, 1.0)); // z
    glm::mat4 matS = glm::scale(mat, t.getScale());
    glm::mat4 matT = glm::translate(mat, t.getPosition());

    mat = matT * matS * matRZ * matRY * matRX;
}

void Transform::apply(glm::mat4& mat) const
{
    apply(*getOwner().getTransform(), mat);
}

}
