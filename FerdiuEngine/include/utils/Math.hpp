
#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>
#include <glm/gtc/quaternion.hpp>

#include "../Components/Transform.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{
    namespace Math
    {
        FERDIU_ENGINE_EXPORT reactphysics3d::Quaternion convert(glm::fquat q);
        FERDIU_ENGINE_EXPORT reactphysics3d::Vector3 convert(glm::vec3 v);
        FERDIU_ENGINE_EXPORT reactphysics3d::Vector2 convert(glm::vec2 v);
        FERDIU_ENGINE_EXPORT glm::fquat convert(reactphysics3d::Quaternion q);
        FERDIU_ENGINE_EXPORT glm::vec3 convert(reactphysics3d::Vector3 v);
        FERDIU_ENGINE_EXPORT glm::vec2 convert(reactphysics3d::Vector2 v);
        FERDIU_ENGINE_EXPORT glm::mat4 convert(Transform const& t, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT reactphysics3d::Transform convert(Transform const& t);
        FERDIU_ENGINE_EXPORT Transform convert(reactphysics3d::Transform t, glm::vec3 scale);
        FERDIU_ENGINE_EXPORT Transform convert(reactphysics3d::Transform t, reactphysics3d::Vector3 scale);

        FERDIU_ENGINE_EXPORT glm::fquat eulerToQuaternion(glm::vec3 rot);
        FERDIU_ENGINE_EXPORT reactphysics3d::Quaternion eulerToQuaternion(reactphysics3d::Vector3 rot);

        FERDIU_ENGINE_EXPORT reactphysics3d::Vector3 quaternionToEuler(reactphysics3d::Vector3 q);
        FERDIU_ENGINE_EXPORT glm::vec3 quaternionToEuler(glm::fquat q);

        FERDIU_ENGINE_EXPORT glm::mat4 rotationMatrix(glm::vec3 rot, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 scaleMatrix(glm::vec3 scale, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 translationMatrix(glm::vec3 translation, glm::mat4 mat = glm::mat4(1));
    }
}
