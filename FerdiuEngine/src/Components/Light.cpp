
#include <glm/glm.hpp>

#include "../../include/Components/Light.hpp"

namespace FerdiuEngine
{

// Set directional light
void setDirectionalLight(Light_t& l, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
{
    l.type = LIGHT_DIRECTIONAL;
    l.ambient = ambient;
    l.diffuse = diffuse;
    l.specular = specular;
    l.direction = direction;
}

// Set point light
void setPointLight(Light_t& l, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
{
    l.type = LIGHT_POINT;
    l.ambient = ambient;
    l.diffuse = diffuse;
    l.specular = specular;
    l.position = position;
}

// Set spot light
void setSpotLight(Light_t& l, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction, glm::vec3 position, float cutOff, float outerCutOff)
{
    l.type = LIGHT_SPOT;
    l.ambient = ambient;
    l.diffuse = diffuse;
    l.specular = specular;
    l.direction = direction;
    l.position = position;
    l.cutOff = cutOff;
    l.outerCutOff = outerCutOff;
}

// -------------------------------------------------------

Light::Light(LightType type)
{
    this->l.type = type;
}

Light::~Light()
{
    // TODO: DESTROY
}

// Ambient getter and setter
void Light::setAmbient(glm::vec3 ambient)
{
    this->l.ambient[0] = ambient[0];
    this->l.ambient[1] = ambient[1];
    this->l.ambient[2] = ambient[2];
}
glm::vec3 Light::getAmbient()
{
    return this->l.ambient;
}

// Diffuse getter and setter
void Light::setDiffuse(glm::vec3 diffuse)
{
    this->l.diffuse[0] = diffuse[0];
    this->l.diffuse[1] = diffuse[1];
    this->l.diffuse[2] = diffuse[2];
}
glm::vec3 Light::getDiffuse()
{
    return this->l.diffuse;
}

// Specular getter and setter
void Light::setSpecular(glm::vec3 specular)
{
    this->l.specular[0] = specular[0];
    this->l.specular[1] = specular[1];
    this->l.specular[2] = specular[2];
}
glm::vec3 Light::getSpecular()
{
    return this->l.specular;
}

// Direction getter and setter
void Light::setDirection(glm::vec3 direction)
{
    this->l.direction[0] = direction[0];
    this->l.direction[1] = direction[1];
    this->l.direction[2] = direction[2];
}
glm::vec3 Light::getDirection()
{
    return this->l.direction;
}

// Position getter and setter
void Light::setPosition(glm::vec3 position)
{
    this->l.position[0] = position[0];
    this->l.position[1] = position[1];
    this->l.position[2] = position[2];
}
glm::vec3 Light::getPosition()
{
    return this->l.position;
}

// Attenuation getter and setter
void Light::setAttenuation(float constant, float linear, float quadratic)
{
    this->l.attenuation.constant = constant;
    this->l.attenuation.linear = linear;
    this->l.attenuation.quadratic = quadratic;
}
Attenuation *Light::getAttenuation()
{
    return &(this->l.attenuation);
}
float Light::getAttenuationConstant()
{
    return this->l.attenuation.constant;
}
float Light::getAttenuationLinear()
{
    return this->l.attenuation.linear;
}
float Light::getAttenuationQuadratic()
{
    return this->l.attenuation.quadratic;
}

// Cutoff getter and setter
void Light::setCutOff(float cutOff, float outerCutOff)
{
    this->l.cutOff = cutOff;
    this->l.outerCutOff = outerCutOff;
}
float Light::getCutOff()
{
    return this->l.cutOff;
}
float Light::getOuterCutOff()
{
    return this->l.outerCutOff;
}

Light_t *Light::lightStruct()
{
    return &(this->l);
}

}
