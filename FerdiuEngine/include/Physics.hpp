
#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#include <btBulletDynamicsCommon.h>
#pragma GCC diagnostic pop

#include "utils/Debug.hpp"

#include "FerdiuEngine_export.h"

#define PHYSICS_TIME_STEP 0.016666666666666666 // 1/60

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Physics
{
public:
    FERDIU_ENGINE_EXPORT static void init();

    FERDIU_ENGINE_EXPORT static btDiscreteDynamicsWorld& world();

private:
    static bool _initialized;

    static btDiscreteDynamicsWorld *_world;

    static void update(); friend class Engine;
};

}
