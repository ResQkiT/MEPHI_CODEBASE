
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

int main(void) {
    int mass[15];
    int *r = mass;
    int i = 0;


    for(i  = 0; i < 15 ; i++){
        *(r + i) = (rand() % 13);
    }
    
    for ( i = 0; i < 15; i++)
    {
        printf("%d\n" , *(r + i));
    }

    double sredn = 0;
    for (i = 0; i < 15; i++)
    {
        sredn += *(r + i);
    }
    sredn /= 15.0;
    printf("%f" , sredn);
    
    
}