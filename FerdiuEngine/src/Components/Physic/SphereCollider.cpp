
#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/SphereCollider.hpp"

namespace FerdiuEngine
{

SphereCollider::SphereCollider(glm::vec3 center, float radius) : Collider()
{
    setBounds(new Bounds(center, glm::vec3(radius)));
}

bool SphereCollider::checkCollision(Collider *c)
{
    // TODO: implement collision check
    (void) c;
    return false;
}

}
