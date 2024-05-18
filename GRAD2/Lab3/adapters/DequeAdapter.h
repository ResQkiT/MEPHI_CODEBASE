#pragma once
#include "AbstractAdapter.h"
#include "../Deque.hpp"
#include <iostream>
#include <string>
using namespace std;

template<class T>
class DequeAdapter : public AbstractAdapter<T>{
private:
    Deque<T> container;
    string type = "deque";
public:

    DequeAdapter(): container{Deque<T>()}{}
    ~DequeAdapter() = default;

    void create_working_adt(T * list , size_t size) override
    {
        for (size_t i = 0; i < size; i++)
        {
            container.push_back(list[i]);
        }
    }
    void output() override{
        Deque<T> copy(container);
        cout << "Printing elements in "<< get_type() <<" order" << endl;
        while(!copy.empty()){
            cout << copy.front() << " ";
            copy.pop_front();
        }
        cout << endl;
    }
    void append(const T & value) override{
        cout << "Appending element to beginning" << endl;
        container.push_back(value);
    }
    void prepend(const T & value) override{
        cout << "Prepending element to ending" <<endl;
        container.push_front(value);
    }
    std::string & get_type() override {
        return type;
    }
    DequeAdapter<T> * clone(){
        DequeAdapter<T> * clone = new DequeAdapter();
        clone->type = this->type;
        clone->container = this->container; 
        return clone;
    }
};