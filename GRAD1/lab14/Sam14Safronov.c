#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
} Node;
typedef struct linkedlist{
    Node *begin;
    Node *end;
} LinkedList;

void push_front(LinkedList **linkedlist, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    if ((*linkedlist)->begin == NULL) {
        (*linkedlist)->begin = new_node;
        (*linkedlist)->end = new_node;
    } else {
        new_node->next = (*linkedlist)->begin;
        (*linkedlist)->begin->prev = new_node;
        (*linkedlist)->begin = new_node;
    }
}
void push_back(LinkedList **linkedlist, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    if ((*linkedlist)->end == NULL) {
        (*linkedlist)->end = new_node;
        (*linkedlist)->begin = new_node;
    } else {
        new_node->prev = (*linkedlist)->end;
        (*linkedlist)->end->next = new_node;
        (*linkedlist)->end = new_node;
    }
}
void pop_front(LinkedList **linkedlist) {
    if ((*linkedlist)->begin!= NULL) {
        Node *temp = (*linkedlist)->begin;
        (*linkedlist)->begin = (*linkedlist)->begin->next;
        free(temp);
    }
}
void pop_back(LinkedList **linkedlist) {
    if ((*linkedlist)->end!= NULL) {
        Node *temp = (*linkedlist)->end;
        (*linkedlist)->end = (*linkedlist)->end->prev;
        free(temp);
    }
}
void printf_linkedlist(LinkedList *linkedlist) {
    Node *temp = linkedlist->begin;
    while (temp!= NULL) {
        printf("%4d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void printf_linkedlist_reverse(LinkedList *linkedlist) {
    Node *temp = linkedlist->end;
    while (temp!= NULL) {
        printf("%4d", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}
int count_sum(LinkedList *linkedlist) {
    int sum = 0;
    Node *temp = linkedlist->begin;
    while (temp!= NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}
void add_add_random_elements_back(LinkedList **linkedlist, int n, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        push_back(linkedlist, rand() % (max - min + 1) + min);
    }
}
void add_add_random_elements_front(LinkedList **linked, int n, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        push_front(linked, rand() % (max - min + 1) + min);
    }
}
void clear_linkedlist(LinkedList **linkedlist) {
    while ((*linkedlist)->begin!= NULL) {
        pop_front(linkedlist);
    }
}
Node *find_node_by_data(LinkedList *linkedlist, int data) {
    Node *temp = linkedlist->begin;
    while (temp!= NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void remove_node_by_adress(LinkedList **linkedlist, Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}
void add_add_elements_before_by_adress(LinkedList **linkedlist, Node *node, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
}
int main(void) {
    int number, to_find, to_add;
    char input[1000];
    //Создание стека
    LinkedList* linkedlist = (LinkedList*)malloc(sizeof(LinkedList));
    linkedlist->begin = NULL;
    linkedlist->end = NULL;

    fgets(input, 100, stdin);
    char* token = strtok(input, " ");
    while (token != NULL) {
        if (token[0] == 'n') {
            break;  
        }
        
        number = atoi(token);
        push_front(&linkedlist, number);
        token = strtok(NULL, " ");
    }
    scanf("%d", &to_find);
    scanf("%d", &to_add);
    Node *node = find_node_by_data(linkedlist, to_find);
    if (node == NULL) 
    {
        printf_linkedlist(linkedlist);
    }else {
        add_add_elements_before_by_adress(&linkedlist ,node, to_add);
        printf_linkedlist(linkedlist);
        remove_node_by_adress(&linkedlist, node);
        printf_linkedlist(linkedlist);
    }
    clear_linkedlist(&linkedlist);
    return 0;
}
/*
42 7 23 19 5 80 74 6 n
19
38

*/