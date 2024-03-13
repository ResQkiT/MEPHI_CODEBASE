#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <complex.h>
#include <assert.h>

#include "integer.h"

void outTitle()
{
  printf("Лабараторная работа № 1 "
         "Реализация квадратных матриц"
         " \nАвтор: Сафронов Илья Сергеевич Б23-554\nGit: https://github.com/ResQkiT \n");
}


/*


void multipleMatrixToNumber(){
    int n;

    printf("Операция: Умножение на число. ");
    printf("Введите размерность матрицы n: ");
    scanf("%d", &n);
    Matrix *matrix = newMatrix(n, n,  , INTEGER_IMPL);
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

}
void sumOfMatrix(){
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
}
*/

void printIntMatrix(Matrix* self){
    Matrix *matrix = self;
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0; j < matrix->n; j++)
        {
            printf("%d " , *((int*)(matrix->impl->get(matrix, i, j))));
        }
        putchar('\n');
    }   
}

int main(void)
{

    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n, type_marker;
    char operation;

    outTitle();
    printf("Вберете операцию: \
    \n 1 - Умножение матрицы на число \
    \n 2 - Сложение матриц \
    \n 3 - Умножение матриц\n");
    
    Matrix *first = newMatrix(5, 2, &INTEGER_IMPL);
    printIntMatrix(first);
    getchar();

    return 0;
}
