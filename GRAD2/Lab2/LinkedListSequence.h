#pragma once
#include "Sequence.h"
#include "LinkedList.h"
template<class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> * impl;
public:
    explicit LinkedListSequence() : impl{new LinkedList<T>}{}
    
    explicit LinkedListSequence(LinkedList<T> * list) : impl{list} {}

    explicit LinkedListSequence(T * items, size_t size) : impl{new LinkedList(items, size)}{}

    T getFirst() const override
    {
        return impl->front();
    }

    T getLast() const override
    {
        return impl->back();
    }

    T get(size_t index) const override 
    { //std::advance(it, n)
        for (int i = 0 , auto it = impl->begin() ; i < index; it++ , i++);
        return *iter;
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