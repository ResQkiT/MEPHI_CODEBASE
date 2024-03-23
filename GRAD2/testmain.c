#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "complex.h"
#include "double.h"

#include <string.h>
#include "test.h"

int tests_run = 0;

int foo = 7;
int bar = 5;

static char *test_integer_sum()
{
    printf("Test 1: testing the summation of two double matrices \n");
    
    FILE *fptr1 = fopen("tests/test1/matrix1.1", "r");
    FILE *fptr2 = fopen("tests/test1/matrix1.2", "r");
    FILE *fptrAns = fopen("tests/test1/answer", "r");
    Matrix* a = newMatrixFromFile(fptr1);
    Matrix* b = newMatrixFromFile(fptr2);
    Matrix* answer = newMatrixFromFile(fptrAns);
    
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix* res = newMatrix(getRows(a), getCols(a), getFieldInfo(a));
    addMatrix(a, b, res);
    delete(a);
    delete(b);

    printMatrix(res);
    printMatrix(answer);
    int flag = equal(res, answer);
    delete(res);
    delete(answer);
    
    mu_assert("TEST 1 FAILED", flag);
    return 0;
}
static char *test_complex_sum()
{
    printf("Test 2: testing the summation of two complex matrices \n");
    
    FILE *fptr1 = fopen("tests/test2/matrix2.1", "r");
    FILE *fptr2 = fopen("tests/test2/matrix2.2", "r");
    FILE *fptrAns = fopen("tests/test2/answer", "r");
    Matrix* a = newMatrixFromFile(fptr1);
    Matrix* b = newMatrixFromFile(fptr2);
    Matrix* answer = newMatrixFromFile(fptrAns);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix* res = newMatrix(getRows(a), getCols(a), getFieldInfo(a));
    addMatrix(a, b, res);
    delete(a);
    delete(b);

    printMatrix(res);
    printMatrix(answer);
    int flag = equal(res, answer);
    delete(res);
    delete(answer);
    
    mu_assert("TEST 2 FAILED", flag);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_integer_sum);
    mu_run_test(test_complex_sum);
    return 0;
}

int main(int argc, char **argv)
{
    printf("Testing...\n");
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
/*
int main()
{
    FILE *file1 = fopen("matrix1.txt", "r");
    FILE *file2 = fopen("matrix2.txt", "r");
    printf("%p %p", file1, file2);
    Matrix *matrix1 = newMatrixFromFile(file1);
    printMatrix(matrix1);
    Matrix *matrix2 = newMatrixFromFile(file2);
    Matrix *res = newMatrix(getRows(matrix1), getCols(matrix1), getFieldInfo(matrix1));
    printMatrix(matrix2);
    multMatrix(matrix1, matrix2, res);
    printMatrix(res);
    fclose(file1);
    fclose(file2);
    delete (matrix1);
    delete (matrix2);
    delete (res);
    /*
    Matrix* res =  newMatrix(getRows(matrix1), getCols(matrix1), getFieldInfo(matrix1));
    addMatrix(matrix1, matrix2, res);
    printMatrix(res);
    delete(matrix1);
    delete(matrix2);
    delete(res);


    int a1, b1, a2 , b2;
    scanf("%d %d" , &a1, &b1);
    printf("enter first: \n");
    Matrix* matrix = newMatrix(a1,  b1,getIntegerImplimentationInstance());
    readMatrix(matrix);
    printMatrix(matrix);
    printf("enter second: \n");
    scanf("%d %d" , &a2, &b2);
    Matrix* matrix2 = newMatrix(a2, b2, getIntegerImplimentationInstance());
    readMatrix(matrix2);
    printMatrix(matrix2);
    printf("result: \n");
    Matrix* res = newMatrix(a1, b2, getIntegerImplimentationInstance());
    multMatrix(matrix, matrix2, res);

    printf("end add main\n");
    printMatrix(res);
    delete(matrix);
    delete(matrix2);
    delete(res);

    */
    /*
     int x, y;
     double re, im;
     scanf("%d %d %lf %lf" , &x, &y, &re, &im);
     Matrix *m1 = newMatrix(x, y, getComplexImplimentationInstance());
     readMatrix(m1);
     Matrix *r1 = newMatrix(x, y, getComplexImplimentationInstance());
     void * complex = newComplex(re, im);
     r1 = multMatrixToNumber(m1 , complex, r1);
     printMatrix(m1);
     printMatrix(r1);
     free(complex);
     delete(m1);
     delete(r1);
     return 0;
    
}

*/