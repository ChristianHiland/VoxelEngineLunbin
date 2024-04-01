#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#ifdef _WIN64
#include <unistd.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
#include <assert.h>
#include <time.h>


using namespace std;

bool ReadFile(const char* fileName, std::string& outFile);
char* ReadBinaryFile(const char* pFileName, int& size);
void WriteBinaryFile(const char* pFilename, const void* pData, int size);

void OgldevError(const char* pFileName, uint line, const char* msg, ... );
void OgldevFileError(const char* pFileName, uint line, const char* pFileError);

#define OGLDEV_ERROR0(msg) OgldevError(__FILE__, __LINE__, msg)
#define OGLDEV_ERROR(msg, ...) OgldevError(__FILE__, __LINE__, msg, __VA_ARGS__)
#define OGLDEV_FILE_ERROR(FileError) OgldevFileError(__FILE__, __LINE__, FileError);

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ZERO_MEM_VAR(var) memset(&var, 0, sizeof(var))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define minH(a,b) (a) < (b) ? (a) : (b)
#define maxH(a,b) (a) > (b) ? (a) : (b)

#define VSNPRINTF vsnprintf

#endif