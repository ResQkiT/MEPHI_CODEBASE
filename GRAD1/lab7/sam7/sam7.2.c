#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int MAX_ROW_COUNT = 300000;
const int MAX_NUMBER_COUNT = 200000;
const int MIN_NUMBER = 0;
//нельзя составит массив из более миллиона элементов
// т.е я не могу индексировать число из более чем 6ти символов

const long long MAX_NUMBER = 10000;
const int SIZE_OF_HASH_MAP = 10;

int getRandom(int a, int b) {return a + rand() % (((long long)a) - b);}
void clearbuffer(char buffer[] , int size){
    for (int i = 0; i < size; i++)
        buffer[i] = 0;
}

int zeros(int *m, int k){
    int *iter = m;
    while (iter < m + k)
    {
        *(iter++) = 0;
    }
}
void createFile(FILE *fp)
{
    int COUNT_OF_LINES = getRandom(1, MAX_ROW_COUNT);
    int NUMBERS_IN_LINE;
    int temp_number;
    for (int i = 0; i < COUNT_OF_LINES; i++)
    {
        // пройдемся по каждой строке
        NUMBERS_IN_LINE = getRandom(1, MAX_NUMBER_COUNT);

        temp_number = getRandom(MIN_NUMBER, MAX_NUMBER);
        fprintf(fp, "%d", temp_number);

        for (int j =  1; j < NUMBERS_IN_LINE ; j++)
        {
            // для каждого числа
            temp_number = getRandom(MIN_NUMBER, MAX_NUMBER);
            fprintf(fp, " %d", temp_number);
            
        }
        putc('\n', fp);
    }
}
int find_max_in_file(FILE *fp){
    int max_number = -1;
    int current_row = 1;
    int allMaxROW[MAX_ROW_COUNT + 1];
    //int allNumberCount[1000000];

    
    int allNumberCount[SIZE_OF_HASH_MAP];

    zeros(allMaxROW, MAX_ROW_COUNT + 1);
    zeros(allNumberCount , SIZE_OF_HASH_MAP);

    char ch;
    char buffer[10000];
    int number_temp = -1;
    int marker = 0;
    int count_of_max = 0 ;
    int count_of_ends = 0;

    while ((ch = getc(fp)) != EOF)
    {
        
        if (ch == '\n' && buffer[0] == 0)
        {
            //ch = getc(fp);
            break;
        }
        
        
        if (ch == '\n'|| ch == ' ')
        {
            
            count_of_ends++;
            number_temp = atoi(buffer);    
            clearbuffer(buffer, 10);
            marker = 0;
            //allNumberCount[number_temp]++;
            if(number_temp > max_number){
                zeros(allMaxROW, MAX_ROW_COUNT + 1);
                count_of_max = 1;
                max_number = number_temp;
                allMaxROW[current_row] = 1;
            }else if(number_temp == max_number){
                count_of_max++;
                allMaxROW[current_row] = 1;
            }
            
            
        }else{
            int number_temp =ch-'0';
            allNumberCount[number_temp]++;
            count_of_ends = 0;
            buffer[(marker++)] = ch;
        }
        if(ch == '\n'){
            current_row++;
        }
    }

    
    for (int i = 0, qw = 0; i < current_row + 1; i++ )
    {
        
        if (allMaxROW[i]){
            if(qw > 0){
                printf(" ");
            }
            printf("%d" , i);
            qw++;
        }
            
    }

    printf("\n\n");
    for (int i = 0; i < SIZE_OF_HASH_MAP; i++)
    {
        printf("%d " , i);
        for (int j = 0; j < (( (allNumberCount[i] / 3) + ((allNumberCount[i] % 3) == 2? 1: 0))); j++)
        {
            printf("*");
        }
        printf(" %d\n" , allNumberCount[i]);
    }
    return max_number;
}
int fileWork(){
    srand(time(NULL));
    FILE *fp;
    int max = 0;
    if ((fp = fopen("myfile.txt", "w")) == NULL)
    {
        printf("Не удается открыть файл.\n");
        exit(1);
    }else{
        createFile(fp);
        
        fclose(fp);
    }

    if ((fp = fopen("myfile.txt", "r")) == NULL)
    {
        printf("Не удается открыть файл.\n");
        exit(1);
    }else{
        max = find_max_in_file(fp);
        
        fclose(fp);
    }
}
int main()
{
    //в прошлой посылке я считал количество вхождений чисел

    //fileWork();
    int k = find_max_in_file(stdin);
    //printf("\n");
}