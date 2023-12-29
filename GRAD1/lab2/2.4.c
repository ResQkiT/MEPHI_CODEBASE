#include <stdio.h>
int main(void) {
    int a, s;
    scanf("%i", &a);
    while(a){
        s+=a;
        scanf("%i", &a);
    }
        
    printf("%i", s);
}