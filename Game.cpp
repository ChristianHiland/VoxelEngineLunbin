#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Engine/vectors.h"
#include "Engine/util.cpp"

// IDK
GLuint VBO;

// Loading The Scene
static void RenderSceneCB()
{
    // Clearing the window
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}
// Making The Vectex Buffer
static void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, 1.0f, 0.0f);
    Vertices[1] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}
// Add Shader Func
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }
    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1034];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }
    glAttachShader(ShaderProgram, ShaderObj);
}
// The Shader Files!!!
const char* pVSFileName = "Engine/Shaders/shader.vs";
const char* pFSFileName = "Engine/Shaders/shader.fs";

static void CompileShaders() {
    // Starting The Shader Program
    GLuint ShaderProgram = glCreateProgram();
    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    std::string vs, fs;
    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };
    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};
    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
    glUseProgram(ShaderProgram);
}
// Main Start Point
int main(int argc, char** argv)
{
    // Setting Up The Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    int width = 1920;
    int height = 1080;
    glutInitWindowSize(width, height);
    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    // Making The Window
    int win = glutCreateWindow("Game Engine");
    printf("window id: %d\n", win);
    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    // Clearing The Window with just black
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);
    // Running The Function
    CreateVertexBuffer();
    // Compile The Shaders
    CompileShaders();
    // Re-rendering the frame
    glutDisplayFunc(RenderSceneCB);
    // Keeping The Window Open
    glutMainLoop();
    return 0;
}