#include <stdio.h>
int main(void) {
    int x, y;
    scanf("%i %i", &x, &y);
    if( (x*x + y*y < 200 * 200) && !(x<=100 && x >= -100 && y <= 100 &&y>= -100) && !((y >= x && x>=0) || (y <= -x && x >= 0)) ){
        printf("inside\n");
    }else{
        printf("outside\n");
    }
}