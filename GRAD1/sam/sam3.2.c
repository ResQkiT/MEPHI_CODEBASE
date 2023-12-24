#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

double PI = 3.141592653589793238462643383279502884;
double ep = 1e-15;

double function(int n){
    if((n+1) % 2 == 1){
        return (-1) * ( 1.0 /  n / (n + 1) ); 
    }else {
        return ( 1.0 / n  / (n + 1) ); 
    }
}
int main(){

    double no_cor = 0;
    double with_cor = 0;
    double f, fcor, cor = 0.0, Scor = 0.0;
    int i = 1;
    double ideal = 2 * log(2) - 1;
    while(fabs(ideal - no_cor) > 1e-8)
    {
        f = function((double)i);
        no_cor += f;
        fcor = f - cor;
        Scor = with_cor + fcor;
        cor = (Scor - with_cor) - fcor;
        with_cor = Scor;
        i++;
        
    }
    printf("%.8lf\n", ideal);
    printf("%.8lf\n", no_cor);
    printf("%.8lf\n", fabs(ideal - no_cor));
    printf("%d\n", i - 1);
    
}