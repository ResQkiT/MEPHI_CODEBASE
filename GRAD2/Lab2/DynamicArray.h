#include "ArraySequence.h"
template<class T>
class DynamicArray : public ArraySequence<T>
{
private:
    T * list;
    int length;
public:
    ArraySequence(T* items, int count)list{nullptr} length{0}{
        this->list = items;
        this->length = count
    }
    ArraySequence();
    ArraySequence(ArraySequence<T> & arraySequence const);

    ~ArraySequence();

    T getFirst();
    T getLast();
    T get(int index);
    ArraySequence<T> getSubsequence(int startIndex, int endIndex);
    
    int getLength(){
        return this->length;
    }
    void append(T item);
    void prepend(T item);
    void insertAt(int index, T value);
    ArraySequence<T> concat(Sequence<T> * list);
};