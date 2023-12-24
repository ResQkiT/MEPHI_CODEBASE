#include <stdio.h>
#include <stdlib.h>
void print_arr(int *arr, int size){
    printf("%3d", 1); 
    for (int i = 2; i < size + 1; i++)
    {
        printf("%3d", i); 
    }
    printf("\n");
    printf("%3d", *(arr)); 
    for (int i = 1; i < size; i++)
    {
        printf("%3d", *(arr + i)); 
    }
    printf("\n");
}

int main()
{
    int N;
    int prisv = 0 , sravn = 0 ;
    scanf("%d", &N);
    int* mass;
    mass = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &mass[i]);

    print_arr(mass, N);
    printf("\n");
    int tmp;
    for (int i = N - 1; i > 0; --i)
    {

        for (int j = 0; j < i; j++)
        {
            sravn++;
            if (mass[j] > mass[j + 1])
            {
                tmp = mass[j];
                mass[j] = mass[j + 1];
                mass[j + 1] = tmp;
                prisv+= 3;
            }
        }
        
        if(i >= 2){
             print_arr(mass, N);
            printf("\n");
        }
           
    }

    print_arr(mass, N);
    printf("%d %d\n" , prisv, sravn);
    free(mass);
    return 0;
}