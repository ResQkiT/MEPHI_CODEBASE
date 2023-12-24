#include <stdio.h>
int d(int a, int b, int c)
{
    return (c * b + 1) * (c * b + 1) - 4 * c * a;
}
void solution(int a, int b, int c, int *code, double *x1, double *x2)
{
    if (a == b)
    {
        if (c == 0)
        {
            *code = 3; // случай бесконечного чиcла решений не отслеживается -> 0
            return;
        }
        *code = 1;
        *x1 = 1.0 / ((double)c);
        if (*x1 == b)
            *code = 3;
        return;
    }

    if (c * b + 1 == 0 && a == 0)
    {
        *code = 1;
        *x1 = 0.0;
        return;
    }
    if (c == 0)
    {
        *x1 = a;
        if (b != *x1)
        {
            // уравнение имеет 1 решение
            *code = 1;
            return;
        }
        else
        {
            // деление на 0 -> вообще нет корней
            // девятый тест
            *code = 3;
            return;
        }
    }

    if (a == 0)
    {
        // два корня с != 0
        *code = 0;
        *x1 = 0.0;
        *x2 = (double)b + (1.0 / ((double)c));
        if (*x1 == b)
        {
            *x1 = b + 1.0 / ((double)c);
            *code = 1;
        }
        return;
    }

    if ((c * b + 1) == 0)
    {
        // возможны 3 случая
        if (-((double)a) / ((double)c) > 0)
        {
            // два действительных корня
            *code = 0;
            *x1 = -sqrtf(-((double)a) / ((double)c));
            if (*x1 == b)
                *code = 1; // один из корней совпадает с b
            *x2 = sqrtf(-((double)a) / ((double)c));
            if (*x2 == b)
                *code = 1; // второй корень может не совпасть
            if (*x1 == b && *x2 == b)
                *code = 3; // оба корня могут не совпасть -> x1 = x2 = 0 - фиктивный случай
            return;
        }
        else if (-((double)a) / ((double)c) < 0)
        {
            // два комплексных корня ->нет действительных
            *code = 2;
            return;
        }
        else
        {
            // бессмысленно
            /* a== 0 и b == 0;
            //a = 0, значит у уравнения 1 корень x1 = 0;
            *code = 1;
            *x1 = 0.0;
            if(*x1 == b) *code = 3; //деление на 0
            return;
            */
        }
    }

    // все коэфициенты не 0
    int D = d(a, b, c);
    // printf(" decremenant : %f\n", D );
    // если D < 0
    if (D < 0)
    {
        // нет вещественных корней, только комплексные
        *code = 2;
        return;
    }
    else if (D == 0)
    {
        // один корень
        *code = 1;
        *x1 = ((double)(c * b + 1)) / (double)(2 * c);
        return;
    }
    else
    {
        // два действительных корня
        *code = 0;
        *x1 = ((double)((c * b + 1) - sqrt(D))) / (double)(2 * c);
        *x2 = ((double)((c * b + 1) + sqrt(D))) / (double)(2 * c);
        return;
    }
}
int main()
{
    int a, b, c, code;
    double x1, x2;
    scanf("%d %d %d", &a, &b, &c);
    solution(a, b, c, &code, &x1, &x2);
    if (code == -1)
    {
        printf("%d\n", 0);
    }
    else
    {
        printf("%d\n", code);
        if (code == 0)
        {
            printf("%.6f\n%.6f\n", x1, x2);
        }
        else if (code == 1)
        {
            printf("%.6f\n", x1);
        }
        else if (code == 2 || code == 3)
        {
            // ничего не выводим
        }
        return 0;
    }
}