#include <stdio.h>
int main(void) {
    int n , k, l = 1;
    scanf("%i %i", &n, &k);
    while(k!=1){
        if(k%2 != 0){
            l *=n;
            k--;
        }
        else{
            l*= n*n;
            k/=2;
        }
    }
    printf("%i", l);
}