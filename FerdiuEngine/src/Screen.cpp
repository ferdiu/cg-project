
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <asm-generic/errno.h>

#include "../include/Screen.hpp"
#include "../include/Components/Camera.hpp"

namespace FerdiuEngine
{

// screen
int Screen::width()
{
    return glutGet(GLUT_SCREEN_WIDTH);
}
int Screen::height()
{
    return glutGet(GLUT_SCREEN_HEIGHT);
}
int Screen::centerX()
{
    return width()/2;
}
int Screen::centerY()
{
    return height()/2;
}
float Screen::ratio()
{
    return width() / (float) height();
}

// window
int Screen::windowX()
{
    return glutGet(GLUT_WINDOW_X);
}
int Screen::windowY()
{
    return glutGet(GLUT_WINDOW_Y);
}

int Screen::windowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}
int Screen::windowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}
float Screen::windowRatio()
{
    return windowWidth() / (float) windowHeight();
}
float Screen::windowInitialRatio()
{
    return glutGet(GLUT_INIT_WINDOW_WIDTH) / (float) glutGet(GLUT_INIT_WINDOW_HEIGHT);
}

// viewport
int Screen::viewportWidth()
{
    return viewportSize[0];
}
int Screen::viewportHeight()
{
    return viewportSize[0];
}
int Screen::viewportX()
{
    return (windowWidth() - viewportWidth()) / 2;
}
int Screen::viewportY()
{
    return (windowHeight() - viewportHeight()) / 2;
}

// resize modes
void Screen::setMode(Screen::ResizeMode mode)
{
    Screen::mode = mode;
}
Screen::ResizeMode Screen::getMode()
{
    return mode;
}

void Screen::stretch(Camera& c, int w, int h)
{
    float r = windowInitialRatio();
    setViewportSize(0, 0, w, h);
    c.setParameterMults(r, r);
}

void Screen::keepAspect(Camera& c, int w, int h)
{
    float ir = windowInitialRatio();
    float nr = (w / (float) h);
    float finalMult;

    if (ir <= nr)
    {
        int finalWidth = (int) round(w / ir);
        setViewportSize((w - finalWidth) / 2, 0, finalWidth, h);
        finalMult = (float)finalWidth / h;
        c.setParameterMults(finalMult, finalMult);
    }
    else
    {
        int finalHeight = (int) round(w * ir);
        setViewportSize(0, (h - finalHeight) / 2, w, finalHeight);
        finalMult = (float)finalHeight / w;
        c.setParameterMults(1, 1, finalMult, finalMult);
    }
}

void Screen::keepWidth(Camera& c, int w, int h)
{
    float revRatio = 1.0 / windowRatio();
    setViewportSize(0, 0, w, h);
    c.setParameterMults(1, 1, revRatio, revRatio);
}

void Screen::keepHeight(Camera& c, int w, int h)
{
    float r = windowRatio();
    setViewportSize(0, 0, w, h);
    c.setParameterMults(r, r);
}

void Screen::expand(Camera& c, int w, int h)
{
    if (windowInitialRatio() < ((float) w / (float) h))
        keepHeight(c, w, h);
    else
        keepWidth(c, w, h);
}

void Screen::resize(int w, int h)
{
    Camera *c = Camera::getCurrent();

    if (nullptr == c)
        return;

    switch (mode)
    {
        case STRETCH: stretch(*c, w, h); break;
        case KEEP_ASPECT: keepAspect(*c, w, h); break;
        case KEEP_WIDTH: keepWidth(*c, w, h); break;
        case KEEP_HEIGHT: keepHeight(*c, w, h); break;
        case EXPAND: expand(*c, w, h); break;
    }

    c->updateProjectionMatrix();

    // eventually call user defined function
    if (nullptr != f) f(w, h);

    glutPostRedisplay();
}

void Screen::setViewportSize(int x, int y, int w, int h)
{
    viewportSize[0] = w;
    viewportSize[1] = h;
    glViewport(x, y, w, h);
}

// fullscreen
void Screen::fullscreen(bool v)
{
    _fullscreen = v;

    if (_fullscreen)
    {
        glutReshapeWindow(_oldSize[0], _oldSize[1]);
        glutPositionWindow(_oldPos[0], _oldPos[1]);
    }
    else
    {
        _oldSize[0] = windowWidth();
        _oldSize[1] = windowHeight();
        _oldPos[0] = windowX();
        _oldPos[1] = windowHeight();
        glutFullScreen();
    }
}
bool Screen::fullscreen()
{
    return _fullscreen;
}

// personal function
void Screen::onResize(void (*f)(int w, int h))
{
    Screen::f = f;
}

Screen::ResizeMode Screen::mode = Screen::KEEP_ASPECT;

bool Screen::_fullscreen = false;
int Screen::_oldPos[2] = { 0, 0 };
int Screen::_oldSize[2] = { 800, 600 };

int Screen::viewportSize[2] = { 0, 0 };

void (*Screen::f)(int w, int h) = nullptr;

}
