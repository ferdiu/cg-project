
#include <glm/glm.hpp>

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/BoxCollider.hpp"
#include "../../../include/Physics.hpp"
#include "../../../include/utils/Math.hpp"

namespace FerdiuEngine
{

BoxCollider::BoxCollider(glm::vec3 center, glm::vec3 size) : Collider()
{
    setBounds(new Bounds(center, size));
    this->shape = Physics::common().createBoxShape(Math::convert(size));
}

bool BoxCollider::checkCollision(Collider *c)
{
    // TODO: implement collision check
    (void) c;
    return false;
}

}
