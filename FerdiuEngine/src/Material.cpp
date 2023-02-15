
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
    this->shader = new Shader(vertexFilePath, fragmentFilePath);
}

Material::Material(Shader *shader)
{
    this->shader = shader;
}

void Material::setAmbient(glm::vec4 ambient)
{
    this->material.ambient = ambient;
}
glm::vec4 Material::getAmbient()
{
    return this->material.ambient;
}
void Material::setDiffuse(glm::vec4 diffuse)
{
    this->material.diffuse = diffuse;
}
glm::vec4 Material::getDiffuse()
{
    return this->material.diffuse;
}
void Material::setSpecular(glm::vec4 specular)
{
    this->material.specular = specular;
}
glm::vec4 Material::getSpecular()
{
    return this->material.specular;
}
void Material::setEmission(glm::vec4 emission)
{
    this->material.emission = emission;
}
glm::vec4 Material::getEmission()
{
    return this->material.emission;
}
void Material::setShininess(float shininess)
{
    this->material.shininess = shininess;
}
float Material::getShininess()
{
    return this->material.shininess;
}

void Material::setShader(Shader *shader)
{
    this->shader = shader;
}
Shader *Material::getShader()
{
    return shader;
}

void Material::use()
{
    shader->use();
}

Material_t *Material::materialStruct()
{
    return &material;
}

}
