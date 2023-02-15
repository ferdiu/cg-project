
#pragma once

#include <glm/glm.hpp>
#include "Debug.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

// This struct will hold all matrices used in rendering
typedef struct FERDIU_ENGINE_EXPORT GLMatrices {
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
} GLMatrices;

class FERDIU_ENGINE_EXPORT GLMatrix
{
public:
    FERDIU_ENGINE_EXPORT static void copy(glm::mat4& dest, glm::mat4 const& src);
    FERDIU_ENGINE_EXPORT static void copy(GLMatrices& dest, GLMatrices const& src);
};

}
