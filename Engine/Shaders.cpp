#include "util.h"

GLuint gWVPLocation;

// The Shader Files!!!
const char* pVSFileName = "Engine/Shaders/shader.vs";
const char* pFSFileName = "Engine/Shaders/shader.fs";

// Add Shader Func
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);}
    const GLchar* p[1]; p[0] = pShaderText;
    GLint Lengths[1]; Lengths[0] = (GLint)strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1034];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);}
    glAttachShader(ShaderProgram, ShaderObj);
}
static void CompileShaders() {
    // Starting The Shader Program
    GLuint ShaderProgram = glCreateProgram();
    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);}
    std::string vs, fs;
    if (!ReadFile(pVSFileName, vs)) {
        exit(1);};
    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    if (!ReadFile(pFSFileName, fs)) {
        exit(1);};
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};
    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s;\n", ErrorLog);
        exit(1);}
    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);}
    glUseProgram(ShaderProgram);
    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    assert(gWVPLocation != 0xFFFFFFFF);
}