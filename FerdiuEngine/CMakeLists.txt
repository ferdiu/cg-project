# ref: https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake

# CMAKE version
cmake_minimum_required(VERSION 3.25)

# project definition
project(ferdiuengine VERSION 0.0.1 DESCRIPTION "Small game engine by Ferdiu")


########## MAIN ###############
# compiler falgs and build type
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-shared -std=c++17 -lfreetype -lglut -lGLU -lGL -lGLEW -lm -luuid -pedantic -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_FORTIFY_SOURCE=2")

# NOTE: enable this to add verbose debug messages
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_VERBOSE")
# NOTE: enable this to add proj, view and model matrices to be printed (needs DEBUG_VERBOSE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MATRICES")
# NOTE: enable this to add rendering debug infos (needs DEBUG_VERBOSE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_RENDERING")
# NOTE: disable debug log indentation
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_NO_INDENT")

# dir definitions
set(SRC_DIR src)
set(INC_DIR include)

# add sources to SOURCES
include(${SRC_DIR}/CMakeLists.txt)

# add headers to PUBLIC_HEADERS
include(${INC_DIR}/CMakeLists.txt)

# NOTE: ugly!!!
set(PHYSICS_HEADS
    # "reactphysics3d/include/reactphysics3d/reactphysics3d.h"
    # "reactphysics3d/include/reactphysics3d/configuration.h"
    # "reactphysics3d/include/reactphysics3d/decimal.h"
    # "reactphysics3d/include/reactphysics3d/body/CollisionBody.h"
    # "reactphysics3d/include/reactphysics3d/body/RigidBody.h"
    # "reactphysics3d/include/reactphysics3d/collision/ContactPointInfo.h"
    # "reactphysics3d/include/reactphysics3d/collision/ContactManifoldInfo.h"
    # "reactphysics3d/include/reactphysics3d/collision/ContactPair.h"
    # "reactphysics3d/include/reactphysics3d/collision/broadphase/DynamicAABBTree.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/CollisionDispatch.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInput.h"
    # "reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/AABB.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/ConvexShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/ConvexPolyhedronShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/BoxShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/CapsuleShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/CollisionShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/ConvexMeshShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/SphereShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/TriangleShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveMeshShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/shapes/HeightFieldShape.h"
    # "reactphysics3d/include/reactphysics3d/collision/RaycastInfo.h"
    # "reactphysics3d/include/reactphysics3d/collision/Collider.h"
    # "reactphysics3d/include/reactphysics3d/collision/TriangleVertexArray.h"
    # "reactphysics3d/include/reactphysics3d/collision/PolygonVertexArray.h"
    # "reactphysics3d/include/reactphysics3d/collision/TriangleMesh.h"
    # "reactphysics3d/include/reactphysics3d/collision/PolyhedronMesh.h"
    # "reactphysics3d/include/reactphysics3d/collision/HalfEdgeStructure.h"
    # "reactphysics3d/include/reactphysics3d/collision/ContactManifold.h"
    # "reactphysics3d/include/reactphysics3d/constraint/BallAndSocketJoint.h"
    # "reactphysics3d/include/reactphysics3d/constraint/ContactPoint.h"
    # "reactphysics3d/include/reactphysics3d/constraint/FixedJoint.h"
    # "reactphysics3d/include/reactphysics3d/constraint/HingeJoint.h"
    # "reactphysics3d/include/reactphysics3d/constraint/Joint.h"
    # "reactphysics3d/include/reactphysics3d/constraint/SliderJoint.h"
    # "reactphysics3d/include/reactphysics3d/engine/Entity.h"
    # "reactphysics3d/include/reactphysics3d/engine/EntityManager.h"
    # "reactphysics3d/include/reactphysics3d/engine/PhysicsCommon.h"
    # "reactphysics3d/include/reactphysics3d/systems/ConstraintSolverSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/ContactSolverSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/DynamicsSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/CollisionDetectionSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/SolveBallAndSocketJointSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/SolveFixedJointSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/SolveHingeJointSystem.h"
    # "reactphysics3d/include/reactphysics3d/systems/SolveSliderJointSystem.h"
    # "reactphysics3d/include/reactphysics3d/engine/PhysicsWorld.h"
    # "reactphysics3d/include/reactphysics3d/engine/EventListener.h"
    # "reactphysics3d/include/reactphysics3d/engine/Island.h"
    # "reactphysics3d/include/reactphysics3d/engine/Islands.h"
    # "reactphysics3d/include/reactphysics3d/engine/Material.h"
    # "reactphysics3d/include/reactphysics3d/engine/OverlappingPairs.h"
    # "reactphysics3d/include/reactphysics3d/systems/BroadPhaseSystem.h"
    # "reactphysics3d/include/reactphysics3d/components/Components.h"
    # "reactphysics3d/include/reactphysics3d/components/CollisionBodyComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/RigidBodyComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/TransformComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/ColliderComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/JointComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/BallAndSocketJointComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/FixedJointComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/HingeJointComponents.h"
    # "reactphysics3d/include/reactphysics3d/components/SliderJointComponents.h"
    # "reactphysics3d/include/reactphysics3d/collision/CollisionCallback.h"
    # "reactphysics3d/include/reactphysics3d/collision/OverlapCallback.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/mathematics.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/mathematics_common.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/mathematics_functions.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Matrix2x2.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Matrix3x3.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Quaternion.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Transform.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Vector2.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Vector3.h"
    # "reactphysics3d/include/reactphysics3d/mathematics/Ray.h"
    # "reactphysics3d/include/reactphysics3d/memory/MemoryAllocator.h"
    # "reactphysics3d/include/reactphysics3d/memory/PoolAllocator.h"
    # "reactphysics3d/include/reactphysics3d/memory/SingleFrameAllocator.h"
    # "reactphysics3d/include/reactphysics3d/memory/HeapAllocator.h"
    # "reactphysics3d/include/reactphysics3d/memory/DefaultAllocator.h"
    # "reactphysics3d/include/reactphysics3d/memory/MemoryManager.h"
    # "reactphysics3d/include/reactphysics3d/containers/Stack.h"
    # "reactphysics3d/include/reactphysics3d/containers/LinkedList.h"
    # "reactphysics3d/include/reactphysics3d/containers/Array.h"
    # "reactphysics3d/include/reactphysics3d/containers/Map.h"
    # "reactphysics3d/include/reactphysics3d/containers/Set.h"
    # "reactphysics3d/include/reactphysics3d/containers/Pair.h"
    # "reactphysics3d/include/reactphysics3d/containers/Deque.h"
    # "reactphysics3d/include/reactphysics3d/utils/Profiler.h"
    # "reactphysics3d/include/reactphysics3d/utils/Logger.h"
    # "reactphysics3d/include/reactphysics3d/utils/DefaultLogger.h"
    # "reactphysics3d/include/reactphysics3d/utils/DebugRenderer.h"
)

# setting target
add_library(ferdiuengine SHARED ${SOURCES} ${PUBLIC_HEADERS} ${PHYSICS_HEADS})

# Make all non-exported symbols hidden by default
set_target_properties(ferdiuengine PROPERTIES CXX_VISIBILITY_PRESET hidden)
# Treat the public symbols as exported
target_compile_definitions(ferdiuengine PRIVATE "FERDIU_ENGINE_BUILD")
# Export the library's public header path to dependent targets
target_include_directories(ferdiuengine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# set properties for version
set_target_properties(ferdiuengine PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(ferdiuengine PROPERTIES SOVERSION 0)
set_target_properties(ferdiuengine PROPERTIES PUBLIC_HEADER ${MAIN_API_HEADER})
###############################


######## ReactPhysics3D #######
# add all headers of reactphysics3d
add_subdirectory(reactphysics3d)
include_directories(reactphysics3d/include)

# link ReactPhysics3D to ferdiuengine
target_link_libraries(ferdiuengine reactphysics3d)

set_target_properties(reactphysics3d PROPERTIES CXX_VISIBILITY_PRESET default)
# ignore warnings from reactphysics3d
target_compile_options(reactphysics3d PRIVATE -std=c++17 -w -fPIC)
###############################


########## KDevelop ###########
# not really needed but KDevelop is complaining about missing glut otherwise...
include_directories(/usr/include)
include_directories(/usr/lib)
link_directories(/usr/lib64)
link_directories(/usr/lib32)
link_directories(/usr/lib)
###############################


########### OPENGL ############
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_dependencies(ferdiuengine OpenGL::OpenGL)

target_link_libraries(ferdiuengine OpenGL::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
###############################


######## FINALIZE #############
target_include_directories(ferdiuengine PUBLIC ${INC_DIR})
target_include_directories(ferdiuengine PRIVATE ${SRC_DIR})

include(GNUInstallDirs)

install(TARGETS ferdiuengine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
###############################
