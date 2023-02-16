
#include "Components/Light.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include <FerdiuEngine.hpp>

#include "Screen.hpp"
#include "include/DefaultShader.hpp"
#include "include/LookAtCamera.hpp"
#include "include/Board.hpp"
#include "include/Inputs.hpp"

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

// board
static Board *b;

// testing object
static SphereRenderer *sr;
static DefaultShader *ds;
static LookAtCamera *lac;
GameObject *go;
GameObject *goChild;

void mouseMove(int x, int y) { mousePassive(b, c, x, y); }

void setup()
{
    // init globals
    root = Scene::getCurrent()->root();
    c = Camera::getCurrent();
    c->getOwner()->setPosition(glm::vec3(0, CAMERA_Y, 0));
    c->setFrustum(-3, 3, -3, 3, 5, 1000);

    Engine::onUpdate(update);
    Engine::onMouseInput(mouseControl);
    Engine::onMouseMove(mouseMove);
    Engine::onKeyboardDown(keyInput);
    Screen::setMode(Screen::KEEP_HEIGHT);



    // light
    lightGO = (new GameObject("Light"))->addComponent((light = new Light(LIGHT_DIRECTIONAL)));
    light->setAmbient(glm::vec3(0.5, 0.5, 0.5));
    light->setDiffuse(glm::vec3(0.4, 0.4, 0.4));
    light->setSpecular(glm::vec3(.75, .75, .75));
    light->setAttenuation(.005, 0.05, 0.023);
    light->setCutOff(0, 0);
    light->setPosition(glm::vec3(0, 0, 0));
    light->setDirection(glm::vec3(45, 45, 45));
    lightGO->instantiate(root);



    // init common
    sh = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    material = new Material(sh);
    material->setAmbient(glm::vec4(.5, .5, .5, 1));
    material->setDiffuse(glm::vec4(.25, .25, .25, 1));
    material->setSpecular(glm::vec4(3, 3, 3, 1));
    material->setEmission(glm::vec4(.75, .75, .75, 1));
    material->setShininess(32);



    // BUILD BOARD
    b = new Board("resources/maps/map1.map", light);
    b->instantiate(root);
    lac = new LookAtCamera(b->getRoot(), c, glm::vec3(0, 0, -1));
    b->getRoot()->addComponent(lac); // add look at camera script



    (void) b;
    (void) lac;
    (void) ds;
    (void) sr;
    // // TODO: init ball
    // sr = new SphereRenderer(5, *material);
    // ds = new DefaultShader();
    // ds->setColor(glm::vec4(1, 0, 0, 1));
    // ds->setLight(light);
    //
    // go = (new GameObject("BALL"))
    // ->addRenderer((Renderer*) sr) // add renderer
    // ->addComponent(ds); // add shader handler
    // // lac = new LookAtCamera(go, c);
    // // go->addComponent(lac); // add look at camera script
    // go->setPosition(vec3(-5, 0, -20));
    // go->instantiate(root);



    // TODO: fix cube rendering
    // // cute box
    // GameObject *box = Primitives::Cube(20, material);
    // DefaultShader *dsBox = new DefaultShader();
    // dsBox->setColor(glm::vec4(0, 1, 0, 1));
    // dsBox->setLight(light);
    // box->addComponent(dsBox);
    // // box->addComponent(new LookAtCamera(box, c)); // add look at camera script
    // box->setPosition(vec3(0, 0, -30));
    // box->setRotation(vec3(45, 0, 0));
    // box->instantiate(root);
}



int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;

    Engine::Start(argc, argv, setup);

    return 0;
}
