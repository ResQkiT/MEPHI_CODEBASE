#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Field{
    char name[20];
    char surname[20];
    int department;
    int salary;
    int bonus;
    int taxes;
}field;

int calcSalary(struct Field person)
{
    return person.salary + person.bonus - person.taxes; 
}

void printFormatData(struct Field data[], int size){
    for (int i = 0; i < size; i++)
    {
        printf("%-15s%-15s%5d%5d%5d%5d\n" , 
        data[i].surname, 
        data[i].name,
        data[i].department,
        data[i].salary, 
        data[i].bonus,
        data[i].taxes);
    }
}
void getWord(char word[] )
{
    char c;
    char buffer[20] = {0};
    int index = 0;
    while ((c = getchar()) != ' '){
        if (c == '\n')
        {
            continue;
        }else{
            buffer[index] = c;
            index++;
        }
    }
    strcpy(word , buffer);
}
void solve2(struct Field data[], int size , int *maxSalary){
    int needdepartment = 2;
    int count_of_deparment = 0;
    
    for (int i = 0; i < size; i++)
    {
        if (data[i].department == needdepartment)
        {
            
            count_of_deparment++;
            if (*maxSalary < calcSalary(data[i]))
            {
                *maxSalary= calcSalary(data[i]);
            }
        }
    }
    struct Field *NeedDeparmentData = malloc(count_of_deparment*sizeof(field));
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (data[i].department == needdepartment)
        {
            NeedDeparmentData[i] = data[i];
        }
        index++;
    }
    for (int i = 0; i < count_of_deparment; i++)
    {
        if (calcSalary(NeedDeparmentData[i]) == *maxSalary)
        {
            printf("%s %s\n" , NeedDeparmentData[i].surname , NeedDeparmentData[i].name);
        }
        
    }
}
void solve3(struct Field data[], int size , int *maxSalary){
    for (int i = 0; i < size; i++)
    {
        if (calcSalary(data[i]) > *maxSalary)
        {
            printf("%s %s\n" , data[i].surname , data[i].name);
        }
    }
    
}
int main(){
    int n;
    int maxSalary = -1;

    scanf("%d" , &n);
    struct Field *data = malloc(n*sizeof(field));
    for(int i = 0; i < n; i++){
        getWord(data[i].surname);
        getWord(data[i].name);
        scanf("%d %d %d %d", &(data[i].department), &(data[i].salary),&(data[i].bonus),&(data[i].taxes));
    }
    printFormatData(data , n);
    printf("\n");
    solve2(data, n, &maxSalary);
    printf("\n");
    solve3(data , n, &maxSalary);
}