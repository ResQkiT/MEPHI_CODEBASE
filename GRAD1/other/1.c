#include <stdio.h>

void deleteNumber(int);
int getMax(int, int);
int element, maxSum = 0;

int main(void)
{
    for (int i = 480; i <= 510; ++i)
    {
        deleteNumber(i);
    }
    printf("\n%d\n", element);
    return 0;
}

void deleteNumber(int x)
{
    printf("%3d  ", x);
    int count = -1, flag = 0, sum = 0, point;
    for (int i = 2; i != x; ++i)
    {
        if (x % i == 0) {
            if (flag) {printf(",");}
            flag = 1;
            count += 1;
            if (count == 4) {printf("\n"); printf("     ");}
            count %= 4;
            printf("%3d", i);
            sum += i;
        }
    }
    if (flag == 0)
        point = 18;
    else if(count == 3)
        point = 3;
    else
        point = 3 + (4 - (count + 1)) * 4;
    while (point != 0)
    {
        printf(" ");
        --point;
    }
    if(maxSum != getMax(sum, maxSum)) {maxSum = sum; element = x;}
    printf("%3d\n", sum);
}

int getMax(int first, int second)
{
    if (first < second) return second; else return first;
}