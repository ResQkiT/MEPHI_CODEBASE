#pragma once
#include "fieldinfo.h"

FieldInfo* getIntegerImplimentationInstance();
void* integerAddition(const void* arg1, const void* arg2, void* result);
void* integerMultiplication(const void* arg1,const void* arg2, void* result);
void* integerPrint(void * arg);
void* integerInput(void* result);

void zerointegerInplace(void *ptrToZero);

void* zeroInteger();
