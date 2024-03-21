#include "fieldinfo.h"
#include "complex.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    double re;
    double im;
} Complex;

FieldInfo *getComplexImplimentationInstance()
{
    static FieldInfo * complexImplementatinInstance = NULL;
    if (complexImplementatinInstance == NULL)
    {
        complexImplementatinInstance = malloc(sizeof(FieldInfo));
        complexImplementatinInstance->allocsize = sizeof(Complex);
        complexImplementatinInstance->addition = complexAddition;
        complexImplementatinInstance->multiplication = complexMultiplication;
        complexImplementatinInstance->printElement = complexPrint;
        complexImplementatinInstance->input = complexInput;
        complexImplementatinInstance->zero_ = zeroComplex;
        complexImplementatinInstance->zeroInPlace = zeroComplexInplace;
    }
    return complexImplementatinInstance;
}

void *complexAddition(const void *arg1,const void *arg2, void* result)
{
    Complex *res = (Complex*)result;
    res->re = ((Complex *)arg1)->re + ((Complex *)arg2)->re;
    res->im = ((Complex *)arg1)->im + ((Complex *)arg2)->im;
    return (void *)res;
}

void *complexMultiplication(const void *arg1,const void *arg2, void* result)
{
    Complex *res = (Complex*)result;
    res->re = (((Complex *)arg1)->re * ((Complex *)arg2)->re) -
              (((Complex *)arg1)->im * ((Complex *)arg2)->im);

    res->im = (((Complex *)arg1)->re * ((Complex *)arg2)->im) +
              (((Complex *)arg1)->im * ((Complex *)arg2)->re);

    return (void *)res;
}

void *complexPrint(const void *arg)
{
    Complex *c = (Complex *)arg;
    printf("%.2lf", c->re);
    if (c->im >= 0)
        printf("+");
    printf("%.2lf", c->im);
    printf("i ");
    return (void *)c;
}
void *complexInput(void* target)
{
    Complex *c = (Complex*) target;
    scanf("%lf %lf", &(c->re), &(c->im));
    return (void *)target;
}

void zeroComplexInplace(const void *ptrToZero)
{
    Complex *theZero = (Complex *)ptrToZero;
    theZero->re = 0;
    theZero->im = 0;
}

const void *zeroComplex()
{
    static Complex *theZero = NULL;

    if (theZero == NULL)
    {
        theZero = malloc(sizeof(Complex));
        zeroComplexInplace(theZero);
    }

    return (void *)theZero;
}