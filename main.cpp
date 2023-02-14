
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "FerdiuEngine/include/Components/Component.hpp"
#include "FerdiuEngine/include/FerdiuEngine.hpp"

using namespace FerdiuEngine;
using namespace std;
using namespace glm;

void setup()
{
    std::cout << "STARTING GAME!!!" << std::endl;

    Camera::getCurrent()->setClearColor(vec3(1));

    GameObject *go = new GameObject("Test");
    go->instantiate(Scene::getCurrent()->root());
}

int main(int argc, char **argv) {
    Engine::Start(argc, argv, setup);

    return 0;
}
