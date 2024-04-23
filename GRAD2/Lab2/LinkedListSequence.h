#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> impl;

    explicit LinkedListSequence(LinkedList<T> list) : impl{list} {}
public:
    explicit LinkedListSequence() : impl{LinkedList<T>()}{}
    
    explicit LinkedListSequence(T * items, size_t size) : impl{new LinkedList(items, size)}{}

    T getFirst() const override
    {
        return impl.front();
    }

    T getLast() const override
    {
        return impl.back();
    }

    T get(size_t index) const override 
    { 
        auto it = impl.begin();
        for (int i = 0; i < index; it++ , i++);
        return *it;
    }
    LinkedListSequence<T> * getSubsequence(size_t startIndex, size_t endIndex){

        LinkedList<T> subsequence = LinkedList<T>();
        auto it_from = impl.begin();
        
        for (size_t i = 0; i < startIndex ; i++, it_from++);
        for (size_t i = 0; i < endIndex - startIndex; i++, it_from++)
        {
            subsequence.push_back(*it_from);
        }
        return new LinkedListSequence(subsequence);
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
    LinkedListSequence<T> * concat(Sequence<T> ** list, size_t count) override
    {
        //делаем динамик каст к 
    }
    LinkedListSequence<T> & operator+(const LinkedListSequence<T> & other) const
    {
        LinkedList<T> newLinkedList;
        newLinkedList += *this;
        newLinkedList += other;
        return LinkedListSequence<T>(newLinkedList);
    }
    LinkedListSequence<T> & operator+=(const LinkedListSequence<T> & other){
        auto it = other.begin();
        for(;it != other.end();it++)
        {
            append(*it);
        }
        return *this;
    }

};  

template<class T>
std::ostream& operator << (std::ostream &os, const LinkedListSequence<T> &list)
{
    auto it = list.begin();

    for (; it != list.end();it++)
    {
        os << *it<< " ";
    }
    os << std::endl;
    return os;
    
}