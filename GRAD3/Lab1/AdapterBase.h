#pragma once
#include <stddef.h>
#include <string>

template<class T> 
class AdapterBase{
public:
    virtual ~AbstractAdapter() = default;
    virtual void append(const T & value) = 0;
    virtual void prepend(const T & value) = 0;
    void insert(size_t index, T & value) = 0;
    T& get(size_t index) = 0;
    T& getFirst() = 0;
    T& getLast() = 0;
    size_t get_size() = 0;
    std::string raw_string() = 0;
};