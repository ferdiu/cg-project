
#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

namespace FerdiuEngine
{

class BoxCollider : Collider
{
public:
    BoxCollider(glm::vec3 center, glm::vec3 size);

    bool checkCollision(Collider c) override;
private:
    // TODO:
};

}
