#pragma once
typedef struct {
    void* (*addition)(void*,void*);
    void* (*multiply)(void*, void*);
    void* (*printElement)(void*);
    void* (*input)();
    int allocsize;
} FieldInfo;
