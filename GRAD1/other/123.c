#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

void func(int *p, int *q)
{
    while (p < q)
        printf("%d ", *(q--) + *(p++));
}

int main(void)
{
    int m[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    func(&m[9], m);

    
}
