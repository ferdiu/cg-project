
#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Scene.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Component.hpp"
#include "Components/Physic/SphereCollider.hpp"
#include "Components/Physic/Bounds.hpp"
#include "Components/Physic/RigidBody.hpp"
#include "Components/Physic/Collider.hpp"
#include "Components/Physic/BoxCollider.hpp"
#include "Components/Camera.hpp"
#include "Components/SphereRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/CubeRenderer.hpp"
#include "Components/Transform.hpp"
#include "utils/BitMapFile.hpp"
#include "utils/GLMatrices.hpp"
#include "utils/GLMatricesStack.hpp"
#include "utils/Debug.hpp"
#include "GameObject.hpp"

#include "FerdiuEngine_export.h"

#ifndef WIN_W
#define WIN_W 700
#endif

#ifndef WIN_H
#define WIN_H 700
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
    FERDIU_ENGINE_EXPORT static void OnResize(void (*resize)(int w, int h));
    FERDIU_ENGINE_EXPORT static void OnMouseInput(void (*mouseControl)(int button, int state, int x, int y));
    FERDIU_ENGINE_EXPORT static void OnKeyboardDown(void (*keyInput)(unsigned char key, int x, int y));
    FERDIU_ENGINE_EXPORT static void OnKeyboardUp(void (*keyInputUp)(unsigned char key, int x, int y));
    FERDIU_ENGINE_EXPORT static void OnMouseWheel(void (*mouseWheel)(int wheel, int direction, int x, int y));
    FERDIU_ENGINE_EXPORT static void OnMouseMove(void (*mousePassive)(int x, int y));

private:
    static void Update();
    static void FixedUpdate();
};

}
