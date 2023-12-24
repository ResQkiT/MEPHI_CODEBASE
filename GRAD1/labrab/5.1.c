#include <stdio.h>
#include <math.h>
void myswap(double *a, double *b){
    double t = *b;
    *b = *a;
    *a = t;
}
int d(int a , int b , int c){
    return (c * b + 1) * (c * b + 1) - 4 * c * a;
}
void solution(int a, int b, int c, int *code, double *x1 , double *x2){
    if(c ==0 && (-(c*b+1)) !=0){
        *x1  = (a) / (double)((c*b+1));
        *code = 1;
        return;
    }
    if((-(c*b+1)) == 0 && c != 0){
        if( - (double)a / ((double )c) > 0){
            *x1 = sqrtf(- (double)a / ((double )c));
            *x2 = -sqrtf(- (double)a / ((double )c));
            *code = 0;
            return;
        }else{
            *code = 2;
            return;
        }
    }
    if(c == 0 && (-c)*b+1 ==0){
        *code = 3;
        return; 
    }
    int des = d(a, b, c);
    if (des > 0)
    {
        //два корня
        *code = 0;
        *x1 = (double)(c * b + 1 + sqrtf(des)) / (double)(2 * c);
        *x2 = (double)(c * b + 1 - sqrtf(des)) / (double)(2 * c);
        if(*x1 > *x2) myswap(x1, x2);
    }else if(des == 0){
        *code = 1;
        *x1 = (double) (c* b + 1)/(double)( 2 * c);
    }else{
        //нет действительных корней
        code = 2;
    }
    
    

    
}
int main(void)
{
    int a, b , c , code;
    double x1, x2;
    scanf("%i %i %i" , &a, &b, &c);
    solution(a, b, c, &code, &x1, &x2);
    printf("%d\n", code);
    if (code == 0)
    {
        printf("%.6f\n%.6f\n", x1 , x2);
    }else if(code == 1)
    {
        printf("%.6f\n" , x1);
    }else if(code == 2)
    {
        //
    }else if(code == 3){
        //
    }
    return 0;
}
