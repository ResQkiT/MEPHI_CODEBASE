#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fieldinfo.h"
#include "double.h"
#include "constants.h"

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
        doubleImplementationInstance->zeroInPlace = zeroDoubleInplace;
        doubleImplementationInstance->equal = doubleEqual;
    }
    return doubleImplementationInstance;
}

void *doubleAddition(void *arg1, void *arg2, void *result)
{
    double temp = (*((double *)arg1)) + (*((double *)arg2));
    *(double *)result = temp;
    return result;
}

void *doubleMultiplication(void *arg1, void *arg2, void *result)
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

void *doubleInput(void *source, void *target)
{
    FILE *file = (FILE *)source;
    fscanf(source, "%lf", (double *)target);
    return target;
}

void zeroDoubleInplace(void *ptrToZero)
{
    *(double *)ptrToZero = 0.0;
}

const void *zeroDouble()
{
    static void *zero = NULL;
    if (zero == NULL)
    {
        zero = malloc(sizeof(double));
        zeroDoubleInplace(zero);
    }
    return (void *)zero;
}

int doubleEqual(void *arg1, void *arg2)
{
    if (arg1 == arg2)
        return true;
    if (fabs(*(double *)arg1 - *(double *)arg2) <= 1e-9)
        return true;
    return false;
}