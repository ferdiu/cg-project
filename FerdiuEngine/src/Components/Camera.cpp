
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "../../include/Components/Camera.hpp"
#include "../../include/utils/GLMatricesStack.hpp"

namespace FerdiuEngine
{

Camera::Camera(float left, float right, float bottom, float top, float near, float far, Mode cameraMode)
{
    this->stack = MatricesStack();
    this->mode = cameraMode;
    this->params = { left, right, bottom, top, near, far };
}

// camera modes
void Camera::setFrustum(float left, float right, float bottom, float top, float near, float far)
{
    this->mode = PERSPECTIVE;
    this->params = { left, right, bottom, top, near, far };
}
void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far)
{
    this->mode = ORTHOGRAPHIC;
    this->params = { left, right, bottom, top, near, far };
}
Camera::Mode Camera::getMode()
{
    return mode;
}

// current
Camera * Camera::getCurrent()
{
    return current;
}
void Camera::setCurrent()
{
    current = this;
}
void Camera::setCurrent(Camera *camera)
{
    current = camera;
}

// matrices getters
glm::mat4 *Camera::getPorjectionMatrix()
{
    return this->stack.getPorjectionMatrix();
}
glm::mat4 *Camera::getViewMatrix()
{
    return this->stack.getViewMatrix();
}
glm::mat4 *Camera::getModelMatrix()
{
    return this->stack.getModelMatrix();
}

void Camera::clear()
{
    glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], 1.0);
}

}
