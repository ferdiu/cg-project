
#include <list>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../../include/Vertex.hpp"
#include "../../include/Material.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Components/SphereRenderer.hpp"
#include "../../include/Components/Renderer.hpp"

namespace FerdiuEngine
{

// ------------------------------- public ----------------------------------
SphereRenderer::SphereRenderer(glm::vec3 center, float radius, Material material) : Renderer(material)
{
    this->center = center;
    this->radius = radius;
}
SphereRenderer::SphereRenderer(float radius, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->radius = radius;
}
SphereRenderer::SphereRenderer(glm::vec3 center, float radius, Texture tex, Material material) : Renderer(material)
{
    this->center = center;
    this->radius = radius;

    setTexture(tex);
}
SphereRenderer::SphereRenderer(float radius, Texture tex, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->radius = radius;

    setTexture(tex);
}
SphereRenderer::SphereRenderer(glm::vec3 center, float radius, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = center;
    this->radius = radius;

    setTexture(texturePath);
}
SphereRenderer::SphereRenderer(float radius, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->radius = radius;

    setTexture(texturePath);
}

// ------------------------------- protected ----------------------------------
void SphereRenderer::Init()
{
    // generate sphere data
    generateVertices();
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

void SphereRenderer::_Draw()
{
    glMultiDrawElements(GL_TRIANGLE_STRIP, this->counts, GL_UNSIGNED_INT,
                        (const void **)this->offsets, SPH_STEPS);
}

// ------------------------------- private -----------------------------------

void SphereRenderer::generateVertices()
{
    size_t i, j, k = 0;
    float xSegment, ySegment, xPos, yPos, zPos;

    for (i = 0; i <= SPH_STEPS; i++)
        for (j = 0; j <= SPH_STEPS; j++) {
            xSegment = (float) i / (float) SPH_STEPS;
            ySegment = (float) j / (float) SPH_STEPS;
            xPos = cos(xSegment * 2.0 * M_PI) * sin(ySegment * M_PI);
            yPos = cos(ySegment * M_PI);
            zPos = sin(xSegment * 2.0 * M_PI) * sin(ySegment * M_PI);

            // coords
            vertices[k].coords.x = radius * xPos;
            vertices[k].coords.y = radius * yPos;
            vertices[k].coords.z = radius * zPos;
            vertices[k].coords.w = 1.0;

            // normals
            vertices[k].normal.x = xPos;
            vertices[k].normal.y = yPos;
            vertices[k].normal.z = zPos;

            // texCoords
            vertices[k].tex.x = xSegment;
            vertices[k].tex.y = ySegment;

            k++;
        }
}

// Fill the array of index arrays.
void SphereRenderer::generateIndices()
{
    size_t i, j;
    bool oddRow = false;
    unsigned int n1, n2, tmpi;

    for (j = 0; j < SPH_STEPS; j++) {
        for (i = 0; i <= SPH_STEPS; i++) {
            tmpi = oddRow ? SPH_STEPS - i : i;

            n1 = (j * (SPH_STEPS + 1) + tmpi);
            n2 = ((j + 1) * (SPH_STEPS + 1) + tmpi);

            indices[j][2 * i] = oddRow ? n2 : n1;
            indices[j][2 * i + 1] = oddRow ? n1 : n2;
        }
        oddRow = !oddRow;
    }
}

// Fill the array of counts.
void SphereRenderer::generateCounts()
{
    for (size_t i = 0; i < 2 * SPH_STEPS; i++)
        counts[i] = 2 * (SPH_STEPS + 1);
}

// Fill the array of buffer offsets.
void SphereRenderer::generateOffsets()
{
    for (size_t i = 0; i < 2 * SPH_STEPS; i++)
        offsets[i] = (GLvoid *)(2 * (SPH_STEPS + 1) * i * sizeof(unsigned int));
}

}
