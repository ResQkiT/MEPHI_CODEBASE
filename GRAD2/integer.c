#include "fieldinfo.h"
#include "integer.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo* newIntegerImpl(){
    FieldInfo* integerImpl = malloc(sizeof(FieldInfo));
    integerImpl->allocsize = sizeof(int);
    integerImpl->addition = integerAddition;
    integerImpl->multiply = integerMultiplication;
    integerImpl->printElement = integerPrint;
    integerImpl->input = integerInput;
    return integerImpl;
}
//переделать в глобальную переменную
void* integerAddition(const void* v1, const  void* v2){
    int temp = (*((int* ) v1))+(*((int* ) v2));
    int* res = &temp;
    return (void*) res;
}

void* integerMultiplication(void* v1, void* v2){
    int temp = (*((int* ) v1)) * (*((int* ) v2));
    int* res = &temp;
    return (void*) res;
}

void* integerPrint(void * v){
    printf("%d", *(int*)v);
    return (void* ) v;
}
void* integerInput(){
    int d;
    scanf("%d", &d);
    int* res = &d;
    return (void*) res;
}

