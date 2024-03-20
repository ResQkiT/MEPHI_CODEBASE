#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "matrix.h"
#include "fieldinfo.h"
#include "integer.h"
#include "complex.h"
#include "double.h"

#include <string.h>
int main(){
    int m, n;
    scanf("%d %d" , &m, &n);
    Matrix* matrix = newMatrix(m, n,getIntegerImplimentationInstance());
    Matrix* matrix2 = newMatrix(m, n, getDoubleImplimentationInstance());
    printMatrix(matrix);
    readMatrix(matrix);
    printMatrix(matrix);

    readMatrix(matrix2);
    printMatrix(matrix);
    printMatrix(matrix2);

    //Matrix* a = malloc(sizeof(Matrix));
    return 0;
}