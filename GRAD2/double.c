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

void* doubleAddition(void* arg1, void*  arg2){
    double temp = (*((double* )  arg1))+(*((double* ) arg2));
    double* res = &temp;
    return (void*) res;
}

void* doubleMultiplication(void*  arg1, void* arg2){
    double temp = (*((double* )  arg1)) * (*((double* ) arg2));
    double* res = &temp;
    return (void*) res;
}

void* doublePrint(void * arg){
    printf("%lf", *(double*)arg);
    return (void* ) arg;
}
void* doubleInput(){
    double d;
    scanf("%lf", &d);
    double* res = &d;
    return (void*) res;
}