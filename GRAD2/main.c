#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <complex.h>
#include <assert.h>
#include <string.h>
#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "double.h"
#include "complex.h"
Matrix* createMatrixInterface(){
  int m, n;
  char type;
  Matrix* matrix;
  _start:
  printf("Input matrix\n");
  printf("Input dimensions of the matrix (m, n) : ");
  scanf("%d %d", &m, &n);
  printf("Input the matrix type\n ('i' for integer, 'r' for real, 'c' for complex'):");\
  fgetchar();
  type = fgetchar();
  switch (type - '0')
  {
  case 'i' - '0':
    printf("The type is Integer\n");
    matrix = newMatrix(m, n , newIntegerImpl());
    break;
  case 'r' - '0':
    printf("The type is Real\n");
    matrix = newMatrix(m, n, newDoubleImpl());
    break;
  case 'c' - '0':
    printf("The type is Complex\n");
    printf("Intput the real part first, that the imaginary. \n");
    matrix = newMatrix(m, n, newComplexImpl());
    break;
  default:
    printf("Unsupported value type. You wil be departed to beggining \n");
    goto _start;
    return createPolynomial();
  }

  readMatrix(matrix);

  printf("Matrix which has been entered:\n");
  printMatrix(matrix);
  return matrix;
}
void sumMatrix(){
  printf("Option: sum of 2 matrix\n");
  printf("Enter first matrix\n");
  Matrix* matrixA = createMatrixInterface();
  printf("Enter second matrix:\n");
  Matrix* matrixB = createMatrixInterface();
  Matrix* matrixC = addMatrix(matrixA, matrixB);
  printf("Sum of two matrix:\n");
  printMatrix(matrixC);
}
void multyplyMatrix(){
  printf("Option: multiplication of 2 matrix\n");
  printf("Enter first matrix\n");
  Matrix* matrixA = createMatrixInterface();
  printf("Enter second matrix:\n");
  Matrix* matrixB = createMatrixInterface();
  Matrix* matrixC = multMatrix(matrixA, matrixB);
  printf("Result of multiplication:\n");
  printMatrix(matrixC);
}
void multiplyMatrixbyNumber(){
  printf("Option: multiplication matrix to nuber");
  printf("Enter matrix\n");
  Matrix* matrixA = createMatrixInterface();
  printf("Enter number (number must have same type as matrix): \n");
  void* number = malloc(matrixA->impl->allocsize);
  memcpy(number,  matrixA->impl->input(), matrixA->impl->allocsize);
  printf("The entered number is: ");
  matrixA->impl->printElement(number);
  printf("\n");
  Matrix *res = multMatrixToNumber(matrixA, number);
  printf("Result of multiplication:\n");
  printMatrix(res);
}
void transMatrix(){
  printf("Option: transpose matrix");
  printf("Enter matrix\n");
  Matrix* matrix = createMatrixInterface();
  Matrix* res = transposeMatrix(matrix);
  printMatrix(res);
}
int main(void)
{
  printf("by: Safronov Ilya B23-554");
  printf("Choose an option: \n1) Sum two matrix \n2) Multiply two matrix \n3)Multiply by number\n4)Transpose matrix\n");
  switch (fgetchar()-'0')
  {
  case '1'-'0':
      sumMatrix();
      break;
  case '2'-'0':
      multyplyMatrix();
      break;
  case '3'-'0':
      multiplyMatrixbyNumber();
      break;
  case '4'-'0':
      transMatrix();
      break;
  default:
      printf("UNKNOWN CODE OF OPERATION");
      break;
  }
  return 0;
}
