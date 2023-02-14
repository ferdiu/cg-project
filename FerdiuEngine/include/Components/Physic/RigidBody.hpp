
#pragma once

#include <glm/glm.hpp>

#include "../Component.hpp"
#include "Collider.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT RigidBody : public Component
{
public:

    FERDIU_ENGINE_EXPORT glm::vec3 getVelocity();
    FERDIU_ENGINE_EXPORT void setVelocity(glm::vec3 v);
    FERDIU_ENGINE_EXPORT void addVelocity(glm::vec3 v);

    FERDIU_ENGINE_EXPORT float getGravity();
    FERDIU_ENGINE_EXPORT void setGravity(float v);

    FERDIU_ENGINE_EXPORT float getMass();
    FERDIU_ENGINE_EXPORT void setGMass(float v);

private:
    float gravity = 9.81f;
    float mass = 1.0;
    glm::vec3 velocity;
};

}
