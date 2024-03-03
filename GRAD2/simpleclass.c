#include <stdio.h>
typedef struct Collection {
    int a;
    int b;
}Collection;
//обертка над простым int 
typedef struct Number{
    char meta;
    int data;
    int* add;
} Number;

typedef struct ExtendedNumber{
    char meta;
    Number x;
    Number y;
} ExtendedNumber;

ExtendedNumber* ExtendedNumberConstructor(Number a, Number b){
    ExtendedNumber* number = malloc(sizeof(ExtendedNumber));
    number->x = a;
    number->y = b;
    return number;
}

int main(void) {
    Number* a = malloc(sizeof(Number));
    Number* b = malloc(sizeof(Number));  
    ExtendedNumber *extended = ExtendedNumberConstructor(*a, *b);
}