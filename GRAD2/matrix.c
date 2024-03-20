#include "fieldinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <assert.h>
#include "integer.h"
#include "matrix.h"

struct Matrix
{
    int rows;
    int cols;
    void *data;
    FieldInfo *impl;
};

Matrix *newMatrix(int rows, int cols, FieldInfo *impl)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->data = calloc(rows * cols, impl->allocsize);

    matrix->impl = impl;
    matrix->rows = rows;
    matrix->cols = cols;

    zeros(matrix);
    return matrix;
}

// ууказатель на элемен тв матрице, а не ноовый
void *get(Matrix *self, int rowIndex, int colIndex)
{
    assert(self != NULL && rowIndex < self->rows && colIndex < self->cols);
    //printf("adres: %d\n", (void *)((char*)self->data + (rowIndex * (self->cols) + colIndex) * self->impl->allocsize));
    return (void *)((char*)self->data + (rowIndex * (self->cols) + colIndex) * self->impl->allocsize);
}

void set(Matrix *self, int rowIndex, int colIndex, void *data)
{
    // printf("%d %d", row, col);
    assert(self != NULL && data != NULL && rowIndex < self->rows && colIndex < self->cols);
    memcpy(get(self, rowIndex, colIndex),
           data,
           self->impl->allocsize);
}

void zeros(Matrix *self)
{
    Matrix *matrix = self;
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            set(self, i, j, (void*)matrix->impl->zero_());
        }
    }
}

void printMatrix(Matrix *self)
{
    assert(self != NULL);
    void * temp; //без этого не работает
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            temp = get(self, i, j);
            self->impl->printElement(temp);
            printf(" ");
        }
        printf("\n");
    }
}
void readMatrix(Matrix *self)
{
    assert(self != NULL);
    void * temp;
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            //printf("%d %d\n",i, j );
            self->impl->input(temp);
            set(self, i, j, temp);
        }
    }
    printf("end read\n");
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
    assert(matrixA->rows == matrixB->rows && matrixA->cols == matrixB->cols && matrixA->impl->allocsize == matrixB->impl->allocsize);
    int m = matrixA->rows;
    int n = matrixA->cols;
    Matrix *result = newMatrix(m, n, matrixA->impl);
    void *temp;
    void *arg1;
    void *arg2;
    for (int row = 0; row < matrixA->rows; row++)
    {
        for (int j = 0; j < matrixA->cols; j++)
        {
            // перенести временные переменные
            arg1 = get(matrixA, row, j);
            arg2 = get(matrixB, row, j);
            temp = result->impl->addition(arg1, arg2);
            set(result, row, j, temp);
            free(arg1);
            free(arg2);
        }
    }
    return result;
}
Matrix *multMatrix(Matrix *matrixA, Matrix *matrixB)
{
    assert(matrixA != NULL && matrixB != NULL);
    assert(matrixA->rows == matrixB->cols && matrixA->impl->allocsize == matrixB->impl->allocsize);
    Matrix *result = newMatrix(matrixA->rows, matrixB->cols, matrixA->impl);
    for (int i = 0; i < matrixA->rows; i++)
    {
        for (int j = 0; j < matrixB->cols; j++)
        {
            void *sum;
            void *temp;
            for (int k = 0; k < matrixA->cols; k++)
            {
                void *arg1 = get(matrixA, i, k);
                void *arg2 = get(matrixB, k, j);
                temp = matrixA->impl->multiplication(arg1, arg2);
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
    Matrix *result = newMatrix(matrix->rows, matrix->cols, matrix->impl);
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            set(result, i, j, result->impl->multiplication(get(matrix, i, j), number));
        }
    }
    return result;
}

Matrix *transposeMatrix(Matrix *target)
{
    assert(target != NULL);
    Matrix *result = newMatrix(target->cols, target->rows, target->impl);
    for (int row = 0; row < target->rows; row++)
    {
        for (int col = 0; col < target->cols; col++)
        {
            set(result, col, row, get(target, row, col));
        }
    }
    return result;
}
