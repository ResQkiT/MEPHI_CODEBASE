#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "DynamicArraySequence.h"
#include "LinkedListSequence.h"

using namespace std;

template<class T>
Sequence<T> * input_to(Sequence<T> * target){
    
    T temp;
    for (size_t i = 0; i <target->get_length(); i++)
    {
        cin >> temp;
        target->append(temp);
    }
    return target;
}
template<class T>
Sequence<T> * input_to(Sequence<T> & target){
    T temp;
    for (size_t i = 0; i <target.get_length(); i++)
    {
        cin >> temp;
        target.append(temp);
    }
    return target;
}

template<class T>
void output(Sequence<T> * target){    
    for (size_t i = 0; i <target->get_length(); i++)
    {
        cout << target->get(i);
    }
    return;
}

template<class T>
void output(Sequence<T> & target){
    T temp;
    for (size_t i = 0; i <target.get_length(); i++)
    {
        cout << target.get(i);
    }
    return;
}