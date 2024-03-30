#pragma once
#include "fieldinfo.h"

FieldInfo *getIntegerImplimentationInstance();
void *integerAddition(void *arg1, void *arg2, void *result);
void *integerMultiplication(void *arg1, void *arg2, void *result);
void *integerPrint(void *arg);
void *integerInput(void *source, void *result);

void zeroIntegerInplace(void *ptrToZero);

const void *zeroInteger();

int integerEqual(void *arg1, void *arg2);