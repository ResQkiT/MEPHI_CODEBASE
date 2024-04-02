#include "Sequence.h"

template<class T>
class ArraySequence : public Sequence<T> 
{

public:
    virtual ArraySequence(T* items, int count);
    virtual ArraySequence();
    virtual  ArraySequence(ArraySequence<T> & arraySequence const);

    virtual  ~ArraySequence();

    virtual T getFirst();
    virtual T getLast();
    virtual T get(int index);
    virtual ArraySequence<T> getSubsequence(int startIndex, int endIndex);
    
    virtual int getLength();
    virtual void append(T item);
    virtual void prepend(T item);
    virtual void insertAt(int index, T value);
    virtual ArraySequence<T> concat(Sequence<T> * list);
};
