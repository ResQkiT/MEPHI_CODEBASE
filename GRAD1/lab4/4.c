#include <stdio.h>
void main(){
    int a, b;
    scanf("%i %i", &a, &b);
    if(a > b){
        printf("%i", a);
    }
    else if(b > a){
        printf("%i", b);
    }
    return 0;
}