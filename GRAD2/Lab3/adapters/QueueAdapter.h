#pragma once
#include "AbstractAdapter.h"
#include "../Queue.hpp"
#include <iostream>
#include <string>
using namespace std;

template<class T>
class QueueAdapter : public AbstractAdapter<T>{
private:
    Queue<T> container;
    string type = "queue";
public:

    QueueAdapter(): container{Queue<T>()}{}
    ~QueueAdapter() = default;

    void create_working_adt(T * list , size_t size) override
    {
        for (size_t i = 0; i < size; i++)
        {
            container.push(list[i]);
        }
    }
    void output() override{
        Queue<T> copy(container);
        cout << "Printing elements in "<< get_type() <<" order" << endl;
        while(!copy.empty()){
            cout << copy.front() << " ";
            copy.pop();
        }
        cout << endl;
    }
    void append(const T & value) override{
        container.push(value);
    }
    void prepend(const T & value) override{
        cout << "Warning! cant prepend element to start of queue, because od semantic rules"<<endl;
        cout << "Element wil be appended to endl" << endl;
        append(value);
    }
    std::string & get_type() override {
        return type;
    }
    QueueAdapter<T> * clone(){
        QueueAdapter<T> * clone = new QueueAdapter();
        clone->type = this->type;
        clone->container = this->container; 
        return clone;
    }
    
};