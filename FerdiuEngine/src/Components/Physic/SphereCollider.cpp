
#include <glm/glm.hpp>

#include "../../../include/utils/Math.hpp"
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/SphereCollider.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/Components/Physic/RigidBody.hpp"
#include "../../../include/Components/Transform.hpp"
#include "../../../include/utils/Debug.hpp"

namespace FerdiuEngine
{

SphereCollider::SphereCollider(float radius) : Collider()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[SphereCollider] start->constructor");
#endif

    this->_shape = new btSphereShape(radius);

#ifdef DEBUG_PHYSICS
    Debug::Log("[SphereCollider] finish->constructor");
    Debug::unindent();
#endif
}

}
