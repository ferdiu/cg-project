
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

#include <FerdiuEngine.hpp>
#include "../include/Board.hpp"

#define CAMERA_Y 30
#define TILT_SCALE 0.005

void mouseControl(int button, int state, int x, int y);
void keyInput(unsigned char key, int x, int y);
void captureMouse();
void mousePassive(Board *b, FerdiuEngine::Camera *c, int x, int y);
void update();
