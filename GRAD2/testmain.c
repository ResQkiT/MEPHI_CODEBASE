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
#include <string.h>
int main(){
    Matrix* matrix = newMatrix(2, 2,getIntegetImplimentationInstance());
    printMatrix(matrix);
    readMatrix(matrix);
    
    printMatrix(matrix);
    //Matrix* a = malloc(sizeof(Matrix));
    return 0;
}