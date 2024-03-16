#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <complex.h>
#include <assert.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "double.h"

int main(void)
{
  //printf("End!");
  Matrix* matrixA = newMatrix(1, 3, newDoubleImpl());
  readMatrix(matrixA);
  //printMatrix(matrixA);

  Matrix* matrixB = newMatrix(3, 1, newDoubleImpl());
  readMatrix(matrixB);
  //printMatrix(matrixB);

  Matrix* matrixC = multMatrix(matrixA, matrixB);
  printMatrix(matrixC);
  printf("point!");
  fgetchar();
  
  printf("End!");
  fgetchar();
}
