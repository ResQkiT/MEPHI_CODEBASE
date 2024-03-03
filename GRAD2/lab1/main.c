#include <stdio.h>
#include <locale.h>
#include <complex.h>
#include <assert.h>
#define INTEGER_TYPE 1
#define COMPLEX_TYPE 2

/*Информация о типе матрицы , содержащие методы для работы*/
typedef struct DataImpl {
  void* (*add)(void*, void*);
  void* (*sub)(void*, void*);
  void* (*mul)(void*, void*);
  void* (*div)(void*, void*);
} DataImpl;

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
/*
complex addComplex(void *a, void *b){ return (*((complex*) a ) +  *((complex*) b )); }
complex subComplex(void *a, void *b){ return (*((complex*) a ) -  *((complex*) b )); }
complex mulComplex(void *a, void *b){ return (*((complex*) a ) *  *((complex*) b )); }
complex divComplex(void *a, void *b){ return (*((complex*) a ) /  *((complex*) b )); }
*/

DataImpl INTEGER_DATA_IMP = {addInt, subInt, mulInt, divInt};
//DataImpl COMPLEX_DATA_IMP = {addInt, subInt, mulInt, divInt};

typedef struct {
    int is_complex;
    union {
        int integer;
        double complex complexValue;
    } value;
} Number;

typedef struct {
    int rows;
    int cols;
    Number **elements;
    DataImpl impl;
} Matrix;

Matrix* newMatrix(int rows, int cols, DataImpl impl) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->impl = impl;
    matrix->elements = (Number**)malloc(rows * sizeof(Number*));
    
    for (int i = 0; i < rows; i++) {
        matrix->elements[i] = (Number*)malloc(cols * sizeof(Number));
    }
    fillMatrixZeros(matrix);
    return matrix;
}
Number* newNumber(){
  Number *number = (Number*)malloc( sizeof(Number));
  return number;
}
void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (matrix->elements[i][j].is_complex) {
                printf("%.2lf + %.2lfi\t", creal(matrix->elements[i][j].value.complexValue),
                       cimag(matrix->elements[i][j].value.complexValue));
            } else {
                printf("%d\t\t", matrix->elements[i][j].value.integer);
            }
        }
        printf("\n");
    }
}
void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix);
}
void fillMatrixZeros(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->elements[i][j].is_complex = 0;
            matrix->elements[i][j].value.integer = 0;
        }
    }
}

void readMatrixFromConsole(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("Ввод элемента на позиции [%d][%d]\nЯвляется ли элемент комплексным числом?(1 = yes/ 0 = no): ", i, j);

            int isComplexInput;
            scanf("%d", &isComplexInput);
            
            if (isComplexInput) {
                double realPart, imagPart;
                printf("Введите действительную часть комплексного число (Rel): ");
                scanf("%lf", &realPart);
                printf("Введите мнимую часть комплексного числа (Img): ");
                scanf("%lf", &imagPart);
                
                matrix->elements[i][j].is_complex = 1;
                matrix->elements[i][j].value.complexValue = (double complex)((double)realPart +  I * (double)imagPart);
            } else {
                int integerValue;
                printf("Введите целочисленное значение: ");
                scanf("%d", &integerValue);
                
                matrix->elements[i][j].is_complex = 0;
                matrix->elements[i][j].value.integer = integerValue;
            }
        }
    }
}
Matrix *multMatrixToNumber(Matrix* matrix, Number* element) {
    Matrix *result = newMatrix(matrix->rows, matrix->cols, matrix->impl);
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
          if (element->is_complex)
          {
            result->elements[i][j].is_complex = 1;
            
          }else{

          }
          
          if (element->is_complex || matrix->elements[i][j].is_complex ) {
              result->elements[i][j].is_complex = 1;
              result->elements[i][j].value.complexValue = matrix->elements[i][j].is_complex ? \
                matrix->elements[i][j].value.complexValue * element->value.complexValue :  \
                matrix->elements[i][j].value.integer * element->value.complexValue;
          } else {
              result->elements[i][j].is_complex = 0;
              result->elements[i][j].value.integer = matrix->elements[i][j].value.integer * element->value.integer;
          }
        }
    }
    
    return result;
}
/*

Matrix *sumMatrix(Matrix* matrixA, Matrix* matrixB) {
    assert(matrixA->cols == matrixB->cols && matrixA->rows==matrixB->rows);

    Matrix *result = newMatrix(matrixA->rows, matrixA->cols, matrixA->impl);
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
          result->elements[i][j].is_complex =  matrixA->elements[i][j].is_complex || matrixB->elements[i][j].is_complex; 
          result->elements[i][j].value.complexValue = matrix->elements[i][j].is_complex ? \
                  matrix->elements[i][j].value.complexValue * element->value.complexValue :  \
                  matrix->elements[i][j].value.integer * element->value.complexValue;
        }
    }
    
    return result;
}*/
void outTitle()
{
  printf("Лабараторная работа № 1 "
         "Реализация квадратных матриц"
         " \nАвтор: Сафронов Илья Сергеевич Б23-554\nGit: https://github.com/ResQkiT \n");
}

int main(void)
{

  setlocale(LC_ALL, "ru_RU.UTF-8");
  int n, type_marker;
  char operation ;

  outTitle();
  printf("Вберете операцию: \
    \n 1 - Умножение матрицы на число \
    \n 2 - Сложение матриц \
    \n 3 - Умножение матриц\n");
  scanf("%c", &operation);

  switch (operation)
  {
  case '1':
  
    printf("Операция: Умножение на число. ");
    printf("Введите размерность матрицы n: ");
    scanf("%d", &n);
    Matrix *matrix = newMatrix(n, n , INTEGER_DATA_IMP);
    printf("Введите матрицу %d строк %d столбцов:\n", n, n);
    readMatrixFromConsole(matrix);
    printMatrix(matrix);
    printf("Введите число на которое необходимо умножить.");
    Number *number = newNumber();
    _FIRSTCHOISE:
    printf("Выполнить умножение на \nкомплексное число (1)\nцелое число (0): ");
    scanf("%d", &type_marker);
    if (type_marker == 0)
    {
      int intValue;
      printf("Целое число: ");
      scanf("%d", &intValue);
      number->is_complex = 0;
      number->value.integer = intValue;
    }
    else if(type_marker == 1){
      double realPart, imagPart;
      printf("Введите действительную часть комплексного число (Rel): ");
      scanf("%lf", &realPart);
      printf("Введите мнимую часть комплексного числа (Img): ");
      scanf("%lf", &imagPart);
      double complex complexNum = realPart + imagPart * I;
      number->is_complex = 1;
      number->value.complexValue = complexNum;
    }
    else
    {
      //я знаю что это плохая практика, но я не хочу еще сильнее усложнять код ввода, который по факту ничего не проверяет
      printf("Некоректный выбор в меню, вы будете отброшены в начало.\n");
      goto _FIRSTCHOISE;
    }
    Matrix *resultMatrix = multMatrixToNumber(matrix, number);
    printf("Результат операции умножения матрицы на число:\n");
    printMatrix(resultMatrix);
    freeMatrix(matrix);
    freeMatrix(resultMatrix);
    free(number);
    break;

  case '2':
    printf("Операция: Сложение 2х матриц. \nВведите размерность первой матрицы: ");
    int m1, n1, m2, n2;
    scanf("%d %d" , &m1, &n1);
    printf("Введите размерность второй матрицы: ");
    scanf("%d %d" , &m2 , &n2);
    printf("Введите первую матрицу размерностью %dx%d" , m1, n1);
    Matrix* matrixA =newMatrix(m1, n1, INTEGER_DATA_IMP);
    readMatrixFromConsole(matrixA);
    printf("Введите вторую матрицу размерностью %dx%d" , m2, n2);
    Matrix* matrixB =newMatrix(m2, n2, INTEGER_DATA_IMP);
    readMatrixFromConsole(matrixB);
    if(m1 == m2 && n1 == n2){
      
    }else{
      printf("Нельзя сложить матрицы т.к не равны их размерности!");
    }
    break;

  case '3':
    break;
  default:
    printf("Выбран неверный код оперции");
    break;

    return 0;
  }
}
