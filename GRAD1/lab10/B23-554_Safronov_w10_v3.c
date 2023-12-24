#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int size){
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

void swap(int *x, int *y, int *A, int n)
{
    int temp; /* temp - вспомогательная переменная */
    temp = *x;
    *x = *y;
    *y = temp;

    print_arr(A , n);
    putchar('\n');
}
void QuickSort(int* A,int first, int last , int n, int *count_of_prisv, int * count_of_sravn)
{
    if(first > last) return;
    int pivot; /*опорное значение*/
    int l, r;  /*левый и правый счетчики*/
    l = first;
    r = last;
    pivot = A[(l + r) / 2]; /*определение опорного значения*/
    while (l <= r)
    {
        for()
        (*count_of_sravn)++;
        while (A[l] < pivot){
            l++;
            (*count_of_sravn)++;
        }
        (*count_of_sravn)++;
        while (A[r] > pivot){
            r--;
            (*count_of_sravn)++;
        }
        if (l <= r)
        {
            swap(&A[l], &A[r], A, n); /*перестановка двух элементов*/
            *(count_of_prisv)+=3;
            l++;
            r--;
        }
    } /*Рекурсивная сортировка:*/
    QuickSort(A , first, r , n, count_of_prisv, count_of_sravn); /*- левого участка, */
    QuickSort(A, l, last, n, count_of_prisv, count_of_sravn); /*- правого участка.*/
}
int main(){
    int n, *A;
    scanf("%d", &n);
    A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    print_arr(A , n);
    putchar('\n');
    
    int count_of_prisv = 0, count_of_sravn = 0;
    QuickSort(A,0,n-1 , n, &count_of_prisv, &count_of_sravn);
    
    printf("%d %d\n" , count_of_prisv, count_of_sravn);
  
    free(A);
}