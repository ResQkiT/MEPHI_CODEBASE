#include "fieldinfo.h"
#include "integer.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo* getIntegetImplimentationInstance(){
    static FieldInfo * integerImplementationInstance = NULL;
    if (integerImplementationInstance == NULL)
    {
        integerImplementationInstance = malloc(sizeof(FieldInfo));
        integerImplementationInstance->allocsize = sizeof(int);
        integerImplementationInstance->addition = integerAddition;
        integerImplementationInstance->multiplication = integerMultiplication;
        integerImplementationInstance->printElement = integerPrint;
        integerImplementationInstance->input = integerInput;
        integerImplementationInstance->zero_ = zeroInteger;
    }
    
    return integerImplementationInstance;
}
//переделать в глобальную переменную
void* integerAddition(const void* arg1, const void* arg2, void* result){
    int temp = (*((int* ) arg1))+(*((int* ) arg2));
    *(int*)result = temp; 
    return result;
}

void* integerMultiplication(const void* arg1,const void* arg2, void* result){
    int temp = (*((int* ) arg1)) * (*((int* ) arg2));
    *(int*)result = temp; 
    return result;
}

void* integerPrint(void * arg){
    printf("%d", *(int*)arg);
    return arg;
}
void* integerInput(void* target){
    int d;
    scanf("%d", &d);
    *(int*)target = d;
    return target;
}
void zeroIntegerInplace(void *ptrToZero)
{
    int *theZero = (int *)ptrToZero;
    *theZero = 0;
}

const void* zeroInteger(){
    static int * zero = NULL;

    if (zero == NULL)
    {
        zero = malloc(sizeof(int));
        zeroIntegerInplace(zero);
    }

    return (void *)zero;
}

