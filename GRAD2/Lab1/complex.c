#include "fieldinfo.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct
{
    double re;
    double im;
} Complex;


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
void *complexInput(FILE * source, void *target)
{
    Complex *c = (Complex *)target;
    fscanf(source,"%lf %lf", &(c->re), &(c->im));
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

FieldInfo *getComplexImplementationInstance()
{
    static FieldInfo *complexImplementationInstance = NULL;
    if (complexImplementationInstance == NULL)
    {
        complexImplementationInstance = malloc(sizeof(FieldInfo));
        complexImplementationInstance->allocsize = sizeof(Complex);
        complexImplementationInstance->addition = complexAddition;
        complexImplementationInstance->multiplication = complexMultiplication;
        complexImplementationInstance->printElement = complexPrint;
        complexImplementationInstance->input = complexInput;
        complexImplementationInstance->zero_ = zeroComplex;
        complexImplementationInstance->zeroInPlace = zeroComplexInplace;
        complexImplementationInstance->equal = complexEqual;
        complexImplementationInstance->metadata = 'c';
    }
    return complexImplementationInstance;
}