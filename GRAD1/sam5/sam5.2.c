#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <limits.h>
#define li long int
//optimization
#define MEMORY_SIZE 500
#define CALL_SIZE 10000
int isForTEST = 1;


int memory[MEMORY_SIZE] ;

int marker = 0;
int A[CALL_SIZE];
int B[CALL_SIZE];
int C[CALL_SIZE];
int isOKCode = 1;
int *code = &isOKCode;
int f(int k, int level){   
    if(isForTEST) {
        A[marker] = level;
        B[marker] = k;
        marker ++;
    }
    if(memory[k] != -1){
        return memory[k];
    }
    if(k == 1){
        return 1;
    }else if(k == 2){
        return 3;
    }else if(k <= 0){
        //нереалистичный случай
        return 0;
    }
    int s1 = f(k - 1, level + 1);
    if ( *code == -1)
    {
        //произошло переполнение
        *code = -1; 
        return 0;
    }
    
    int s2 = f(k - 2, level + 1);
    
    if (s1 > INT_MAX - s2 || *code == -1)
    {
        //произошло переполнение
        *code = -1; 
        return 0;
    }
    memory[k] = s1 + s2;
    
    
    if(isForTEST) C[marker] = s1 + s2;
    return s1 + s2;

}

int main(void)
{
    for (int i = 0; i < MEMORY_SIZE ; i++)
    {
        memory[i] = -1;
    }
    for(int i = 0; i < CALL_SIZE;  i ++){
        A[i] = -1;
        B[i] = -1;
    }

    int k;
    scanf("%d" , &k);
    
    int answer = f(k, 1);

    if(isForTEST){
        for(int level = 1; level < CALL_SIZE; level ++){
        for (int i = 0; i < CALL_SIZE; i++)
        {
            if(A[i] == level){
                printf("level: %d, down value: %d up value %d\n" , A[i] , B[i], C[i]);
            }
        }
                
    }
    }
    
   if(*code == -1){
        printf("!\n");
   }else{
        printf("%d\n", answer);
   }
}