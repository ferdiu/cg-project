
#include "GameObject.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <FerdiuEngine.hpp>

#include "include/DefaultShader.hpp"

using namespace FerdiuEngine;
using namespace std;
using namespace glm;

static Shader *sh;
static Material *material;
static SphereRenderer *sr;

static GameObject *root;

void setup()
{
    root = Scene::getCurrent()->root();
    sh = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    material = new Material(sh);
    sr = new SphereRenderer(10, *material);

    GameObject *go = (new GameObject("Test"))
        ->addRenderer((Renderer*) sr);
    go->instantiate(root);

    GameObject *box = Primitives::Cube(5, material);
    box->instantiate(root);
}

int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;

    Engine::Start(argc, argv, setup);

    return 0;
}
