
#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>

namespace FerdiuEngine
{

class Shader
{
public:
    Shader();
    Shader(std::string vertexFilePath, std::string fragmentFilePath);
    ~Shader();

    void use();

    bool isEmpty();

    // various setUniform overloads
    void setUniform(std::string uniform, glm::mat4 *value);
    void setUniform(std::string uniform, glm::mat3 *value);
    void setUniform(std::string uniform, glm::mat2 *value);
    void setUniform(std::string uniform, glm::vec4 *value);
    void setUniform(std::string uniform, glm::vec3 *value);
    void setUniform(std::string uniform, glm::vec2 *value);
    void setUniform(std::string uniform, int value);
    void setUniform(std::string uniform, float value);

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
