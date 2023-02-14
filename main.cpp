
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "FerdiuEngine/include/Components/Component.hpp"
#include "FerdiuEngine/include/FerdiuEngine.hpp"

using namespace FerdiuEngine;

void setup()
{
}

int main(int argc, char **argv) {
    Engine::Start(argc, argv, setup);

    return 0;
}
