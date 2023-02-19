
#include "../include/utils/Debug.hpp"
#include "../include/Physics.hpp"
#include "../include/Time.hpp"

namespace FerdiuEngine
{

void PhysicsEventListener::onContact(rp3d::CollisionCallback::CallbackData const& data)
{
    Debug::Log("CONTACT!!");
}
void PhysicsEventListener::onTrigger (rp3d::OverlapCallback::CallbackData const& data)
{
    Debug::Log("TRIGGER!!");
}


rp3d::DefaultLogger *addLogger(rp3d::PhysicsCommon &physicsCommon)
{
    // Create the default logger
    rp3d::DefaultLogger* logger = physicsCommon.createDefaultLogger();

    // Log level (warnings and errors)
    uint logLevel = static_cast<uint>(
        static_cast<uint>(rp3d::Logger::Level::Warning) |
        static_cast<uint>(rp3d::Logger::Level::Error));

    // Output the logs into the standard output
    logger->addStreamDestination(std::cout, logLevel, rp3d::DefaultLogger::Format::Text);

    // Set the logger
    physicsCommon.setLogger(logger);

    return logger;
}

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

    listener = new PhysicsEventListener();

    rp3d::PhysicsWorld::WorldSettings s;
    s.worldName = "PhysicsWorld";
    s.isSleepingEnabled = false;

// #ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Physics] start->PhysicsWorld::WorldSettings");
    std::cout << s.to_string();
    Debug::Log("[Physics] finish->PhysicsWorld::WorldSettings");
    Debug::unindent();
// #endif

    physicsCommon = new rp3d::PhysicsCommon();
    _world = physicsCommon->createPhysicsWorld(s);
    _world->setEventListener(listener);
    _initialized = true;

#ifdef DEBUG
    addLogger(*physicsCommon);
#endif

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
    _accumulator += Time::fixedDeltaTime();

    // While there is enough accumulated time to take
    // one or several physics steps
    do {
        // Update the Dynamics world with a constant time step
        world().update(Time::fixedDeltaTimeStep());

        // Decrease the accumulated time
        _accumulator -= Time::fixedDeltaTimeStep();
    } while (_accumulator >= Time::fixedDeltaTimeStep());

#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] finish->update");
    Debug::unindent();
#endif
}

bool Physics::_initialized = false;
rp3d::PhysicsWorld *Physics::_world = nullptr;
rp3d::PhysicsCommon *Physics::physicsCommon = nullptr;
PhysicsEventListener *Physics::listener = nullptr;
float Physics::_accumulator = 0;

}
