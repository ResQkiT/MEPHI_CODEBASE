#include <stdio.h>
#include <math.h>
#include <limits.h>

int main(){

    int a[] = {1,2, 3, 4};
    int *ua = a;


    printf("%d\n" , *(a + 3));
    printf("%d" , a[3]);
}
