
#pragma once

// Fixed delta time value
#ifndef FIXED_DELTA_TIME_MILLISEC
#define FIXED_DELTA_TIME_MILLISEC 16 // about 1 / 60
#endif

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Time
{
public:
    FERDIU_ENGINE_EXPORT static Time *_instance;
    FERDIU_ENGINE_EXPORT static Time& instance()
    {
        if (_instance == nullptr)
            _instance = new Time();

        return *_instance;
    }
    // Get time passed from last rendered frame
    FERDIU_ENGINE_EXPORT static float deltaTime();
    // Get time passed from last glutTimerFunc call (see startFixedDeltaTime)
    FERDIU_ENGINE_EXPORT static float fixedDeltaTime();

    // Get time passed from last rendered frame scaled by scale
    FERDIU_ENGINE_EXPORT static float scaledDeltaTime();
    // Get time passed from last glutTimerFunc call scaled by scale
    FERDIU_ENGINE_EXPORT static float scaledFixedDeltaTime();

    // get time scale
    FERDIU_ENGINE_EXPORT static float scale();
    // set time scale
    FERDIU_ENGINE_EXPORT static void scale(float value);

    // set update routine
    FERDIU_ENGINE_EXPORT static void setUpdateRoutine(void (*updateRoutine)(void));

    // delete unwanted operators
    FERDIU_ENGINE_EXPORT Time(Time const&)            = delete;
    FERDIU_ENGINE_EXPORT void operator=(Time const&)  = delete;

private:
    float _lastTime = 0.0f;
    float _fixed_lastTime = 0.0f;

    float _deltaTime = 0.0f;
    float _fixedDeltaTime = 0.0f;

    float _scale = 1.0f;

    void (*updateRoutine)(void);

    // private constructor (Singleton!)
    Time();

    // Update DeltaTime (should be called at each frame)
    static void updateDeltaTime();
    // Update FixedDeltaTime (see startFixedDeltaTime)
    static void updateFixedDeltaTime(int n);
};

}
