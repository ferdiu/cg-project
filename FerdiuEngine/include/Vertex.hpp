
#pragma once

namespace FerdiuEngine
{

#include <glm/glm.hpp>

typedef struct Vertex {
    glm::vec4 coords;
    glm::vec3 normal;
    glm::vec2 tex;
} Vertex;

}
