
#pragma once

#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Component.hpp"
#include "../utils/GLMatricesStack.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Camera : Component
{
public:
    enum FERDIU_ENGINE_EXPORT Mode { PERSPECTIVE, ORTHOGRAPHIC };

    FERDIU_ENGINE_EXPORT Camera(float left, float right, float bottom, float top, float near, float far, Mode cameraMode = PERSPECTIVE);

    // camera modes
    FERDIU_ENGINE_EXPORT void setFrustum(float left, float right, float bottom, float top, float near, float far);
    FERDIU_ENGINE_EXPORT void setOrthographic(float left, float right, float bottom, float top, float near, float far);
    FERDIU_ENGINE_EXPORT Mode getMode();

    // current
    FERDIU_ENGINE_EXPORT static Camera *getCurrent();
    FERDIU_ENGINE_EXPORT void setCurrent();
    FERDIU_ENGINE_EXPORT static void setCurrent(Camera *camera);

    // matrices getters
    FERDIU_ENGINE_EXPORT glm::mat4 *getPorjectionMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getViewMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getModelMatrix();

    FERDIU_ENGINE_EXPORT void clear();

private:
    FERDIU_ENGINE_EXPORT static Camera *current;

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
