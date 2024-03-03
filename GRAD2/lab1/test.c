#include <stdio.h>

typedef struct DataImpl {
  void* (*add)(void*, void*);
  void* (*sub)(void*, void*);
  void* (*mul)(void*, void*);
  void* (*div)(void*, void*);
} DataImplType;

int addInt(int* a, int* b) { 
  int* result = malloc(sizeof(int));
  *result = *a + *b;
  return result;
}

int subInt(int* a, int* b) { 
  int* result = malloc(sizeof(int));
  *result = *a - *b;
  return result;
}

int mulInt(int* a, int* b) { 
  int* result = malloc(sizeof(int));
  *result = *a * *b;
  return result;
}

int divInt(int* a, int* b) { 
  int* result = malloc(sizeof(int));
  *result = *a / *b;
  return result;
}

int main() {
  DataImplType dataImpl;
  dataImpl.add = addInt;
  dataImpl.sub = subInt;
  dataImpl.mul = mulInt;
  dataImpl.div = divInt;

  int num1 = 10, num2 = 5;
  int* resultAdd = dataImpl.add(&num1, &num2);
  int* resultSub = dataImpl.sub(&num1, &num2);
  int* resultMul = dataImpl.mul(&num1, &num2);
  int* resultDiv = dataImpl.div(&num1, &num2);

  printf("Addition: %d\n", *resultAdd);
  printf("Subtraction: %d\n", *resultSub);
  printf("Multiplication: %d\n", *resultMul);
  printf("Division: %d\n", *resultDiv);

  free(resultAdd);
  free(resultSub);
  free(resultMul);
  free(resultDiv);

  return 0;
}
