
#include "../include/LookAtCamera.hpp"
#include "utils/Debug.hpp"

using namespace FerdiuEngine;

LookAtCamera::LookAtCamera(GameObject *target, Camera *c, glm::vec3 up)
{
    this->camera = c;
    this->target = target->getTransform();
    this->up = up;
}
LookAtCamera::LookAtCamera(Transform *target, Camera *c, glm::vec3 up)
{
    this->camera = c;
    this->target = target;
    this->up = up;
}

void LookAtCamera::awake()
{
#ifdef DEBUG
    if (nullptr == this->camera)
    {
        Debug::indent();
        Debug::Warn("Camera not setted in constructor of LookAtCamera: falling back to current");
        Debug::Warn("Consider adding it in your script because this will not happen in non-debug build!");
        Debug::unindent();
        this->camera = Camera::getCurrent();
    }
#endif
    Component::awake();
}

void LookAtCamera::update()
{
    camera->lookAt(*target, up);
}

