#include <stdio.h>
#include <stdlib.h>
int *A;
int n;
int sravn = 0, prisv = 0;

void print_arr(int *arr, int size)
{
    printf("%3d", 1);
    for (int i = 2; i < size + 1; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    printf("%3d", *(arr));
    for (int i = 1; i < size; i++)
    {
        printf("%3d", *(arr + i));
    }
    printf("\n");
}

void swap(int *x, int *y)
{
    int temp; /* temp - вспомогательная переменная */
    temp = *x;
    *x = *y;
    *y = temp;
    prisv += 3;

    print_arr(A, n);
    putchar('\n');
}
void TreeRebuild(int r, int q)
{
    int v;
    int i, j;
    int pp;

    i = r;    /*индекс рассматриваемого элемента*/
    v = A[i]; /*рассматриваемый элемент*/
    prisv++;
    j = 2 * i + 1; /*индекс элемента, с которым проводится сравнение*/
    pp = 0;        /*предположение, что не найдено место в пирамиде*/
    while (j < q && !pp)
    {
        if (j < q)
            sravn++;
        if (A[j] < A[j + 1])
        { /*сравнение с меньшим элементом*/
            j++;
        }
        sravn++;
        if (v >= A[j])
        {
            pp = 1; /*элемент стоит на своем месте*/
        }
        else
        {
            A[i] = A[j]; /*перестановка элемента*/
            prisv++;
            i = j;
            j = 2 * i + 1; /*прохождение дальше по пирамиде*/
        }
    }
    A[i] = v;
    prisv++;
    print_arr(A, n);
    putchar('\n');
}

void TreeSort()
{
    int k, i;
    k = n / 2; /*эта часть массива является пирамидой*/
    for (i = k - 1; i >= 0; i--)
        TreeRebuild(i, n - 1); /*построение пирамиды (только один раз)*/

    for (i = n - 1; i >= 1; i--)
    {
        swap(&A[0], &A[i]);    /*перестановка 0-го и i-го элементов*/
        TreeRebuild(0, i - 1); /* «проталкивание» i-го элемента*/
    }
}
int main()
{
    int l;
    scanf("%d", &l);
    n = l;
    A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", A + i);
    }
    print_arr(A, n);
    putchar('\n');

    TreeSort();
    printf("%d %d\n", prisv, sravn);
    free(A);
}