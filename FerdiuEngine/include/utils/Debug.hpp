
#pragma once

#include <glm/glm.hpp>

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

FERDIU_ENGINE_EXPORT void ftab(size_t tab);
FERDIU_ENGINE_EXPORT void fprint(glm::vec3 *mat);
FERDIU_ENGINE_EXPORT void fprint(glm::vec4 *mat);
FERDIU_ENGINE_EXPORT void fprint(glm::vec3 v);
FERDIU_ENGINE_EXPORT void fprint(glm::vec4 v);
FERDIU_ENGINE_EXPORT void fprint(bool b);

}
