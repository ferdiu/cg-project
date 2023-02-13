
#include <glm/glm.hpp>

#include "../../../include/Components/Component.hpp"
#include "../../../include/Components/Physic/Bounds.hpp"

namespace FerdiuEngine
{

// ------------------------- public ---------------------------------------
Bounds::Bounds(glm::vec3 center, glm::vec3 size)
{
    setCenter(center);
    setSize(size);
}

glm::vec3 Bounds::getCenter()
{
    return center;
}
glm::vec3 Bounds::getSize()
{
    return size;
}

glm::vec3 Bounds::getExtents()
{
    return extents;
}
glm::vec3 Bounds::getMin()
{
    return min;
}
glm::vec3 Bounds::getMax()
{
    return max;
}

// ------------------------- protected ---------------------------------------
void Bounds::setCenter(glm::vec3 v)
{
    center = v;
}
void Bounds::setSize(glm::vec3 v)
{
    size = v;
}

void Bounds::setExtentes(glm::vec3 v)
{
    extents = v;
}
void Bounds::setMin(glm::vec3 v)
{
    min = v;
}
void Bounds::setMax(glm::vec3 v)
{
    max = v;
}

}
