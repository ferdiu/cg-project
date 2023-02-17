# ref: https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake

# CMAKE version
cmake_minimum_required(VERSION 3.25)

# project definition
project(ferdiuengine VERSION 0.0.1 DESCRIPTION "Small game engine by Ferdiu")


########## MAIN ###############
# compiler falgs and build type
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-shared -std=c++17 -lfreetype -lglut -lGLU -lGL -lGLEW -lm -luuid -pedantic -Wall -Wextra -Werror")
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

# setting target
add_library(ferdiuengine SHARED ${SOURCES} ${PUBLIC_HEADERS})

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

# ignore warnings from reactphysics3d
set_target_properties(reactphysics3d PROPERTIES COMPILE_FLAGS "-w")
###############################


########## KDevelop ###########
# not really needed but KDevelop is complaining about missing glut otherwise...
include_directories(/usr/include)
include_directories(/usr/lib)
include_directories(/usr/include)
link_directories(/usr/lib64)
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
target_include_directories(ferdiuengine PUBLIC ${SRC_DIR})

include(GNUInstallDirs)

install(TARGETS ferdiuengine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
###############################
