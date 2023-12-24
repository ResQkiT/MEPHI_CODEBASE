#include <stdio.h>
#include <math.h>
#include <limits.h>
double function(int n){
    if((n+1) % 2 == 1){
        return (-1) * ( 1.0 /  n / (n + 1) ); 
    }else {
        return ( 1.0 / n  / (n + 1) ); 
    }
}
double getABS(double r){
    if (r > 0) return r;
    else if(r < 0)return ((-1) * r);
    else return 0.0;
}
int main(){
    double ideal = 2 * log(2) - 1;
    printf("%.8f\n",  ideal);
    //0.38629436
    double epsilon = 1e-8;
    double S = 0.0;
    double temp ;
    int n  = 1;
    //printf("delta ->%f\n" , ideal - S);
    while(getABS(ideal - S) > epsilon){
        temp = function(n);
        //printf("temp ->%.8f\n" ,  temp);
        S += temp;
        n++;
    }
    printf("%.8f\n",  S );
    printf("%.8f\n",epsilon);
    printf("%d\n" , ++n );
}

