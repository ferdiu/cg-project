
#include <iostream>
#include <fstream>
#include "../../include/utils/Debug.hpp"

namespace FerdiuEngine
{

void fdoublespace(size_t s)
{
    for (size_t i = 0; i < s; i++)
        std::cout << "  ";
}

void ftab(size_t tab)
{
    for (size_t i = 0; i < tab; i++)
        std::cout << "\t";
}

// Print 3x3 matrix
void fprint(glm::mat3 const& mat)
{
    for (size_t i = 0; i < 3; i++)
        std::cout << "| " << mat[0][i] << " " << mat[1][i] << " " << mat[2][i] << " |" << std::endl;
}
// Print 4x4 matrix
void fprint(glm::mat4 const& mat)
{
    for (size_t i = 0; i < 4; i++)
        std::cout << "| " << mat[0][i] << " " << mat[1][i] << " " << mat[2][i] << " " << mat[3][i] << " |" << std::endl;
}

void fprint(glm::vec3 const& v)
{
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}
void fprint(glm::vec4 const& v)
{
    std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}
void fprint(bool b)
{
    std::cout << (b ? "true" : "false");
}

namespace Debug
{
    static unsigned int _indent = 0;
    void indent()
    {
        _indent++;
    }
    void unindent()
    {
        _indent--;
    }

    void Log(std::string message)
    {
#ifdef DEBUG
#ifndef DEBUG_NO_INDENT
        fdoublespace(_indent);
#endif
        std::cout << "Log: " << message << std::endl;
#else
        (void) message;
#endif
    }

    void Warn(std::string message)
    {
#ifdef DEBUG
#ifndef DEBUG_NO_INDENT
        fdoublespace(_indent);
#endif
        std::cout << "Warn: " << message << std::endl;
#else
        (void) message;
#endif
    }

    void Error(std::string message)
    {
#ifdef DEBUG
#ifndef DEBUG_NO_INDENT
        fdoublespace(_indent);
#endif
        std::cout << "Error: " << message << std::endl;
#else
        (void) message;
#endif
    }
}

}
