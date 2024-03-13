#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <complex.h>
#include <assert.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"

int main(void)
{
  //printf("End!");
  Matrix* matrixA = newMatrix(2, 3, newIntegerImpl());
  readMatrix(matrixA);
  printMatrix(matrixA);

  Matrix* matrixB = newMatrix(2, 3, newIntegerImpl());
  readMatrix(matrixB);
  printMatrix(matrixB);

  
  printf("point!");
  fgetchar();
  
  printf("End!");
  fgetchar();
}
