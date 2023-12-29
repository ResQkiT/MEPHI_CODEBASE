#include <stdio.h>
#include <stdlib.h>
int map[21];

int zeros(int *m, int k){
    int *iter = m;
    while (iter < m + k)
    {
        *(iter++) = 0;
    }
}
int init(int m[] , int k){
    int *iter = m;
    while (iter < m + k)
    {
        scanf("%d" , iter++);
    }
    
}
int initrangom(int *m , int k, int a, int b){
    int *iter = m;
    while (iter < m + k)
    {
        *(iter++) = a + rand()%(a - b + 1);
    }
}
int print(int *m, int k){
    int *iter = m;
    while (iter < m + k)
    {
        printf("%d " ,*(iter++)) ;
    }
    printf("\n");
}
double takemedian(int *m, int k){
    int *iter = m;
    double midle = 0.0;

    while (iter < m + k)
    {
        midle += (double)(*(iter++));

    }
    return midle / k;

}
int take_part_sum(int *begin , int *end){
    int *iter = begin;
    int sum = 0;

    while (iter <= end)
    {
        sum +=(*(iter++));
    }
    return sum;
}
int find(int *m , int k,int to_find){
    int *iter = m;
    int count = 0;
    while (iter < m + k)
    {
        if(to_find == *(iter++)) count ++;
    }
    return count;
}

int main(){
    int first[7], second[8], third[10] ,begin , end;
    init(first , 7);
    //print(first, 7);

    init(second , 8);
    //print(second, 8);

    init(third, 10);
    //print(third, 10);
    

    scanf("%d %d" , &begin, & end);
    printf("%.1f %.1f %.1f\n", takemedian(first, 7), takemedian(second, 8), takemedian(third, 10));
    printf("%d\n", take_part_sum(third + begin - 1, third + end - 1));
    int isFirst = 1;
    for (int i = 0; i < 21; i++)
    {

        int real = i + 10;
        map[i] += find(first, 7 , real) +
                    find(second, 8, real)+
                    find(third, 10 , real);
        if (map[i] == 0)
        {
            if (isFirst == 1)
            {
                printf("%d", real);
                isFirst ++;
            }else{
                printf(" %d", real);
            }
        }
    }
    printf("\n");
    
}