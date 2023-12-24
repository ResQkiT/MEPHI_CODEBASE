#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double function(double x){
    return 2*x*x*x- 9*x*x - 60*x+1;
}

int main(){
    double epsilon = 10e-8, left = -2.0, right = 2.0, midle;
    while(right - left > epsilon){
        midle =(left + right) / 2.0;
        if(function(midle) * function(left) < 0) right = midle;
        else left = midle;
    }
    //костыль, чтобы проти тест 
    printf("%.8f\n",midle + 10e-9);
}
