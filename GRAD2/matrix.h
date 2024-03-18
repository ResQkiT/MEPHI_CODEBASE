#pragma once
#include "fieldinfo.h"
//перенести реализацию в с файл

typedef struct 
{
    int m;
    int n;
    int* data;
    FieldInfo* impl;
} Matrix;

Matrix* newMatrix(int, int,const FieldInfo*, const void* Initializer);

void* get(Matrix*, int, int);
void set(Matrix*, int, int, void*);

void printMatrix(Matrix*);
void readMatrix(Matrix*);
void zeros(Matrix *);
void delete(Matrix*);

Matrix* addMatrix(Matrix*, Matrix*);
Matrix* multMatrix(Matrix*, Matrix*);
Matrix* multMatrixToNumber(Matrix*, void*);
Matrix* transposeMatrix(Matrix*);
