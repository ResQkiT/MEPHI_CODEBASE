#include <limits.h>
#include <stdio.h>
int main(void) {
    int a, b;
    scanf("%i %i", &a, &b);
    if((a <= INT_MAX - b) || (a >= INT_MIN -b)){
        printf("%i", a + b);
    }
    else{
        printf("PEREPOLNENIE\n");
        printf("%i", a + b);
    }
}