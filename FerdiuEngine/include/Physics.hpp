
#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "FerdiuEngine_export.h"

#define PHYSICS_TIME_STEP 0.016666666666666666 // 1/60

namespace FerdiuEngine
{

// Your event listener class
class FERDIU_ENGINE_EXPORT PhysicsEventListener : public reactphysics3d::EventListener
{
};

class FERDIU_ENGINE_EXPORT Physics
{
public:
    FERDIU_ENGINE_EXPORT static void init();

    FERDIU_ENGINE_EXPORT static reactphysics3d::PhysicsCommon& common();

    FERDIU_ENGINE_EXPORT static reactphysics3d::PhysicsWorld& world();

    FERDIU_ENGINE_EXPORT static float accumulator();

private:
    static bool _initialized;

    static reactphysics3d::PhysicsCommon physicsCommon;
    static reactphysics3d::PhysicsWorld *_world;
    static PhysicsEventListener listener;

    static float _accumulator;
    static void update(); friend class Engine;
};

}
