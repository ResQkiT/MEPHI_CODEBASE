#include <stdio.h>
void massiveinit(int *m ,int size,int a, int b){
    for (int i = 0; i < size; i++)
    {
        *(m + i) = a * ( i -b) ;
    }
}
void printpart(int *m, int *begin , int *end){
    int *iter;
    iter = begin;
    for (int i = begin - m + 1; i <= end - m + 1; i++)
    {
        printf("%5d", i);
    }
    printf("\n");
    for (;iter <= end; iter++)
    {
        //убрать последний пробелл
        printf("%5d" , *iter);
    }
    printf("\n");
}
void swap(int* a, int* b) { // Функция для обмена значениями
    int temp = *a;
    *a = *b;
    *b = temp;
}
void swapPerts(int *m1, int size_1, int *m2, int size_2, int k){
    
    //Функция меняет местами последние k элементов первого массива
    // и первые k элементов второго массива
    int *iter1 = m1 + size_1 - k , *iter2 = m2;
    for (int i = 0; i < k; i++)
    {
        //printf("mas1 -> %d, mas2 -> %d\n", *iter1, *iter2);
        swap(iter1, iter2);
        //printf("mas1 -> %d, mas2 -> %d\n", *iter1, *iter2);
        iter1 ++;
        iter2 ++;
    }
    
}


int main(){
    int a[] = {1 , 2 , 3 ,4, 5, 6,7,8,9, 10};
    //printpart(a ,  a + 1 , a + 8);
    int a1, b1, a2 , b2 ,k;
    scanf("%d %d", &a1, &b1);
    scanf("%d %d", &a2, &b2);
    scanf("%d", &k);
    int m1[14] , m2[10];
    massiveinit(m1, 14,a1, b1 );
    massiveinit(m2, 10,a2, b2 );


    printpart(m1, m1 + 0 , m1 + 13 );
    printf("\n");
    printpart(m2, m2 + 0 , m2 + 9 );
    printf("\n");

    //printf("\n");

    swapPerts(m1, 14, m2, 10, k);
    //swapPerts(m2, 10, m1, 14, k);
    //swapPerts(m1, 14, m1, 14, k);

    printpart(m1, m1 + 0 , m1 + 13 );
    printf("\n");
    printpart(m2, m2 + 0 , m2 + 9 );
    //printf("\n");

    
}