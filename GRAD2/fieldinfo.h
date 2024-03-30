#pragma once

typedef struct {
    void* (*addition)( void*, void*, void*);
    void* (*multiplication)(void*,void*, void*);
    void* (*printElement)(void*);
    void* (*input)(void *,void*);
    int allocsize;
    void (*zeroInPlace)(void *);
    const void *(*zero_)();
    int (*equal)(void*, void*);
} FieldInfo;

