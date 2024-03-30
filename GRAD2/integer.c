#include "fieldinfo.h"
#include "integer.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo *getIntegerImplimentationInstance()
{
    static FieldInfo *integerImplementationInstance = NULL;
    if (integerImplementationInstance == NULL)
    {
        integerImplementationInstance = malloc(sizeof(FieldInfo));
        integerImplementationInstance->allocsize = sizeof(int);
        integerImplementationInstance->addition = integerAddition;
        integerImplementationInstance->multiplication = integerMultiplication;
        integerImplementationInstance->printElement = integerPrint;
        integerImplementationInstance->input = integerInput;
        integerImplementationInstance->zero_ = zeroInteger;
        integerImplementationInstance->zeroInPlace = zeroIntegerInplace;
        integerImplementationInstance->equal = integerEqual;
        integerImplementationInstance->metadata = 'i';
    }

    return integerImplementationInstance;
}
void *integerAddition( void *arg1, void *arg2, void *result)
{
    int temp = (*((int *)arg1)) + (*((int *)arg2));
    *(int *)result = temp;
    return result;
}

void *integerMultiplication( void *arg1,  void *arg2, void *result)
{
    int temp = (*((int *)arg1)) * (*((int *)arg2));
    *(int *)result = temp;
    return result;
}

void *integerPrint(void *arg)
{
    int *ptr = (int*)arg;
    printf("%i", *ptr);
    return arg;
}
void *integerInput(void * source, void *target)
{
    FILE * file = (FILE*)source;
    fscanf(file, "%d", (int*)target);
    return target;
}
void zeroIntegerInplace(void *ptrToZero)
{
    *(int *)ptrToZero = 0;
}

const void *zeroInteger()
{
    static void *zero = NULL;

    if (zero == NULL)
    {
        zero = malloc(sizeof(int));
        zeroIntegerInplace(zero);
    }

    return (void *)zero;
}

int integerEqual(void *arg1, void* arg2){
    if (arg1 == arg2) return true;
    if(*(int*)arg1 == *(int*)arg2) return true;
    return false;
}