#pragma once
#include "fieldinfo.h"

typedef struct Matrix Matrix;

Matrix *newMatrix(int rows, int cols, FieldInfo *);

void *get(Matrix *self, int rowIndex, int colIndex);
void set(Matrix *self, int rowIndex, int colIndex, void *data);

void printMatrix(Matrix *self);
Matrix *newMatrixFromFile(FILE *file);
void readMatrixFromFile(FILE *source, Matrix *self);
void readMatrix(Matrix *self);
void zeros(Matrix *self);
void delete(Matrix *self);

Matrix *addMatrix(Matrix *matrixA, Matrix *matrixB, Matrix *result);
Matrix *multMatrix(Matrix *matrixA, Matrix *matrixB, Matrix *result);
Matrix *multMatrixToNumber(Matrix *matrix, void *number, Matrix *result);

int getRows(Matrix *self);
int getCols(Matrix *self);
FieldInfo *getFieldInfo(Matrix *self);

int equal(Matrix *matrixA, Matrix *matrixB);

Matrix *newClone(Matrix *source);

Matrix *newDeepClone(Matrix *source);