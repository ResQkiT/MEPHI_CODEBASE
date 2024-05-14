#pragma once
#include "AbstractAdapter.h"
#include "../SegmentedDeque.hpp"

using namespace std;

template<class T>
class SegmentedDequeAdapter : public AbstractAdapter<T>{
private:
SegmentedDeque<T> container;

const string type = "segmented stack";
public:
    SegmentedDequeAdapter() : container{SegmentedDeque<T>()}{};
    ~SegmentedDequeAdapter() = default;
    
    void create_working_adt(T * list , size_t size) override
    {
        for (size_t i = 0; i < size; i++)
        {
            container.push_back(list[i]);
        }
    }
    void output() override{
        SegmentedDeque<T> copy(container);
        cout << "Printing elements in "<< get_type() <<" order" << endl;
        while(!copy.empty()){
            cout << copy.front()<< " ";
            copy.pop_front();
        }
        cout << endl;
    }
    void append(const T & value) override{
        container.push_back(value);
    }
    void prepend(const T & value) override{
        container.push_front(value);
    }
    const string get_type(){
        return type;
    }
};