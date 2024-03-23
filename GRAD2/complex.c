#include "fieldinfo.h"
#include "complex.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct
{
    double re;
    double im;
} Complex;

FieldInfo *getComplexImplimentationInstance()
{
    static FieldInfo *complexImplementatinInstance = NULL;
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
        complexImplementatinInstance->equal = complexEqual;
    }
    return complexImplementatinInstance;
}

void *complexAddition(void *arg1, void *arg2, void *result)
{
    Complex *res = (Complex *)result;
    res->re = ((Complex *)arg1)->re + ((Complex *)arg2)->re;
    res->im = ((Complex *)arg1)->im + ((Complex *)arg2)->im;
    return (void *)res;
}

void *complexMultiplication(void *arg1, void *arg2, void *result)
{
    Complex *res = (Complex *)result;
    res->re = (((Complex *)arg1)->re * ((Complex *)arg2)->re) -
              (((Complex *)arg1)->im * ((Complex *)arg2)->im);

    res->im = (((Complex *)arg1)->re * ((Complex *)arg2)->im) +
              (((Complex *)arg1)->im * ((Complex *)arg2)->re);

    return (void *)res;
}

void *complexPrint(void *arg)
{
    Complex *c = (Complex *)arg;
    printf("%.2lf", c->re);
    if (c->im >= 0)
        printf("+");
    printf("%.2lf", c->im);
    printf("i ");
    return (void *)c;
}
void *complexInput(void* source, void *target)
{
    FILE * file = (FILE*) source;
    Complex *c = (Complex *)target;
    fscanf(file,"%lf %lf", &(c->re), &(c->im));
    return (void *)target;
}

void zeroComplexInplace(void *ptrToZero)
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
void *newComplex(double re, double im)
{
    Complex *complex = malloc(sizeof(Complex));
    complex->re = re;
    complex->im = im;
    return complex;
}
int complexEqual(void * arg1, void * arg2){
    if (arg1 == arg2) return true;
    Complex* c1 = (Complex*) arg1;
    Complex* c2 = (Complex*) arg2;
    if( fabs(c1->re - c2->re)<=1e-6 && fabs(c1->im - c2->im)<=1e-6 ) return true; 
    return false;
}