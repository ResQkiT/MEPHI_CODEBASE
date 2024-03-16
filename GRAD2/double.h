#pragma once
#include "fieldinfo.h"

FieldInfo* newDoubleImpl();
void* doubleAddition(void*, void*);
void* doubleMultiplication(void*, void*);
void* doublePrint(void*);
void* doubleInput();