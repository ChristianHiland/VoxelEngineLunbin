// Engine
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "vectors.cpp"
#include "util.cpp"
#include "pipline.cpp"
#include "Shaders.cpp"
#include "glut_backend.cpp"
#include "app.cpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


// IDK (Yet)
GLuint VBO;
GLuint IBO;

PersProjInfo gPersProjInfo;

// Loading The Scene
static void RenderSceneCB() {
    Vector3f Pos(5.0f, 1.0f, -3.0f);
    Vector3f Target(0.0f, 0.0f, 1.0f);
    Vector3f Up(0.0, 1.0f, 0.0f);

    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);
    pGameCamera->OnRender();
    // Clearing the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Figure Out
    static float Scale = 0.0f;
    Scale += 0.1f;
    Pipeline p;
    p.Rotate(0.0f, Scale, 0.0f);
    p.WorldPos(0.0f, 0.0f, 3.0f);
    p.SetCamera(pGameCamera->GetPos(), pGameCamera->GetTarget(), pGameCamera->GetUp());
    p.SetPerspectiveProj(gPersProjInfo);
    Pos = Pos + Vector3f(0.0f, 0.0f, 3.0f);

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetWPTrans());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

// Making The Vectex Buffer
static void CreateVertexBuffer() {
    Vector3f Vertices[4];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
    Vertices[1] = Vector3f(0.0f, -1.0f, -1.15475f);
    Vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}
// Making The Index Buffer
static void CreateIndexBuffer() {
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}