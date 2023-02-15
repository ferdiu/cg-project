
#include "../include/FerdiuEngine.hpp"

namespace FerdiuEngine
{

void Engine::Start(int argc, char **argv, void (*setup)(void))
{
    GLenum glErr;

    glutInit(&argc, argv);

    glutInitContextVersion(4, 6);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(
        (glutGet(GLUT_SCREEN_WIDTH)-WIN_W)/2,
        (glutGet(GLUT_SCREEN_HEIGHT)-WIN_H)/2
    );
    glutCreateWindow(PROJECT_NAME);

    // INITIALIZE TIME
    Time::setUpdateRoutine(FixedUpdate);
    glutDisplayFunc(Engine::Update);

    // INITIALIZE DEFAULT SCENE
    Scene::setCurrent(new Scene("DefaultScene"));

    // INITIALIZE DEFAULT CAMERA
    GameObject *cameraObject = new GameObject("MainCamera");
    cameraObject->addComponent(Camera::getCurrent());
    cameraObject->instantiate(Scene::getCurrent()->root());

    // TODO: too hardcoded
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);

    if ((glErr = glGetError()) != 0)
    {
        std::cerr << "error: Engine initialization failed with error code " << glErr << std::endl;
        exit(1);
    }

    if ((glErr = glewInit()) != GLEW_OK)
    {
        std::cerr << "error: GLEW init failed: " << glewGetErrorString(glErr) << std::endl;
        exit(1);
    }

#ifdef DEBUG_VERBOSE
    Debug::Log("start->setup");
#endif

    if (setup != nullptr)
        setup();

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->setup");
#endif

    if ((glErr = glGetError()) != 0)
    {
        std::cerr << "error: setup failed with error code " << glErr << std::endl;
        exit(1);
    }

    glutMainLoop();
}

void Engine::OnResize(void (*resize)(int w, int h))
{
    glutReshapeFunc(resize);
}

void Engine::OnMouseInput(void (*mouseControl)(int button, int state, int x, int y))
{
    glutMouseFunc(mouseControl);
}

void Engine::OnKeyboardDown(void (*keyInput)(unsigned char key, int x, int y))
{
    glutKeyboardFunc(keyInput);
}

void Engine::OnKeyboardUp(void (*keyInputUp)(unsigned char key, int x, int y))
{
    glutKeyboardUpFunc(keyInputUp);
}

void Engine::OnMouseWheel(void (*mouseWheel)(int wheel, int direction, int x, int y))
{
    glutMouseWheelFunc(mouseWheel);
}

void Engine::OnMouseMove(void (*mousePassive)(int x, int y))
{
    glutMotionFunc(mousePassive);
}

void Engine::Update()
{
#ifdef DEBUG
    int glErr;
#endif

#ifdef DEBUG_VERBOSE
    Debug::Log("start->Engine::Update");
#endif

    Camera *c = Camera::getCurrent();
    Scene *s = Scene::getCurrent();

    // update camera
    c->clear();
    c->updateProjectionMatrix();
    c->updateViewMatrix(*c->getOwner()->getTransform());

    // update scene
    s->update();
    s->draw();

#ifdef DEBUG
    if ((glErr = glGetError()) != 0) {
        fprintf(stderr, "error: Engine::Update failed with error code %d \n", glErr);
        exit(-1);
    }
#endif

    glutSwapBuffers();

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->Engine::Update");
#endif
}

void Engine::FixedUpdate()
{
#ifdef DEBUG
    int glErr;
#endif

#ifdef DEBUG_VERBOSE
    Debug::Log("start->Engine::FixedUpdate");
#endif

    Scene::getCurrent()->fixedUpdate();

#ifdef DEBUG
    if ((glErr = glGetError()) != 0) {
        fprintf(stderr, "error: Engine::FixedUpdate failed with error code %d \n", glErr);
        exit(-1);
    }
#endif

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->Engine::FixedUpdate");
#endif
}

}
