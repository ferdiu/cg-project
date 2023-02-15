
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>

#include "Components/Light.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class Material;

class FERDIU_ENGINE_EXPORT Shader
{
public:
    FERDIU_ENGINE_EXPORT Shader();
    FERDIU_ENGINE_EXPORT Shader(std::string vertexFilePath, std::string fragmentFilePath);
    FERDIU_ENGINE_EXPORT ~Shader();

    FERDIU_ENGINE_EXPORT void use();

    FERDIU_ENGINE_EXPORT bool isEmpty();

    // various setUniform overloads
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::mat4 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::mat3 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::mat2 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::vec4 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::vec3 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, glm::vec2 const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, int const value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, float const value);

    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, struct Material_t const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, Material& value);

    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, struct Light_t const& value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string const uniform, Light& value);

private:
    std::string vertexPath = "";
    std::string fragmentPath = "";

    unsigned int programId = 0;

    std::map<std::string, unsigned int> uniformMap = std::map<std::string, unsigned int>();

    unsigned int compile(std::string shaderType, std::string shaderFile);

    void createProgram();
    void print();
};

}
