#include "matrix.h"
#include <stdio.h>
void setInteger(void* self, int i, int j, void *data){
    Matrix* matrix = (Matrix*)self;
    matrix->data[i * (matrix->n) + j] = *((int* )(data));
}
void* getInteger(void* self, int i , int j){
    Matrix* matrix = (Matrix*)self;
    return ((int*)(matrix->data[i * (matrix->n) + j]));
}

