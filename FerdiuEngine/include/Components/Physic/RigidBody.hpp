
#pragma once

#include <glm/glm.hpp>

#include "../../Physics.hpp"
#include "../Component.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class Transform;
class Engine;
class Collider;

class FERDIU_ENGINE_EXPORT RigidBody : public Component
{
public:
    typedef enum FERDIU_ENGINE_EXPORT RigidBodyType
    {
        RB_DYNAMIC,
        RB_KINEMATIC,
        RB_STATIC
    } RigidBodyType;

    FERDIU_ENGINE_EXPORT RigidBody(RigidBodyType type = RB_DYNAMIC, float mass = 1);
    FERDIU_ENGINE_EXPORT ~RigidBody() override;

    // Component
    FERDIU_ENGINE_EXPORT void awake() override;
    FERDIU_ENGINE_EXPORT void start() override;
    FERDIU_ENGINE_EXPORT void physicsUpdatePre() override;
    FERDIU_ENGINE_EXPORT void physicsUpdatePost() override;


    FERDIU_ENGINE_EXPORT glm::vec3 getVelocity();
    FERDIU_ENGINE_EXPORT void setVelocity(glm::vec3 v);
    FERDIU_ENGINE_EXPORT void addVelocity(glm::vec3 v);

    FERDIU_ENGINE_EXPORT float getGravityScale();
    FERDIU_ENGINE_EXPORT void setGravityScale(float v);

    FERDIU_ENGINE_EXPORT float getMass();
    FERDIU_ENGINE_EXPORT void setGMass(float v);

    FERDIU_ENGINE_EXPORT void applyForce(glm::vec3 v);

    FERDIU_ENGINE_EXPORT btRigidBody *getPhysicsRigidBody();

    FERDIU_ENGINE_EXPORT Transform *getPhysicsTransform();
    FERDIU_ENGINE_EXPORT Transform *getTransform();

    FERDIU_ENGINE_EXPORT RigidBodyType getType();
    FERDIU_ENGINE_EXPORT bool isDynamic();
    FERDIU_ENGINE_EXPORT bool isKinematic();
    FERDIU_ENGINE_EXPORT bool isStatic();

    FERDIU_ENGINE_EXPORT void syncTransfromToPhysics();
    FERDIU_ENGINE_EXPORT void syncTransfromToPhysics(btTransform t);
    FERDIU_ENGINE_EXPORT void syncPhysicsToTransform();
    FERDIU_ENGINE_EXPORT void syncPhysicsToTransform(btTransform *t);

    FERDIU_ENGINE_EXPORT void bindToCollider(Collider *c);

private:
    btTransform *tr;
    btRigidBody *rb;

    RigidBodyType type;

    float gravityScale = 1;
    float mass = 1.0;

    btTransform _prevTransform;

    void initRigidBody();

    btTransform *getTransform_RP3D();
    Transform *getTransform_Normal();
    btTransform *getPhysicsTransform_RP3D();
    Transform *getPhysicsTransform_Normal();
};

}
