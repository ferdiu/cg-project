
#include "../include/utils/Debug.hpp"
#include "../include/Physics.hpp"
#include "../include/Time.hpp"

namespace FerdiuEngine
{

void Physics::init()
{
#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] start->init");
#endif

    if (_initialized)
    {
        Debug::Error("Trying to initialize again Physics module!");
        return;
    }

    physicsCommon = new rp3d::PhysicsCommon();
    _world = physicsCommon->createPhysicsWorld();
    _world->setEventListener(listener);
    _initialized = true;

#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] finish->init");
#endif
}

rp3d::PhysicsCommon& Physics::common()
{
    return *Physics::physicsCommon;
}

rp3d::PhysicsWorld& Physics::world()
{
    return *Physics::_world;
}

float Physics::accumulator()
{
    return _accumulator;
}

void Physics::update()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Physics] start->update");
#endif

    // Add the time difference in the accumulator
    _accumulator += Time::deltaTime();

    // While there is enough accumulated time to take
    // one or several physics steps
    do {

        // Update the Dynamics world with a constant time step
        world().update(PHYSICS_TIME_STEP);

        // Decrease the accumulated time
        _accumulator -= PHYSICS_TIME_STEP;
    } while (_accumulator >= PHYSICS_TIME_STEP);

#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] start->update");
    Debug::unindent();
#endif
}

bool Physics::_initialized = false;
rp3d::PhysicsWorld *Physics::_world = nullptr;
rp3d::PhysicsCommon *Physics::physicsCommon = nullptr;
PhysicsEventListener *Physics::listener = new PhysicsEventListener();
float Physics::_accumulator = 0;

}
