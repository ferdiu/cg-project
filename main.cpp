
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Components/Renderer.hpp"
#include "Components/SphereRenderer.hpp"
#include "Material.hpp"
#include "FerdiuEngine/include/Components/Component.hpp"
#include "FerdiuEngine/include/FerdiuEngine.hpp"

using namespace FerdiuEngine;
using namespace std;
using namespace glm;

static Shader *sh;
static Material *material;
static SphereRenderer *sr;

void setup()
{
    sh = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    material = new Material(sh);
    sr = new SphereRenderer(10, *material);

    GameObject *go = (new GameObject("Test"))
        ->addRenderer((Renderer*) sr);

    go->instantiate(Scene::getCurrent()->root());
}

int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;

    Engine::Start(argc, argv, setup);

    return 0;
}
