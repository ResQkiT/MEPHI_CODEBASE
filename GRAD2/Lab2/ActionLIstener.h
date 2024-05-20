#pragma one
#include <iostream>
#include <cstddef>
#include "ImmutableDynamicArraySequence.h"
#include "ImmutableLinkedListSequense.h"
#include "readio.h"

using namespace std;

template<class T, template<class> class _sequence_container>
class ActionListener{
private:
    _sequence_container<T> * working_container = new _sequence_container<T>();
public:
    ActionListener(){}
    ~ActionListener() {
        delete[] working_container;
    }

    ActionListener<T, _sequence_container> * create_linked_list__sequence()
    {
        cout << "Creating Immutable Linked List _sequence_container\nenter size of _sequence_container->";
        int n;
        console_get_or_throw(n);
        T data[n];
        cout << "Enter " << n << " elements of future array\n->";
        for (int i = 0; i < n; i++)
        {
            console_get_or_throw(data[i]);
        }
        _sequence_container<T> *linked_list = new _sequence_container<T>(data, n);
        working_container = linked_list;
        return this;
    }
    

};