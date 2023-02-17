
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
}

void Collider::start()
{
    if (nullptr != shape)
    {
        Debug::Log("This Collider has no Shape: initialize it in the constructor of the derived class!!!");
        return;
    }

    GameObject *o = getOwner();

    if (nullptr != o)
    {
        Debug::Log("This Collider has no Owner!!!");
        return;
    }

    if (!o->rigidbody().has_value())
    {
        Debug::Log("This Collider has no RigidBody!!!");
        return;
    }

    RigidBody *rb = o->rigidbody().value();

    bindToRigidBody(rb->getPhysicsRigidBody());
}

bool Collider::isTrigger()
{
    return collider->getIsTrigger();
}
void Collider::setTrigger(bool v)
{
    collider->setIsTrigger(v);
    trigger = v;
}

Bounds *Collider::getBounds()
{
    return bounds;
}

void Collider::bindToRigidBody(reactphysics3d::RigidBody *rb)
{
    Transform *t = this->getOwner()->getTransform();
    this->collider = rb->addCollider(
        shape,
        reactphysics3d::Transform(
            Math::convert(t->getPosition()),
            Math::eulerToQuaternion(Math::convert(t->getRotation()))));
}

// --------------------------------- protected -------------------------------
void Collider::setBounds(Bounds *b)
{
    bounds = b;
}

}
