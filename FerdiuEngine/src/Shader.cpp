#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <map>

#include "../include/Material.hpp"
#include "../include/Shader.hpp"

namespace FerdiuEngine
{

//---------------------- utils -----------------------------------

// Function to read text file.
inline char *readTextFile(char *aTextFile)
{
    FILE *filePointer = fopen(aTextFile, "rb");
    char *content = NULL;
    long numVal = 0;
    int nread = 0;

    fseek(filePointer, 0L, SEEK_END);
    numVal = ftell(filePointer);
    fseek(filePointer, 0L, SEEK_SET);
    content = (char *) malloc((numVal + 1) * sizeof(char));
    if ((nread = fread(content, 1, numVal, filePointer)) < 0)
        perror("reading shader program");
    content[numVal] = '\0';
    fclose(filePointer);
    return content;
}
inline char *readTextFile(std::string aTextFile)
{
    return readTextFile((char *) aTextFile.c_str());
}

//---------------------- public -----------------------------------

Shader::Shader() {}
Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
    this->vertexPath = vertexFilePath;
    this->fragmentPath = fragmentFilePath;
    this->createProgram();
}

Shader::~Shader()
{
    glDeleteShader(this->programId);
}

void Shader::use()
{
    glUseProgram(this->programId);
}

bool Shader::isEmpty()
{
    return this->vertexPath == "" && this->fragmentPath == "";
}

// various setUniform overloads
void Shader::setUniform(std::string const uniform, glm::mat4 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniformMatrix4fv(uniformMap[uniform], 1, GL_FALSE, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, glm::mat3 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniformMatrix3fv(uniformMap[uniform], 1, GL_FALSE, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, glm::mat2 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniformMatrix2fv(uniformMap[uniform], 1, GL_FALSE, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, glm::vec4 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniform4fv(uniformMap[uniform], 1, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, glm::vec3 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniform3fv(uniformMap[uniform], 1, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, glm::vec2 const& value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniform2fv(uniformMap[uniform], 1, (GLfloat *) &value);
}
void Shader::setUniform(std::string const uniform, int const value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniform1i(uniformMap[uniform], value);
}
void Shader::setUniform(std::string const uniform, float const value)
{
    if (uniformMap.count(uniform) == 0)
        uniformMap[uniform] = glGetUniformLocation(this->programId, (char *) uniform.c_str());

    glUniform1f(uniformMap[uniform], value);
}
void Shader::setUniform(std::string const uniform, Material_t const& value)
{
    if (uniformMap.count(uniform + ".ambient") == 0)
        uniformMap[uniform + ".ambient"] = glGetUniformLocation(this->programId, (char *) (uniform + ".ambient").c_str());
    if (uniformMap.count(uniform + ".diffuse") == 0)
        uniformMap[uniform + ".diffuse"] = glGetUniformLocation(this->programId, (char *) (uniform + ".diffuse").c_str());
    if (uniformMap.count(uniform + ".specular") == 0)
        uniformMap[uniform + ".specular"] = glGetUniformLocation(this->programId, (char *) (uniform + ".specular").c_str());
    if (uniformMap.count(uniform + ".emission") == 0)
        uniformMap[uniform + ".emission"] = glGetUniformLocation(this->programId, (char *) (uniform + ".emission").c_str());
    if (uniformMap.count(uniform + ".shininess") == 0)
        uniformMap[uniform + ".shininess"] = glGetUniformLocation(this->programId, (char *) (uniform + ".shininess").c_str());

    glUniform4fv(uniformMap[uniform + ".ambient"], 1, &value.ambient[0]);
    glUniform4fv(uniformMap[uniform + ".diffuse"], 1, &value.diffuse[0]);
    glUniform4fv(uniformMap[uniform + ".specular"], 1, &value.specular[0]);
    glUniform4fv(uniformMap[uniform + ".emission"], 1, &value.emission[0]);
    glUniform1f(uniformMap[uniform + ".shininess"], value.shininess);
}
void Shader::setUniform(std::string const uniform, Material& value)
{
    setUniform(uniform, *value.materialStruct());
}
void Shader::setUniform(std::string const uniform, Light_t const& value)
{
    if (uniformMap.count(uniform + ".type") == 0)
        uniformMap[uniform + ".type"] = glGetUniformLocation(this->programId, (char *) (uniform + ".type").c_str());
    if (uniformMap.count(uniform + ".ambient") == 0)
        uniformMap[uniform + ".ambient"] = glGetUniformLocation(this->programId, (char *) (uniform + ".ambient").c_str());
    if (uniformMap.count(uniform + ".diffuse") == 0)
        uniformMap[uniform + ".diffuse"] = glGetUniformLocation(this->programId, (char *) (uniform + ".diffuse").c_str());
    if (uniformMap.count(uniform + ".specular") == 0)
        uniformMap[uniform + ".specular"] = glGetUniformLocation(this->programId, (char *) (uniform + ".specular").c_str());
    if (uniformMap.count(uniform + ".direction") == 0)
        uniformMap[uniform + ".direction"] = glGetUniformLocation(this->programId, (char *) (uniform + ".direction").c_str());
    if (uniformMap.count(uniform + ".position") == 0)
        uniformMap[uniform + ".position"] = glGetUniformLocation(this->programId, (char *) (uniform + ".position").c_str());
    if (uniformMap.count(uniform + ".attenuation.constant") == 0)
        uniformMap[uniform + ".attenuation.constant"] = glGetUniformLocation(this->programId, (char *) (uniform + ".attenuation.constant").c_str());
    if (uniformMap.count(uniform + ".attenuation.linear") == 0)
        uniformMap[uniform + ".attenuation.linear"] = glGetUniformLocation(this->programId, (char *) (uniform + ".attenuation.linear").c_str());
    if (uniformMap.count(uniform + ".attenuation.quadratic") == 0)
        uniformMap[uniform + ".attenuation.quadratic"] = glGetUniformLocation(this->programId, (char *) (uniform + ".attenuation.quadratic").c_str());
    if (uniformMap.count(uniform + ".cutOff") == 0)
        uniformMap[uniform + ".cutOff"] = glGetUniformLocation(this->programId, (char *) (uniform + ".cutOff").c_str());
    if (uniformMap.count(uniform + ".outerCutOff") == 0)
        uniformMap[uniform + ".outerCutOff"] = glGetUniformLocation(this->programId, (char *) (uniform + ".outerCutOff").c_str());

    glUniform1i(uniformMap[uniform + ".type"], value.type);

    glUniform3fv(uniformMap[uniform + ".ambient"], 1, &value.ambient[0]);
    glUniform3fv(uniformMap[uniform + ".diffuse"], 1, &value.diffuse[0]);
    glUniform3fv(uniformMap[uniform + ".specular"], 1, &value.specular[0]);

    glUniform3fv(uniformMap[uniform + ".direction"], 1, &value.direction[0]);
    glUniform3fv(uniformMap[uniform + ".position"], 1, &value.position[0]);

    glUniform1f(uniformMap[uniform + ".attenuation.constant"], value.attenuation.constant);
    glUniform1f(uniformMap[uniform + ".attenuation.linear"], value.attenuation.linear);
    glUniform1f(uniformMap[uniform + ".attenuation.quadratic"], value.attenuation.quadratic);

    glUniform1f(uniformMap[uniform + ".cutOff"], value.cutOff);
    glUniform1f(uniformMap[uniform + ".outerCutOff"], value.outerCutOff);
}
void Shader::setUniform(std::string const uniform, Light& value)
{
    setUniform(uniform, *value.lightStruct());
}

//------------------------- private -------------------------------

unsigned int Shader::compile(std::string shaderType, std::string shaderFile)
{
    int shaderId = -1;
    char *shader = readTextFile(shaderFile);

    // set shaderId based on the shader type
    if (shaderType == "vertex")
        shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if (shaderType == "tessControl")
        shaderId = glCreateShader(GL_TESS_CONTROL_SHADER);
    else if (shaderType == "tessEvaluation")
        shaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);
    else if (shaderType == "geometry")
        shaderId = glCreateShader(GL_GEOMETRY_SHADER);
    else if (shaderType == "fragment")
        shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    else {
        std::cerr << "Invalid shader type provided: " << shaderType << std::endl;
        return -1;
    }

    glShaderSource(shaderId, 1, (const char **) &shader, NULL);
    glCompileShader(shaderId);

    GLint isCompiled = false;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar errorLog[524288]; // 2^19
        // The maxLength includes the NULL character
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

        std::cerr << "shader (" << shaderFile << ") compilation error: " << errorLog << std::endl;

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shaderId); // Don't leak the shader.
        exit(-1);
    }

    free(shader);

    return shaderId;
}

void Shader::createProgram()
{
    int vertexShaderId, fragmentShaderId;

    vertexShaderId = compile("vertex", vertexPath);
    fragmentShaderId = compile("fragment", fragmentPath);
    this->programId = glCreateProgram();
    glAttachShader(this->programId, vertexShaderId);
    glAttachShader(this->programId, fragmentShaderId);
    glLinkProgram(this->programId);
}

void Shader::print()
{
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, glm::vec3 or glm::mat4, etc)

    const GLsizei bufSize = 64; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    std::cout << "Shader Program (id: " << this->programId << "): {" << std::endl;

    glGetProgramiv(this->programId, GL_ACTIVE_ATTRIBUTES, &count);
    std::cout << "\tattributes: (" << count << ") [" << std::endl;

    for (i = 0; i < count; i++) {
        glGetActiveAttrib(this->programId, (GLuint)i, bufSize, &length, &size, &type, name);

        std::cout << "\t\t#" << i << ": " << name << " (type: " << type << ")," << std::endl;
    }
    std::cout << "\t]," << std::endl;

    glGetProgramiv(this->programId, GL_ACTIVE_UNIFORMS, &count);
    std::cout << "\tuniforms: (" << count << ") [" << std::endl;

    for (i = 0; i < count; i++) {
        glGetActiveUniform(this->programId, (GLuint)i, bufSize, &length, &size, &type, name);

        std::cout << "\t\t#" << i << ": " << name << " (type: " << type << ")," << std::endl;
    }
    std::cout << "\t]" << std::endl;
    std::cout << "}" << std::endl;
}

}
