#include <stdio.h>
#include <stdlib.h>
/*
4 4
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
*/
void print_arr(int *arr, int size){
    for (int i = 1; i <= size; i++) printf("%3d", i);
    printf("\n");
    for (int i = 0; i < size; i++) printf("%3d", arr[i]);
    printf("\n");
}

void print_double_arr(int **arr, int m , int n){
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d" , arr[i][j]);
        }
        putchar('\n');
    }
}

void solve_task_2(int **mass, int m , int n){
    int *hash;
    hash = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int temp_sum = 0;
        for (int j = 0; j < m; j++)
        {
            temp_sum += *(*(mass + j) + i);
        }
        *(hash + i) = temp_sum;
    }
    //print_arr(hash, n);
    int max_sum = -1;
    for (int i = 0; i < n; i++)
    {
        if (*(hash + i) >=max_sum)
        {
            max_sum = *(hash + i);
        }
        
    }
    int count_max = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(hash + i) == max_sum)
        {
            //printf("%d" , *(hash + i));
            count_max++;
        }

    }
    int temp_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(hash + i) == max_sum)
        {
            printf("%d", i + 1);
            temp_count++;
            if (temp_count < count_max)
            {
                putchar(' ');
            }
            else
            {
                putchar('\n');
            }
        }
    }
    free(hash);
}

void solve_task_3(int **matrix, int ROWS, int COLS)
{
    int row, col, saddlePoint = 0, saddlePointValue, count = 0;

    for (row = 0; row < ROWS; row++)
    {
        int maxValue = matrix[row][0], maxCol = 0;
        for (col = 1; col < COLS; col++)
        {
            if (matrix[row][col] < maxValue)
            {
                maxValue = matrix[row][col];
                maxCol = col;
            }
        }

        int minValue = matrix[0][maxCol], minRow = 0;
        for (int i = 1; i < ROWS; i++)
        {
            if (matrix[i][maxCol] > minValue)
            {
                minValue = matrix[i][maxCol];
                minRow = i;
            }
        }

        if (minValue == maxValue)
        {
            saddlePoint = 1;
            saddlePointValue = minValue;
        }
    }
    if (saddlePoint)
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (matrix[i][j] == saddlePointValue){
                    count ++;
                }
            }
        }
        if (count == 1)
        {
            printf("%d\n", saddlePointValue);
        }else{
            printf("%d %d\n", saddlePointValue, count);
        }
    }
    else
    {
        printf("-\n");
    }
}
int main(){
    int n, m, size;
    int *A, **mass;
    scanf("%d %d" , &m , &n);
    size = n * m;
    A = malloc((size)*sizeof(int));
    
    for (int i = 0; i < size ; i++)
    {
        scanf("%d" , A + i);
    }
    mass = malloc((m)*sizeof(int));
    for (int i = 0; i < m; i++)
    {
        *(mass + i) = malloc(n * sizeof(int));
    }
    
    int way = 1 , index = 0;
    //0 - заполнение вниз
    //1 - заполнение вверх
    //итерация вправо
    for (int i = 0; i < n; i++)
    {

        if (way)
        {
            //итерацияя вниз
            for (int j = 0; j < m; j++)
            {
                *(*(mass + j) + i) = A[index];
                index++;
            }
            way = 0;
        }
        else
        {
            // итерация вверх
            for (int j = m-1; j >=0; j--)
            {
                *(*(mass + j) + i) = A[index];
                index++;
            }
            way = 1;
        }
    }
    print_double_arr(mass, m , n);
    putchar('\n');
    solve_task_2(mass, m , n);
    solve_task_3(mass, m , n);
    free(A);
    free(mass);
    return 0;
}