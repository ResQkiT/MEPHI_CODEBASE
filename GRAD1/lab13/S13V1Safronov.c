#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct elem{
    int data;
    struct elem *link; 
} Elem;
int push_front(Elem **top , int to_add){
    Elem *p;
    p = (Elem *) malloc(sizeof(Elem));
    p->data = to_add;
    p->link = *(top);
    *(top) = p;
}
int push_back(Elem **top , int to_add){
    Elem *temp = *(top);
    while (temp->link->link != NULL) temp = temp->link;
    Elem *newElem;
    newElem->data = to_add;
    newElem->link = temp->link;
    temp->link = newElem;
}
int pop_front(Elem **top){
    int upper;
    Elem *p;
    upper = (*top)->data;
    p = (*top);
    (*top) = p->link;
    free(p);
    return upper;
}
int pop_back(Elem **top){
    Elem *temp = *(top);
    while (temp->link->link != NULL) temp = temp->link;
    printf("%d \n" , temp->data);
    Elem *p =temp;
    temp = temp->link;
    printf("%d \n" , temp->data);
    free(p);
}
Elem* find(Elem **top, int to_find){
    Elem *temp = *top;
    while (temp->link != NULL)
    {
        if(temp->data == to_find)
            return temp;
        temp = temp->link;
    }
    return NULL;
}
int popAfter(Elem **top , Elem *target){
    Elem *todelete = target->link;
    target->link = target->link->link;
    free(todelete);
}
int createStack(Elem **Start){
    Elem *Top, *p;
    Top = NULL;
    p = (Elem *) malloc(sizeof(Elem));
    p->data = 0;
    p->link = NULL;
    Top = p;
    *(Start) = Top;
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
        if (token[0] == 'n') 
            break;  
        number = atoi(token);
        push_front(&start , number);
        token = strtok(NULL, " ");
    }
    int target;
    scanf("%d" , &target);
    Elem *e = find(&start , target);
    if (e == NULL)
    {
        printf("no such element in stack\n");
        return 0;
    }
    
    popAfter(&start , e);
    printStack(start);
    return 0;
    
}

/*
42 7 23 19 5 80 74 6 n
19

*/