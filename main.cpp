
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
#include "include/Ball.hpp"
#include "include/Inputs.hpp"
#include "include/PrintPhysicsPosition.hpp"

using namespace FerdiuEngine;
using namespace std;
using namespace glm;

// globals
static GameObject *root;
static Light *light;
static GameObject *lightGO;
static Camera *c;

// common
static Material *material;

// board
static Board *b;

// testing object
static LookAtCamera *lac;
static GameObject *ball;

void mouseMove(int x, int y) { mousePassive(b, c, x, y); }

void setup()
{
    // init globals
    root = Scene::getCurrent()->root();
    c = Camera::getCurrent();
    c->getOwner()->setLocalPosition(glm::vec3(0, CAMERA_Y, 0));
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
    light->setDirection(glm::vec3(45, 10, 45));
    lightGO->instantiate(root);



    // BUILD BOARD
    b = new Board("resources/maps/map1.map", light);
    b->instantiate(root);
    lac = new LookAtCamera(b->getRoot(), c, glm::vec3(0, 0, -1));
    b->getRoot()->addComponent(lac); // add look at camera script


    // INIT BALL
    material = new Material(new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl"));
    material->setAmbient(glm::vec4(.25, .25, .25, 1));
    material->setDiffuse(glm::vec4(.25, .25, .25, 1));
    material->setSpecular(glm::vec4(1, 1, 1, 1));
    material->setEmission(glm::vec4(.75, .75, .75, 1));
    material->setShininess(32);

    // instantiate
    SphereRenderer *sr = new SphereRenderer(.5, *material);
    DefaultShader *ds = new DefaultShader();
    ds->setColor(glm::vec4(0.5, 0.5, 0.5, 1));
    ds->setLight(light);

    ball = (new GameObject("BALL"))
        ->addRigidbody(new RigidBody(RigidBody::RigidBodyType::RB_DYNAMIC))
        ->addRenderer(sr) // add renderer
        ->addComponent(ds) // add shader handler
        ->addComponent(new Ball(b));
    ball->instantiate(Scene::getCurrent()->root());
    ball->addComponent(new PrintPhysicsPosition());
}

void instructions()
{
    cout << "##############################################" << endl;
    cout << "# Click and drag to tilt the board           #" << endl;
    cout << "# Bring the ball from the start (red sphere) #" << endl;
    cout << "# to the finish (green sphere) to win        #" << endl;
    cout << "# ESC - quit game                            #" << endl;
    cout << "# F - toggle full screen                     #" << endl;
    cout << "##############################################" << endl;
}

int main(int argc, char **argv) {
    std::cout << "STARTING GAME!!!" << std::endl;
    instructions();

    Engine::Start(argc, argv, setup);

    return 0;
}
