
#include <reactphysics3d/reactphysics3d.h>

#include "../../include/utils/Math.hpp"
#include "../../include/Components/Transform.hpp"

#include "../../include/FerdiuEngine_export.h"

namespace FerdiuEngine
{
    namespace Math
    {
        reactphysics3d::Quaternion convert(glm::fquat q)
        {
            return reactphysics3d::Quaternion(q.x, q.y, q.z, q.w);
        }
        reactphysics3d::Vector3 convert(glm::vec3 v)
        {
            return reactphysics3d::Vector3(v.x, v.y, v.z);
        }
        reactphysics3d::Vector2 convert(glm::vec2 v)
        {
            return reactphysics3d::Vector2(v.x, v.y);
        }
        glm::fquat convert(reactphysics3d::Quaternion q)
        {
            return glm::fquat(q.x, q.y, q.z, q.w);
        }
        glm::vec3 convert(reactphysics3d::Vector3 v)
        {
            return glm::vec3(v.x, v.y, v.z);
        }
        glm::vec2 convert(reactphysics3d::Vector2 v)
        {
            return glm::vec2(v.x, v.y);
        }
        glm::mat4 convert(Transform const& t, glm::mat4 mat)
        {
            // https://gamedev.stackexchange.com/questions/138358/what-is-the-transformation-order-when-using-the-transform-class
            // https://community.khronos.org/t/correct-order-of-transformations/75448/2
            return
                translationMatrix(t.getPosition(), mat)
                *scaleMatrix(t.getScale(), mat)
                *rotationMatrix(t.getRotation(), mat);
        }
        reactphysics3d::Transform convert(Transform const& t)
        {
            return reactphysics3d::Transform(
                convert(t.getPosition()),
                convert(eulerToQuaternion(t.getRotation()))
            );
        }
        Transform convert(reactphysics3d::Transform t, glm::vec3 scale)
        {
            return Transform(
                convert(t.getPosition()),
                scale,
                quaternionToEuler(convert(t.getOrientation())));
        }
        Transform convert(reactphysics3d::Transform t, reactphysics3d::Vector3 scale)
        {
            return convert(t, (glm::vec3) convert(scale));
        }

        glm::fquat eulerToQuaternion(glm::vec3 rot)
        {
            glm::fquat qx = glm::angleAxis(rot.x, glm::vec3(1, 0, 0));
            glm::fquat qy = glm::angleAxis(rot.y, glm::vec3(0, 1, 0));
            glm::fquat qz = glm::angleAxis(rot.z, glm::vec3(0, 0, 1));
            return qz * qy * qx;
        }
        reactphysics3d::Quaternion eulerToQuaternion(reactphysics3d::Vector3 rot)
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

            return angles;
        }
        reactphysics3d::Vector3 quaternionToEuler(reactphysics3d::Vector3 q)
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
