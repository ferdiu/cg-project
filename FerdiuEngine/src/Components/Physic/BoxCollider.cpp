
#include <glm/glm.hpp>
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/BoxCollider.hpp"

namespace FerdiuEngine
{

BoxCollider::BoxCollider(glm::vec3 center, glm::vec3 size)
{
    setBounds(Bounds(center, size));
}

bool BoxCollider::checkCollision(Collider c)
{
    // TODO: implement collision check
    (void) c;
    return false;
}

}
