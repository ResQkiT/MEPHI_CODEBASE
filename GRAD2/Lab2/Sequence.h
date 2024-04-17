#pragma once

template<class T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    
    
    virtual Sequence<T> getSubsequence(int startIndex, int endIndex) = 0;
    
    virtual int getLength() = 0;
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(int index, T value) = 0;
    
    virtual Sequence<T> concat(Sequence<T> * list) = 0;
};