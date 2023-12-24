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

void print_point_arr(int **arr, int size){
    for (int i = 1; i <= size; i++) printf("%3d", i);
    printf("\n");
    for (int i = 0; i < size; i++) printf("%3d", *(arr[i]));
    printf("\n");
}

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
 }
int main(){
    int n1, n2;
    int *A, *B;
    scanf("%d" , &n1);
    A = malloc(n1*sizeof(int));
    for (int i = 0; i < n1 ; i++)
    {
        scanf("%d" , A + i);
    }
    
    scanf("%d" , &n2);
    B = malloc(n2*sizeof(int));
    for (int i = 0; i < n2 ; i++)
    {
        scanf("%d" , B + i);
    }
    
    print_arr(A, n1);
    printf("\n");
    print_arr(B, n2);

    

    qsort(A, n1, sizeof(int), cmp);
    qsort(B, n2, sizeof(int), cmp);

    int **mass;
    mass = malloc((n1 + n2)*sizeof(int));

    int a = 0, b = 0;
    for (int i = 0; i < n1+n2; i++)
    {
        if(A[a] <= B[b]){
            mass[i] = &(A[a]);
            a++;
        }else{
            mass[i] = &(B[b]);
            b++;
        }
    }
    putchar('\n');
    print_point_arr(mass, n1+n2);
    putchar('\n');
}