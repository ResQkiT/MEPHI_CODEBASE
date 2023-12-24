#include <stdio.h>
#include <ctype.h>
#define IN 1  /* внутри слова */
#define OUT 0 /* снаружи слова */
int main(void)
{
    int c,     /* текущий символ */
        state, /* состояние потока (внутри или снаружи слова) */
        nc,    /* количество символов (number of characters) */
        nw,    /* количество слов (number of words) */
        nl;    /* количество строк (number of lines) */
    state = OUT;
    nc = nw = nl = 0;
    while ((c = getchar()) != EOF)
    { /* пока не найден конец файла */
        ++nc;
        if (c == '\n') /* если текущий символ - конец строки */
            ++nl;
        if (isspace(c))  /* если текущий символ - пробельный */
            state = OUT; /* текущий символ находится снаружи слова */
        else if (state == OUT)
        {               /* если предыдущий символ снаружи слова */
            state = IN; /* текущий символ находится внутри слова */
            ++nw;
        }
    }
    printf("Символов: %d; слов: %d; строк: %d.\n", nc, nw, nl);
    return 0;
}