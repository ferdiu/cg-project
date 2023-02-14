
#include "../include/Time.hpp"
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

    glutDisplayFunc(Engine::Update);

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

    if (setup != nullptr)
        setup();

    if ((glErr = glGetError()) != 0)
    {
        std::cerr << "error: setup failed with error code " << glErr << std::endl;
        exit(1);
    }

    (void) Time::instance();

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
    // TODO:
}

}
