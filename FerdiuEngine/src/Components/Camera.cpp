
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../../include/Components/Camera.hpp"
#include "../../include/Components/Transform.hpp"
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
Camera *Camera::getCurrent()
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

void Camera::pushMatrices()
{
    this->stack.push();
}
void Camera::popMatrices()
{
    this->stack.pop();
}

void Camera::applyModelMatrix(Transform *t)
{
    glm::mat4 *m = getModelMatrix();
    glm::vec3 r = t->getRotation();

    // TODO: completely arbitrary order of transformations!!! but good enough for now
    *m = glm::translate(*m, t->getPosition());
    *m = glm::scale(*m, t->getScale());
    // TODO: uglyer!!!
    *m = glm::rotate(*m, glm::radians(r[0]), glm::vec3(1.0, 0.0, 0.0));
    *m = glm::rotate(*m, glm::radians(r[1]), glm::vec3(0.0, 1.0, 0.0));
    *m = glm::rotate(*m, glm::radians(r[2]), glm::vec3(0.0, 0.0, 1.0));

    stack.setModelMatrix(*m);
}

void Camera::clear()
{
    glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::setClearColor(glm::vec3 color)
{
    this->clearColor[0] = color[0];
    this->clearColor[1] = color[1];
    this->clearColor[2] = color[2];

    if (Camera::getCurrent() == this)
        glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], 1.0);
}

glm::vec3 Camera::getClearColor()
{
    return this->clearColor;
}

Camera* Camera::current = new Camera(-5, 5, -5, 5, 5, 1000);

}
