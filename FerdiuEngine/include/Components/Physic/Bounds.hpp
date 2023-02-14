
#pragma once

#include <glm/glm.hpp>
#include "../Component.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Bounds
{
public:
    FERDIU_ENGINE_EXPORT Bounds(glm::vec3 center = glm::vec3(0), glm::vec3 size = glm::vec3(1));

    FERDIU_ENGINE_EXPORT glm::vec3 getCenter();
    FERDIU_ENGINE_EXPORT glm::vec3 getSize();

    FERDIU_ENGINE_EXPORT glm::vec3 getExtents();
    FERDIU_ENGINE_EXPORT glm::vec3 getMin();
    FERDIU_ENGINE_EXPORT glm::vec3 getMax();

protected:
    virtual void setCenter(glm::vec3 v);
    virtual void setSize(glm::vec3 v);

    void setExtentes(glm::vec3 v);
    void setMin(glm::vec3 v);
    void setMax(glm::vec3 v);

private:
    glm::vec3 center = glm::vec3(0, 0, 0);
    glm::vec3 size = glm::vec3(1, 1, 1);

    glm::vec3 extents;
    glm::vec3 min;
    glm::vec3 max;
};

}
