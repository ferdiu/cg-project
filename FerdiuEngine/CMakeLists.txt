# ref: https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake

# CMAKE version
cmake_minimum_required(VERSION 3.25)

# project definition
project(libferdiuengine VERSION 0.0.1 DESCRIPTION "Small game engine by Ferdiu")


####### DEFINITIONS ###########
# compiler falgs and build type
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-std=c++17 -lfreetype -lglut -lGLU -lGL -lGLEW -lm -pedantic -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_FORTIFY_SOURCE=2")

# dir definitions
set(SRC_DIR src)
set(INC_DIR include)

# add sources to SOURCES
include(${SRC_DIR}/CMakeLists.txt)

# add headers to PUBLIC_HEADERS
include(${INC_DIR}/CMakeLists.txt)

###############################

# setting target
add_library(libferdiuengine ${SOURCES} ${PUBLIC_HEADERS})

# set properties for version
set_target_properties(libferdiuengine PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(libferdiuengine PROPERTIES SOVERSION 0)
set_target_properties(libferdiuengine PROPERTIES PUBLIC_HEADER ${MAIN_API_HEADER})

# not really needed but KDevelop is complaining about missing glut otherwise...
include_directories(/usr/include)
include_directories(/usr/lib)
include_directories(/usr/include)
link_directories(/usr/lib64)
link_directories(/usr/lib)


####### OPENGL #######
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_dependencies(libferdiuengine OpenGL::OpenGL)

target_link_libraries(libferdiuengine OpenGL::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
######################


##### FINALIZE #####
target_include_directories(libferdiuengine PRIVATE ${INC_DIR})
target_include_directories(libferdiuengine PRIVATE ${SRC_DIR})

include(GNUInstallDirs)

install(TARGETS libferdiuengine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


