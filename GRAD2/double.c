#include "fieldinfo.h"
#include "double.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo* newDoubleImpl(){
    FieldInfo* impl = malloc(sizeof(FieldInfo));
    impl->allocsize = sizeof(double);
    impl->addition = doubleAddition;
    impl->multiply = doubleMultiplication;
    impl->printElement = doublePrint;
    impl->input = doubleInput;
    return impl;
}

void* doubleAddition(void* v1, void* v2){
    double temp = (*((double* ) v1))+(*((double* ) v2));
    double* res = &temp;
    return (void*) res;
}

void* doubleMultiplication(void* v1, void* v2){
    double temp = (*((double* ) v1)) * (*((double* ) v2));
    double* res = &temp;
    return (void*) res;
}

void* doublePrint(void * v){
    printf("%lf", *(double*)v);
    return (void* ) v;
}
void* doubleInput(){
    double d;
    scanf("%lf", &d);
    double* res = &d;
    return (void*) res;
}