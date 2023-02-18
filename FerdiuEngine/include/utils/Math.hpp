
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
        FERDIU_ENGINE_EXPORT rp3d::Quaternion convert(glm::fquat q);
        FERDIU_ENGINE_EXPORT rp3d::Vector3 convert(glm::vec3 v);
        FERDIU_ENGINE_EXPORT rp3d::Vector2 convert(glm::vec2 v);
        FERDIU_ENGINE_EXPORT glm::fquat convert(rp3d::Quaternion q);
        FERDIU_ENGINE_EXPORT glm::vec3 convert(rp3d::Vector3 v);
        FERDIU_ENGINE_EXPORT glm::vec2 convert(rp3d::Vector2 v);
        FERDIU_ENGINE_EXPORT glm::mat4 convert(Transform const& t, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT rp3d::Transform convert(Transform const& t);
        FERDIU_ENGINE_EXPORT Transform convert(rp3d::Transform t, glm::vec3 scale);
        FERDIU_ENGINE_EXPORT Transform convert(rp3d::Transform t, rp3d::Vector3 scale);

        FERDIU_ENGINE_EXPORT glm::fquat eulerToQuaternion(glm::vec3 rot);
        FERDIU_ENGINE_EXPORT rp3d::Quaternion eulerToQuaternion(rp3d::Vector3 rot);

        reactphysics3d::Vector3 quaternionToEuler(reactphysics3d::Quaternion q);
        FERDIU_ENGINE_EXPORT glm::vec3 quaternionToEuler(glm::fquat q);

        FERDIU_ENGINE_EXPORT glm::mat4 rotationMatrix(glm::vec3 rot, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 scaleMatrix(glm::vec3 scale, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 translationMatrix(glm::vec3 translation, glm::mat4 mat = glm::mat4(1));
    }
}
