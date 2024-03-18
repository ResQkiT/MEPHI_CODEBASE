#include "fieldinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <assert.h>
#include "integer.h"
//
typedef struct
{
    int m;
    int n;
    void *data;
    FieldInfo *impl;
} Matrix;

Matrix *newMatrix(int m, int n, FieldInfo *impl)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->data = malloc(m * n * impl->allocsize);

    matrix->impl = impl;
    matrix->m = m;
    matrix->n = n;

    zeros(matrix);
    return matrix;
}

// добавить проверку на валидность
// ууказатель на элемен тв матрице
void *get(Matrix *self, int i, int j)
{
    assert(self != NULL && i < self->m && j < self->n);
    void *val = malloc(self->impl->allocsize);
    memcpy(val, (char *)self->data + (i * (self->n) + j) * self->impl->allocsize, self->impl->allocsize);
    return val;
}

// добавить проверку на валидност
// row col
// переименовать переменные
void set(Matrix *self, int i, int j, void *data)
{
    assert(self != NULL && data != NULL && i < self->m && j < self->n);
    memcpy((void *)((char *)self->data + (i * (self->n) + j) * self->impl->allocsize),
           data,
           self->impl->allocsize);
}
// переписать все через set
void zeros(Matrix *self)
{
    assert(self != NULL);
    memset((void *)(self->data), 0, (self->m * self->n) * self->impl->allocsize);
}

void zeros_(Matrix *self)
{
    void *zeroValue = malloc(self->impl->allocsize);
    (*self->impl->zero)(zeroValue);

    for (int row = 0; row < self->m; ++row)
    {
        for (int col = 0; col < self->n; ++col)
        {
            set(self, row, col, zeroValue);
        }
    }

    free(zeroValue);
}

void printMatrix(Matrix *self)
{
    assert(self != NULL);
    for (int i = 0; i < self->m; i++)
    {
        for (int j = 0; j < self->n; j++)
        {
            self->impl->printElement(get(self, i, j));
            printf(" ");
        }
        printf("\n");
    }
}
void readMatrix(Matrix *self)
{
    assert(self != NULL);
    for (int i = 0; i < self->m; i++)
    {
        for (int j = 0; j < self->n; j++)
        {
            set(self, i, j, self->impl->input());
        }
    }
}
void delete(Matrix *target)
{
    assert(target != NULL);
    free(target->impl);
    free(target->data);
    free(target);
}

Matrix *addMatrix(Matrix *matrixA, Matrix *matrixB)
{
    // Проверим что сигнатуры совпадают, иначе накричим на пользователя
    assert(matrixA->m == matrixB->m && matrixA->n == matrixB->n && matrixA->impl->allocsize == matrixB->impl->allocsize);
    int m = matrixA->m;
    int n = matrixA->n;
    Matrix *result = newMatrix(m, n, matrixA->impl);
    void *temp;
    for (int i = 0; i < matrixA->m; i++)
    {
        for (int j = 0; j < matrixA->n; j++)
        {
            // перенести временные переменные
            void *arg1 = get(matrixA, i, j);
            void *arg2 = get(matrixB, i, j);
            temp = result->impl->addition(arg1, arg2);
            set(result, i, j, temp);
            free(arg1);
            free(arg2);
        }
    }
    return result;
}
Matrix *multMatrix(Matrix *matrixA, Matrix *matrixB)
{
    assert(matrixA != NULL && matrixB != NULL);
    assert(matrixA->m == matrixB->n && matrixA->impl->allocsize == matrixB->impl->allocsize);
    Matrix *result = newMatrix(matrixA->m, matrixB->n, matrixA->impl);
    for (int i = 0; i < matrixA->m; i++)
    {
        for (int j = 0; j < matrixB->n; j++)
        {
            void *sum;
            void *temp;
            for (int k = 0; k < matrixA->n; k++)
            {
                void *arg1 = get(matrixA, i, k);
                void *arg2 = get(matrixB, k, j);
                temp = matrixA->impl->multiply(arg1, arg2);
                set(result, i, j, matrixA->impl->addition(get(result, i, j), temp));
                free(arg1);
                free(arg2);
            }
        }
    }
    return result;
}

Matrix *multMatrixToNumber(Matrix *matrix, void *number)
{
    assert(matrix != NULL && number != NULL);
    Matrix *result = newMatrix(matrix->m, matrix->n, matrix->impl);
    for (int i = 0; i < result->m; i++)
    {
        for (int j = 0; j < result->n; j++)
        {
            set(result, i, j, result->impl->multiply(get(matrix, i, j), number));
        }
    }
    return result;
}

Matrix *transposeMatrix(Matrix *target)
{
    assert(target != NULL);
    Matrix *result = newMatrix(target->n, target->m, target->impl);
    for (int i = 0; i < target->m; i++)
    {
        for (int j = 0; j < target->n; j++)
        {
            set(result, j, i, get(target, i, j));
        }
    }
    return result;
}
