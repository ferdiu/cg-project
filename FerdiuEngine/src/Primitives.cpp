
#include "../include/Primitives.hpp"
#include "Components/Physic/BoxCollider.hpp"
#include "Components/Physic/RigidBody.hpp"
#include "Components/Physic/SphereCollider.hpp"
#include "Components/SphereRenderer.hpp"
#include "Components/CubeRenderer.hpp"
#include "Components/PlaneRenderer.hpp"
#include <GL/gl.h>

namespace FerdiuEngine
{

GameObject *Primitives::Sphere(float radius, Material *material)
{
    return (new GameObject("Sphere"))
        ->addRigidbody(new RigidBody())
        ->addCollider(new SphereCollider(radius))
        ->addRenderer(new SphereRenderer(radius, *material));
}

GameObject *Primitives::Cube(float size, Material *material)
{
    return (new GameObject("Cube"))
        ->addRigidbody(new RigidBody())
        ->addCollider(new BoxCollider(glm::vec3(size)))
        ->addRenderer(new CubeRenderer(size, *material));
}

GameObject *Primitives::Plane(float size, Material *material)
{
    return (new GameObject("Plane"))
        ->addRigidbody(new RigidBody())
        ->addCollider(new BoxCollider(glm::vec3(size, 0.0001, size)))
        ->addRenderer(new PlaneRenderer(size, *material));
}


}
