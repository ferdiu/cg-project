
#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT SphereCollider : public Collider
{
public:
    FERDIU_ENGINE_EXPORT SphereCollider(glm::vec3 center, float size);

    FERDIU_ENGINE_EXPORT bool checkCollision(Collider *c) override;
private:
    // TODO:
};

}
