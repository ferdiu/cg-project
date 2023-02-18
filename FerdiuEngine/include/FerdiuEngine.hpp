
#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Scene.hpp"
#include "Screen.hpp"
#include "Texture.hpp"
#include "Physics.hpp"
#include "Material.hpp"
#include "Time.hpp"
#include "Components/Light.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Primitives.hpp"
#include "Components/Component.hpp"
#include "Components/Physic/SphereCollider.hpp"
#include "Components/Physic/RigidBody.hpp"
#include "Components/Physic/Collider.hpp"
#include "Components/Physic/BoxCollider.hpp"
#include "Components/Camera.hpp"
#include "Components/SphereRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/PlaneRenderer.hpp"
#include "Components/CubeRenderer.hpp"
#include "Components/Transform.hpp"
#include "utils/BitMapFile.hpp"
#include "utils/Math.hpp"
#include "utils/GLMatrices.hpp"
#include "utils/GLMatricesStack.hpp"
#include "utils/Debug.hpp"
#include "GameObject.hpp"

#include "FerdiuEngine_export.h"

#ifndef WIN_W
#define WIN_W 1280
#endif

#ifndef WIN_H
#define WIN_H 720
#endif

#ifndef PROJECT_NAME
#define PROJECT_NAME "FerdiuEngine Player"
#endif

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Engine
{
public:
    FERDIU_ENGINE_EXPORT static void Start(int argc, char **argv, void (*setup)(void));
    FERDIU_ENGINE_EXPORT static void onUpdate(void (*update)(void));
    FERDIU_ENGINE_EXPORT static void onResize(void (*resize)(int w, int h));
    FERDIU_ENGINE_EXPORT static void onMouseInput(void (*mouseControl)(int button, int state, int x, int y));
    FERDIU_ENGINE_EXPORT static void onKeyboardDown(void (*keyInput)(unsigned char key, int x, int y));
    FERDIU_ENGINE_EXPORT static void onKeyboardUp(void (*keyInputUp)(unsigned char key, int x, int y));
    FERDIU_ENGINE_EXPORT static void onMouseWheel(void (*mouseWheel)(int wheel, int direction, int x, int y));
    FERDIU_ENGINE_EXPORT static void onMouseMove(void (*mousePassive)(int x, int y));

private:
    static void update();
    static void fixedUpdate();

    static void (*userUpdate)(void);
};

}
