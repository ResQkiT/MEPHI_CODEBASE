#include <stdio.h>
#include <limits.h>
#define uli unsigned long int

uli m(uli a, uli b){
    return a>b ? a: b;
}
int o(uli a, uli b, uli c){
    if(a > UINT_MAX - b){
        //переполнение 
        return 1;
    }else{
        uli r = a + b;
        if( r > UINT_MAX - 1){
            //переполнение
            return 1;
        }
    }
    return 0;
}
uli f(uli a, uli b,int *endlessflag, int *overflowflag,uli recursivecount){
    //printf("rec: %d\n", recursivecount );

    
    if (*endlessflag == 1 || recursivecount > 10000) //про тип данных счетчика ничего не сказано
    {
        *endlessflag = 1;
        return 1;
    }
    if(*overflowflag == 1 ){
        *overflowflag = 1;
        return 1;
    }
    
    uli answer = 0;
    uli f1, f2;
    if((a + b) % 2 == 0 ){
        answer = m(a, b);
    }else{
        //эти строчки стоит провеерить на переполнение
        if(o(a, b , 1)){
            //переполнение при сложении
            *overflowflag = 1;
            return 1;
        }
        uli r =( a+ b + 1)/2;
        f1 =  f(r, b, endlessflag, overflowflag , recursivecount + 1);
        f2 = f(a, r, endlessflag, overflowflag, recursivecount + 1);
        answer =f1 + f2;
    }
    return answer;
}

int main(){
    uli a, b;
    int endlessflag = 0, overflowflag = 0;
    scanf("%i %i", &a, &b );
    

    uli answer = f(a, b ,&endlessflag , &overflowflag, 0);
    if(endlessflag == 1){
        printf("endless\n");
    }else if(overflowflag == 1){
        printf("overflow\n");
    }else{
        printf("%d\n" ,answer );
    }
    
}