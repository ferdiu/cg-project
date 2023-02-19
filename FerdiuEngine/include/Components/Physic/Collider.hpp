
#pragma once

#include <glm/glm.hpp>

#include "../Component.hpp"
#include "../../Physics.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class RigidBody;

class FERDIU_ENGINE_EXPORT Collider : public Component
{
public:
    FERDIU_ENGINE_EXPORT Collider();
    FERDIU_ENGINE_EXPORT virtual ~Collider() {};

    FERDIU_ENGINE_EXPORT void start() override;

    FERDIU_ENGINE_EXPORT bool isTrigger();
    FERDIU_ENGINE_EXPORT void setTrigger(bool v);

    FERDIU_ENGINE_EXPORT void bindToRigidBody(RigidBody *rb);

protected:
    rp3d::Collider *collider;
    rp3d::CollisionShape *shape;

private:
    bool trigger = false;

};

}
