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
int main(){
    int m, n;
    scanf("%d %d" , &m, &n);
    printf("enter first: \n");
    Matrix* matrix = newMatrix(m, n,getComplexImplimentationInstance());
    readMatrix(matrix);

    printMatrix(matrix);
    printf("enter second: \n");
    Matrix* matrix2 = newMatrix(m, n, getComplexImplimentationInstance());
    readMatrix(matrix2);
    printMatrix(matrix2);
    printf("result: \n");
    Matrix* res = newMatrix(m, n, getComplexImplimentationInstance()); 
    addMatrix(matrix, matrix2, res);

    printf("end add main\n");
    printMatrix(res);
    delete(matrix);
    delete(matrix2);
    delete(res);
    return 0;
}