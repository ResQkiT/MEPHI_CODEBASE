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
void insert_element(int a, int k, int **arr, int *size){
    int *ap = realloc(*(arr), ((*size) + 1) * sizeof(int));
    if(*ap == NULL){
        printf("Memory error\n");
        return;
    }else{
        *arr = ap;
        *((*arr) + (*size)) = 0;
    }
    (*size)++;
    int temp = (*arr)[k - 1];
    for (int j = (*size) - 1 ; j >= k; j--)
    {
        (*arr)[j] = (*arr)[j - 1];

    }
    (*arr)[k - 1 ] = a;
}
void swap_elements(int i, int j , int **arp){
    i--;
    j--;

    int temp = (*arp)[i];
    (*arp)[i] =(*arp)[j];
    (*arp)[j] = temp;
}
int main(void) {
    int n;
    int a, k , i ,j, *arr;
    scanf("%d" , &n);


    arr = malloc(n * (sizeof(int)));
    for (int i = 0; i < n; i++)
    {
        scanf("%d",(arr + i)); 
    }
    scanf("%d%d%d%d" , &a, &k, &i, &j);
    print_arr(arr, n);
    printf("\n");
    insert_element(a, k , &arr, &n);
    swap_elements(i , j, &arr);
    print_arr(arr, n);

}