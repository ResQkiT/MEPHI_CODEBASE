#include <stdio.h>
#include <limits.h>
int peremen;
long int getSum(long int a, long int b, int needToPrint){
    if(a >= INT_MAX - b){
        if(needToPrint)
            peremen = 1;
        return -1;
    }
    return a + b;
}
long int multiply(long int a, long int b, int needToPrint){
    if(a >= INT_MAX / b + 1){
        if(needToPrint)
            peremen = 2;
        return -1;
    }
    return a * b;
}

int main(void) {
    int k;
    long int sum = -1 ;
    long int maxSum = -1;
    long long oldSum = -1;
    int needtoprint = 1;
    int n = 1;
    
    scanf("%i", &k);
    _start:
    for(; ; n++){
        sum = 0;
        //для фиксированного n:
        for(long int i = 1;i <= k; i++ ){
            long int temp = i * 2 -1 ;
            //возведение в степень
            long int miult = 1;
            for(int j = 1; j <= n; j++){
                if(multiply(miult, temp, needtoprint)== -1){
                    goto END;
                }else{
                    //нет переполнения при умножении
                    miult = multiply(miult, temp, needtoprint );
                }
            }
            if(getSum(sum, miult, needtoprint) == -1){
                goto END;
            }else{
                //нет переполнения при сложении
                sum = getSum(sum, miult, needtoprint);
            }

        }  

        oldSum = sum;     
    }   
    END:
    printf("%i\n", oldSum);
    n--;
    printf("%i\n", n);
    switch (peremen)
    {
    case 1:
        printf("+\n");
        break;
    case 2:
        printf("*\n");
        break;
    }
}
