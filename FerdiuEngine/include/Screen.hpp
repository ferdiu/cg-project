
#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Components/Camera.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Screen
{
public:
    typedef enum FERDIU_ENGINE_EXPORT ResizeMode
    {
        STRETCH,
        KEEP_ASPECT,
        KEEP_WIDTH,
        KEEP_HEIGHT,
        EXPAND
    } ResizeMode;

    // screen
    FERDIU_ENGINE_EXPORT static int width();
    FERDIU_ENGINE_EXPORT static int height();
    FERDIU_ENGINE_EXPORT static int centerX();
    FERDIU_ENGINE_EXPORT static int centerY();
    FERDIU_ENGINE_EXPORT static float ratio();

    // window
    FERDIU_ENGINE_EXPORT static int windowX();
    FERDIU_ENGINE_EXPORT static int windowY();

    FERDIU_ENGINE_EXPORT static int windowWidth();
    FERDIU_ENGINE_EXPORT static int windowHeight();
    FERDIU_ENGINE_EXPORT static float windowRatio();
    FERDIU_ENGINE_EXPORT static float windowInitialRatio();

    // viewport
    FERDIU_ENGINE_EXPORT static int viewportWidth();
    FERDIU_ENGINE_EXPORT static int viewportHeight();
    FERDIU_ENGINE_EXPORT static int viewportX();
    FERDIU_ENGINE_EXPORT static int viewportY();

    // resize modes
    FERDIU_ENGINE_EXPORT static void setMode(ResizeMode mode);
    FERDIU_ENGINE_EXPORT static ResizeMode getMode();
    FERDIU_ENGINE_EXPORT static void resize(int w, int h);

    // fullscreen
    FERDIU_ENGINE_EXPORT static void fullscreen(bool v);
    FERDIU_ENGINE_EXPORT static bool fullscreen();

    // personal function
    FERDIU_ENGINE_EXPORT static void onResize(void (*f)(int w, int h));

private:
    static ResizeMode mode;

    static bool _fullscreen;
    static int _oldPos[2];
    static int _oldSize[2];

    static void (*f)(int w, int h);

    static int viewportSize[2];

    static void setViewportSize(int x, int y, int w, int h);

    static void stretch(Camera& c, int w, int h);
    static void keepAspect(Camera& c, int w, int h);
    static void keepWidth(Camera& c, int w, int h);
    static void keepHeight(Camera& c, int w, int h);
    static void expand(Camera& c, int w, int h);
};

}
