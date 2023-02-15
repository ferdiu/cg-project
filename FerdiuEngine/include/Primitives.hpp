
#include "Components/SphereRenderer.hpp"
#include "Components/CubeRenderer.hpp"
#include "GameObject.hpp"
#include "Material.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class Primitives
{
public:
    FERDIU_ENGINE_EXPORT static GameObject *Sphere(float radius, Material *material);
    FERDIU_ENGINE_EXPORT static GameObject *Cube(float size, Material *material);
    FERDIU_ENGINE_EXPORT static GameObject *Plane(float size, Material *material);
};

}
