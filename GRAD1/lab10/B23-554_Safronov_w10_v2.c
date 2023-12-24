#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void vivod_mas(int a[]);
void swap(int *, int *, int a[]);
void QuickSort(int, int);


int n, *cmas;
int srav = 0, prisv = 0;
int main(void)
{
    scanf("%d", &n);
    cmas = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d" , &cmas[i]);
    }
    
    vivod_mas(cmas);
    printf("\n");
    QuickSort(0, n - 1);
    printf("%d %d\n", prisv, srav);
    free(cmas);
    return 0;
}

void vivod_mas(int a[])
{
    for (int i = 1; i <= n; i++)
        printf("%3d", i);
    printf("\n");

    for (int i = 0; i < n; i++)
        printf("%3d", a[i]);
    printf("\n");
}
void swap(int *x, int *y, int a[])
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

    vivod_mas(a);
    printf("\n");
}

void QuickSort(int first, int last)
{
    int sr;
    int l, r;
    l = first;
    r = last;
    sr = cmas[(l + r) / 2];
    while (l < r)
    {
        srav++;
        while (cmas[l] < sr)
        {
            l++;
            srav++;
        }

        srav++;
        while (cmas[r] > sr)
        {
            r--;
            srav++;
        }
        
        if (l < r)
        {
            swap(&cmas[l], &cmas[r], cmas);
            prisv += 3;
            l++;
            r--;
        }
        else
        {
            l++;
            r--;
        }
    }
    if (first < r)
        QuickSort(first, r);
    if (l < last)
        QuickSort(l, last);
}
