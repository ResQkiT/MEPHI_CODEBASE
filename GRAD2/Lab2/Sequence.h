#pragma once


template<class T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(size_t index) = 0;
    
    
    virtual Sequence<T> * get_subsequence(size_t startIndex, size_t endIndex) = 0;
    
    virtual size_t get_length() const = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert_at(size_t index, T item) = 0;
    
    virtual Sequence<T> * concat(Sequence<T> * list) = 0;
};