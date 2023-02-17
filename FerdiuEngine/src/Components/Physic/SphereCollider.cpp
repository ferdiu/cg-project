
#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/SphereCollider.hpp"
#include "../../../include/utils/Math.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/Components/Physic/RigidBody.hpp"
#include "../../../include/Components/Transform.hpp"
#include "../../../include/utils/Debug.hpp"

namespace FerdiuEngine
{

SphereCollider::SphereCollider(glm::vec3 center, float radius) : Collider()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[SphereCollider] start->constructor");
#endif

    setBounds(new Bounds(center, glm::vec3(radius)));
    this->shape = Physics::common().createSphereShape(radius);

#ifdef DEBUG_PHYSICS
    Debug::Log("[SphereCollider] finish->constructor");
    Debug::unindent();
#endif
}

bool SphereCollider::checkCollision(Collider *c)
{
    // TODO: implement collision check
    (void) c;
    return false;
}


}
