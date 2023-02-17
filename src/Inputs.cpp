
#include "../include/Inputs.hpp"

using namespace FerdiuEngine;

static bool mouseCaptured = false;

// Handle user keyboard input.
void mouseControl(int button, int state, int x, int y) {
    (void) x;
    (void) y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutSetCursor(GLUT_CURSOR_NONE);
        mouseCaptured = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        glutSetCursor(GLUT_CURSOR_INHERIT);
        mouseCaptured = false;
    }

    glutPostRedisplay();
}

// Handle user keyboard input.
void keyInput(unsigned char key, int x, int y) {
    (void) x;
    (void) y;
    switch (key) {
        case 27: exit(0); break;
        case 'f': case 'F': Screen::fullscreen(!Screen::fullscreen()); break;
    }
}

// Capture mouse at the center of the screen.
void captureMouse()
{
    glutWarpPointer(
        glutGet(GLUT_WINDOW_WIDTH) / 2,
        glutGet(GLUT_WINDOW_HEIGHT) / 2
    );
}

void mousePassive(Board *b, Camera *c, int x, int y)
{
    int dev_x, dev_y;
    dev_x = (glutGet(GLUT_WINDOW_WIDTH) / 2) - x;
    dev_y = (glutGet(GLUT_WINDOW_HEIGHT) / 2) - y;
    if (mouseCaptured)
    {
        b->addTilt(glm::vec2(TILT_SCALE * dev_x, TILT_SCALE * dev_y));
        glm::vec2 tilt = b->getTilt();
        c->getOwner()->setPosition(glm::vec3(tilt[0] * 5, CAMERA_Y, tilt[1] * 5));
    }
}

void update()
{
    if (mouseCaptured)
        captureMouse();
}
