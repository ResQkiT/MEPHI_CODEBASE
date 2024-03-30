#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <string.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "double.h"
#include "complex.h"
#include "constants.h"
Matrix *readFromFileInterface()
{
  bool loophere = true;
  char filepath[100];
  do
  {
    printf("Enter path to file ->");
    scanf("%s", filepath);
    FILE *path = fopen(filepath, "r");
    if (path == NULL)
    {
      printf("Invalid path entered or file not found\n");
    }
    else
    {
      Matrix *matrix = newMatrixFromFile(path);
      fclose(path);
      printf("Have read matrix with rows: %d\ncols: %d\ntype: %c\n", getRows(matrix), getCols(matrix), getFieldInfo(matrix)->metadata);
      printMatrix(matrix);

      return matrix;
    }
  } while (loophere);
}
Matrix *createMatrixInterface()
{
  char choise;
  printf("Would you like to read matrix from file?(y/n)->");
  scanf(" %c", &choise);
  if (choise == 'y')
  {
    return readFromFileInterface();
  }

  int m, n;
  char type;
  bool flag = true;
  Matrix *matrix;
  do
  {
    printf("Input matrix\n");
    printf("Input dimensions of the matrix (m, n) : ");
    scanf("%d %d", &m, &n);
    printf("Input the matrix type\n ('i' for integer, 'd' for real, 'c' for complex'):\n");
    scanf(" %c", &type);
    switch (type - '0')
    {
    case 'i' - '0':
      printf("The type is Integer\n");
      matrix = newMatrix(m, n, getIntegerImplimentationInstance());
      flag = false;
      break;
    case 'd' - '0':
      printf("The type is Real\n");
      matrix = newMatrix(m, n, getDoubleImplimentationInstance());
      flag = false;
      break;
    case 'c' - '0':
      printf("The type is Complex\n");
      printf("Intput the real part first, that the imaginary. \n");
      matrix = newMatrix(m, n, getComplexImplimentationInstance());
      flag = false;
      break;
    default:
      printf("Unsupported value type. You wil be departed to beggining \n");
      return NULL;
    }
  } while (flag);
  printf("matrix:\n");
  readMatrix(matrix);

  printf("Matrix which has been entered:\n");
  printMatrix(matrix);
  return matrix;
}

void sumMatrix()
{
  printf("Option: sum of 2 matrix\nEnter first matrix\n");
  Matrix *matrixA = createMatrixInterface();
  printf("Enter second matrix (same type as first one):\n");
  Matrix *matrixB = createMatrixInterface();
  Matrix *matrixC = newMatrix(getRows(matrixA), getCols(matrixB), getFieldInfo(matrixA));
  addMatrix(matrixA, matrixB, matrixC);
  printf("Sum of two matrix:\n");
  printMatrix(matrixC);
  delete (matrixA);
  delete (matrixB);
  delete (matrixC);
}

void multiplyMatrix()
{
  printf("Option: multiplication of 2 matrix\nEnter first matrix\n");
  Matrix *matrixA = createMatrixInterface();
  printf("Enter second matrix:\n");
  Matrix *matrixB = createMatrixInterface();
  Matrix *matrixC = newMatrix(getRows(matrixA), getCols(matrixB), getFieldInfo(matrixA));
  multMatrix(matrixA, matrixB, matrixC);
  printf("Result of multiplication:\n");
  printMatrix(matrixC);
  delete (matrixA);
  delete (matrixB);
  delete (matrixC);
}

void multiplyMatrixbyNumber()
{
  printf("Option: multiplication matrix to nuber\nEnter matrix\n");
  Matrix *matrixA = createMatrixInterface();
  printf("Enter number (number must have same type as matrix): \n");
  void *number = malloc(getFieldInfo(matrixA)->allocsize);

  memcpy(number, getFieldInfo(matrixA)->input(stdin, number), getFieldInfo(matrixA)->allocsize);
  printf("The entered number is: ");
  getFieldInfo(matrixA)->printElement(number);
  printf("\n");
  Matrix *res = newClone(matrixA);

  multMatrixToNumber(matrixA, number, res);
  printf("Result of multiplication:\n");
  printMatrix(res);
  delete (res);
  delete (matrixA);
  free(number);
}
int main(int argc, const char **argv)
{
  printf("by: Safronov Ilya B23-554 \n");

  printf("Choose an option: \n1) Sum two matrix \n2) Multiply two matrix \n3) Multiply by number \n\n");
  switch (getchar() - '0')
  {
  case '1' - '0':
    sumMatrix();
    break;
  case '2' - '0':
    multiplyMatrix();
    break;
  case '3' - '0':
    multiplyMatrixbyNumber();
    break;
  default:
    printf("UNKNOWN CODE ");
    break;
  }
  return 0;
}
