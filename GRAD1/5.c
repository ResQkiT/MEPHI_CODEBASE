#include <stdio.h>
int main(void){
    int a;
    scanf("%i", &a);
    if((a > 0)  && ((a % 2) == 0)){
        printf("even and positive");
    }
}