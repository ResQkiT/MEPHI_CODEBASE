#pragma once

template<class T>
class Sequence
{
public:
    Sequence();
    ~Sequence();

    virtual T getFirst();
    virtual T getLast();
    
    virtual T get(int index);
    
    virtual Sequence<T> getSubsequence(int startIndex, int endIndex);
    
    virtual int getLength();
    virtual void append(T item);
    virtual void prepend(T item);
    virtual void insertAt(int index, T value);
    
    virtual Sequence<T> concat(Sequence<T> * list);
};