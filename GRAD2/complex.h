#pragma once
#include "fieldinfo.h"

FieldInfo* newComplexImpl();
void* complexAddition(void*, void*);
void* complexMultiplication(void*, void*);
void* complexPrint(void*);
void* complexInput();