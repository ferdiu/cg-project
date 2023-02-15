
#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "../FerdiuEngine_export.h"

#ifndef DEBUG
// disable all debugging if DEBUG is not enabled
#undef DEBUG_VERBOSE
#endif

#ifndef DEBUG_VERBOSE
#undef DEBUG_RENDERING
#undef DEBUG_MATRICES
#endif

namespace FerdiuEngine
{

FERDIU_ENGINE_EXPORT void fdoublespace(size_t s);
FERDIU_ENGINE_EXPORT void ftab(size_t tab);
FERDIU_ENGINE_EXPORT void fprint(glm::mat3 const& mat);
FERDIU_ENGINE_EXPORT void fprint(glm::mat4 const& mat);
FERDIU_ENGINE_EXPORT void fprint(glm::vec3 const& v);
FERDIU_ENGINE_EXPORT void fprint(glm::vec4 const& v);
FERDIU_ENGINE_EXPORT void fprint(bool b);

namespace Debug
{
    FERDIU_ENGINE_EXPORT void indent();
    FERDIU_ENGINE_EXPORT void unindent();

    FERDIU_ENGINE_EXPORT void Log(std::string message = "");
    FERDIU_ENGINE_EXPORT void Warn(std::string message = "");
    FERDIU_ENGINE_EXPORT void Error(std::string message = "");
};

}
