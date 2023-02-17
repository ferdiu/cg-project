
#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>
#include "Collider.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT SphereCollider : public Collider
{
public:
    FERDIU_ENGINE_EXPORT SphereCollider(glm::vec3 center, float size);

    FERDIU_ENGINE_EXPORT bool checkCollision(Collider *c) override;
};

}
