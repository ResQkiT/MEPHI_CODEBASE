#include "Sequence.h"

template<class T>
class ArraySequence : public Sequence<T> 
{

public:
    ArraySequence(T* items, int count);
    ArraySequence();
    ArraySequence(const ArraySequence<T> & arraySequence );

    virtual  ~ArraySequence();

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
