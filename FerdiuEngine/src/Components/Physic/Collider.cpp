
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#include <btBulletDynamicsCommon.h>
#pragma GCC diagnostic pop

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/utils/Math.hpp"
#include "../../../include/Components/Transform.hpp"

namespace FerdiuEngine
{

// --------------------------------- public ----------------------------------
Collider::Collider() : _shape(nullptr) {}

Collider::~Collider()
{
    this->_shape = 0;
    delete this->_shape;
}

bool Collider::isTrigger()
{
    return trigger;
}
void Collider::setTrigger(bool v)
{
    trigger = v;
    // TODO: maybe something to set here in the collisionShape???
    // SEE: https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=2943
}

btCollisionShape* Collider::shape()
{
    return this->_shape;
}

}
