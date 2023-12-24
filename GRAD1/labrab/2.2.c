#include <limits.h>
#include <stdio.h>

int main(void) {
    int k ;
    scanf("%i", &k);
    long int first = 1;
    long int second = 3;
    long int buff = 0;
    int i ;
    if(k == 1){
        printf("%3i  %i\n", 1 , 1);
    }else if(k>=2){
        printf("%3i  %i\n", 1 , 1);
        printf("%3i  %i\n", 2 , 3);
    }
    for(i = 2; i< k; i++){
        if(first >= INT_MAX - second){
            continue; // не выводит строку
        }
        buff = first + second;
        first = second;
        second = buff;
        printf("%3i  %i\n" , i + 1, buff);
    }
    printf("\n");
    first = 1;
    second = 3;
    buff = 0;
    for(i = 2; ; i++){
        if(first >= INT_MAX - second){
            printf("%3i  %i\n" , i - 1 - 1, buff - first    );
            printf("%3i  %i\n" , i   -1 , first);
            printf("%3i  %i\n" , i , buff);
            break; // не выводит строку
        }
        buff = first + second;
        first = second;
        second = buff;
    }
}