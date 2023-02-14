
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Shader
{
public:
    FERDIU_ENGINE_EXPORT Shader();
    FERDIU_ENGINE_EXPORT Shader(std::string vertexFilePath, std::string fragmentFilePath);
    FERDIU_ENGINE_EXPORT ~Shader();

    FERDIU_ENGINE_EXPORT void use();

    FERDIU_ENGINE_EXPORT bool isEmpty();

    // various setUniform overloads
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::mat4 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::mat3 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::mat2 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::vec4 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::vec3 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, glm::vec2 *value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, int value);
    FERDIU_ENGINE_EXPORT void setUniform(std::string uniform, float value);

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
