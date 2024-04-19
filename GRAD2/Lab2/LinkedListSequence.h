#pragma once
#include "Sequence.h"
#include "LinkedList.h"
template<class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> * impl;
public:
    LinkedListSequence() : impl{new LinkedList<T>}{}

    T getFirst(){
        return impl->front();
    }
    T getLast(){
        return impl->back();
    }
    T get(size_t index){
        return this
    }
    Sequence<T> getSubsequence(size_t startIndex, size_t endIndex){
        //TODO realization oof subsequence
    }
    size_t getLength(){
        return impl->size();
    }
    void append(T item){
        impl->push_back(item);
    }
    void prepend(T item){
        impl->push_front(item);
    }
    void insertAt(size_t index, T item){
        
    }
    Sequence<T> concat(Sequence<T> * list){

    }
};  