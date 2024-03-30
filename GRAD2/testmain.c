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
int tests_failed = 0;
int tests_succses = 0;

static char *test_integer_sum()
{
    printf("Test 1: testing the summation of two integer matrices \n");

    FILE *fptr1 = fopen("tests/test1/matrix1.1", "r");
    FILE *fptr2 = fopen("tests/test1/matrix1.2", "r");
    FILE *fptrAns = fopen("tests/test1/answer", "r");
    Matrix *a = newMatrixFromFile(fptr1);
    Matrix *b = newMatrixFromFile(fptr2);
    Matrix *answer = newMatrixFromFile(fptrAns);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix *res = newMatrix(getRows(a), getCols(a), getFieldInfo(a));
    addMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    int flag = equal(res, answer);
    delete (res);
    delete (answer);

    mu_assert("TEST 1 FAILED", flag);
    return 0;
}
static char *test_complex_sum()
{
    printf("Test 2: testing the summation of two complex matrices \n");

    FILE *fptr1 = fopen("tests/test2/matrix2.1", "r");
    FILE *fptr2 = fopen("tests/test2/matrix2.2", "r");
    FILE *fptrAns = fopen("tests/test2/answer", "r");
    Matrix *a = newMatrixFromFile(fptr1);
    Matrix *b = newMatrixFromFile(fptr2);
    Matrix *answer = newMatrixFromFile(fptrAns);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix *res = newMatrix(getRows(a), getCols(a), getFieldInfo(a));
    addMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    int flag = equal(res, answer);
    delete (res);
    delete (answer);

    mu_assert("TEST 2 FAILED\n", flag);
    return 0;
}
static char *test_double_multiplication()
{
    printf("Test 3: testing the multiplication of double matrix by number\n");

    FILE *mfptr = fopen("tests/test3/matrix", "r");
    FILE *fptrAns = fopen("tests/test3/answer", "r");
    Matrix *matrix = newMatrixFromFile(mfptr);
    Matrix *answer = newMatrixFromFile(fptrAns);

    fclose(mfptr);
    fclose(fptrAns);

    double number = -13.3;

    Matrix *res = newMatrix(getRows(matrix), getCols(matrix), getFieldInfo(matrix));
    multMatrixToNumber(matrix, ((void *)&number), res);
    delete (matrix);

    printMatrix(res);
    printMatrix(answer);

    int flag = equal(res, answer);

    delete (answer);
    delete (res);

    mu_assert("TEST 3 FAILED\n", flag);
    return 0;
}
static char *test_integer_two_matrix_multiplication()
{
    printf("Test 4: testing two matrix multiplication \n");

    FILE *fptr1 = fopen("tests/test4/matrix4.1", "r");
    FILE *fptr2 = fopen("tests/test4/matrix4.2", "r");
    FILE *fptrAns = fopen("tests/test4/answer", "r");

    Matrix *a = newMatrixFromFile(fptr1);
    Matrix *b = newMatrixFromFile(fptr2);

    Matrix *answer = newMatrixFromFile(fptrAns);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix *res = newMatrix(getRows(a), getCols(b), getFieldInfo(a));
    multMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    int flag = equal(res, answer);
    delete (res);
    delete (answer);

    mu_assert("TEST 4 FAILED\n", flag);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_integer_sum);
    mu_run_test(test_complex_sum);
    mu_run_test(test_double_multiplication);
    mu_run_test(test_integer_two_matrix_multiplication);
    return 0;
}

int main(int argc, char **argv)
{
    printf("Testing...\n");
    char *result = all_tests();
    printf("Tests run: %d\nTests succes:%d\nTests failed: %d\n", tests_run, tests_succses, tests_failed);
    if (tests_run == tests_succses)
    {
        printf("ALL TESTS PASSED\n");
    }
    return result != 0;
}