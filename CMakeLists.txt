
# cmake version
cmake_minimum_required(VERSION 3.25)

# project name
project(cg-project)

########## MAIN ###############
# compiler flags and build mode
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS "-std=c++17 -lfreetype -lglut -lGLU -lGL -lGLEW -lm -pedantic -Wall -Wextra -Werror -Wno-error=type-limits")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_FORTIFY_SOURCE=2")

# define directories
set(SRC_DIR src)
set(INC_DIR include)

# include headers sources
include(${SRC_DIR}/CMakeLists.txt)
include(${INC_DIR}/CMakeLists.txt)

# copy shaders to bin directory
include(shaders/CMakeLists.txt)
# copy resources to bin directory
include(resources/CMakeLists.txt)

add_executable(cg-project main.cpp ${SRCS})
###############################


######## FerdiuEngine #########
# add all headers of FerdiuEngine NOTE: ugly but functional
include(FerdiuEngine/include/CMakeLists.txt)
foreach(H IN LISTS PUBLIC_HEADERS)
    list(APPEND SRCS FerdiuEngine/${H})
endforeach()

add_subdirectory(FerdiuEngine)
include_directories(FerdiuEngine/include)

# link ferdiuengine to main
target_link_libraries(cg-project ferdiuengine)
###############################


########## KDevelop ###########
# not really needed but KDevelop is complaining about missing glut otherwise...
include_directories(FerdiuEngine/reactphysics3d/include)
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

add_dependencies(cg-project OpenGL::OpenGL)

target_link_libraries(cg-project OpenGL::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
###############################


######## FINALIZE #############
target_include_directories(cg-project PRIVATE ${INC_DIR})

install(TARGETS cg-project RUNTIME DESTINATION bin)
###############################
