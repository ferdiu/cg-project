
#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#include <btBulletDynamicsCommon.h>
#pragma GCC diagnostic pop

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../Physics.hpp"
#include "../Components/Transform.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{
    namespace Math
    {
        FERDIU_ENGINE_EXPORT btQuaternion convert(glm::fquat q);
        FERDIU_ENGINE_EXPORT btVector3 convert(glm::vec3 v);
        // TODO: FERDIU_ENGINE_EXPORT rp3d::Vector2 convert(glm::vec2 v);
        FERDIU_ENGINE_EXPORT glm::fquat convert(btQuaternion q);
        FERDIU_ENGINE_EXPORT glm::vec3 convert(btVector3 v);
        // TODO: FERDIU_ENGINE_EXPORT glm::vec2 convert(rp3d::Vector2 v);
        FERDIU_ENGINE_EXPORT glm::mat4 convert(Transform const& t, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT btTransform convert(Transform const& t);
        FERDIU_ENGINE_EXPORT Transform convert(btTransform t, glm::vec3 scale = glm::vec3(1));
        FERDIU_ENGINE_EXPORT Transform convert(btTransform t, btVector3 scale = btVector3(1, 1, 1));
        FERDIU_ENGINE_EXPORT Transform *convert_ptr(btTransform t, glm::vec3 scale = glm::vec3(1));
        FERDIU_ENGINE_EXPORT Transform *convert_ptr(btTransform t, btVector3 scale = btVector3(1, 1, 1));

        FERDIU_ENGINE_EXPORT glm::fquat eulerToQuaternion(glm::vec3 rot);
        FERDIU_ENGINE_EXPORT btQuaternion eulerToQuaternion(btVector3 rot);

        btVector3 quaternionToEuler(btQuaternion q);
        FERDIU_ENGINE_EXPORT glm::vec3 quaternionToEuler(glm::fquat q);

        FERDIU_ENGINE_EXPORT glm::mat4 rotationMatrix(glm::vec3 rot, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 scaleMatrix(glm::vec3 scale, glm::mat4 mat = glm::mat4(1));
        FERDIU_ENGINE_EXPORT glm::mat4 translationMatrix(glm::vec3 translation, glm::mat4 mat = glm::mat4(1));
    }
}
