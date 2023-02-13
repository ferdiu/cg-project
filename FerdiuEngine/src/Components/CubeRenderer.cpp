
#include <list>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../../include/Components/CubeRenderer.hpp"
#include "../../include/Components/Renderer.hpp"
#include "../../include/Vertex.hpp"
#include "../../include/Material.hpp"

namespace FerdiuEngine
{

CubeRenderer::CubeRenderer(glm::vec3 center, float size, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;
}
CubeRenderer::CubeRenderer(float size, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;
}
CubeRenderer::CubeRenderer(glm::vec3 center, float size, Texture tex, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;

    setTexture(tex);
}
CubeRenderer::CubeRenderer(float size, Texture tex, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;

    setTexture(tex);
}
CubeRenderer::CubeRenderer(glm::vec3 center, float size, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;

    setTexture(texturePath);
}
CubeRenderer::CubeRenderer(float size, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;

    setTexture(texturePath);
}

// ------------------------------- protected ----------------------------------
void CubeRenderer::Init()
{
    // generate cube data
    applySize();
    generateIndices();
    generateCounts();
    generateOffsets();

    // generete VBOs
    glGenBuffers(2, vbos);

    // bind them and fill them with data (vertices and indices)
    glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

    // Coordinates attribute pointer init.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                            sizeof(this->vertices[0]),
                            0);
    glEnableVertexAttribArray(0);

    // Normals attribute pointer init.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                            sizeof(this->vertices[0]),
                            (GLvoid *)sizeof(this->vertices[0].coords));
    glEnableVertexAttribArray(1);

    // Textures attribute pointer init.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                            sizeof(this->vertices[0]),
                            (GLvoid *)(sizeof(this->vertices[0].coords) + sizeof(this->vertices[0].normal)));
    glEnableVertexAttribArray(2);
}

void CubeRenderer::_Draw()
{
    glMultiDrawElements(GL_TRIANGLE_STRIP, this->counts, GL_UNSIGNED_INT,
                        (const void **)this->offsets, N_CUBE_FACES);
}

// ---------------------------- private --------------------------------------

// apply size to coordinates of vertices
void CubeRenderer::applySize()
{
    float halfSize = size * 0.5;
    for (size_t i = 0; i < N_CUBE_VERTICES_PER_FACE * N_CUBE_FACES; i++) {
        vertices[i].coords[0] = vertices[i].coords[0] * halfSize;
        vertices[i].coords[1] = vertices[i].coords[1] * halfSize;
        vertices[i].coords[2] = vertices[i].coords[2] * halfSize;
    }
}

// Fill the indices matrix.
void CubeRenderer::generateIndices()
{
    for (size_t i = 0; i < N_CUBE_FACES; i++) {
        indices[i][0] = i;
        indices[i][1] = i + 1;
        indices[i][2] = i + 2;
        indices[i][3] = i + 3;
    }
}

// Fill the array of counts.
void CubeRenderer::generateCounts()
{
    for (size_t i = 0; i < N_CUBE_FACES; i++)
        counts[i] = N_CUBE_VERTICES_PER_FACE;
}

// Fill the array of buffer offsets.
void CubeRenderer::generateOffsets()
{
    for (size_t i = 0; i < N_CUBE_FACES; i++)
        offsets[i] = (GLvoid *)(N_CUBE_VERTICES_PER_FACE * i * sizeof(unsigned int));
}

}
