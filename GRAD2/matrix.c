#include "fieldinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <assert.h>
#include "integer.h"
#include "matrix.h"


Matrix *newMatrix(int rows, int cols, FieldInfo *impl)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->data = malloc(rows * cols* impl->allocsize);

    matrix->impl = impl;
    matrix->rows = rows;
    matrix->cols = cols;
    //printf("%d %d", matrix->rows, matrix->cols);
    zeros(matrix);
    return matrix;
}

// ууказатель на элемен тв матрице, а не ноовый
void *get(Matrix *self, int rowIndex, int colIndex)
{
    assert(self != NULL && rowIndex < self->rows && colIndex < self->cols);

    //printf("adres: %d\n", (void *)((char*)self->data + (rowIndex * (self->cols) + colIndex) * self->impl->allocsize));
    return (void *)(self->data + (rowIndex * (self->cols) + colIndex) * self->impl->allocsize);
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
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            self->impl->zeroInPlace(get(self, i, j));
        }
    }
}

void printMatrix(Matrix *self)
{
    //printf("!0");
    assert(self != NULL);
    //printf("!1");
    void * temp = NULL ; //без этого не работает
    //printf("!2");
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

    //free(temp);
    
}

void readMatrix(Matrix *self)
{
    assert(self != NULL);
    void * temp =malloc(self->impl->allocsize);
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            self->impl->input(temp);
            set(self, i, j, temp);
        }
    }
    free(temp);
    printf("enter ended\n");
}

void delete(Matrix *target)
{
    assert(target != NULL);
    free(target->data);
    free(target);
}

Matrix *addMatrix(Matrix *matrixA, Matrix *matrixB, Matrix *result)
{
    // Проверим что сигнатуры совпадают, иначе накричим на пользователя
    assert(matrixA->rows == matrixB->rows && matrixA->cols == matrixB->cols && matrixA->impl->allocsize == matrixB->impl->allocsize);
    void *temp = malloc(result->impl->allocsize); // выделяем память для текущего элемента
    void *arg1;
    void *arg2;
    void *target;
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            arg1 = get(matrixA, i, j);
            arg2 = get(matrixB, i, j);
            target = get(result, i, j);
            //printf("%d %d\n", arg1, arg2);
            result->impl->addition(arg1, arg2, temp);
            //printf("%d\n", *(int*) temp);
            set(result, i, j, temp);
        }
    }
    free(temp);
    //printf("end add\n");
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
                //set(result, i, j, matrixA->impl->addition(get(result, i, j)));
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
