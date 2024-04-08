#include "Engine/Engine.cpp"

static void InitializeGlutCallbacks() {
    glutDisplayFunc(RenderSceneCB);
    glutIdleFunc(RenderSceneCB);
    //glutSpecialFunc(SpecialKeyboardCB);
    //glutPassiveMotionFunc(PassiveMouseCB);
    //glutKeyboardFunc(KeyboardCB);
}
// Main Start Point
int main(int argc, char** argv)
{
    // Setting Up The Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int x = 200; int y = 100;
    glutInitWindowPosition(x, y);
    // Making The Window
    int win = glutCreateWindow("Game Engine");
    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    // Clearing The Window with just black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Creating the Buffers
    CreateVertexBuffer();
    CreateIndexBuffer();
    // Compile The Shaders
    CompileShaders();
    // Player Settings
    gPersProjInfo.FOV = 30.0f;
    gPersProjInfo.Height = WINDOW_HEIGHT;
    gPersProjInfo.Width = WINDOW_WIDTH;
    gPersProjInfo.zNear = 1.0f;
    gPersProjInfo.zFar = 100.0f;

    

    // Keeping The Window Open
    glutMainLoop();
    return 0;
}