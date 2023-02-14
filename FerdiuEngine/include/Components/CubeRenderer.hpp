
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

#define N_CUBE_FACES 6
#define N_CUBE_VERTICES 8
#define N_CUBE_VERTICES_PER_FACE 4

// normalized component
#define NC 0.5773502691896258

class FERDIU_ENGINE_EXPORT CubeRenderer : public Renderer
{
public:
    FERDIU_ENGINE_EXPORT CubeRenderer(glm::vec3 center, float size, Material material);
    FERDIU_ENGINE_EXPORT CubeRenderer(float size, Material material);
    FERDIU_ENGINE_EXPORT CubeRenderer(glm::vec3 center, float size, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT CubeRenderer(float size, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT CubeRenderer(glm::vec3 center, float size, ::std::string texturePath, Material material);
    FERDIU_ENGINE_EXPORT CubeRenderer(float size, ::std::string texturePath, Material material);

protected:
    void Init() override;
    void _draw() override;

private:
    glm::vec3 center = glm::vec3(0);
    float size = 1;

    unsigned int vbos[2];

    FerdiuEngine::Vertex vertices[N_CUBE_VERTICES_PER_FACE * N_CUBE_FACES] = {
        // front
        { {  1, -1, -1, 1 }, {  NC, -NC, -NC }, { 0, 0 } },
        { { -1, -1, -1, 1 }, { -NC, -NC, -NC }, { 1, 0 } },
        { {  1,  1, -1, 1 }, {  NC,  NC, -NC }, { 0, 1 } },
        { { -1,  1, -1, 1 }, { -NC,  NC, -NC }, { 1, 1 } },
        // back
        { { -1, -1,  1, 1 }, { -NC, -NC,  NC }, { 0, 0 } },
        { {  1, -1,  1, 1 }, {  NC, -NC,  NC }, { 1, 0 } },
        { { -1,  1,  1, 1 }, { -NC,  NC,  NC }, { 0, 1 } },
        { {  1,  1,  1, 1 }, {  NC,  NC,  NC }, { 1, 1 } },
        // left
        { { -1, -1, -1, 1 }, { -NC, -NC,  NC }, { 0, 0 } },
        { { -1, -1,  1, 1 }, { -NC, -NC, -NC }, { 1, 0 } },
        { { -1,  1, -1, 1 }, { -NC,  NC, -NC }, { 0, 1 } },
        { { -1,  1,  1, 1 }, { -NC,  NC,  NC }, { 1, 1 } },
        // right
        { {  1, -1,  1, 1 }, {  NC, -NC,  NC }, { 0, 0 } },
        { {  1, -1, -1, 1 }, {  NC, -NC, -NC }, { 1, 0 } },
        { {  1,  1,  1, 1 }, {  NC,  NC,  NC }, { 0, 1 } },
        { {  1,  1, -1, 1 }, {  NC,  NC, -NC }, { 1, 1 } },
        // top
        { {  1,  1, -1, 1 }, {  NC,  NC, -NC }, { 0, 0 } },
        { { -1,  1, -1, 1 }, { -NC,  NC, -NC }, { 1, 0 } },
        { {  1,  1,  1, 1 }, {  NC,  NC,  NC }, { 0, 1 } },
        { { -1,  1,  1, 1 }, { -NC,  NC,  NC }, { 1, 1 } },
        // bottom
        { {  1, -1,  1, 1 }, {  NC, -NC,  NC }, { 0, 0 } },
        { { -1, -1,  1, 1 }, { -NC, -NC,  NC }, { 1, 0 } },
        { {  1, -1, -1, 1 }, {  NC, -NC, -NC }, { 0, 1 } },
        { { -1, -1, -1, 1 }, { -NC, -NC, -NC }, { 1, 1 } },
    };
    unsigned int indices[N_CUBE_FACES][N_CUBE_VERTICES_PER_FACE];
    int counts[N_CUBE_FACES];
    void *offsets[N_CUBE_FACES];

    // apply size to coordinates of vertices
    void applySize();

    // Fill the indices matrix.
    void generateIndices();

    // Fill the array of counts.
    void generateCounts();

    // Fill the array of buffer offsets.
    void generateOffsets();
};

}
