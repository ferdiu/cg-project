
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../include/Components/Camera.hpp"
#include "../../include/Components/Transform.hpp"
#include "../../include/utils/GLMatricesStack.hpp"
#include "utils/GLMatrices.hpp"

namespace FerdiuEngine
{

void applyTransoform(glm::mat4& mat, Transform const& t)
{
    glm::mat4 *tmp = new glm::mat4(1);
    GLMatrix::copy(*tmp, mat);

    glm::vec3 rot = t.getRotation();
    // TODO: completely arbitrary order of transformations!!! but good enough for now
    *tmp = glm::translate(*tmp, t.getPosition());
    *tmp = glm::scale(*tmp, t.getScale());
    // TODO: even uglyer!!!
    *tmp = glm::rotate(*tmp, glm::radians(rot[0]), glm::vec3(1.0, 0.0, 0.0));
    *tmp = glm::rotate(*tmp, glm::radians(rot[1]), glm::vec3(0.0, 1.0, 0.0));
    *tmp = glm::rotate(*tmp, glm::radians(rot[2]), glm::vec3(0.0, 0.0, 1.0));

    GLMatrix::copy(mat, *tmp);
}

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

void Camera::updateProjectionMatrix()
{
    glm::mat4 proj = glm::mat4(1);
    switch (this->mode)
    {
        case PERSPECTIVE:
            proj = glm::frustum(
                params.left, params.right,
                params.bottom, params.top,
                params.near, params.far);
            break;
        case ORTHOGRAPHIC:
            proj = glm::ortho(
                params.left, params.right,
                params.bottom, params.top,
                params.near, params.far);
            break;
    }
    this->stack.setPorjectionMatrix(proj);
}
void Camera::updateViewMatrix(Transform const& t)
{
#ifdef DEBUG
    if (nullptr == this->getOwner())
        std::cerr << "warning: a Camera has not been assigned to any object!" << std::endl;
#endif
    // apply transormation
    glm::mat4 *m = new glm::mat4(1);
    applyTransoform(*m, t);
    stack.setViewMatrix(*m);
}

glm::mat4 *Camera::applyModelMatrix(Transform const& t)
{
    // apply transormation
    glm::mat4 *m = getModelMatrix();
    applyTransoform(*m, t);
    stack.setModelMatrix(*m);

    // copy result in a new pointer and return it
    glm::mat4 *res = new glm::mat4(1);
    GLMatrix::copy(*res, *m);
    return res;
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

void Camera::lookAt(Transform& camera, glm::vec3 pos, glm::vec3 up)
{
    glm::mat4 *la = new glm::mat4(glm::lookAt(camera.getPosition(), pos, up));

    glm::mat4 *m = new glm::mat4(1);
    GLMatrix::copy(*m, *la);
    stack.setViewMatrix(*m);
}
void Camera::lookAt(Transform& camera, Transform const& pos, glm::vec3 up)
{
    lookAt(camera, pos.getPosition(), up);
}

Camera* Camera::current = new Camera(-5, 5, -5, 5, 5, 1000);

}
