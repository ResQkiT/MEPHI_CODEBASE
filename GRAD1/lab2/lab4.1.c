#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(){
    int i, m[40], *p, a, sum = 0, count = 0, s2 = 0 , min3 = INT_MAX, count3 = 1;
    p = &(m[0]);
    for (i = 0; i < 40; i++) scanf("%d" , p+i);
    scanf("%d" , &a);
    for (i = 0; i < 40; i++)
    {
        if(*(p + i) > a){
            sum += *(p + i);
            count++;   
        }
    }
    double sredn = (sum * 1.0) / (count * 1.0);
    printf("%.4f\n" , sredn);
    for (i = 0; i < 40; i++)
    {
        if( *(p + i) > sredn){
            s2 += *(p + i);
            if(*(p + i) < min3) min3 = *(p + i);
            else if(*(p + i) == min3) count3++;
        }
    }
    printf("%d\n" , s2);
    printf("%d %d\n" , min3 , count3);    
}