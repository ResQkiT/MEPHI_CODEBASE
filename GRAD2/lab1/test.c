#include <stdio.h>
#include <stdlib.h>
typedef struct {
    void* (*set)(void* , int*, int* , void*);
    void* (*get)(void*);
} FieldInfo;
typedef struct
{
    int m;
    int n;
    void* data;
    FieldInfo* impl;
} Matrix;
typedef struct 
{
    double re;
    double im;
}Complex;



Matrix* newMatrix(int n, int m , void* data, FieldInfo* impl){
    Matrix *new = malloc(sizeof(Matrix));
    new->m = m;
    new->n = n;
    new->data = data;
    new->impl = impl;
    return new;
}
void* setInteger(void* self, int* i, int* j, void *data){
    ((Matrix*)(self))->data = ((int*)(data));
}
void* setComplex(void* self, int* i, int* j, void *data ){
    ((Matrix*)(self))->data = ((Complex*)(data));
}
void* printInt(void* self){
    printf("%d" , *((int* )(((Matrix*)(self))->data)));
}
void* printComplex(void* self){
    printf("%.2f+i%.2f", (((Complex*)(((Matrix*)(self))->data))->re), (((Complex*)(((Matrix*)(self))->data))->im) );
}
FieldInfo INTEGER_IMPL = {setInteger, printInt};
FieldInfo COMPLEX_IMPL = {setComplex, printComplex};
int main(void*){
    int a = 2;
    Complex complex ={5.9, 6.1};
    Matrix *first = newMatrix(&a , &INTEGER_IMPL);
    Matrix *second = newMatrix(&complex , &COMPLEX_IMPL);
    first->impl->set(first, &a , &a, (void *)(&a));
    first->impl->get(first);
    second->impl->set(second,&a , &a, (void *)(&complex));
    second->impl->get(second);
}