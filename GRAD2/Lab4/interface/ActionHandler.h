#pragma once
#include "AbstractAdapter.h"

#include <iostream>
#include <string>

using namespace std;

template<class T>
class ActionHandler{
private:
    AbstractAdapter<T> * adapter;
public:
    ActionHandler(): adapter{nullptr}{};
    ActionHandler(AbstractAdapter<T> * adapter) : adapter{adapter}{};
    ~ActionHandler(){delete adapter;};

    string & get_type(){
        if(adapter == nullptr) throw new std::runtime_error("Adapter is null");
        return adapter->get_type();
    }

    ActionHandler<T> & set_adapter(AbstractAdapter<T> * adapter){
        if(adapter != nullptr) delete this->adapter;
        this->adapter = adapter->clone();
        return *this;
    }

    ActionHandler<T> & input_data(){
        cout << "Input data, into structure, of type: "<< adapter->get_type() << endl;
        size_t size;
        cout << "Enter count of element in structure: ";
        console_get_or_throw(size);
        T list[size];
        cout << "Reading data...:";
        for (size_t i = 0; i < size; i++)
        {
            console_get_or_throw(list[i]);
        }
        adapter->create_working_atd(list, size);
        return *this;
    }  
    ActionHandler<T> & pre_order_output_data(){
        cout << "Current data in work: "<<endl;
        adapter->pre_order_output();
        return *this;
    }
    ActionHandler<T> & in_order_output_data(){
        cout << "Current data in work: "<<endl;
        adapter->in_order_output();
        return *this;
    }
    ActionHandler<T> & post_order_output_data(){
        cout << "Current data in work: "<<endl;
        adapter->post_order_output();
        return *this;
    }
    ActionHandler<T> & insert_element(){
        cout << "Operation: appending element" << endl;
        cout << "Please, enter element(same type as mentioned): ";
        T elem;
        console_get_or_throw(elem);
        adapter->insert(elem);
        return *this;
    }
    ActionHandler<T> & remove_element(){
        cout << "Operation: prepending element to ending" << endl;
        cout << "Please, enter element(same type as mentioned): ";
        T elem;
        console_get_or_throw(elem);
        adapter->remove(elem);
        return *this;
    }
    
};