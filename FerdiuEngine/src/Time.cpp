
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../include/Time.hpp"

namespace FerdiuEngine
{

// private constructor
Time::Time()
{
    glutTimerFunc(FIXED_DELTA_TIME_MILLISEC, Time::updateFixedDeltaTime, 0);
}

// Update DeltaTime (should be called at each frame)
void Time::updateDeltaTime() {
    float currentTime = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    Time::instance()._deltaTime = currentTime - Time::instance()._lastTime;
    Time::instance()._lastTime = currentTime;
}

// Update FixedDeltaTime (see startFixedDeltaTime)
void Time::updateFixedDeltaTime(int n) {
    (void) n;

    float currentTime = (float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    Time::instance()._fixedDeltaTime = currentTime - Time::instance()._fixed_lastTime;
    Time::instance()._fixed_lastTime = currentTime;

    if (Time::instance().updateRoutine != nullptr)
        Time::instance().updateRoutine();

    glutTimerFunc(FIXED_DELTA_TIME_MILLISEC, updateFixedDeltaTime, 0);
}

// Get time passed from last rendered frame
float Time::deltaTime()
{
    return Time::instance()._deltaTime;
}

// Get time passed from last glutTimerFunc call (see startFixedDeltaTime)
float Time::fixedDeltaTime()
{
    return Time::instance()._fixedDeltaTime;
}

// Get time passed from last rendered frame scaled by scale
float Time::scaledDeltaTime()
{
    return Time::instance()._deltaTime * Time::instance()._scale;
}

// Get time passed from last glutTimerFunc call scaled by scale
float Time::scaledFixedDeltaTime()
{
    return Time::instance()._fixedDeltaTime * Time::instance()._scale;
}

// get time scale
float Time::scale()
{
    return Time::instance()._scale;
}
// set time scale
void Time::scale(float value)
{
    Time::instance()._scale = value;
}

void Time::setUpdateRoutine(void (*updateRoutine)(void))
{
    Time::instance().updateRoutine = updateRoutine;
}

Time* Time::_instance = nullptr;

}
