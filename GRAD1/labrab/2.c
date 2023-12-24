#include <stdio.h>
int main(void) {
    int a , b , c;
    scanf("%i %i %i" , &a , &b, &c);
    int max, min, sred;
    if (a == b & b == c){
        max = a;
        min = c;
        sred = b;
    }
    if(a > b){
        max = a;
    }else{
        max = b;
    }
    if(c > max){
        max = c;
    }

    if(a < b){
        min = a;
    }else{
        min = b;
    }
    if(c < min){
        min = c;
    }
    sred = (a + b + c) - max -min;
    a = max;
    b = sred;
    c = min;
    if(a == b & b == c & a==c) {
        printf("%i=%i=%i\n", a, b, c);
        
    }else if(a == b & b > c){
        printf("%i=%i>%i\n", a, b, c);
    }else if(b == c & b > a){
        printf("%i=%i>%i\n", b, c, a);
    }
    else if(b == c & b < a){
        printf("%i=%i<%i\n", b, c, a);
    }else{
        printf("%i\n" , b);
    }
}