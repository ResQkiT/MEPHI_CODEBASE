#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "fieldinfo.h"
#include "integer.h"
#include "complex.h"
#include "double.h"
#include "matrix.h"
#include "constants.h"

typedef struct Matrix
{
    int rows;
    int cols;
    void *data;
    FieldInfo *impl;
} Matrix;

Matrix *newMatrix(int rows, int cols, FieldInfo *impl)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->data = malloc(rows * cols * impl->allocsize);

    matrix->impl = impl;
    matrix->rows = rows;
    matrix->cols = cols;
    zeros(matrix);
    return matrix;
}
int getRows(Matrix *self)
{
    return self->rows;
}
int getCols(Matrix *self)
{
    return self->cols;
}
FieldInfo *getFieldInfo(Matrix *self)
{
    return self->impl;
}
void *get(Matrix *self, int rowIndex, int colIndex)
{
    assert(self != NULL && rowIndex < self->rows && colIndex < self->cols);
    return (void *)(self->data + (rowIndex * (self->cols) + colIndex) * self->impl->allocsize);
}

void set(Matrix *self, int rowIndex, int colIndex, void *data)
{
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
    assert(self != NULL);
    void *temp;
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

void readMatrixFromFile(FILE *source, Matrix *self)
{
    assert(self != NULL);
    void *temp = malloc(self->impl->allocsize);
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->cols; j++)
        {
            self->impl->input(source, temp);
            set(self, i, j, temp);
        }
    }
    free(temp);
}
// что то вроде перегрузки
void readMatrix(Matrix *self)
{
    assert(self != NULL);
    readMatrixFromFile(stdin, self);
}
// читает матрицу из .txt файла в формате
// первая строка->m m t  число строк число столбцов тип матрицы
// далее->m строк по n элементов в каждой
// возвращет ссылку на матрицу в памяти
Matrix *newMatrixFromFile(FILE *file)
{
    int rows, cols;
    char t;

    fscanf(file, "%d %d %c", &rows, &cols, &t);
    // printf("%d %d %c", rows, cols, t);

    Matrix *matrix;
    switch (t - '0')
    {
    case 'i' - '0':
        matrix = newMatrix(rows, cols, getIntegerImplimentationInstance());
        break;
    case 'd' - '0':
        matrix = newMatrix(rows, cols, getDoubleImplimentationInstance());
        break;
    case 'c' - '0':
        matrix = newMatrix(rows, cols, getComplexImplimentationInstance());
        break;
    default:
        printf("null\n");
        return NULL;
        break;
    }
    readMatrixFromFile(file, matrix);
    return matrix;
}

void delete(Matrix *target)
{
    assert(target != NULL);
    free(target->data);
    free(target);
}

Matrix *addMatrix(Matrix *matrixA, Matrix *matrixB, Matrix *result)
{
    assert(matrixA->rows == matrixB->rows && matrixA->cols == matrixB->cols && matrixA->impl->allocsize == matrixB->impl->allocsize);
    void *temp = malloc(result->impl->allocsize);
    void *arg1;
    void *arg2;
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            arg1 = get(matrixA, i, j);
            arg2 = get(matrixB, i, j);
            result->impl->addition(arg1, arg2, temp);
            set(result, i, j, temp);
        }
    }
    free(temp);
    return result;
}

Matrix *multMatrix(Matrix *matrixA, Matrix *matrixB, Matrix *result)
{
    assert(matrixA != NULL && matrixB != NULL && result != NULL);
    assert(matrixA->cols == matrixB->rows && matrixA->impl->allocsize == matrixB->impl->allocsize);
    assert(result->cols == matrixB->cols && result->rows == matrixA->rows);

    void *arg1;
    void *arg2;
    void *sum = malloc(result->impl->allocsize);
    void *temp = malloc(result->impl->allocsize);

    for (int i = 0; i < matrixA->rows; i++)
    {
        for (int j = 0; j < matrixB->cols; j++)
        {
            result->impl->zeroInPlace(sum);
            for (int k = 0; k < matrixA->cols; k++)
            {
                result->impl->zeroInPlace(temp);
                arg1 = get(matrixA, i, k);
                arg2 = get(matrixB, k, j);
                result->impl->multiplication(arg1, arg2, temp);

                result->impl->addition(sum, temp, sum);
                set(result, i, j, sum);
            }
        }
    }
    free(sum);
    free(temp);
    return result;
}

Matrix *multMatrixToNumber(Matrix *matrix, void *number, Matrix *result)
{
    assert(matrix != NULL && number != NULL && result != NULL);
    void *temp = malloc(result->impl->allocsize);
    void *arg1;
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            arg1 = get(matrix, i, j);
            result->impl->multiplication(arg1, number, temp);
            set(result, i, j, temp);
        }
    }
    free(temp);
    return result;
}

int equal(Matrix *matrixA, Matrix *matrixB)
{
    if (matrixA == matrixB)
        return true;
    if (matrixA == NULL || matrixB == NULL)
        return false;
    if (matrixA->impl != matrixB->impl || matrixA->rows != matrixB->rows || matrixA->cols != matrixB->cols)
        return false;
    int m = matrixA->rows;
    int n = matrixA->cols;
    void *arg1;
    void *arg2;
    int f = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arg1 = get(matrixA, i, j);
            arg2 = get(matrixB, i, j);
            f = f && matrixA->impl->equal(arg1, arg2);
        }
    }
    return f;
}
//copy without data
Matrix* newClone(Matrix* source){
    Matrix* clone = newMatrix(getRows(source), getCols(source), getFieldInfo(source));
    return clone;
}
//copy with data
Matrix* newDeepClone(Matrix* source){
    Matrix* clone = newMatrix(getRows(source), getCols(source), getFieldInfo(source));
    for (int i = 0; i < getRows(source); i++)
    {
        for (int j = 0; j < getCols(source); j++)
        {
            set(clone,i,j,get(source,i,j));
        }
        
    }
    return clone;
    
}