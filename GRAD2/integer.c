#include "fieldinfo.h"
#include "integer.h"
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
    }

    return integerImplementationInstance;
}
// переделать в глобальную переменную
void *integerAddition(const void *arg1, const void *arg2, void *result)
{
    int temp = (*((int *)arg1)) + (*((int *)arg2));
    *(int *)result = temp;
    return result;
}

void *integerMultiplication(const void *arg1, const void *arg2, void *result)
{
    int temp = (*((int *)arg1)) * (*((int *)arg2));
    *(int *)result = temp;
    return result;
}

void *integerPrint(void *arg)
{
    printf("%d", *(int *)arg);
    return arg;
}
void *integerInput(void *target)
{
    int* ptr = (int*)target;
    scanf("%d", ptr);
    *(int*)target = *ptr;
    return ptr;
}
void zeroIntegerInplace(void *ptrToZero)
{
    *(int *)ptrToZero = 0;
}

void *zeroInteger()
{
    static void *zero = NULL;

    if (zero == NULL)
    {
        zero = malloc(sizeof(int));
        zeroIntegerInplace(zero);
    }

    return (void *)zero;
}
