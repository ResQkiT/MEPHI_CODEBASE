#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getRandom(int a, int b) {return a + rand() % (a - b + 1);}
void clearbuffer(char buffer[] , int size){
    for (int i = 0; i < size; i++)
        buffer[i] = 0;
}

void createFile(FILE *fp)
{
    int COUNT_OF_LINES = getRandom(1, 30);
    int NUMBERS_IN_LINE;
    int temp_number;
    for (int i = 0; i < COUNT_OF_LINES; i++)
    {
        // пройдемся по каждой строке
        NUMBERS_IN_LINE = getRandom(1, 20);
        for (int j = 0; j < NUMBERS_IN_LINE; j++)
        {
            // для каждого числа
            temp_number = getRandom(1, 100);
            fprintf(fp, "%d ", temp_number);
            
        }
        putc('\n', fp);
    }
}
int find_max_in_file(FILE *fp){
    int max_number = -1;
    int current_row = 1;
    int allMaxROW[31];
    
    
    char ch;
    char buffer[10];
    int number_temp = 0;
    int marker = 0;
    //найдем максимальное число
    while ((ch = getc(fp)) != EOF)
    {
        //считываем посимвольно
        if (ch == '\n'|| ch == ' ')
        {
            number_temp = atoi(buffer);
            clearbuffer(buffer, 10);
            marker = 0;
            if(number_temp > max_number){
                max_number = number_temp;
                //allMaxROW[current_row] = 1;
            }
        }
        else{
            buffer[(marker++)] = ch;
        }
        if(ch == '\n'){
            current_row++;
        }
    }
    printf("MAX INT is %d\n" , max_number);
    return max_number;
}
int find_in_rows(FILE *fp ,int target){
    int current_row = 1;
    int allMaxROW[31];
    char ch;
    char buffer[10];
    int number_temp = 0;
    int marker = 0;
    
    for (int p = 0; p < 31; p++)
    {
        allMaxROW[p] = 0;
    }

    while ((ch = getc(fp)) != EOF)
    {
        //считываем посимвольно
        if (ch == '\n'|| ch == ' ')
        {
            number_temp = atoi(buffer);
            clearbuffer(buffer, 10);
            marker = 0;
            if(target == number_temp){
                allMaxROW[current_row] = 1;
            }
        }
        else{
            buffer[(marker++)] = ch;
        }
        if(ch == '\n'){
            current_row++;
        }
    }
    printf("MAX NUMBER IN ROWS: ");
    for (int i = 0; i < 31; i++)
    {
        if (allMaxROW[i])
            printf("%d " , i);
    }
    printf("\n");
}
int main()
{
    srand(time(NULL));
    FILE *fp;
    int max = 0;
    if ((fp = fopen("myfile.txt", "w")) == NULL)
    {
        printf("Не удается открыть файл.\n");
        exit(1);
        /* завершение программы с возвратом кода ошибки 1 */
    }else{
        createFile(fp);
        
        fclose(fp);
    }

    if ((fp = fopen("myfile.txt", "r")) == NULL)
    {
        printf("Не удается открыть файл.\n");
        exit(1);
        /* завершение программы с возвратом кода ошибки 1 */
    }else{
        max = find_max_in_file(fp);
        
        fclose(fp);
    }
    if ((fp = fopen("myfile.txt", "r")) == NULL)
    {
        printf("Не удается открыть файл.\n");
        exit(1);
        /* завершение программы с возвратом кода ошибки 1 */
    }else{
        find_in_rows(fp, max);
        
        fclose(fp);
    }
    


}