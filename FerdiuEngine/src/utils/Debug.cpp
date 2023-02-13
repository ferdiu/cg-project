
#include <iostream>
#include <fstream>
#include "../../include/utils/Debug.hpp"

namespace FerdiuEngine
{

void ftab(size_t tab)
{
    for (size_t i = 0; i < tab; i++)
        ::std::cout << "\t";
}

// Print 3x3 matrix
void fprint(glm::vec3 *mat)
{
    for (size_t i = 0; i < 3; i++)
        ::std::cout << "| " << mat[i][0] << " " << mat[i][1] << " " << mat[i][2] << " |" << ::std::endl;
}
// Print 4x4 matrix
void fprint(glm::vec4 *mat)
{
    for (size_t i = 0; i < 3; i++)
        ::std::cout << "| " << mat[i][0] << " " << mat[i][1] << " " << mat[i][2] << " " << mat[i][3] << " |" << ::std::endl;
}

void fprint(glm::vec3 v)
{
    ::std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}
void fprint(glm::vec4 v)
{
    ::std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}
void fprint(bool b)
{
    ::std::cout << (b ? "true" : "false");
}

}
