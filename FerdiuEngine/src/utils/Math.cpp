#include "../../include/utils/Math.hpp"
#include "../../include/Components/Transform.hpp"

#include "../../include/FerdiuEngine_export.h"

namespace FerdiuEngine
{
    namespace Math
    {
        btQuaternion convert(glm::fquat q)
        {
            return btQuaternion(q.x, q.y, q.z, q.w);
        }
        btVector3 convert(glm::vec3 v)
        {
            return btVector3(v.x, v.y, v.z);
        }
        /* TODO: btVector2 convert(glm::vec2 v)
        {
            return btVector2(v.x, v.y);
        } */
        glm::fquat convert(btQuaternion q)
        {
            return glm::fquat(q.x(), q.y(), q.z(), q.w());
        }
        glm::vec3 convert(btVector3 v)
        {
            return glm::vec3(v.x(), v.y(), v.z());
        }
        /* TODO: glm::vec2 convert(btVector2 v)
        {
            return glm::vec2(v.x, v.y);
        } */
        glm::mat4 convert(Transform const& t, glm::mat4 mat)
        {
            // https://gamedev.stackexchange.com/questions/138358/what-is-the-transformation-order-when-using-the-transform-class
            // https://community.khronos.org/t/correct-order-of-transformations/75448/2
            return
                translationMatrix(t.getPosition(), mat)
                *scaleMatrix(t.getScale(), mat)
                *rotationMatrix(t.getRotation(), mat);
        }
        btTransform convert(Transform const& t)
        {
            return btTransform(
                convert(eulerToQuaternion(t.getRotation())),
                convert(t.getPosition())
            );
        }
        Transform convert(btTransform t, glm::vec3 scale)
        {
            return Transform(
                convert(t.getOrigin()),
                scale,
                quaternionToEuler(convert(t.getRotation())));
        }
        Transform convert(btTransform t, btVector3 scale)
        {
            return convert(t, (glm::vec3) convert(scale));
        }
        Transform *convert_ptr(btTransform t, glm::vec3 scale)
        {
            return new Transform(
                convert(t.getOrigin()),
                scale,
                quaternionToEuler(convert(t.getRotation())));
        }
        Transform *convert_ptr(btTransform t, btVector3 scale)
        {
            return convert_ptr(t, (glm::vec3) convert(scale));
        }

        glm::fquat eulerToQuaternion(glm::vec3 rot)
        {
            rot = glm::radians(rot);
            // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            // Abbreviations for the various angular functions
            float cr = cos(rot.x * 0.5);
            float sr = sin(rot.x * 0.5);
            float cp = cos(rot.y * 0.5);
            float sp = sin(rot.y * 0.5);
            float cy = cos(rot.z * 0.5);
            float sy = sin(rot.z * 0.5);

            glm::fquat q;
            q.w = cr * cp * cy + sr * sp * sy;
            q.x = sr * cp * cy - cr * sp * sy;
            q.y = cr * sp * cy + sr * cp * sy;
            q.z = cr * cp * sy - sr * sp * cy;

            return q;
        }
        btQuaternion eulerToQuaternion(btVector3 rot)
        {
            return convert(eulerToQuaternion(convert(rot)));
        }

        glm::vec3 quaternionToEuler(glm::fquat q)
        {
            // https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            glm::vec3 angles = glm::vec3(0);

            // roll (x-axis rotation)
            float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
            float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
            angles.x = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            float sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
            float cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
            angles.y = 2 * std::atan2(sinp, cosp) - M_PI / 2;

            // yaw (z-axis rotation)
            float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
            float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
            angles.z = std::atan2(siny_cosp, cosy_cosp);

            return glm::degrees(angles);
        }
        btVector3 quaternionToEuler(btQuaternion q)
        {
            return convert(quaternionToEuler((convert(q))));
        }

        glm::mat4 rotationMatrix(glm::vec3 rot, glm::mat4 mat)
        {
            glm::mat4 matRX = glm::rotate(mat, glm::radians(rot[0]), glm::vec3(1, 0, 0));
            glm::mat4 matRY = glm::rotate(mat, glm::radians(rot[1]), glm::vec3(0, 1, 0));
            glm::mat4 matRZ = glm::rotate(mat, glm::radians(rot[2]), glm::vec3(0, 0, 1));

            return matRZ * matRY * matRX;
        }
        glm::mat4 scaleMatrix(glm::vec3 scale, glm::mat4 mat)
        {
            return glm::scale(mat, scale);
        }
        glm::mat4 translationMatrix(glm::vec3 translation, glm::mat4 mat)
        {
            return glm::translate(mat, translation);
        }

    }
}
