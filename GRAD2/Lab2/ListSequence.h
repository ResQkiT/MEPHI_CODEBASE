#pragma once
#include <Sequence.h>
template<class T>
class ListSequence : public Sequence<T>
{
private:

public:
    virtual ListSequence(T* items, int count);
    virtual ListSequence();
    virtual ListSequence(ListSequence<T> & listSequence const);

    virtual ~ListSequence();

    virtual T getFirst();
    virtual T getLast();
    virtual T get(int index);
    virtual ListSequence<T> getSubsequence(int startIndex, int endIndex);

    virtual int getLenth();
    virtual void append(T item);
    virtual void prepend(T item);
    virtual void insertAt(int index, T value);

    virtual ListSequence<T> concat(ListSequence<T> * list);
    
};  