
#pragma once

#include <list>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "../Material.hpp"
#include "../Vertex.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

#define N_PLANE_VERTICES_PER_FACE 4

class FERDIU_ENGINE_EXPORT PlaneRenderer : public Renderer
{
public:
    FERDIU_ENGINE_EXPORT PlaneRenderer(glm::vec3 center, float size, Material material);
    FERDIU_ENGINE_EXPORT PlaneRenderer(float size, Material material);
    FERDIU_ENGINE_EXPORT PlaneRenderer(glm::vec3 center, float size, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT PlaneRenderer(float size, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT PlaneRenderer(glm::vec3 center, float size, ::std::string texturePath, Material material);
    FERDIU_ENGINE_EXPORT PlaneRenderer(float size, ::std::string texturePath, Material material);

protected:
    void Init() override;
    void _draw() override;

private:
    glm::vec3 center = glm::vec3(0);
    float size = 1;

    unsigned int vbos[2];

    FerdiuEngine::Vertex vertices[N_PLANE_VERTICES_PER_FACE] = {
        // top
        { { -1,  1,  1, 1 }, { 0, 1, 0 }, { 0, 0 } },
        { {  1,  1,  1, 1 }, { 0, 1, 0 }, { 1, 0 } },
        { { -1,  1, -1, 1 }, { 0, 1, 0 }, { 0, 1 } },
        { {  1,  1, -1, 1 }, { 0, 1, 0 }, { 1, 1 } },
    };
    unsigned int indices[1][N_PLANE_VERTICES_PER_FACE] = {{ 0, 1, 2, 3 }};
    int counts[1] = { N_PLANE_VERTICES_PER_FACE };
    void *offsets[1] = { (GLvoid *) 0 };

    // apply size to coordinates of vertices
    void applySize();
};

}
