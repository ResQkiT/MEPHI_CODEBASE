#include "fieldinfo.h"
#include "double.h"
#include <stdlib.h>
#include <stdio.h>

FieldInfo *getDoubleImplimentationInstance()
{
    static FieldInfo *doubleImplementationInstance = NULL;
    if (doubleImplementationInstance == NULL)
    {
        doubleImplementationInstance = malloc(sizeof(FieldInfo));
        doubleImplementationInstance->allocsize = sizeof(double);
        doubleImplementationInstance->addition = doubleAddition;
        doubleImplementationInstance->multiplication = doubleMultiplication;
        doubleImplementationInstance->printElement = doublePrint;
        doubleImplementationInstance->input = doubleInput;
        doubleImplementationInstance->zero_ = zeroDouble;
    }

    return doubleImplementationInstance;
}
// переделать в глобальную переменную
void *doubleAddition(const void *arg1, const void *arg2, void *result)
{
    double temp = (*((double *)arg1)) + (*((double *)arg2));
    *(double *)result = temp;
    return result;
}

void *doubleMultiplication(const void *arg1, const void *arg2, void *result)
{
    double temp = (*((double *)arg1)) * (*((double *)arg2));
    *(double *)result = temp;
    return result;
}

void *doublePrint(void *arg)
{
    printf("%lf", *(double *)arg);
    return arg;
}
void *doubleInput(void *target)
{
    scanf("%lf", (double *)target);
    return target;
}
void zeroDoubleInplace(void *ptrToZero)
{
    *(double *)ptrToZero = 0.0;
}

void *zeroDouble()
{
    static void *zero = NULL;

    if (zero == NULL)
    {
        zero = malloc(sizeof(double));
        zeroDoubleInplace(zero);
    }

    return (void *)zero;
}
