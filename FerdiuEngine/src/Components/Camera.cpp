
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "../../include/Components/Camera.hpp"
#include "../../include/Components/Transform.hpp"
#include "../../include/utils/GLMatricesStack.hpp"
#include "../../include/GameObject.hpp"
#include "../../include/utils/GLMatrices.hpp"

namespace FerdiuEngine
{

Camera::Camera(float left, float right, float bottom, float top, float near, float far, Mode cameraMode)
{
    this->stack = MatricesStack();
    this->mode = cameraMode;
    this->params = { left, right, bottom, top, near, far };
}

Camera::~Camera()
{
    // TODO: DESTORY
}

// camera modes
void Camera::setFrustum(float left, float right, float bottom, float top, float near, float far)
{
    this->mode = PERSPECTIVE;
    setParametes(left, right, bottom, top, near, far);
}
void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far)
{
    this->mode = ORTHOGRAPHIC;
    setParametes(left, right, bottom, top, near, far);
}
Camera::Mode Camera::getMode()
{
    return mode;
}
void Camera::setParametes(float left, float right, float bottom, float top, float near, float far)
{
    this->params = { left, right, bottom, top, near, far };
}
CameraModeParams const& Camera::getParameters() const
{
    return params;
}
void Camera::setParameterMults(float left, float right, float bottom, float top, float near, float far)
{
    this->paramsMult = { left, right, bottom, top, near, far };
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
                params.left * paramsMult.left, params.right * paramsMult.right,
                params.bottom * paramsMult.bottom, params.top * paramsMult.top,
                params.near * paramsMult.near, params.far * paramsMult.far);
            break;
        case ORTHOGRAPHIC:
            proj = glm::ortho(
                params.left * paramsMult.left, params.right * paramsMult.right,
                params.bottom * paramsMult.bottom, params.top * paramsMult.top,
                params.near * paramsMult.near, params.far * paramsMult.far);
            break;
    }
    this->stack.setPorjectionMatrix(proj);
#ifdef DEBUG_MATRICES
    printf("--- proj ---\n");
    fprint(*getPorjectionMatrix());
#endif
}
void Camera::updateViewMatrix()
{
#ifdef DEBUG
    if (nullptr == this->getOwner())
        std::cerr << "warning: a Camera has not been assigned to any object!" << std::endl;
#endif
    // apply transormation
    glm::mat4 *m = new glm::mat4(1);
    getOwner()->getTransform()->apply(*m);
    stack.setViewMatrix(*m);

#ifdef DEBUG_MATRICES
    printf("--- view ---\n");
    fprint(*getViewMatrix());
#endif
}

void Camera::updateModelMatrix(glm::mat4 const& m)
{
#ifdef DEBUG
    if (nullptr == this->getOwner())
        std::cerr << "warning: a Camera has not been assigned to any object!" << std::endl;
#endif
    stack.setModelMatrix(m * (*getModelMatrix()));
}

void Camera::clear()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("[Camera] clear");
    Debug::unindent();
#endif

    glClearColor(this->clearColor[0], this->clearColor[1], this->clearColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::setClearColor(glm::vec3 color)
{
    this->clearColor[0] = color[0];
    this->clearColor[1] = color[1];
    this->clearColor[2] = color[2];
}

glm::vec3 Camera::getClearColor()
{
    return this->clearColor;
}

void Camera::lookAt(glm::vec3 pos, glm::vec3 up)
{
    Transform *t = this->getOwner()->getTransform();
    glm::mat4 *la = new glm::mat4(glm::lookAt(t->getPosition(), pos, up));
    stack.setViewMatrix(*la);

    // https://community.khronos.org/t/determining-angles-from-modelview-matrix/55809
    // TODO: update angles https://stackoverflow.com/questions/15022630/how-to-calculate-the-angle-from-rotation-matrix
    // t->setRotation(glm::vec3(
    //     glm::euler() * atan2((*m)[3][2], (*m)[3][3]),
    //     glm::euler() * atan2(-(*m)[3][1], sqrt((*m)[3][2]*(*m)[3][2] + (*m)[3][3]*(*m)[3][3])),
    //     glm::euler() * atan2((*m)[2][1], (*m)[1][1])
    // ));
}
void Camera::lookAt(Transform const& pos, glm::vec3 up)
{
    lookAt(pos.getPosition(), up);
}
void Camera::lookAt(GameObject const& pos, glm::vec3 up)
{
    lookAt(pos.getLocalPosition(), up);
}
void Camera::lookAt(Component const& pos, glm::vec3 up)
{
    lookAt(pos.getOwner().getLocalPosition(), up);
}

Camera* Camera::current = new Camera(-5, 5, -5, 5, 5, 1000);

}
