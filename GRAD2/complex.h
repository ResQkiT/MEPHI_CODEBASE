#pragma once
#include "fieldinfo.h"
FieldInfo *getComplexImplimentationInstance();
void *complexAddition(void *arg1,void *arg2, void* result);
void *complexMultiplication( void *arg1, void *arg2, void* result);
void *complexPrint( void *arg);
void *complexInput(void* source, void* target);
void zeroComplexInplace(void *ptrToZero);
const void *zeroComplex();
void* newComplex(double re, double im);

int complexEqual(void * arg1, void * arg2);