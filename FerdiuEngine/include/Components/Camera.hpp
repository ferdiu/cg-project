
#pragma once

#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Component.hpp"
#include "../utils/GLMatricesStack.hpp"

namespace FerdiuEngine
{

class Camera : Component
{
public:
    enum Mode { PERSPECTIVE, ORTHOGRAPHIC };

    Camera(float left, float right, float bottom, float top, float near, float far, Mode cameraMode = PERSPECTIVE);

    // camera modes
    void setFrustum(float left, float right, float bottom, float top, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top, float near, float far);
    Mode getMode();

    // current
    static Camera * getCurrent();
    void setCurrent();
    static void setCurrent(Camera *camera);

    // matrices getters
    glm::mat4 *getPorjectionMatrix();
    glm::mat4 *getViewMatrix();
    glm::mat4 *getModelMatrix();

    void clear();

private:
    static Camera* current;

    MatricesStack stack;
    Mode mode = PERSPECTIVE;
    glm::vec3 clearColor = glm::vec3(0);

    struct CameraModeParams
    {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    } params = { -1, 1, -1, 1, 50, 1000 };
};

}
