#include <limits.h>
#include <stdio.h>
int main(void) {
    int m;
    long s = 1;
    int i, j;
    scanf("%i", &m);
    for( i = 1; s <= m; i++){
        s = 1;
        for(j = 0; j < i; j++){
            s *= 5;
        }
    }
    printf("%i\n" , i -1);
}