
#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Component.hpp"
#include "Transform.hpp"
#include "../GameObject.hpp"
#include "../utils/GLMatricesStack.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

typedef struct FERDIU_ENGINE_EXPORT CameraModeParams
{
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
} CameraModeParams;

class FERDIU_ENGINE_EXPORT Camera : public Component
{
public:
    enum FERDIU_ENGINE_EXPORT Mode { PERSPECTIVE, ORTHOGRAPHIC };

    FERDIU_ENGINE_EXPORT Camera(float left, float right, float bottom, float top, float near, float far, Mode cameraMode = PERSPECTIVE);

    // camera modes
    FERDIU_ENGINE_EXPORT void setFrustum(float left, float right, float bottom, float top, float near, float far);
    FERDIU_ENGINE_EXPORT void setOrthographic(float left, float right, float bottom, float top, float near, float far);
    FERDIU_ENGINE_EXPORT Mode getMode();
    FERDIU_ENGINE_EXPORT void setParametes(float left, float right, float bottom, float top, float near, float far);
    FERDIU_ENGINE_EXPORT CameraModeParams const& getParameters() const;
    FERDIU_ENGINE_EXPORT void setParameterMults(float left = 1, float right = 1, float bottom = 1, float top = 1, float near = 1, float far = 1);

    // current
    FERDIU_ENGINE_EXPORT static Camera *getCurrent();
    FERDIU_ENGINE_EXPORT void setCurrent();
    FERDIU_ENGINE_EXPORT static void setCurrent(Camera *camera);

    // matrices getters
    FERDIU_ENGINE_EXPORT glm::mat4 *getPorjectionMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getViewMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getModelMatrix();

    FERDIU_ENGINE_EXPORT void pushMatrices();
    FERDIU_ENGINE_EXPORT void popMatrices();

    FERDIU_ENGINE_EXPORT void updateProjectionMatrix();
    FERDIU_ENGINE_EXPORT void updateViewMatrix();
    FERDIU_ENGINE_EXPORT void updateModelMatrix(glm::mat4 const& m);

    FERDIU_ENGINE_EXPORT void clear();
    FERDIU_ENGINE_EXPORT void setClearColor(glm::vec3 color);
    FERDIU_ENGINE_EXPORT glm::vec3 getClearColor();

    FERDIU_ENGINE_EXPORT void lookAt(glm::vec3 pos, glm::vec3 up = glm::vec3(0, 1, 0));
    FERDIU_ENGINE_EXPORT void lookAt(Transform const& pos, glm::vec3 up = glm::vec3(0, 1, 0));
    FERDIU_ENGINE_EXPORT void lookAt(GameObject const& pos, glm::vec3 up = glm::vec3(0, 1, 0));
    FERDIU_ENGINE_EXPORT void lookAt(Component const& pos, glm::vec3 up = glm::vec3(0, 1, 0));

private:
    FERDIU_ENGINE_EXPORT static Camera *current;

    MatricesStack stack;
    Mode mode = PERSPECTIVE;
    glm::vec3 clearColor = glm::vec3(0);

    CameraModeParams params = { -1, 1, -1, 1, 5, 1000 };
    CameraModeParams paramsMult = { 1, 1, 1, 1, 1, 1 };
};

}
