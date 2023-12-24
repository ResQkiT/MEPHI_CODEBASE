#include <stdio.h>
int main(void){
    int a, b;
    scanf("%i %i", &a, &b);
    int max = a > b ? a : b;
    int min = a > b ? b : a;
    if(max % min == 0){
        printf("%i", max / min);
    }else{
        printf("%i", max + min);
    }

}
