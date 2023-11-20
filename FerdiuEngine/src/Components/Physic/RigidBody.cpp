
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../../../include/GameObject.hpp"
#include "../../../include/Components/Component.hpp"
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/RigidBody.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/utils/Math.hpp"

namespace FerdiuEngine
{

RigidBody::RigidBody(RigidBody::RigidBodyType type, float mass) : type(type), mass(mass) {}
RigidBody::~RigidBody()
{
    // TODO: DESTROY
}

void RigidBody::awake() {}

void RigidBody::start()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[RigidBody] start->start");
#endif

    initRigidBody();

#ifdef DEBUG_PHYSICS
    Debug::Log("[RigidBody] finish->start");
    Debug::unindent();
#endif
}

void RigidBody::physicsUpdatePre()
{
    syncPhysicsToTransform();

    _prevTransform = ((btCollisionObject*) rb)->getWorldTransform();
}

void RigidBody::physicsUpdatePost()
{
    if (RigidBodyType::RB_STATIC != type)
        syncTransfromToPhysics(((btCollisionObject*) rb)->getWorldTransform());
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
    this->rb->setLinearVelocity(Math::convert(v) + this->rb->getLinearVelocity());
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

    if (!(o->collider().has_value()))
    {
        Debug::Error("This RigidBody has no Collider!!!");
        return;
    }

    Collider *c = o->collider().value();

    bindToCollider(c);

#ifdef DEBUG_PHYSICS
    Debug::Log("[RigidBody] finish->initRigidBody");
    Debug::unindent();
#endif
}

void RigidBody::applyForce(glm::vec3 force)
{
    this->rb->applyCentralForce(Math::convert(force));
}

btRigidBody *RigidBody::getPhysicsRigidBody()
{
    return this->rb;
}

Transform *RigidBody::getTransform()
{
    return getTransform_Normal();
}

RigidBody::RigidBodyType RigidBody::getType()
{
    // TODO: this should be set from the physics engine
    return type;
}

bool RigidBody::isDynamic()
{
    return getType() == RigidBodyType::RB_DYNAMIC;
}

bool RigidBody::isKinematic()
{
    return getType() == RigidBodyType::RB_KINEMATIC;
}

bool RigidBody::isStatic()
{
    return getType() == RigidBodyType::RB_STATIC;
}

Transform *RigidBody::getPhysicsTransform()
{
    return getPhysicsTransform_Normal();
}

btTransform *RigidBody::getTransform_RP3D()
{
    GameObject *o = getOwner();
    return new btTransform(
        Math::convert(Math::eulerToQuaternion(o->getLocalRotation())),
        Math::convert(o->getGlobalPosition()));
}

Transform *RigidBody::getTransform_Normal()
{
    return getOwner()->getTransform();
}

btTransform *RigidBody::getPhysicsTransform_RP3D()
{
    btTransform t = ((btCollisionObject*) rb)->getWorldTransform();
    return new btTransform(t.getRotation(), t.getOrigin());
}

Transform *RigidBody::getPhysicsTransform_Normal()
{
    return Math::convert_ptr(((btCollisionObject*) rb)->getWorldTransform(), btVector3(1, 1, 1));
}

void RigidBody::syncPhysicsToTransform()
{
    // https://stackoverflow.com/questions/12251199/re-positioning-a-rigid-body-in-bullet-physics
    btTransform *t = new btTransform();
    GameObject *o = getOwner();
    t->setOrigin(Math::convert(o->getGlobalPosition()));
    t->setRotation(Math::convert(Math::eulerToQuaternion(o->getTransform()->getRotation())));
    ((btCollisionObject*) rb)->setWorldTransform(*t);
}

void RigidBody::syncPhysicsToTransform(btTransform *t)
{
    GameObject *o = getOwner();
    t->setOrigin(Math::convert(o->getGlobalPosition()));
    t->setRotation(Math::convert(Math::eulerToQuaternion(o->getTransform()->getRotation())));
    ((btCollisionObject*) rb)->setWorldTransform(*t);
}

void RigidBody::syncTransfromToPhysics()
{
    Transform *pt = getPhysicsTransform();
    Transform *nt = getTransform();
    nt->setPosition(pt->getPosition());
    nt->setRotation(pt->getRotation());
}

void RigidBody::syncTransfromToPhysics(btTransform t)
{
    Transform *nt = getTransform();
    nt->position = Math::convert(t.getOrigin());
    nt->rotation = Math::convert(Math::quaternionToEuler(t.getRotation()));
}

void RigidBody::bindToCollider(Collider *c)
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[RigidBody] start->bindToCollider");
#endif

    GameObject *o = getOwner();

    if (nullptr == o)
    {
        Debug::Error("bindToCollider() called on a RigidBody with no Owner!");
        return;
    }

    tr = new btTransform(
        Math::convert(Math::eulerToQuaternion(o->getLocalRotation())),
        Math::convert(o->getGlobalPosition()));

    btDefaultMotionState* ms = new btDefaultMotionState(*tr);

    btVector3 localInertia(0, 0, 0);
    if (mass != 0)
        c->shape()->calculateLocalInertia(mass, localInertia);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, ms, c->shape(), localInertia);
    rb = new btRigidBody(rbInfo);

    rb->setMassProps(type == RigidBodyType::RB_DYNAMIC ? mass : 0, localInertia);

    // TODO rb->setType(convert(this->type));
    // TODO: maybe something to set here in the collisionShape based on the RigidBodyType???
    // SEE: https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=2943

    Physics::world().addRigidBody(this->rb);

#ifdef DEBUG_PHYSICS
    Debug::Log("[RigidBody] finish->bindToCollider");
    Debug::unindent();
#endif
}

}
