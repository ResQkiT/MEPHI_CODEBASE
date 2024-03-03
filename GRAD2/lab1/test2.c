#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

typedef struct {
    int is_complex;
    union {
        int integer;
        double complexValue;
    } value;
} MatrixElement;

typedef struct {
    int rows;
    int cols;
    MatrixElement **elements;
} Matrix;

Matrix* createMatrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->elements = (MatrixElement**)malloc(rows * sizeof(MatrixElement*));
    
    for (int i = 0; i < rows; i++) {
        matrix->elements[i] = (MatrixElement*)malloc(cols * sizeof(MatrixElement));
    }
    return matrix;
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
int main() {
    int rows, cols;
    printf("Enter the number of rows and columns for the matrix: ");
    scanf("%d %d", &rows, &cols);

    Matrix* matrix = createMatrix(rows, cols);
    fillMatrixZeros(matrix);
    // Заполнение матрицы
    matrix->elements[0][0].is_complex = 1;
    matrix->elements[0][0].value.complexValue = 1.0 + 2.0 * I;

    matrix->elements[1][1].is_complex = 1;
    matrix->elements[1][1].value.complexValue = 3.0 + 4.0 * I;

    matrix->elements[2][2].is_complex = 0;
    matrix->elements[2][2].value.integer = 5;

    // Вывод матрицы
    printMatrix(matrix);

    // Освобождение памяти
    freeMatrix(matrix);

    return 0;
}
