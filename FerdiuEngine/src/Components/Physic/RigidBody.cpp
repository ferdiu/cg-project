
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "../../../include/GameObject.hpp"
#include "../../../include/Components/Component.hpp"
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/RigidBody.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/utils/Math.hpp"

namespace FerdiuEngine
{


RigidBody::RigidBodyType convert(rp3d::BodyType bt)
{
    switch (bt)
    {
        case rp3d::BodyType::DYNAMIC:
            return RigidBody::RigidBodyType::RB_DYNAMIC;
        case rp3d::BodyType::KINEMATIC:
            return RigidBody::RigidBodyType::RB_KINEMATIC;
        default:
            return RigidBody::RigidBodyType::RB_STATIC;
    }
}

rp3d::BodyType convert(RigidBody::RigidBodyType bt)
{
    switch (bt)
    {
        case RigidBody::RigidBodyType::RB_DYNAMIC:
            return rp3d::BodyType::DYNAMIC;
        case RigidBody::RigidBodyType::RB_KINEMATIC:
            return rp3d::BodyType::KINEMATIC;
        default:
            return rp3d::BodyType::STATIC;
    }
}

RigidBody::RigidBody(RigidBody::RigidBodyType type, float mass) : type(type), mass(mass) {}

void RigidBody::awake()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[RigidBody] start->awake");
#endif

    initRigidBody();
    Component::awake();

#ifdef DEBUG_PHYSICS
    Debug::Log("[RigidBody] finish->awake");
    Debug::unindent();
#endif
}

void RigidBody::start() {}

void RigidBody::update()
{
    syncTransfromToPhysics();
//     // TODO: is this really needed now???
//     decimal factor = Physics::accumulator() / PHYSICS_TIME_STEP;
//
//     // Compute the interpolated transform of the rigid body
//     rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(prevTransform, tr, factor);
//
//     // Now you can render your body using the interpolated transform here
//
//     // Update the previous transform
//     prevTransform = currTranform;
}
glm::vec3 RigidBody::getVelocity()
{
    return Math::convert(this->rb->getLinearVelocity());
}
void RigidBody::setVelocity(glm::vec3 v)
{
    this->rb->setLinearVelocity(Math::convert(v));
}
void RigidBody::addVelocity(glm::vec3 v)
{
    this->rb->setLinearVelocity(rb->getLinearVelocity() + Math::convert(v));
}

float RigidBody::getGravityScale()
{
    return gravityScale;
}
void RigidBody::setGravityScale(float v)
{
    gravityScale = v;
}

void RigidBody::initRigidBody()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[RigidBody] start->initRigidBody");
#endif

    GameObject *o = getOwner();

    if (nullptr == o)
    {
        Debug::Error("awake() called on a RigidBody with no Owner!");
        return;
    }

    tr = new rp3d::Transform(
        Math::convert(o->getGlobalPosition()),
        Math::convert(Math::eulerToQuaternion(o->getLocalRotation())));

    this->rb = Physics::world().createRigidBody(*tr);
    this->rb->setMass(mass);
    this->rb->setType(convert(this->type));

#ifdef DEBUG_PHYSICS
    Debug::Log("[RigidBody] finish->initRigidBody");
    Debug::unindent();
#endif
}

void RigidBody::applyForce(glm::vec3 force)
{
    this->rb->applyWorldForceAtCenterOfMass(Math::convert(force));
}

rp3d::RigidBody *RigidBody::getPhysicsRigidBody()
{
    return this->rb;
}

Transform *RigidBody::getTransform()
{
    return getTransform_Normal();
}

Transform *RigidBody::getPhysicsTransform()
{
    return getPhysicsTransform_Normal();
}

rp3d::Transform *RigidBody::getTransform_RP3D()
{
    GameObject *o = getOwner();
    return new rp3d::Transform(
        Math::convert(o->getGlobalPosition()),
        Math::convert(Math::eulerToQuaternion(o->getLocalRotation())));
}

Transform *RigidBody::getTransform_Normal()
{
    return getOwner()->getTransform();
}

rp3d::Transform *RigidBody::getPhysicsTransform_RP3D()
{
    return new rp3d::Transform(rb->getTransform());
}

Transform *RigidBody::getPhysicsTransform_Normal()
{
    return getOwner()->getTransform();
}

void RigidBody::syncPhysicsToTransform()
{
    rp3d::Transform *t = getTransform_RP3D();
    GameObject *o = getOwner();
    t->setPosition(Math::convert(o->getGlobalPosition()));
    t->setOrientation(Math::convert(Math::eulerToQuaternion(o->getTransform()->getRotation())));
    rb->setTransform(*t);
}

void RigidBody::syncTransfromToPhysics()
{
    Transform *pt = getPhysicsTransform();
    Transform *nt = getTransform();
    nt->position = pt->getPosition();
    nt->rotation = pt->getRotation();
}

}
