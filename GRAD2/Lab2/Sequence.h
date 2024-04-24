#pragma once
#include <cstddef>

template<class T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(size_t index) const = 0;
    
    
    virtual Sequence<T> * getSubsequence(size_t startIndex, size_t endIndex) = 0;
    
    virtual size_t getLength() const = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(size_t index, T item) = 0;
    
    virtual Sequence<T> * concat(Sequence<T> * list) = 0;
};