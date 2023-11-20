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

option(FENG_VERBOSE "Enable this to add verbose debug messages" OFF)
option(FENG_MATRICES "Enable this to add proj, view and model matrices to be printed (needs DEBUG_VERBOSE)" OFF)
option(FENG_RENDERING "Enable this to add rendering debug infos (needs DEBUG_VERBOSE)" OFF)
option(FENG_PHYSICS "Enable this to add physics debug infos (needs DEBUG_VERBOSE)" OFF)
option(FENG_NO_INDENT "Disable debug log indentation" OFF)

if(FENG_VERBOSE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_VERBOSE")
endif()
if(FENG_MATRICES)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MATRICES")
endif()
if(FENG_RENDERING)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_RENDERING")
endif()
if(FENG_PHYSICS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_PHYSICS")
endif()
if(FENG_NO_INDENT)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_NO_INDENT")
endif()

# dir definitions
set(SRC_DIR src)
set(INC_DIR include)

# add sources to SOURCES
include(${SRC_DIR}/CMakeLists.txt)

# add headers to PUBLIC_HEADERS
include(${INC_DIR}/CMakeLists.txt)

# NOTE: ugly!!!
set(PHYSICS_HEADS
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


########### BULLET3 ###########
# specify the OpenGL version to use (who needs legacy?)
set(OpenGL_GL_PREFERENCE "GLVND")

# add all headers of bullet3
add_subdirectory(bullet3)
include_directories(bullet3/src)

# link bullet3 to ferdiuengine
target_link_libraries(ferdiuengine
    Bullet3Common
    Bullet3Collision
    BulletInverseDynamics
    Bullet3Dynamics
    BulletSoftBody
    BulletDynamics
    Bullet3OpenCL_clew
    Bullet2FileLoader
    BulletCollision
    Bullet3Geometry
    LinearMath
)

set_target_properties(Bullet3Common PROPERTIES CXX_VISIBILITY_PRESET default)
# ignore warnings from bullet3
target_compile_options(Bullet3Common PRIVATE -std=c++17 -w -fPIC)
target_compile_options(Bullet3Collision PRIVATE -std=c++17 -w -fPIC)
target_compile_options(BulletInverseDynamics PRIVATE -std=c++17 -w -fPIC)
target_compile_options(Bullet3Dynamics PRIVATE -std=c++17 -w -fPIC)
target_compile_options(BulletSoftBody PRIVATE -std=c++17 -w -fPIC)
target_compile_options(BulletDynamics PRIVATE -std=c++17 -w -fPIC)
target_compile_options(Bullet3OpenCL_clew PRIVATE -std=c++17 -w -fPIC)
target_compile_options(Bullet2FileLoader PRIVATE -std=c++17 -w -fPIC)
target_compile_options(BulletCollision PRIVATE -std=c++17 -w -fPIC)
target_compile_options(Bullet3Geometry PRIVATE -std=c++17 -w -fPIC)
target_compile_options(LinearMath PRIVATE -std=c++17 -w -fPIC)
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
