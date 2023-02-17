
#pragma once

#include <glm/glm.hpp>
#include "Component.hpp"
#include "../utils/GLMatrices.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Transform : public Component
{
public:
    // constructor
    FERDIU_ENGINE_EXPORT Transform(glm::vec3 pos = glm::vec3(0), glm::vec3 scale = glm::vec3(1), glm::vec3 rot = glm::vec3(0));

    // ------- GETTERS-SETTERS -------
    // position
    FERDIU_ENGINE_EXPORT glm::vec3 getPosition() const;
    FERDIU_ENGINE_EXPORT void setPosition(glm::vec3 v);

    // scale
    FERDIU_ENGINE_EXPORT glm::vec3 getScale() const;
    FERDIU_ENGINE_EXPORT void setScale(glm::vec3 v);

    // rotation
    FERDIU_ENGINE_EXPORT glm::vec3 getRotation() const;
    FERDIU_ENGINE_EXPORT void setRotation(glm::vec3 v);

    // model matrix
    FERDIU_ENGINE_EXPORT glm::mat4 getModelMatrix() const;

    FERDIU_ENGINE_EXPORT static void apply(Transform const& t, glm::mat4& mat);
    FERDIU_ENGINE_EXPORT void apply(glm::mat4& mat) const;

    FERDIU_ENGINE_EXPORT void copy(Transform const& t);
    FERDIU_ENGINE_EXPORT void copy(Transform *t);

private:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
    // TODO: should really use quaternion for this!
    glm::vec3 rotation = glm::vec3(0);
};

}
