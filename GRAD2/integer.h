#pragma once
#include "fieldinfo.h"

FieldInfo* newIntegerImpl();
void* integerAddition(void*, void*);
void* integerMultiplication(void*, void*);
void* integerPrint(void*);
void* integerInput();