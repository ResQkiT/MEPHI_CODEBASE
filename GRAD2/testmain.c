#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include <string.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "complex.h"
#include "double.h"
#include "constants.h"

int tests_run = 0;
int tests_failed = 0;

void test_integer_sum()
{

    printf("Test 1: testing the summation of two integer matrices \n");

    FILE *fptr1 = fopen("tests/test1/matrix1.1", "r");
    FILE *fptr2 = fopen("tests/test1/matrix1.2", "r");
    FILE *fptrAns = fopen("tests/test1/answer", "r");
    FieldInfo * integerImplementation = getIntegerImplimentationInstance();

    Matrix *a = newMatrixFromFile(fptr1, integerImplementation);
    Matrix *b = newMatrixFromFile(fptr2 , integerImplementation);
    Matrix *answer = newMatrixFromFile(fptrAns, integerImplementation);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix *res = newClone(a);
    
    addMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    bool isEqual = equal(res, answer);
    delete (res);
    delete (answer);
    if (!isEqual)
    {
        printf("TEST 1 FAILED");
        tests_failed++;
    }
}
void test_complex_sum()
{
    printf("Test 2: testing the summation of two complex matrices \n");

    FILE *fptr1 = fopen("tests/test2/matrix2.1", "r");
    FILE *fptr2 = fopen("tests/test2/matrix2.2", "r");
    FILE *fptrAns = fopen("tests/test2/answer", "r");
    FieldInfo * complexImplementation = getComplexImplimentationInstance();

    Matrix *a = newMatrixFromFile(fptr1, complexImplementation);
    Matrix *b = newMatrixFromFile(fptr2, complexImplementation);
    Matrix *answer = newMatrixFromFile(fptrAns, complexImplementation);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);

    Matrix *res = newClone(a);
    addMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    bool isEqual = equal(res, answer);
    delete (res);
    delete (answer);
    if (!isEqual)
    {
        printf("TEST 2 FAILED");
        tests_failed++;
    }
}
void test_double_multiplication()
{
    printf("Test 3: testing the multiplication of double matrix by number\n");

    FILE *mfptr = fopen("tests/test3/matrix", "r");
    FILE *fptrAns = fopen("tests/test3/answer", "r");
    FieldInfo * doubleImplementation = getDoubleImplimentationInstance();

    Matrix *matrix = newMatrixFromFile(mfptr, doubleImplementation);
    Matrix *answer = newMatrixFromFile(fptrAns, doubleImplementation);

    fclose(mfptr);
    fclose(fptrAns);

    double number = -13.3;

    Matrix *res = newClone(matrix);
    multMatrixToNumber(matrix, ((void *)&number), res);
    delete (matrix);

    printMatrix(res);
    printMatrix(answer);

    bool isEqual = equal(res, answer);

    delete (answer);
    delete (res);

    if (!isEqual)
    {
        printf("TEST 3 FAILED");
        tests_failed++;
    }
}
void test_integer_two_matrix_multiplication()
{
    printf("Test 4: testing two matrix multiplication \n");

    FILE *fptr1 = fopen("tests/test4/matrix4.1", "r");
    FILE *fptr2 = fopen("tests/test4/matrix4.2", "r");
    FILE *fptrAns = fopen("tests/test4/answer", "r");
    FieldInfo * integerImplementation = getIntegerImplimentationInstance();

    Matrix *a = newMatrixFromFile(fptr1, integerImplementation);
    Matrix *b = newMatrixFromFile(fptr2, integerImplementation);
    Matrix *answer = newMatrixFromFile(fptrAns, integerImplementation);

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptrAns);
    //кастомное клонирование
    Matrix *res = newMatrix(getRows(a), getCols(b), getFieldInfo(a));
    multMatrix(a, b, res);
    delete (a);
    delete (b);

    printMatrix(res);
    printMatrix(answer);
    bool isEqual = equal(res, answer);
    delete (res);
    delete (answer);
    
    if (!isEqual)
    {
        printf("TEST 4 FAILED");
        tests_failed++;
    }
}
void runTest(void (*test)()){
    tests_run++;
    test();
}
void all_tests()
{
    runTest(test_integer_sum);
    runTest(test_complex_sum);
    runTest(test_double_multiplication);
    runTest(test_integer_two_matrix_multiplication);
}

int main(int argc, char **argv)
{
    printf("Testing...\n");
    all_tests();
    printf("Tests run: %d\nTests succes:%d\nTests failed: %d\n", tests_run, tests_run - tests_failed, tests_failed);
    return 0;
}