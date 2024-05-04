#pragma once
#include <iostream>
#include "readio.h"

template <class T>
class AbstractActionListener
{
public:
    ~AbstractActionListener() = default;

    virtual AbstractActionListener<T> *create_sequence_dialog(){
        std::cout << "1 - to create Mutable Dynamic Array Sequence\n2 - to create Mutable Linked List Sequence\n-1 - to return\n->";
        int choice;
        console_get(choice);
        switch (choice)
        {
        case 1:
            return create_dynamic_array_sequence();
            break;
        case 2:
            return create_linked_list_sequence();
            break;
        default:
            return this;
            break;
        }
    }
    virtual AbstractActionListener<T> *create_linked_list_sequence() = 0;
    virtual AbstractActionListener<T> *create_dynamic_array_sequence() = 0;
    virtual AbstractActionListener<T> *get_n_show_subsequence() = 0;
    virtual AbstractActionListener<T> *add_element_to_begin() = 0;
    virtual AbstractActionListener<T> *add_element_to_position() = 0;
    virtual AbstractActionListener<T> *add_element_to_end() = 0;
    virtual AbstractActionListener<T> *print_working_sequence() = 0;
    virtual AbstractActionListener<T> *concat_with_new_sequence() = 0;
};