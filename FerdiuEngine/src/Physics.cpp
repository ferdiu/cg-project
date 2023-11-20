
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

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = (btBroadphaseInterface*) new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	Physics::_world = new btDiscreteDynamicsWorld(
                        dispatcher, overlappingPairCache,
                        solver, collisionConfiguration);

	Physics::_world->setGravity(btVector3(0, -9.81, 0));

    _initialized = true;

#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] finish->init");
#endif
}

btDiscreteDynamicsWorld& Physics::world()
{
    return *Physics::_world;
}

void Physics::update()
{
#ifdef DEBUG_PHYSICS
    Debug::indent();
    Debug::Log("[Physics] start->update");
#endif

    int maxStep = 10;
    // TODO: read documentation more at:
    // https://pybullet.org/Bullet/BulletFull/classbtDiscreteDynamicsWorld.html#a9776089cc4e4a767ff43147127444773
    _world->stepSimulation(Time::fixedDeltaTimeStep(), maxStep, Time::fixedDeltaTimeStep());

#ifdef DEBUG_PHYSICS
    Debug::Log("[Physics] finish->update");
    Debug::unindent();
#endif
}

bool Physics::_initialized = false;
btDiscreteDynamicsWorld *Physics::_world = nullptr;

}
