
#pragma once

#include <glm/glm.hpp>

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

FERDIU_ENGINE_EXPORT void ftab(size_t tab);
FERDIU_ENGINE_EXPORT void fprint(glm::mat3 const& mat);
FERDIU_ENGINE_EXPORT void fprint(glm::mat4 const& mat);
FERDIU_ENGINE_EXPORT void fprint(glm::vec3 const& v);
FERDIU_ENGINE_EXPORT void fprint(glm::vec4 const& v);
FERDIU_ENGINE_EXPORT void fprint(bool b);

}
