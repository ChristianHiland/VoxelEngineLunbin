#ifndef _WIN64
#include <unistd.h>
#endif
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "util.h"
#include "glut_backend.h"
#include "keys.h"
#include "camera.cpp"

Camera* pGameCamera = NULL;

static void SpecialKeyboardCB(int Key, int x, int y) {
    OGLDEV_KEY ogldevKey = GLUTKeyToOGLDEVKey(Key);
    pGameCamera->OnKeyboard(ogldevKey);
}
static void KeyboardCB(unsigned char Key, int x, int y) {
    switch (Key) {
    case 'q':
        glutLeaveMainLoop();
    }
}
static void PassiveMouseCB(int x, int y) {
    pGameCamera->OnMouse(x, y);
}