#pragma once
#include "Sequence.h"
#include "LinkedList.h"
template<class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> * impl;
public:
    LinkedListSequence(){

    }

    T getFirst(){
        return this->impl->front();
    }
    T getLast(){
        return this->impl->back();
    }
    T get(size_t index){
        return this
    }
    Sequence<T> getSubsequence(size_t startIndex, size_t endIndex){

    }
    size_t getLength(){

    }
    void append(T item){

    }
    void prepend(T item){

    }
    void insertAt(size_t index, T item){
    
    }
    Sequence<T> concat(Sequence<T> * list){

    }
};  