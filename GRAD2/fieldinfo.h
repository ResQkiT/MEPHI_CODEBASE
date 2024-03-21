#pragma once
typedef struct {
    //поправить перевод все в глаголы
    //третий аргумент - не константный
    
    void* (*addition)( void*, void*, void*);
    void* (*multiplication)(const void*,const void*);
    void* (*printElement)(void*);
    void* (*input)(void*);

    //size_t
    int allocsize;

    void (*zeroInPlace)(void *);
    const void *(*zero_)();
    
} FieldInfo;

//

