#pragma once
#include "ArraySequence.h"
template<class T>
class DynamicArray : public ArraySequence<T>
{
private:
    T * list;
    int length;
public:
    DynamicArray(T* items, int count) : list{nullptr}, length{0}{
        this->list = items;
        this->length = count;
    }
    DynamicArray() : list{nullptr}, length{0}{}
    DynamicArray(const DynamicArray<T> & arraySequence){
        this->list = arraySequence.list;
        this->length = arraySequence.length;
    }
    ~DynamicArray() = default;

    T getFirst(){
        return list[0];
    }
    T getLast(){
        return list[length - 1];
    }
    T get(int index){
        return list[index];
    }
    Sequence<T> getSubsequence(int startIndex, int endIndex){
        return *(Sequence<T> *) this;
    }
    
    int getLength(){
        return this->length;
    }
    void append(T item){
        return;
    }
    void prepend(T item){
        return;
    }
    void insertAt(int index, T value){
        return;
    }
    Sequence<T> concat(Sequence<T> * list){
        return *(Sequence<T> *) this;
    }
};
