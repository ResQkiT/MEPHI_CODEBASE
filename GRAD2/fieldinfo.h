#pragma once
typedef struct {
    //поправить перевод все в глаголы
    //третий аргумент - не константный
    
    void* (*addition)(void*, void*);
    void* (*multiply)(void*, void*);
    void* (*printElement)(void*);
    void* (*input)();
    //size_t
    int allocsize;

    void (*zero)(void*);
    const void *(*zero_)();
    
} FieldInfo;

//

