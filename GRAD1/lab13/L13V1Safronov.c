#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct elem{
    int data;
    struct elem *link; 
} Elem;
int createStack(Elem **Start){
    Elem *Top, *p;
    Top = NULL;
    p = (Elem *) malloc(sizeof(Elem));
    p->data = 0;
    p->link = NULL;
    Top = p;
    *(Start) = Top;
}
int addToStack(Elem **top , int to_add){
    Elem *p;
    p = (Elem *) malloc(sizeof(Elem));
    p->data = to_add;
    p->link = *(top);
    *(top) = p;
}
int popStack(Elem **start){
    int upper;
    Elem *p;
    upper = (*start)->data;
    p = (*start);
    (*start) = p->link;
    free(p);
    return upper;
}
int printStack(Elem *top){
    Elem *temp;
    temp = top;
    while (temp->link != NULL)
    {
        printf("%4d" , temp->data);
        temp = temp->link;
    }
    printf("\n");
}
int sumStack(Elem *top){
    int sum = 0;
    Elem *temp;
    temp = top;
    while (temp->link != NULL)
    {
        sum += temp->data;
        temp = temp->link;
    }
    return sum;
}
int main(void) {
    int number;
    char input[1000];
    //Создание стека
    Elem *start;
    createStack(&start);

    fgets(input, 100, stdin);
    char* token = strtok(input, " ");
    while (token != NULL) {
        if (token[0] == 'n') {
            break;  
        }
        number = atoi(token);
        addToStack(&start , number);
        token = strtok(NULL, " ");
    }
    //удалем 2 элемента
    popStack(&start);
    popStack(&start);
    printStack(start);
    printf("%d\n" , sumStack(start));
    return 0;
}
/*
42 7 23 19 5 80 74 6 n

*/