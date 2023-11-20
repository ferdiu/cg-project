
#pragma once

#include <glm/glm.hpp>

#include "../Component.hpp"
#include "RigidBody.hpp"
#include "../../Physics.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

// class RigidBody;

class FERDIU_ENGINE_EXPORT Collider : public Component
{
public:
    FERDIU_ENGINE_EXPORT Collider();
    FERDIU_ENGINE_EXPORT virtual ~Collider();

    FERDIU_ENGINE_EXPORT bool isTrigger();
    FERDIU_ENGINE_EXPORT void setTrigger(bool v);

    FERDIU_ENGINE_EXPORT btCollisionShape* shape();

protected:
    btCollisionShape *_shape;

private:
    bool trigger = false;

    friend void RigidBody::bindToCollider(Collider *c);
};

}
