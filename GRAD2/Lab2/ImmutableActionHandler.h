#pragma one
#include <iostream>
#include <cstddef>
#include "ImmutableSequence.h"
#include "ImmutableDynamicArraySequence.h"
#include "ImmutableLinkedListSequense.h"
#include "AbstractActionListener.h"

using namespace std;

template <class T>
class ImmutableActionHandler : public AbstractActionListener<T>
{
private:
    ImmutableSequence<T> *working_sequence;

public:
    ImmutableActionHandler() : working_sequence{nullptr} {};

    ~ImmutableActionHandler()
    {
        delete[] working_sequence;
    }
    ImmutableActionHandler<T> *create_sequence_dialog() override
    {
        
    }

    ImmutableActionHandler<T> *create_linked_list_sequence() override
    {
        
    }

    ImmutableActionHandler<T> *create_dynamic_array_sequence() override
    {
        
    }
    ImmutableActionHandler<T> *get_n_show_subsequence() override
    {
        
    }
    ImmutableActionHandler<T> *add_element_to_begin() override
    {
        
    }
    ImmutableActionHandler<T> *add_element_to_position() override
    {
        
    }
    ImmutableActionHandler<T> *add_element_to_end() override
    {
        
    }
    ImmutableActionHandler<T> *print_working_sequence() override
    {
        
    }
    ImmutableActionHandler<T> *concat_with_new_sequence() override
    {
        
    }
};
