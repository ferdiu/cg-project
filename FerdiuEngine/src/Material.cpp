
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "../include/Shader.hpp"
#include "../include/Material.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------

Material::Material(::std::string vertexFilePath, ::std::string fragmentFilePath)
{
    this->shader = Shader(vertexFilePath, fragmentFilePath);
}

Material::Material(Shader shader)
{
    this->shader = shader;
}

void Material::setAmbient(glm::vec4 ambient)
{
    this->ambient = ambient;
}
glm::vec4 Material::getAmbient()
{
    return ambient;
}
void Material::setDiffuse(glm::vec4 diffuse)
{
    this->diffuse = diffuse;
}
glm::vec4 Material::getDiffuse()
{
    return diffuse;
}
void Material::setSpecular(glm::vec4 specular)
{
    this->specular = specular;
}
glm::vec4 Material::getSpecular()
{
    return specular;
}
void Material::setEmission(glm::vec4 emission)
{
    this->emission = emission;
}
glm::vec4 Material::getEmission()
{
    return emission;
}
void Material::setShininess(float shininess)
{
    this->shininess = shininess;
}
float Material::getShininess()
{
    return shininess;
}

void Material::setShader(Shader shader)
{
    this->shader = shader;
}
Shader Material::getShader()
{
    return shader;
}

void Material::use()
{
    shader.use();
}

}
