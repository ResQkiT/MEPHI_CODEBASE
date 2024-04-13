#pragma once

template<class T>
class Sequence
{
public:

    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    
    virtual T get(int index);
    
    virtual Sequence<T> getSubsequence(int startIndex, int endIndex);
    
    virtual int getLength();
    virtual void append(T item);
    virtual void prepend(T item);
    virtual void insertAt(int index, T value);
    
    virtual Sequence<T> concat(Sequence<T> * list);
};