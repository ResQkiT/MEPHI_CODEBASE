#pragma once
#include "adapters/AbstractAdapter.h"
#include "../Lab2/readio.h"
#include <iostream>

using namespace std;

template<class T>
class ActionHandler{
private:
    AbstractAdapter<T> * adapter;
public:
    ActionHandler(): adapter{nullptr}{};
    ActionHandler(AbstractAdapter<T> * adapter) : adapter{adapter}{};
    ~ActionHandler(){delete adapter;};

    ActionHandler<T> & input_data(){
        cout << "Input data, into structure, of type: "<< adapter->get_type() << endl;
        size_t size;
        cout << "Enter count of element in structure: ";
        console_get(size);
        T list[size];
        cout << "Reading data...:";
        for (size_t i = 0; i < size; i++)
        {
            console_get(list[i]);
        }
        adapter->create_working_adt(list, size);
        return *this;
    }  
    ActionHandler<T> & output_data(){
        cout << "Current data in work: "<<endl;
        adapter->output();
        return *this;
    }
};