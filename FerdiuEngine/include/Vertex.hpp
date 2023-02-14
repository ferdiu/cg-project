
#pragma once

#include <glm/glm.hpp>

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

typedef struct FERDIU_ENGINE_EXPORT Vertex {
    glm::vec4 coords;
    glm::vec3 normal;
    glm::vec2 tex;
} Vertex;

}
