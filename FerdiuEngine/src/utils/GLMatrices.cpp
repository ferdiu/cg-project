
#include <glm/glm.hpp>
#include <glm/gtx/functions.hpp>
#include <iostream>
#include <string>

#include "../../include/utils/GLMatrices.hpp"

namespace FerdiuEngine
{

void GLMatrix::copy(glm::mat4& dest, glm::mat4 const& src)
{
    // NOTE: not sure this is the best way to do this
    // probably could have used memcpy for performances
    size_t i = 0, j = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

void GLMatrix::copy(GLMatrices& dest, GLMatrices const& src)
{
    copy(dest.proj, src.proj);
    copy(dest.view, src.view);
    copy(dest.model, src.model);
}

}
