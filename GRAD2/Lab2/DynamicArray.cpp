#include "DynamicArray.h"
#include "ArraySequence.h"
DynamicArray<T>::DynamicArray<T>(T* items, int count)list{nullptr} length{0}{
    this->list = items;
    this->length = count
}
DynamicArray::ArraySequence();
DynamicArray::ArraySequence(ArraySequence<T> & arraySequence const);

DynamicArray::~ArraySequence();

DynamicArray::T getFirst();
DynamicArray::T getLast();
DynamicArray::T get(int index);
DynamicArray::ArraySequence<T> getSubsequence(int startIndex, int endIndex);

DynamicArray::int getLength(){
    return this->length;
}
DynamicArray::void append(T item);
DynamicArray::void prepend(T item);
DynamicArray::void insertAt(int index, T value);
DynamicArray::ArraySequence<T> concat(Sequence<T> * list);