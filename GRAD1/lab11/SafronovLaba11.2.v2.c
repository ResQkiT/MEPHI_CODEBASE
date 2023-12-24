
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int m, n;
/*
4 4
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
*/
void zap(int arr[][n], int arm[][n])
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (((n - 1) % 2) == ((n - 1 - i) % 2))
            {
                scanf("%d", &arr[m - 1 - j][n - 1 - i]);
            }
            else
            {
                scanf("%d", &arr[j][n - 1 - i]);
            }
            arm[j][i] = 0;
        }
    }
}

void zap_sluch(int arr[][n], int arm[][n])
{
    int a = 10, b = 13;
    int stime;
    long int ltime;
    ltime = time(NULL);
    stime = (unsigned)ltime / 2;
    srand(stime);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)

        {

            if (((n - 1) % 2) == ((n - 1 - i) % 2))
            {
                arr[m - 1 - j][n - 1 - i] = (a + rand() % (b - a + 1));
            }
            else
            {
                arr[j][n - 1 - i] = (a + rand() % (b - a + 1));
            }
            arm[j][i] = 0;
        }
    }
}
void pokaz(int arr[][n])
{
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            printf("%3d", arr[j][i]);
        }
        printf("%3d\n", arr[j][n - 1]);
    }
}

int main()
{

    int count = 0;
    int miini = 10000;
    scanf("%d %d", &m, &n);
    int arr[m][n];
    int arr_m[m][n];
    zap(arr, arr_m);
    pokaz(arr);
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        int mini = 10000000;
        for (int j = 0; j < n; j++)
        {

            if (mini > arr[i][j])
            {
                mini = arr[i][j];
                if (arr[i][j] < miini)
                {
                    miini = mini;
                }
            }
        }

        for (int k = 0; k < n; k++)
        {
            if (mini == arr[i][k])
                arr_m[i][k] += 1;
        }
    }
    for (int j = 0; j < n; j++)
    {
        int maxi = 0;
        for (int i = 0; i < m; i++)
        {
            if (maxi < arr[i][j])
            {
                maxi = arr[i][j];
            }
        }
        for (int k = 0; k < m; k++)
        {
            if (maxi == arr[k][j])
                arr_m[k][j] += 2;
        }
    }

    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (miini == arr[i][j])
            {
                if (count == 0)
                {
                    printf("%d", i + 1);
                    count += 1;
                    break;
                }
                else
                    printf(" %d", i + 1);
                break;
            }
        }
    }
    printf("\n");
    int znach = 0;
    count = 0;
    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            if (arr_m[i][j] == 3)
            {
                znach = arr[i][j];
                count++;
            }
        }
    }
    
    if (count == 0)
    {
        printf("-\n");
    }
    if (count == 1)
    {
        printf("%d\n", znach);
    }
    if (count > 1)
    {
        printf("%d %d\n", znach, count);
    }
}