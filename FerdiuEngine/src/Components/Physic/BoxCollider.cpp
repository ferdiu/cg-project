
#include <glm/glm.hpp>

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/BoxCollider.hpp"
#include "../../../include/GameObject.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/utils/Math.hpp"

namespace FerdiuEngine
{

BoxCollider::BoxCollider(glm::vec3 center, glm::vec3 size) : Collider()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[BoxCollider] start->constructor");
#endif

    setBounds(new Bounds(center, size));
    this->shape = Physics::common().createBoxShape(Math::convert(size));

#ifdef DEBUG_PHYSICS
    Debug::Log("[BoxCollider] finish->constructor");
    Debug::unindent();
#endif
}

bool BoxCollider::checkCollision(Collider *c)
{
    // TODO: implement collision check
    (void) c;
    return false;
}

}
