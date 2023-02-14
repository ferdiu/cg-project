
# cmake version
cmake_minimum_required(VERSION 3.25)

# project name
project(cg-project)

####### DEFINITIONS ###########
# compiler flags and build mode
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-std=c++17 -lfreetype -lglut -lGLU -lGL -lGLEW -lm -pedantic -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_FORTIFY_SOURCE=2")

# define directories
set(SRC_DIR src)
set(INC_DIR include)

# include headers
# TODO:include(${INC_DIR}/CMakeLists.txt)
set(SOURCES
    FerdiuEngine/include/Time.hpp
    FerdiuEngine/include/Scene.hpp
    FerdiuEngine/include/Texture.hpp
    FerdiuEngine/include/Material.hpp
    FerdiuEngine/include/Vertex.hpp
    FerdiuEngine/include/Shader.hpp
    FerdiuEngine/include/Components/MeshRenderer.hpp
    FerdiuEngine/include/Components/Component.hpp
    FerdiuEngine/include/Components/Physic/SphereCollider.hpp
    FerdiuEngine/include/Components/Physic/Bounds.hpp
    FerdiuEngine/include/Components/Physic/RigidBody.hpp
    FerdiuEngine/include/Components/Physic/Collider.hpp
    FerdiuEngine/include/Components/Physic/BoxCollider.hpp
    FerdiuEngine/include/Components/Camera.hpp
    FerdiuEngine/include/Components/SphereRenderer.hpp
    FerdiuEngine/include/Components/Renderer.hpp
    FerdiuEngine/include/Components/CubeRenderer.hpp
    FerdiuEngine/include/Components/Transform.hpp
    FerdiuEngine/include/utils/BitMapFile.hpp
    FerdiuEngine/include/utils/GLMatrices.hpp
    FerdiuEngine/include/utils/GLMatricesStack.hpp
    FerdiuEngine/include/utils/Debug.hpp
    FerdiuEngine/include/FerdiuEngine.hpp
    FerdiuEngine/include/GameObject.hpp
    FerdiuEngine/include/FerdiuEngine_export.h
)


add_subdirectory(FerdiuEngine)
###############################

add_executable(cg-project main.cpp ${SOURCES})
include_directories(FerdiuEngine/include)

# link ferdiuengine to main
target_link_libraries(cg-project ferdiuengine)

# not really needed but KDevelop is complaining about missing glut otherwise...
include_directories(/usr/include)
include_directories(/usr/lib)
include_directories(/usr/include)
link_directories(/usr/lib64)
link_directories(/usr/lib32)

####### OPENGL #######
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_dependencies(cg-project OpenGL::OpenGL)

target_link_libraries(cg-project OpenGL::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
######################


##### FINALIZE #####
target_include_directories(cg-project PRIVATE ${INC_DIR})

install(TARGETS cg-project RUNTIME DESTINATION bin)


