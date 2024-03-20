#pragma once
#include "fieldinfo.h"

FieldInfo *getDoubleImplimentationInstance();
void *doubleAddition(const void *arg1, const void *arg2, void *result);
void *doubleMultiplication(const void *arg1, const void *arg2, void *result);
void *doublePrint(void *arg);
void *doubleInput(void *target);
void zeroDoubleInplace(void *ptrToZero);
void *zeroDouble();
