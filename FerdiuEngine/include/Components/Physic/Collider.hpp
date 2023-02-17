
#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "../Component.hpp"
#include "Bounds.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Collider : public Component
{
public:
    FERDIU_ENGINE_EXPORT Collider();

    FERDIU_ENGINE_EXPORT void start() override;

    FERDIU_ENGINE_EXPORT bool isTrigger();
    FERDIU_ENGINE_EXPORT void setTrigger(bool v);

    FERDIU_ENGINE_EXPORT Bounds *getBounds();
    FERDIU_ENGINE_EXPORT virtual bool checkCollision(Collider *c) = 0;

    FERDIU_ENGINE_EXPORT void bindToRigidBody(reactphysics3d::RigidBody *rb);

protected:
    FERDIU_ENGINE_EXPORT virtual void setBounds(Bounds *b);

    reactphysics3d::Collider *collider;
    reactphysics3d::CollisionShape *shape;

private:

    bool trigger = false;

    Bounds *bounds;
};

}
