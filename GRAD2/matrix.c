#pragma once
#include "fieldinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int m;
    int n;
    int* data;
    FieldInfo* impl;
} Matrix;

Matrix* newMatrix(int m, int n, FieldInfo* impl){
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->data = malloc(m*n*impl->allocsize);
    
    matrix->impl = impl;
    matrix->m = m;
    matrix->n = n;

    zeros(matrix);
    return matrix;
}

//добавить проверку на валидность
void* get(Matrix* self, int i , int j){
    void* val = malloc(self->impl->allocsize);
    memcpy(val ,(char*)self->data +(i*(self->n) + j)*self->impl->allocsize, self->impl->allocsize );
    return val;
}
//добавить проверку на валидность
void set(Matrix* self, int i, int j, void *data){
   memcpy( ((void*)((char*)(self->data)) +(i*self->n + j)*self->impl->allocsize), data, self->impl->allocsize );
}
void zeros(Matrix *self){
    int zero = 0;
    void* zeroP = (void*)(&zero);
    memset((void*)(self->data), 0xf000, (self->m * self->n) * self->impl->allocsize);
}

void printMatrix(Matrix* matrix){
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0;j < matrix->n; j++)
        {
            matrix->impl->printElement(get(matrix, i, j));
            printf(" ");
        }
        printf("\n");
    }
    
}
void readMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0; j < matrix->n; j++)
        {
            set(matrix, i, j, matrix->impl->input());
        }
    }
}
