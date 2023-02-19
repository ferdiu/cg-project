
#include <iostream>
#include <cstring>
#include <glm/glm.hpp>

#include "../include/Ball.hpp"
#include "../include/Board.hpp"
#include "../include/Ball.hpp"
#include "../include/DefaultShader.hpp"

using namespace std;
using namespace glm;
using namespace FerdiuEngine;

Ball::Ball(Board *b) : b(b) {}
Ball::~Ball() {}

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
    rb->getPhysicsRigidBody()->setLinearLockAxisFactor(rp3d::Vector3(1, 0, 1));
    reset();
}

void Ball::fixedUpdate()
{
    vec2 tmp = b->getTilt() * velocityScale;
    rb->addVelocity(vec3(-tmp.x, 0, -tmp.y));

    if (getOwner()->getGlobalPosition().y < b->getRoot()->getGlobalPosition().y - 5)
        reset();
}

void Ball::reset()
{
    rb->setVelocity(glm::vec3(0, 0, 0));
    rb->getOwner()->setGlobalPosition(b->getStartPositionGlobal() + glm::vec3(0, 0, 0));
}
