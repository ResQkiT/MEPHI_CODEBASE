#ifndef _MATRIX
#define _MATRIX
typedef struct {
    void* (*set)(void* , int, int, void*);
    void* (*get)(void*, int, int);
    int allocsize;
} FieldInfo;

typedef struct
{
    int m;
    int n;
    int* data;
    FieldInfo* impl;
} Matrix;

Matrix* newMatrix(int, int, FieldInfo*);
#endif