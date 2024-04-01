#pragma once
#include <stdio.h>
typedef struct {
    void* (*addition)( void*, void*, void*);
    void* (*multiplication)(void*,void*, void*);
    void* (*printElement)(void*);
    void* (*input)(FILE * file,void* target);
    int allocsize;
    void (*zeroInPlace)(void *);
    const void *(*zero_)();
    int (*equal)(void*, void*);
    char metadata;
} FieldInfo;

