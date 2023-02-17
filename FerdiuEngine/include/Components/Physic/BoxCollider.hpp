
#pragma once

#include <glm/glm.hpp>
#include "Collider.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT BoxCollider : public Collider
{
public:
    FERDIU_ENGINE_EXPORT BoxCollider(glm::vec3 center, glm::vec3 size);

    FERDIU_ENGINE_EXPORT bool checkCollision(Collider *c) override;
};

}
