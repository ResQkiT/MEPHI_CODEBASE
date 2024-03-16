#pragma once
#include "fieldinfo.h"
#include "double.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo* newDoubleImpl(){
    FieldInfo* integerImpl = malloc(sizeof(FieldInfo));
    integerImpl->allocsize = sizeof(double);
    integerImpl->addition = doubleAddition;
    integerImpl->multiply = doubleMultiplication;
    integerImpl->printElement = doublePrint;
    integerImpl->input = doubleInput;
    return integerImpl;
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