
#include <iostream>
#include <cstring>
#include <glm/glm.hpp>

#include "../include/Ball.hpp"
#include "../include/Board.hpp"
#include "../include/Ball.hpp"
#include "../include/DefaultShader.hpp"
#include "Components/Physic/RigidBody.hpp"
#include "Material.hpp"

using namespace std;
using namespace glm;
using namespace FerdiuEngine;

Ball::Ball(Board *b) : b(b) {}

void Ball::awake()
{
    if (!getOwner()->rigidbody().has_value())
    {
        Debug::Error("No RigidBody found on object " + getOwner()->getName());
        return;
    }

    rb = getOwner()->rigidbody().value();
    rb->getPhysicsRigidBody()->enableGravity(true);
    rb->getPhysicsRigidBody()->setIsAllowedToSleep(false);
}

void Ball::update()
{
    vec2 tmp = b->getTilt() * velocityScale;
    rb->addVelocity(vec3(-tmp.x, 0, -tmp.y));

    vec3 v = rb->getVelocity();
    vec3 vv = getOwner()->getParentGlobalPosition();
    vec3 phyPos = rb->getPhysicsTransform()->getPosition() + (vv);
    vec3 norPos = rb->getOwner()->getGlobalPosition();
    cout << "################################" << endl;
    cout << "velocity: (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    cout << "position (phy): (" << phyPos.x << ", " << phyPos.y << ", " << phyPos.z << ")" << endl;
    cout << "position (tr): (" << norPos.x << ", " << norPos.y << ", " << norPos.z << ")" << endl;
    cout << "################################" << endl;

    if (getOwner()->getGlobalPosition().y < b->getRoot()->getGlobalPosition().y - 3)
        reset();
}

void Ball::reset()
{
    rb->setVelocity(glm::vec3(0, 0, 0));
    rb->getOwner()->setGlobalPosition(b->getStartPositionGlobal());
}
