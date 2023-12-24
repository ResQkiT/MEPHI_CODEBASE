#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int m;
    int n;
    int **data;
} Matrix;
int error_code = 0;

Matrix* create_matrix(int * mass, int m, int n){
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->m = m;
    matrix->n = n;
    matrix->data = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++){
        matrix->data[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            matrix->data[i][j] = mass[i * n + j];
        }
    }
    return matrix;
}
Matrix* transpose(Matrix *matrix){
    Matrix *new_matrix = (Matrix *)malloc(sizeof(Matrix));
    new_matrix->m = matrix->n;
    new_matrix->n = matrix->m;
    new_matrix->data = (int **)malloc(new_matrix->m * sizeof(int *));
    for(int i = 0; i < new_matrix->m; i++){
        new_matrix->data[i] = (int *)malloc(new_matrix->n * sizeof(int));
        for(int j = 0; j < new_matrix->n; j++){
            new_matrix->data[i][j] = matrix->data[j][i];
        }
    }
    return new_matrix;
}
void print_matrix(Matrix *matrix){
    if (error_code != 0)
    {
        printf("!%d\n" , error_code);
        return;
    }

    for (int i = 0; i < (*matrix).m; i++) {
        for (int j = 0; j < (*matrix).n; j++) {
            printf("%6d", (*matrix).data[i][j]);
        }
        printf("\n");
    }
}
Matrix* getRandomMatrix(int m, int n){
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->m = m;
    matrix->n = n;
    matrix->data = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++){
        matrix->data[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            matrix->data[i][j] = rand() % 100;
        }
    }
    return matrix;
}
Matrix* readMatrixfromFile(char *filename){
    FILE *fp = fopen(filename, "r");
    int m, n;
    fscanf(fp, "%d %d", &m, &n);
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->m = m;
    matrix->n = n;
    matrix->data = (int **)malloc(m * sizeof(int *));
    for(int i = 0; i < m; i++){
        matrix->data[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            fscanf(fp, "%d", &matrix->data[i][j]);
        }
    }
    fclose(fp);
    return matrix;
}
void saveMatrixtoFile(Matrix *matrix, char *filename){
    FILE *fp = fopen(filename, "w");
    for(int i = 0; i < (*matrix).m; i++){
        for(int j = 0; j < (*matrix).n; j++){
            fprintf(fp, "%d ", (*matrix).data[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
Matrix* addMatrix(Matrix *matrix1, Matrix *matrix2){
    if (matrix1 == NULL || matrix2 == NULL) return NULL;

    if ((matrix1->n != matrix2->n || matrix1->m!= matrix2->m) && error_code == 0){
        error_code = 1;
        return NULL;
    }

    Matrix *new_matrix = (Matrix *)malloc(sizeof(Matrix));
    new_matrix->m = matrix1->m;
    new_matrix->n = matrix1->n;
    new_matrix->data = (int **)malloc(new_matrix->m * sizeof(int *));
    for(int i = 0; i < new_matrix->m; i++){
        new_matrix->data[i] = (int *)malloc(new_matrix->n * sizeof(int));
        for(int j = 0; j < new_matrix->n; j++){
            new_matrix->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }
    return new_matrix;
}
Matrix* multiplyMatrix(Matrix *matrix1, Matrix *matrix2){
    if (matrix1 == NULL || matrix2 == NULL) return NULL;
    if ((matrix1->n != matrix2->m) && error_code == 0){
        error_code = 2;
        return NULL;
    }
        
    Matrix *new_matrix = (Matrix *)malloc(sizeof(Matrix));
    new_matrix->m = matrix1->m;
    new_matrix->n = matrix2->n;
    new_matrix->data = (int **)malloc(new_matrix->m * sizeof(int *));
    for(int i = 0; i < new_matrix->m; i++){
        new_matrix->data[i] = (int *)malloc(new_matrix->n * sizeof(int));
        for(int j = 0; j < new_matrix->n; j++){
            new_matrix->data[i][j] = 0;
            for(int k = 0; k < matrix1->n; k++){
                new_matrix->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }
    return new_matrix;
}
Matrix* powerMatrix(Matrix *matrix, int power){
    if (matrix == NULL) return NULL;

    if ((matrix->n != matrix->m) && error_code == 0){
        error_code = 3;
        return NULL;
    }
    
    if(power == 0){
        return NULL;
    } else if(power == 1){
        return matrix;
    } else {
        Matrix *result = matrix;
        for(int i = 1; i < power; i++){
            result = multiplyMatrix(result, matrix);
        }
        return result;
    }
}
int main(){
    int n1, m1, n2 , m2, *A , *B;
    scanf("%d %d" , &m1 , &n1);
    
    A = malloc((n1*m1)*sizeof(int));
    for (int i = 0; i < m1*n1; i++)
        scanf("%d" , A + i);

    scanf("%d %d", &m2, &n2);
    B = malloc((n2*m2)*sizeof(int));
    for (int i = 0; i < m2*n2; i++)
        scanf("%d", B + i);

    Matrix *matrixA = create_matrix(A, m1, n1);
    Matrix *matrixB = create_matrix(B, m2, n2);

    Matrix *matrixC = addMatrix(multiplyMatrix(matrixA , matrixB) , powerMatrix(multiplyMatrix(matrixA, transpose(matrixA)), 2 ));
    print_matrix(matrixC);
    return 0;
}
/*
3 4
3 2 4 1 5 2 1 4 1 3 4 2
4 3
2 4 5 3 2 1 4 3 3 1 5 2
*/