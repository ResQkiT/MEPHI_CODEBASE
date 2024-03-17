#pragma once
#include "fieldinfo.h"
#include "complex.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct 
{
    double re;
    double im;
}Complex;

FieldInfo* newComplexImpl(){
    FieldInfo* impl = malloc(sizeof(FieldInfo));
    impl->allocsize = sizeof(Complex);
    impl->addition = complexAddition;
    impl->multiply = complexMultiplication;
    impl->printElement = complexPrint;
    impl->input = complexInput;
    return impl;
}

void* complexAddition(void* v1, void* v2){
    Complex* res = malloc(sizeof(Complex));
    res->re = ((Complex*)v1)->re + ((Complex*)v2)->re;
    res->im = ((Complex*)v1)->im + ((Complex*)v2)->im;
    return (void*) res;
}

void* complexMultiplication(void* v1, void* v2){
    Complex* res = malloc(sizeof(Complex));
    res->re = (((Complex *)v1)->re * ((Complex *)v2)->re) - \
              (((Complex *)v1)->im * ((Complex *)v2)->im);

    res->im = (((Complex *)v1)->re * ((Complex *)v2)->im) + \
              (((Complex *)v1)->im * ((Complex *)v2)->re);

    return (void*) res;
}

void* complexPrint(void * v){
    Complex* c = (Complex*)v; 
    printf("%.2lf", c->re);
    if (c->im > 0) printf("+");
    printf("%.2lf", c->im );
    printf("i ");
    return (void* ) c;
}
void* complexInput(){
    Complex* c = malloc(sizeof(Complex));
    scanf("%lf %lf", &(c->re), &(c->im));
    return (void*) c;
}
