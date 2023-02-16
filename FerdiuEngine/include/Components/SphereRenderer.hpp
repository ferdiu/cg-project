
#pragma once

#include <list>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "../Vertex.hpp"
#include "../Texture.hpp"
#include "../Material.hpp"

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

#define SPH_STEPS 30

class FERDIU_ENGINE_EXPORT SphereRenderer : public Renderer
{
public:
    FERDIU_ENGINE_EXPORT SphereRenderer(glm::vec3 center, float radius, Material material);
    FERDIU_ENGINE_EXPORT SphereRenderer(float radius, Material material);
    FERDIU_ENGINE_EXPORT SphereRenderer(glm::vec3 center, float radius, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT SphereRenderer(float radius, Texture tex, Material material);
    FERDIU_ENGINE_EXPORT SphereRenderer(glm::vec3 center, float radius, ::std::string texturePath, Material material);
    FERDIU_ENGINE_EXPORT SphereRenderer(float radius, ::std::string texturePath, Material material);

protected:
    void Init() override;
    void _draw() override;

private:
    glm::vec3 center = glm::vec3(0);
    float radius = 1;

    unsigned int vbos[2];

    Vertex vertices[(SPH_STEPS + 1) * (SPH_STEPS + 1)];
    unsigned int indices[SPH_STEPS][2 * (SPH_STEPS + 1)];
    int counts[2 * SPH_STEPS];
    void *offsets[2 * SPH_STEPS];

    // Fill the array of vertices.
    void generateVertices();

    // Fill the array of index.
    void generateIndices();

    // Fill the array of counts.
    void generateCounts();

    // Fill the array of buffer offsets.
    void generateOffsets();
};

}
