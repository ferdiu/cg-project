
#pragma once

#include <glm/glm.hpp>

#include "Collider.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT SphereCollider : public Collider
{
public:
    FERDIU_ENGINE_EXPORT SphereCollider(float radius);
};

}
