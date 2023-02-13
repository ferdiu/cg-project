
#pragma once

#include <glm/glm.hpp>
#include "Debug.hpp"

namespace FerdiuEngine
{

// This struct will hold all matrices used in rendering
typedef struct GLMatrices {
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
} GLMatrices;

}
