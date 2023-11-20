
#include "../include/PrintPhysicsPosition.hpp"

using namespace FerdiuEngine;
using namespace std;

void PrintPhysicsPosition::awake()
{
    rb = getOwner()->rigidbody().value();
    name = getOwner()->getName();
    Component::awake();
}

void PrintPhysicsPosition::fixedUpdate()
{
    glm::vec3 p = rb->getPhysicsTransform()->getPosition();
    glm::vec3 v = rb->getVelocity();
    glm::vec3 f = Math::convert(rb->getPhysicsRigidBody()->getTotalForce());
    cout << name << " (pos): (" << p.x << ", " << p.y << ", " << p.z << ")" <<
        " (vel): (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
    cout << name << " (for): (" << f.x << ", " << f.y << ", " << f.z << ")" << endl;
}
