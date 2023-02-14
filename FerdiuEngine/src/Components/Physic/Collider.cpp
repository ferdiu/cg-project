
#include <glm/glm.hpp>

#include "../../../include/Components/Physic/Collider.hpp"
#include "../../../include/Components/Physic/Bounds.hpp"

namespace FerdiuEngine
{

// --------------------------------- public ----------------------------------
Collider::Collider()
{
    this->bounds = nullptr;
}

bool Collider::isTrigger()
{
    return trigger;
}
void Collider::setTrigger(bool v)
{
    trigger = v;
}

Bounds *Collider::getBounds()
{
    return bounds;
}

// --------------------------------- protected -------------------------------
void Collider::setBounds(Bounds *b)
{
    bounds = b;
}

}
