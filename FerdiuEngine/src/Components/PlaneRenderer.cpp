
#include <list>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../../include/Components/PlaneRenderer.hpp"
#include "../../include/Components/Renderer.hpp"
#include "../../include/Vertex.hpp"
#include "../../include/Material.hpp"

namespace FerdiuEngine
{

PlaneRenderer::PlaneRenderer(glm::vec3 center, float size, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;

    init();
}
PlaneRenderer::PlaneRenderer(float size, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;

    init();
}
PlaneRenderer::PlaneRenderer(glm::vec3 center, float size, Texture tex, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;

    init();

    setTexture(tex);
}
PlaneRenderer::PlaneRenderer(float size, Texture tex, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;

    init();

    setTexture(tex);
}
PlaneRenderer::PlaneRenderer(glm::vec3 center, float size, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = center;
    this->size = size;

    init();

    setTexture(texturePath);
}
PlaneRenderer::PlaneRenderer(float size, ::std::string texturePath, Material material) : Renderer(material)
{
    this->center = glm::vec3(0, 0, 0);
    this->size = size;

    init();

    setTexture(texturePath);
}
PlaneRenderer::~PlaneRenderer()
{
    // TODO: DESTROY
}

// ------------------------------- protected ----------------------------------
void PlaneRenderer::Init()
{
    // generate cube data
    applySize();

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

void PlaneRenderer::_draw()
{
    glMultiDrawElements(GL_TRIANGLE_STRIP, this->counts, GL_UNSIGNED_INT,
                        (const void **)this->offsets, 1);
}

// ---------------------------- private --------------------------------------

// apply size to coordinates of vertices
void PlaneRenderer::applySize()
{
    float halfSize = size * 0.5;
    for (size_t i = 0; i < N_PLANE_VERTICES_PER_FACE; i++)
    {
        vertices[i].coords[0] *= halfSize;
        vertices[i].coords[1] *= halfSize;
        vertices[i].coords[2] *= halfSize;
    }
}

}
