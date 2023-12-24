#include <stdio.h>
#include <limits.h>
#define ull long long
ull mm(ull x, ull y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}
ull pfo(ull *x, ull *y, int *vf){
    if( *x  > INT_MAX - *y){
        //произошло переполнение
        *vf = 1;
    }
    return *x + *y;
}
ull rec = 0;
ull f(ull x, ull y , int *endl, int *owfl){
    if(LONG_MAX - rec < 0){
        //в бесконечность
        *endl = 1;
        return 0;
    }
    if(*endl == 1){
        return 0;
    }else if(*owfl == 1){
        return 0;
    }
   
    printf("recurcion: %i\n" ,rec );

    (rec) ++;

    ull res1, res2;
    int ovf1 = 0, ovf2 = 0;
    int ed = 1;
    if((x + y) % 2 == 0){
        return mm(x, y);
    }else{
        res1 = f(pfo(pfo( &x, &y , &ovf2) , &ed  ,&ovf2) / 2, y, endl, owfl);
        if(ovf1 == 1){
            *owfl = 1;
        }
        printf("result 1: %i\n", res1);
        
        res2 = f(x, pfo(pfo( &x, &y , &ovf2) , &ed  ,&ovf2) / 2, endl, owfl);
        if(ovf2 == 1){
            *owfl = 1;
        }
        printf("result 1: %i\n", res1);
        return res1 + res2;
    }
}

int main(){

    ull a, b;
    int owfl = 0;
    int endl = 0;
    scanf("%i %i", &a, &b);
    ull answer = f(a, b , &endl, &owfl);
    if(endl == 1){
        printf("overflow\n");
    }else if(owfl == 1){
        printf("endless\n");
    }else{
        printf("%d\n", answer);
    }
}