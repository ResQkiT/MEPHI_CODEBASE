#include <stdio.h>
#include <math.h>
#include <limits.h>
#define li long int
int ERROR_CODE = 0;
li overflowAdd(li a, li b, int *flag)
{
    *flag = 0;
    if (a > (long long)((long long) LONG_MAX - (long long)b))
    {
        *flag = 1;
    }
    return a + b;
}
li overflowMultiolication(li a, li b, int *flag){
    *flag = 0;
    if (a > (long long)( LONG_MAX / (long long)b))
    {
        *flag = 1;
    }
    return a * b;
}
li fromNINEtoTEN(li number)
{
    // transforming number 9 -> 10
    int sign = number > 0 ? 1 : -1;
    number = abs(number);
    li answer = 0, i = 0;
    while (number > 0)
    {
        answer += (number % 10) * pow(9, i);
        number /= 10;
        i++;
    }
    return answer * sign;
}
li fromTENtoNINE(li a)
{
    int i, k, ost, a1, s = 0;
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
            ost = a % 9;
            s += ost * pow(10, i);
            a = a / 9;
        }
    }
    else if (a == 0) s = 0;
    else
    {
        for (i = 0; i <= k; i++)
        {
            ost = a % 9;
            s += ost * pow(10, i);
            a = a / 9;
        }
    }
    return s;
}
li fromTENtoTHREE(li number)
{
    li answer = 0;
    int ternary[32];
    int index = 0, oveflow;
    int sign = number > 0 ? 1 : -1;
    number = abs(number);
    while (number > 0)
    {
        ternary[index] = number % 3;
        number = number / 3;
        index++;
    }
    for (int i = index - 1; i >= 0; i--)
    {
        answer = overflowAdd(answer, ternary[i] * pow(10, i), &oveflow);
        if (oveflow == 1)
        {
            printf("Overflow , returning 0\n");
            return 0;
        }
    }
    return answer * sign;
}
li addition(li a, li b)
{
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    
    //отслеживать переполнение
    //printf("addition with args: a = %d, b = %d\n", a, b);
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);
    int flag = 0;
    li answer = overflowAdd(a, b, &flag);
    if(flag == 1){
        printf("!");
        ERROR_CODE = 1;
        return ERROR_CODE;
        //printf("Additional overfloating...\n");
    } 
    answer = fromTENtoNINE(answer);
    return answer;
}
li substraction(li a, li b)
{
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    //отслеживать переполнение
    //printf("substraction with args: a = %d, b = %d\n", a, b);
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);

    int flag = 0;
    li answer = overflowAdd(a, (-1) *  b, &flag);
    if(flag == 1){
        printf("!");
        ERROR_CODE = 2;
        return ERROR_CODE;
    } //printf("substraction overfloating a = %d ; b = %d ...\n", a, b);

    answer = fromTENtoNINE(answer);
    return answer;
}
li multiplication(li a, li b)
{
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    //отслеживать переполнение
    //printf("multiplication with args: a = %d, b = %d\n", a, b);
    int sign = (long long)a*b <0? -1: 1; 
    a = abs(fromNINEtoTEN(a));
    b = abs(fromNINEtoTEN(b));

    int flag = 0;
    li answer = 0;
    while (b--)
    {
        answer = overflowAdd(answer , a , &flag);
        if(flag == 1) {
            printf("!");
            ERROR_CODE = 3;
            //printf("multiplication overfloating a = %d ; b = %d ...\n", a, b);   
            return ERROR_CODE;
        }
    }

    answer = fromTENtoNINE(answer);
    return sign * answer;
    
}
li securedPOW(li a, li b ){
    if(a == 0) return 0;
    if(a == 1) return 1;
    li result = 1;
    li code = 0;
    for (int i = 1; i <= b; i++)
    {
        result = overflowMultiolication(result, a,  &code);
        if(code){
            //переполнение при возведении в степень
            ERROR_CODE = 4;
            return ERROR_CODE;
        }
    }
    return result;
}
li positivepow(li a, li b)
{
    if(a == 1) return 1;
    if(a == 0) return 0;
    //printf("A : %d, B: %d\n" , a , b);
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    //отслеживать переполнение
    //printf("postivepow with args: a = %d, b = %d\n", a, b);
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);
    //printf("postivepow with args: a = %d, b = %d\n", a, b);
    li result = securedPOW(a, b);
    //printf("result: %d", result);
    //printf("secured result in positivepow: %d\n", result);
    if (ERROR_CODE == 4)
    {
        printf("!");
        ERROR_CODE = 4;
        return ERROR_CODE;
    }
    result = pow(a, b);
    result = fromTENtoNINE(result);
    //printf("result in positivepow: %d\n", result);
    return result;
}
li division(li a, li b)
{
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);
    //printf("B: %d", b);
    //отслеживать деление на 0
    if(b == 0) {
        printf("!");
        ERROR_CODE = 5;
        return ERROR_CODE;
    }
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);
    li answer = a / b;
    answer = fromNINEtoTEN(answer);
    return answer;
}
li mod(li a, li b)
{
    if (ERROR_CODE != 0)
    {
        return ERROR_CODE;
    }
    a = fromNINEtoTEN(a);
    b = fromNINEtoTEN(b);
    //printf("B: %d", b);
    //отслеживать деление на 0
    if( b == 0){
        printf("!");
        ERROR_CODE = 6;
        return ERROR_CODE;
    }
    li answer = a % b;
    //printf(" T result: %d\n", answer);
    answer = fromNINEtoTEN(answer);
    //printf("result: %d\n", answer);
    return answer;
}

int main(void)
{
    li a, b;
    scanf("%d %d", &a, &b);
    ERROR_CODE = 0;
    li answer = substraction(substraction(multiplication(positivepow(a, 2), b), multiplication(b, substraction(a, b))), a);

    printf("%d\n", answer);
    ERROR_CODE = 0;
    li answer2 = division(addition(positivepow(a, 3), b), b);
    printf("%d\n", answer2);
    ERROR_CODE = 0;

    li answer3 = mod(addition(a, positivepow(b, 3)), a);
    printf("%d\n", answer3);
}