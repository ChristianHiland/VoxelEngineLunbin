#ifndef _WIN64
#include <unistd.h>
#endif
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "InputMan.cpp"

// Points to the object implementing the ICallbacks interface which was delivered to
// GLUTBackendRun(). All events are forwarded to this object.
static ICallbacks* s_pCallbacks = NULL;

static bool sWithDepth = false;
static bool sWithStencil = false;

OGLDEV_KEY GLUTKeyToOGLDEVKey(uint Key)
{
    switch (Key) {
                case GLUT_KEY_F1:
                        return OGLDEV_KEY_F1;
                case GLUT_KEY_F2:
                        return OGLDEV_KEY_F2;
                case GLUT_KEY_F3:
                        return OGLDEV_KEY_F3;
                case GLUT_KEY_F4:
                        return OGLDEV_KEY_F4;
                case GLUT_KEY_F5:
                        return OGLDEV_KEY_F5;
                case GLUT_KEY_F6:
                        return OGLDEV_KEY_F6;
                case GLUT_KEY_F7:
                        return OGLDEV_KEY_F7;
                case GLUT_KEY_F8:
                        return OGLDEV_KEY_F8;
                case GLUT_KEY_F9:
                        return OGLDEV_KEY_F9;
                case GLUT_KEY_F10:
                        return OGLDEV_KEY_F10;
                case GLUT_KEY_F11:
                        return OGLDEV_KEY_F11;
                case GLUT_KEY_F12:
                        return OGLDEV_KEY_F12;
                case GLUT_KEY_LEFT:
                        return OGLDEV_KEY_LEFT;
                case GLUT_KEY_UP:
                        return OGLDEV_KEY_UP;
                case GLUT_KEY_RIGHT:
                        return OGLDEV_KEY_RIGHT;
                case GLUT_KEY_DOWN:
                        return OGLDEV_KEY_DOWN;
                case GLUT_KEY_PAGE_UP:
                        return OGLDEV_KEY_PAGE_UP;
                case GLUT_KEY_PAGE_DOWN:
                        return OGLDEV_KEY_PAGE_DOWN;
                case GLUT_KEY_HOME:
                        return OGLDEV_KEY_HOME;
                case GLUT_KEY_END:
                        return OGLDEV_KEY_END;
                case GLUT_KEY_INSERT:
            return OGLDEV_KEY_INSERT;
        case GLUT_KEY_DELETE:
            return OGLDEV_KEY_DELETE;
            //        default:
            //            OGLDEV_ERROR0("Unimplemented GLUT key");
            // exit(1);
    }

    return OGLDEV_KEY_UNDEFINED;
}


static OGLDEV_MOUSE GLUTMouseToOGLDEVMouse(uint Button)
{
    switch (Button) {
    case GLUT_LEFT_BUTTON:
            return OGLDEV_MOUSE_BUTTON_LEFT;
    case GLUT_RIGHT_BUTTON:
            return OGLDEV_MOUSE_BUTTON_RIGHT;
    case GLUT_MIDDLE_BUTTON:
            return OGLDEV_MOUSE_BUTTON_MIDDLE;
    default:
            OGLDEV_ERROR0("Unimplemented GLUT mouse button");
    }

    return OGLDEV_MOUSE_UNDEFINED;
}


static void RRenderSceneCB()
{
    s_pCallbacks->RRenderSceneCB();
}


static void IdleCB()
{
    s_pCallbacks->RRenderSceneCB();
}


static void MouseCB(int Button, int State, int x, int y)
{
        OGLDEV_MOUSE OgldevMouse = GLUTMouseToOGLDEVMouse(Button);
        OGLDEV_KEY_STATE OgldevKeyState = (State == GLUT_DOWN) ? OGLDEV_KEY_STATE_PRESS : OGLDEV_KEY_STATE_RELEASE;

    s_pCallbacks->MouseCB(OgldevMouse, OgldevKeyState, x, y);
}


static void glutInitCallbacks()
{
    glutDisplayFunc(RRenderSceneCB);
    glutIdleFunc(IdleCB);
    glutSpecialFunc(SpecialKeyboardCB);
    glutPassiveMotionFunc(PassiveMouseCB);
    glutKeyboardFunc(KeyboardCB);
    glutMouseFunc(MouseCB);
}


void GLUTBackendInit(int argc, char** argv, bool WithDepth, bool WithStencil)
{
    sWithDepth = WithDepth;
    sWithStencil = WithStencil;

    glutInit(&argc, argv);

    uint DisplayMode = GLUT_DOUBLE|GLUT_RGBA;

    if (WithDepth) {
        DisplayMode |= GLUT_DEPTH;
    }

    if (WithStencil) {
        DisplayMode |= GLUT_STENCIL;
    }

    glutInitDisplayMode(DisplayMode);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}


bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle)
{
    if (isFullScreen) {
        char ModeString[64] = { 0 };
        int bpp = 32;
        SNPRINTF(ModeString, sizeof(ModeString), "%dx%d:%d@60", Width, Height, bpp);
        glutGameModeString(ModeString);
        glutEnterGameMode();
    }
    else {
        glutInitWindowSize(Width, Height);
        glutCreateWindow(pTitle);
    }

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return false;
    }

    return true;
}

void GLUTBackendRun(ICallbacks* pCallbacks)
{
    if (!pCallbacks) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    if (sWithDepth) {
        glEnable(GL_DEPTH_TEST);
    }

    s_pCallbacks = pCallbacks;
    glutInitCallbacks();
    glutMainLoop();
}


void GLUTBackendSwapBuffers()
{
    glutSwapBuffers();
}

void GLUTBackendLeaveMainLoop()
{
    glutLeaveMainLoop();
}
