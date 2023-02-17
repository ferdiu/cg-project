
#include "../include/utils/Debug.hpp"
#include "../include/Physics.hpp"
#include "../include/Time.hpp"

namespace FerdiuEngine
{

void Physics::init()
{
    if (_initialized)
    {
        Debug::Error("Trying to initialize again Physics module!");
        return;
    }
    physicsCommon.destroyPhysicsWorld(_world);
    _world = physicsCommon.createPhysicsWorld();
    _world->setEventListener(&listener);
    _initialized = true;
}

reactphysics3d::PhysicsCommon& Physics::common()
{
    return Physics::physicsCommon;
}

reactphysics3d::PhysicsWorld& Physics::world()
{
    return *Physics::_world;
}

float Physics::accumulator()
{
    return _accumulator;
}

void Physics::update()
{
    // Add the time difference in the accumulator
    _accumulator += Time::deltaTime();

    // While there is enough accumulated time to take
    // one or several physics steps
    while (_accumulator >= PHYSICS_TIME_STEP) {

        // Update the Dynamics world with a constant time step
        world().update(PHYSICS_TIME_STEP);

        // Decrease the accumulated time
        _accumulator -= PHYSICS_TIME_STEP;
    }
}

bool Physics::_initialized = false;
reactphysics3d::PhysicsWorld *Physics::_world = Physics::physicsCommon.createPhysicsWorld();
reactphysics3d::PhysicsCommon Physics::physicsCommon = reactphysics3d::PhysicsCommon();
PhysicsEventListener Physics::listener = PhysicsEventListener();
float Physics::_accumulator = 0;

}
