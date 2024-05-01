#pragma once

template <class T>
class AbstractActionListener
{
public:
    ~AbstractActionListener() = default;

    virtual AbstractActionListener<T> *create_sequence_dialog() = 0;
    virtual AbstractActionListener<T> *create_linked_list_sequence() = 0;
    virtual AbstractActionListener<T> *create_dynamic_array_sequence() = 0;
    virtual AbstractActionListener<T> *get_n_show_subsequence() = 0;
    virtual AbstractActionListener<T> *add_element_to_begin() = 0;
    virtual AbstractActionListener<T> *add_element_to_position() = 0;
    virtual AbstractActionListener<T> *add_element_to_end() = 0;
    virtual AbstractActionListener<T> *print_working_sequence() = 0;
    virtual AbstractActionListener<T> *concat_with_new_sequence() = 0;
};