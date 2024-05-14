#pragma once
#include <stddef.h>
#include <string>

template<class T> 
class AbstractAdapter{
public:
    virtual ~AbstractAdapter() = default;
    virtual void create_working_adt(T * list, size_t size) = 0;
    virtual void output() = 0;
    virtual void append(const T & value) = 0;
    virtual void prepend(const T & value) = 0;
    virtual const std::string & get_type() = 0;
};