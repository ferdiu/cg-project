
#include "Components/Light.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <FerdiuEngine.hpp>

#include "include/DefaultShader.hpp"
#include "include/LookAtCamera.hpp"

using namespace FerdiuEngine;
using namespace std;
using namespace glm;

// globals
static GameObject *root;
static Light *light;
static GameObject *lightGO;
static Camera *c;

// common
static Shader *sh;
static Material *material;

// testing object
static SphereRenderer *sr;
static DefaultShader *ds;
static LookAtCamera *lac;
GameObject *go;
GameObject *goChild;


void setup()
{
    // init globals
    root = Scene::getCurrent()->root();
    c = Camera::getCurrent();
    c->getOwner()->setPosition(glm::vec3(0, 0, -20));


    // light
    lightGO = (new GameObject("Light"))
        ->addComponent((light = new Light(LIGHT_POINT)));
    light->setAmbient(glm::vec3(0.5, 0.5, 0.5));
    light->setDiffuse(glm::vec3(0.4, 0.4, 0.4));
    light->setSpecular(glm::vec3(1, 1, 1));
    light->setAttenuation(.005, 0.05, 0.023);
    light->setCutOff(0, 0);

    light->setPosition(glm::vec3(-2, 2, -2));
    light->setDirection(glm::vec3(0, 0, 0));

    lightGO->instantiate(root);


    // init common
    sh = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    material = new Material(sh);
    material->setAmbient(glm::vec4(.5, .5, .5, 1));
    material->setDiffuse(glm::vec4(.25, .25, .25, 1));
    material->setSpecular(glm::vec4(1, 1, 1, 1));
    material->setEmission(glm::vec4(.75, .75, .75, 1));
    material->setShininess(64);

    // init object
    sr = new SphereRenderer(10, *material);
    ds = new DefaultShader();
    ds->setColor(glm::vec4(.25, .25, .25, 1));
    ds->setLight(light);

    go = (new GameObject("Test"))
        ->addRenderer((Renderer*) sr) // add renderer
        ->addComponent(ds); // add shader handler
    lac = new LookAtCamera(go, c);
    go->addComponent(lac); // add look at camera script
    go->setPosition(vec3(0, 0, -30));
    go->instantiate(root);

    // init object (child)
    // DefaultShader *dsChild = new DefaultShader();
    // dsChild->setColor(glm::vec4(.25, .25, .25, 1));
    // dsChild->setLight(light);
    //
    // goChild = new GameObject("Child");
    // go
    //     ->addRenderer((Renderer*) new SphereRenderer(10, *material)) // add renderer
    //     ->addComponent(dsChild) // add shader handler
    //     ->addComponent(new LookAtCamera(goChild, c)); // add look at camera script
    // goChild->setPosition(vec3(0, 0, -5));
    // goChild->instantiate(go);

    // // cute box
    // GameObject *box = Primitives::Plane(20, material);
    // DefaultShader *dsBox = new DefaultShader();
    // dsBox->setColor(glm::vec4(.25, .25, .25, 1));
    // dsBox->setLight(light);
    // box->addComponent(dsBox);
    // box->addComponent(new LookAtCamera(box, c)); // add look at camera script
    // box->setRotation(vec3(90, 0, 0));
    // box->setPosition(vec3(0, 0, -20));
    // box->instantiate(root);
}

int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;

    Engine::Start(argc, argv, setup);

    return 0;
}
