#pragma once
#include "fieldinfo.h"

FieldInfo *getComplexImplimentationInstance();
void *complexAddition(const void *arg1,const void *arg2, void* result);
void *complexMultiplication(const void *arg1,const void *arg2, void* result);
void *complexPrint(const void *arg);
void *complexInput(void* target);
void zeroComplexInplace(const void *ptrToZero);
const void *zeroComplex();