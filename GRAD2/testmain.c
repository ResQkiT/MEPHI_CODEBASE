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
    Matrix* matrix = newMatrix(m, n,getComplexImplimentationInstance());
    printMatrix(matrix);
    readMatrix(matrix);
    printMatrix(matrix);
    Matrix* matrix2 = newMatrix(m, n, getDoubleImplimentationInstance());
    printMatrix(matrix2);
    readMatrix(matrix2);
    printMatrix(matrix2);
    //readMatrix(matrix2);

    //Matrix* a = malloc(sizeof(Matrix));
    return 0;
}