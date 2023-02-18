
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

void PrintPhysicsPosition::update()
{
    glm::vec3 p = rb->getPhysicsTransform()->getPosition();
    cout << name << ": (" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
}


