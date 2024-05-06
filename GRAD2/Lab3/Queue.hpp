#pragma once
#include <functional>
#include "../Lab2/Sequence.h"
#include "../Lab2/LinkedListSequence.h"
#include "../Lab2/LinkedList.h"
#include "MWRAble.hpp"

template <class T>
class Queue : public MWRAble<T, T>
{
private:
    LinkedList<T> impl;

public:
    Queue() : impl{LinkedList<T>()} {}
    Queue(T items[], size_t size) : impl{LinkedList<T>(items, size)} {}
    Queue(const Queue<T> &other) : impl{other.impl}{}

    ~Queue() = default;

    T front()
    {
        return impl.front();
    }
    T back()
    {
        return impl.back();
    }
    bool empty()
    {
        return impl.is_empty();
    }
    size_t size()
    {
        return impl.get_size();
    }

    void push(T value)
    {
        impl.push_back(value);
    }
    void pop()
    {
        impl.pop_front();
    }
    //safe version of concatination, makes copy of arguments, complexity: O(n)
    void safe_concat(Queue<T> & other){
        for(auto v : other.impl){
            impl.push_back(v);
        }
    }       
    //unsafe version of concatination, argument status is undefined, complexity: O(1)
    void force_concat(Queue<T> & other){
        impl+=other.impl;
        
    }

    void map(std::function<T(T)> function) override {
        T temp;
        LinkedList<T> new_impl = LinkedList<T>();
        while (!impl.is_empty())
        {
            temp = front();
            new_impl.push_back(function(temp));
            pop();
        }
        impl = new_impl;
    }
    void where(std::function<bool(T)> function) override {
        T temp;
        LinkedList<T> new_impl = LinkedList<T>();
        while(!impl.is_empty()){
            temp = front();
            if(function(temp)) new_impl.push_back(temp);
            pop();
        }
        impl = new_impl;
    }
    T reduce(std::function<T(T, T)> function, T start_value) override {
        Queue<T> copy(*this);
        T temp = function(copy.front(), start_value);
        copy.pop();
        while (!copy.empty())
        {
            temp = function(copy.front(), temp);
            copy.pop();
        }
        return temp;
    }
};