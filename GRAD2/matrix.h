#pragma once
#include "fieldinfo.h"
//перенести реализацию в с файл


typedef struct Matrix
{
    int rows;
    int cols;
    void *data;
    FieldInfo *impl;
}Matrix;

Matrix* newMatrix(int, int, FieldInfo*);

void *get(Matrix*, int, int);
void set(Matrix*, int, int, void*);

void printMatrix(Matrix *self);
void readMatrix(Matrix*);
void zeros(Matrix *);
void delete(Matrix*);

Matrix* addMatrix(Matrix*, Matrix*, Matrix*);
Matrix* multMatrix(Matrix*, Matrix*);
Matrix* multMatrixToNumber(Matrix*, void*);
Matrix* transposeMatrix(Matrix*);
void falseprintMatrix(Matrix *);