#include "Sequence.h"

template<class T>
class ArraySequence
{
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual ArraySequence<T> getSubsequence(int startIndex, int endIndex) = 0;
    

};
