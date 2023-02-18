
#pragma once

#include <glm/glm.hpp>

#include "Component.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

typedef enum FERDIU_ENGINE_EXPORT LightType {
    LIGHT_DIRECTIONAL,
    LIGHT_POINT,
    LIGHT_SPOT
} LightType;

// Attenuation parameters
typedef struct FERDIU_ENGINE_EXPORT Attenuation {
    float constant;
    float linear;
    float quadratic;
} Attenuation;

// Light object (any type of light source can be represented this way)
typedef struct FERDIU_ENGINE_EXPORT Light_t {
    LightType type;

    // All types
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 direction; // only directional and spot
    glm::vec3 position; // only point and spot

    // Only point and spot
    Attenuation attenuation;

    // Only spot
    float cutOff;
    float outerCutOff;
} Light_t;

class FERDIU_ENGINE_EXPORT Light : public Component
{
public:
    FERDIU_ENGINE_EXPORT Light(LightType type = LIGHT_DIRECTIONAL);
    FERDIU_ENGINE_EXPORT ~Light() override;

    // ---------------- SETTERS AND GETTERS ------------------
    FERDIU_ENGINE_EXPORT void setAmbient(glm::vec3 ambient);
    FERDIU_ENGINE_EXPORT glm::vec3 getAmbient();

    FERDIU_ENGINE_EXPORT void setDiffuse(glm::vec3 diffuse);
    FERDIU_ENGINE_EXPORT glm::vec3 getDiffuse();

    FERDIU_ENGINE_EXPORT void setSpecular(glm::vec3 specular);
    FERDIU_ENGINE_EXPORT glm::vec3 getSpecular();

    FERDIU_ENGINE_EXPORT void setDirection(glm::vec3 direction);
    FERDIU_ENGINE_EXPORT glm::vec3 getDirection();

    FERDIU_ENGINE_EXPORT void setPosition(glm::vec3 position);
    FERDIU_ENGINE_EXPORT glm::vec3 getPosition();

    FERDIU_ENGINE_EXPORT void setAttenuation(float constant, float linear, float quadratic);
    FERDIU_ENGINE_EXPORT Attenuation *getAttenuation();
    FERDIU_ENGINE_EXPORT float getAttenuationConstant();
    FERDIU_ENGINE_EXPORT float getAttenuationLinear();
    FERDIU_ENGINE_EXPORT float getAttenuationQuadratic();

    FERDIU_ENGINE_EXPORT void setCutOff(float cutOff, float outerCutOff);
    FERDIU_ENGINE_EXPORT float getCutOff();
    FERDIU_ENGINE_EXPORT float getOuterCutOff();

    FERDIU_ENGINE_EXPORT Light_t *lightStruct();

private:
    Light_t l = {
        LIGHT_DIRECTIONAL,

        { 0.0, 0.0, 0.0 }, // amb
        { 1.0, 1.0, 1.0 }, // dif
        { 1.0, 1.0, 1.0 }, // spec

        { 0.0, 0.0, 1.0 }, // dir
        { 0.0, 0.0, 1.0 }, // pos

        { 1.0, 0.0, 1.0 }, // att

        0, // cutOff
        0, // outerCutOff
    };
};

}
