
#include "Components/Light.hpp"
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

// globals
static GameObject *root;
static Light *light;
static GameObject *lightGO;

// common
static Shader *sh;
static Material *material;

// testing object
static SphereRenderer *sr;
static DefaultShader *ds;
GameObject *go;


void setup()
{
    // init globals
    root = Scene::getCurrent()->root();
    lightGO = (new GameObject("Light"))
        ->addComponent((light = new Light(LIGHT_POINT)));
    lightGO->instantiate(root);

    // init common
    sh = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    material = new Material(sh);

    // init object
    sr = new SphereRenderer(10, *material);
    ds = new DefaultShader();
    ds->setLight(light);

    go = (new GameObject("Test"))
        ->addRenderer((Renderer*) sr)
        ->addComponent(ds);
    go->instantiate(root);

    // cute box
    GameObject *box = Primitives::Cube(5, material);
    box->instantiate(root);
}

int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;

    Engine::Start(argc, argv, setup);

    return 0;
}
