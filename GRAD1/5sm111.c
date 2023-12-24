#include <stdio.h>
#include <math.h>
#include <limits.h>
long int sum, raz, um, st, div, mod;

long int error_mod = 666, error_div = 555, error_st = 444, error_um = 333, error_raz = 222, error_sum = 111;

int F1(long int a, int s) // из 5-ой в 10-ю сс
{
    int i = 0, k;
    if (a > 0)
    {
        while (a > 0 && i <= 10)
        {
            k = a % 10;
            s += k * pow(5, i);
            i++;
            a = a / 10;
        }
    }
    else if (a == 0)
        s = 0;
    else if (a < 0)
    {
        while (a < 0 && i <= 10)
        {
            k = a % 10;
            s += k * pow(5, i);
            i++;
            a = a / 10;
        }
    }
    return s;
}
int F2(long int a, int s) // из 10-ой в 5-ю
{
    int i, k, ost, a1;
    a1 = a;
    while (a1 > 0)
    {
        k++;
        a1 = a1 / 10;
    }
    if (a > 0)
    {
        for (i = 0; i <= k; i++)
        {
            ost = a % 5;
            s += ost * pow(10, i);
            a = a / 5;
        }
    }
    else if (a == 0)
        s = 0;
    else
    {
        for (i = 0; i <= k; i++)
        {
            ost = a % 5;
            s += ost * pow(10, i);
            a = a / 5;
        }
    }
    return s;
}
int F3(long int x, long int y) // сложение в 5-ой
{
    int s;
    x = F1(x, s);
    y = F1(y, s);
    if (x > LONG_MAX - y)
        return error_sum;
    else
    {
        sum = F2(x + y, s);
        return sum;
    }
}
int F4(long int x, long int y) // вычитание в 5-ой
{
    int s;
    x = F1(x, s);
    y = F1(y, s);
    if (x - y > LONG_MAX)
        return error_raz;
    else
    {
        if (x < y)
        {
            raz = F2(y - x, s);
            return raz * (-1);
        }
        else
            raz = F2(x - y, s);
        return raz;
    }
}
int F5(long int x, long int y) // умножение в 5-ой
{
    int s;
    x = F1(x, s);
    y = F1(y, s);
    if (x > LONG_MAX / y)
        return error_um;
    else
    {
        um = F2(x * y, s);
        return um;
    }
}
int F6(long int x, int n) // возведение в целую неотриц степень n
{
    int s;
    x = F1(x, s);
    n = F1(n, s);
    if (pow(x, n) > LONG_MAX)
        return error_st;
    else
    {
        st = F2(pow(x, n), s);
        return st;
    }
}
int F7(long int x, long int y) // div
{
    int s;
    x = F1(x, s);
    y = F1(y, s);
    if (y != 0)
    {
        div = F2(x / y, s);
        return div;
    }
    else
        return error_div;
}
int F8(long int x, long int y) // mod
{
    int s;
    x = F1(x, s);
    y = F1(y, s);
    if (y != 0)
    {
        mod = F2(x % y, s);
        return mod;
    }
    else
        return error_mod;
}

int main()
{
    long int a, b;
    int x1, x2, x3;
    scanf("%ld %ld", &a, &b);

    // 1-е выражение
    if (F6(b, 3) == error_st)
        printf("!4\n");
    else
    {
        if (F4(b, a) == error_raz)
            printf("!2\n");
        else
        {
            if (F6(F4(b, a), 2) == error_st)
                printf("!4\n");
            else
            {
                if (F4(F6(b, 3), F6(F4(b, a), 2)) == error_raz)
                    printf("!2\n");
                else
                {
                    if (F3(F4(F6(b, 3), F6(F4(b, a), 2)), a) == error_sum)
                        printf("!1\n");
                    else
                    {
                        x1 = F3(F4(F6(b, 3), F6(F4(b, a), 2)), a);
                        printf("%d\n", x1);
                    }
                }
            }
        }
    }

    // 2-е выражение
    if (F6(a, 3) == error_st)
        printf("!4\n");
    else
    {
        if (F3(F6(a, 3), b) == error_sum)
            printf("!1\n");
        else
        {
            if (F7(F3(F6(a, 3), b), b) == error_div)
                printf("!5\n");
            else
            {
                x2 = F7(F3(F6(a, 3), b), b);
                printf("%d\n", x2);
            }
        }
    }

    // 3-е выражение
    if (F6(b, 3) == error_st)
        printf("!4\n");
    else
    {
        if (F3(F6(b, 3), a) == error_sum)
            printf("!1\n");
        else
        {
            if (F8(F3(F6(b, 3), a), a) == error_mod)
                printf("!6");
            else
            {
                x3 = F8(F3(F6(b, 3), a), a);
                printf("%d\n", x3);
            }
        }
    }
    return 0;
}
