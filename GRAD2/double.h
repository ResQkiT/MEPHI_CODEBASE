#pragma once
#include "fieldinfo.h"

FieldInfo *getDoubleImplimentationInstance();
void *doubleAddition(void *arg1, void *arg2, void *result);
void *doubleMultiplication(void *arg1, void *arg2, void *result);
void *doublePrint(void *arg);
void *doubleInput(void *target);
void zeroDoubleInplace(void *ptrToZero);
const void *zeroDouble();
int doubleEqual(void * arg1, void * arg2);