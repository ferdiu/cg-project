
#pragma once

#include <glm/glm.hpp>
#include "Shader.hpp"

namespace FerdiuEngine
{

// Material object
class Material
{
public:
    Material(std::string vertexFilePath, std::string fragmentFilePath);
    Material(Shader shader);

    void setAmbient(glm::vec4 ambient);
    glm::vec4 getAmbient();
    void setDiffuse(glm::vec4 diffuse);
    glm::vec4 getDiffuse();
    void setSpecular(glm::vec4 specular);
    glm::vec4 getSpecular();
    void setEmission(glm::vec4 emission);
    glm::vec4 getEmission();
    void setShininess(float shininess);
    float getShininess();

    void setShader(Shader shader);
    Shader getShader();

    void use();

private:
    Shader shader;

    glm::vec4 ambient; // ambient reflection
    glm::vec4 diffuse; // diffuse reflection
    glm::vec4 specular; // specular reflection

    glm::vec4 emission;

    float shininess;
};

}
