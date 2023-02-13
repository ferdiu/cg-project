
#pragma once

#include <glm/glm.hpp>

#include "../Component.hpp"
#include "Collider.hpp"

namespace FerdiuEngine
{

class RigidBody : Component
{
public:

    glm::vec3 getVelocity();
    void setVelocity(glm::vec3 v);
    void addVelocity(glm::vec3 v);

    float getGravity();
    void setGravity(float v);

    float getMass();
    void setGMass(float v);

private:
    float gravity = 9.81f;
    float mass = 1.0;
    glm::vec3 velocity;
};

}
