#include <stdio.h>
int main(void) {
    int a;
    int b = 0;
    scanf("%i", &a);
    for(int i = 2; i*i <= a; i++){
        if(a % i == 0)
            b = 1;
    }
    if(!b) printf("PROSTOE");
    else printf("HE PROSTOE");
}