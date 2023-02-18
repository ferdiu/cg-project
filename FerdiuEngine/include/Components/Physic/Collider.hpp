
#pragma once

#include <glm/glm.hpp>

#include "../Component.hpp"
#include "../../Physics.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Collider : public Component
{
public:
    FERDIU_ENGINE_EXPORT Collider();
    FERDIU_ENGINE_EXPORT virtual ~Collider() {};

    FERDIU_ENGINE_EXPORT void start() override;

    FERDIU_ENGINE_EXPORT bool isTrigger();
    FERDIU_ENGINE_EXPORT void setTrigger(bool v);


protected:
    rp3d::Collider *collider;
    rp3d::CollisionShape *shape;

private:
    FERDIU_ENGINE_EXPORT void bindToRigidBody(rp3d::RigidBody *rb);

    bool trigger = false;

};

}
