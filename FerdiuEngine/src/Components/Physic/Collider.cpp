
#include <reactphysics3d/reactphysics3d.h>

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/Bounds.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/utils/Math.hpp"
#include "../../../include/Components/Transform.hpp"

namespace FerdiuEngine
{

// --------------------------------- public ----------------------------------
Collider::Collider()
{
    this->bounds = nullptr;
    this->collider = nullptr;
}

void Collider::start()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Collider] start->start");
#endif

    if (nullptr == shape)
    {
        Debug::Log("This Collider has no Shape: initialize it in the constructor of the derived class!!!");
        return;
    }

    GameObject *o = this->getOwner();

    if (nullptr == o)
    {
        Debug::Log("This Collider has no Owner!!!");
        return;
    }

    if (!(o->rigidbody().has_value()))
    {
        Debug::Log("This Collider has no RigidBody!!!");
        return;
    }

    RigidBody *rb = o->rigidbody().value();

    bindToRigidBody(rb->getPhysicsRigidBody());

#ifdef DEBUG_PHYSICS
    Debug::Log("[Collider] finish->start");
    Debug::unindent();
#endif
}

bool Collider::isTrigger()
{
    return trigger;
}
void Collider::setTrigger(bool v)
{
    trigger = v;
    collider->setIsTrigger(v);
}

Bounds *Collider::getBounds()
{
    return bounds;
}

void Collider::bindToRigidBody(rp3d::RigidBody *rb)
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Collider] start->bindToRigidBody");
#endif

    Transform *t = this->getOwner()->getTransform();
    this->collider = rb->addCollider(
        shape,
        rp3d::Transform(
            Math::convert(t->getPosition()),
            Math::eulerToQuaternion(Math::convert(t->getRotation()))));
    collider->setIsTrigger(trigger);

#ifdef DEBUG_PHYSICS
    Debug::Log("[Collider] finish->bindToRigidBody");
    Debug::unindent();
#endif
}

// --------------------------------- protected -------------------------------
void Collider::setBounds(Bounds *b)
{
    bounds = b;
}

}
