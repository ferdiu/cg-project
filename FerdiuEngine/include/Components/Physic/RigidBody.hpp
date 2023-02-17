
#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "../../Physics.hpp"
#include "Collider.hpp"
#include "../Component.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class Transform;

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

    // Component
    FERDIU_ENGINE_EXPORT void awake() override;
    FERDIU_ENGINE_EXPORT void start() override;
    FERDIU_ENGINE_EXPORT void update() override;

    FERDIU_ENGINE_EXPORT glm::vec3 getVelocity();
    FERDIU_ENGINE_EXPORT void setVelocity(glm::vec3 v);
    FERDIU_ENGINE_EXPORT void addVelocity(glm::vec3 v);

    FERDIU_ENGINE_EXPORT float getGravityScale();
    FERDIU_ENGINE_EXPORT void setGravityScale(float v);

    FERDIU_ENGINE_EXPORT float getMass();
    FERDIU_ENGINE_EXPORT void setGMass(float v);

    FERDIU_ENGINE_EXPORT void applyForce(glm::vec3 v);

    FERDIU_ENGINE_EXPORT rp3d::RigidBody *getPhysicsRigidBody();

    FERDIU_ENGINE_EXPORT Transform *getPhysicsTransform();
    FERDIU_ENGINE_EXPORT Transform *getTransform();

    FERDIU_ENGINE_EXPORT void syncTransfromToPhysics();
    FERDIU_ENGINE_EXPORT void syncPhysicsToTransform();

private:
    rp3d::Transform *tr;
    rp3d::RigidBody *rb;

    RigidBodyType type;

    float gravityScale = 1;
    float mass = 1.0;

    void initRigidBody();

    rp3d::Transform *getTransform_RP3D();
    Transform *getTransform_Normal();
    rp3d::Transform *getPhysicsTransform_RP3D();
    Transform *getPhysicsTransform_Normal();
};

}
