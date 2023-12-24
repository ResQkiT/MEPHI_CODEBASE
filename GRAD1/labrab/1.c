#include <stdio.h>
int main(void) {
    int a;
    scanf("%i", &a);
    int s = a%10 + (a/10) % 10 + (a/100)%10 + (a/1000);
    int r = a % s;
    printf("%i\n" , r);
}