
#include "../include/PrintPhysicsPosition.hpp"

#include <reactphysics3d/reactphysics3d.h>

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
    // glm::vec3 p = rb->getPhysicsTransform()->getPosition();
    // glm::vec3 r = rb->getPhysicsTransform()->getRotation();
    // if (p.x >= 16 && p.x <= 18 && p.z >= -11 && p.z <= -9)
    // {
    //     cout << name << " (pos): (" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
    //     cout << name << " (rot): (" << r.x << ", " << r.y << ", " << r.z << ")" << endl;
    // }
}


