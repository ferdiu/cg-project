
#include <glm/glm.hpp>

#include "../../../include/Components/Component.hpp"
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/RigidBody.hpp"

namespace FerdiuEngine
{

glm::vec3 RigidBody::getVelocity()
{
    return velocity;
}
void RigidBody::setVelocity(glm::vec3 v)
{
    velocity = v;
}
void RigidBody::addVelocity(glm::vec3 v)
{
    velocity += v;
}

float RigidBody::getGravity()
{
    return gravity;
}
void RigidBody::setGravity(float v)
{
    gravity = v;
}

}
