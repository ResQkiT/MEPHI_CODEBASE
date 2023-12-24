#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
const int BUFFER_SIZE = 10001;
void clearbuffer(char buffer[] , int size){
    for (int i = 0; i < size; i++)
        buffer[i] = 0;
}
void printbuffer(char buffer[] , int size){
    for (int i = 0; i < size; i++){
        putchar(buffer[i]);
    }
    putchar('\n');
}
int main(){
    
    char string[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int dictionary = 0, marker = 0, count = 0;
    
    for (char c = getchar() ; c != '\n' ; c = getchar(), count++)
    {
        string[count] = c;
    }
    count++;
    for (int i = 0; i < count; i++)
    {
        char k = string[i];
        if(isalpha(k)){
            //k - часть слова
            buffer[(marker++ )] = k;
            continue;
        }
        else if(marker != 0 && ! isalpha(k)){
            //слово закончилось выведес слово из буфера и очистим его
            printbuffer(buffer , marker);
            dictionary++;
            clearbuffer(buffer, marker);
            marker = 0;
        }
    }
    
    printf("\n%d\n", dictionary);
}