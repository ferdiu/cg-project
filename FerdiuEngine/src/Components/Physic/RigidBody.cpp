
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


RigidBody::RigidBodyType convert(reactphysics3d::BodyType bt)
{
    switch (bt)
    {
        case reactphysics3d::BodyType::DYNAMIC:
            return RigidBody::RigidBodyType::RB_DYNAMIC;
        case reactphysics3d::BodyType::KINEMATIC:
            return RigidBody::RigidBodyType::RB_KINEMATIC;
        default:
            return RigidBody::RigidBodyType::RB_STATIC;
    }
}

reactphysics3d::BodyType convert(RigidBody::RigidBodyType bt)
{
    switch (bt)
    {
        case RigidBody::RigidBodyType::RB_DYNAMIC:
            return reactphysics3d::BodyType::DYNAMIC;
        case RigidBody::RigidBodyType::RB_KINEMATIC:
            return reactphysics3d::BodyType::KINEMATIC;
        default:
            return reactphysics3d::BodyType::STATIC;
    }
}

RigidBody::RigidBody(RigidBody::RigidBodyType type, float mass) : type(type), mass(mass) {}

void RigidBody::awake()
{
    initRigidBody();
    Component::awake();
}
void RigidBody::start() {}

void RigidBody::update()
{
    this->getOwner()->setPosition(Math::convert(this->rb->getLocalCenterOfMass()));
    // TODO: set rotation????
//     // TODO: is this really needed now???
//     decimal factor = Physics::accumulator() / PHYSICS_TIME_STEP;
//
//     // Compute the interpolated transform of the rigid body
//     reactphysics3d::Transform interpolatedTransform = reactphysics3d::Transform::interpolateTransforms(prevTransform, tr, factor);
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
    GameObject *o = getOwner();

    if (nullptr == o)
    {
        Debug::Error("awake() called on a RigidBody with no Owner!");
        return;
    }

    tr = new reactphysics3d::Transform(
        Math::convert(o->getGlobalPosition()),
        Math::convert(Math::eulerToQuaternion(o->getRotation())));

    this->rb = Physics::world().createRigidBody(*tr);
    this->rb->setMass(mass);
    this->rb->setType(convert(this->type));
}

void RigidBody::applyForce(glm::vec3 force)
{
    this->rb->applyWorldForceAtCenterOfMass(Math::convert(force));
}

reactphysics3d::RigidBody *RigidBody::getPhysicsRigidBody()
{
    return this->rb;
}

}
