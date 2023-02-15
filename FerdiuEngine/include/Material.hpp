
#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

typedef struct Material_t
{
    glm::vec4 ambient; // ambient reflection
    glm::vec4 diffuse; // diffuse reflection
    glm::vec4 specular; // specular reflection

    glm::vec4 emission;

    float shininess;
} Material_t;

// Material object
class FERDIU_ENGINE_EXPORT Material
{
public:
    FERDIU_ENGINE_EXPORT Material(std::string vertexFilePath, std::string fragmentFilePath);
    FERDIU_ENGINE_EXPORT Material(Shader *shader);

    FERDIU_ENGINE_EXPORT void setAmbient(glm::vec4 ambient);
    FERDIU_ENGINE_EXPORT glm::vec4 getAmbient();
    FERDIU_ENGINE_EXPORT void setDiffuse(glm::vec4 diffuse);
    FERDIU_ENGINE_EXPORT glm::vec4 getDiffuse();
    FERDIU_ENGINE_EXPORT void setSpecular(glm::vec4 specular);
    FERDIU_ENGINE_EXPORT glm::vec4 getSpecular();
    FERDIU_ENGINE_EXPORT void setEmission(glm::vec4 emission);
    FERDIU_ENGINE_EXPORT glm::vec4 getEmission();
    FERDIU_ENGINE_EXPORT void setShininess(float shininess);
    FERDIU_ENGINE_EXPORT float getShininess();

    FERDIU_ENGINE_EXPORT void setShader(Shader *shader);
    FERDIU_ENGINE_EXPORT Shader *getShader();

    FERDIU_ENGINE_EXPORT void use();

    FERDIU_ENGINE_EXPORT Material_t *materialStruct();

private:
    Shader *shader;

    Material_t material = {
        { 0.2, 0.2, 0.2, 1.0 }, // amb refl
        { 0.8, 0.8, 0.8, 1.0 }, // dif refl
        { 0.0, 0.0, 0.0, 1.0 }, // spec refl

        { 0.0, 0.0, 0.0, 1.0 }, // emit col

        0 // shine
    };
};

}
