#include "matrix.h"
#include <stdlib.h>
Matrix* newMatrix(int m, int n , FieldInfo* impl){
    Matrix *new = malloc(sizeof(Matrix));
    new->m = m;
    new->n = n;
    new->data = calloc(n * m, impl->allocsize);
    new->impl = impl;
    return new;
}