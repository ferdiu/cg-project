
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#include <reactphysics3d/reactphysics3d.h>
#pragma GCC diagnostic pop

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/utils/Math.hpp"
#include "../../../include/Components/Transform.hpp"

namespace FerdiuEngine
{

// --------------------------------- public ----------------------------------
Collider::Collider() : collider(nullptr) {}

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

void Collider::bindToRigidBody(rp3d::RigidBody *rb)
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Collider] start->bindToRigidBody");
#endif

    Transform *t = this->getOwner()->getTransform();
    glm::vec3 pos = this->getOwner()->getGlobalPosition();
    this->collider = rb->addCollider(
        shape,
        rp3d::Transform(
            Math::convert(pos),
            Math::eulerToQuaternion(Math::convert(t->getRotation()))));
    collider->setIsTrigger(trigger);

#ifdef DEBUG_PHYSICS
    Debug::Log("[Collider] finish->bindToRigidBody");
    Debug::unindent();
#endif
}

}
