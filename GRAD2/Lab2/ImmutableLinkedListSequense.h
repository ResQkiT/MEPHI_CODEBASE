#pragma once
#include "ImmutableSequence.h"
#include "LinkedList.h"

/// @brief math-liked implementation of Linked Sequence
/// @tparam T - type of collection
template<class T>
class ImmutableLinkedListSequence : public ImmutableSequence<T>{
private:

    LinkedList<T> impl;

    ImmutableLinkedListSequence(LinkedList<T> & list) : impl{list}{}

public:

    ImmutableLinkedListSequence(): impl{LinkedList<T>()}{}

    ImmutableLinkedListSequence(T items[], size_t size): impl{LinkedList<T>(items, size)} {}

    T get_first() const override
    {
        return impl.front();
    }
    
    T get_last() const override
    {
        return impl.back();
    }

    T get(size_t index) override
    {
        return impl.get(index);
    }

    ImmutableLinkedListSequence<T> * get_subsequence(size_t start_index, size_t end_index) override
    {
        LinkedList<T> subsequence = LinkedList<T>();
        auto it_from = impl.begin();

        for (size_t i = 0; i < start_index; i++){
            it_from ++;
        }
        for (size_t i = 0; i < end_index - start_index; i++, it_from++)
        {
            subsequence.push_back(*it_from);
        }
        return new ImmutableLinkedListSequence<T>(subsequence);
    }

    size_t get_length() const override
    {
        return impl.get_size();
    }

    ImmutableLinkedListSequence<T> * append(T item) override
    {
        LinkedList<T> new_list(impl); 
        new_list.push_back(item);
        return new ImmutableLinkedListSequence<T>(new_list);
    }

    ImmutableLinkedListSequence<T> * prepend(T item) override
    {
        LinkedList<T> new_list(impl); 
        new_list.push_front(item);
        return new ImmutableLinkedListSequence<T>(new_list);
    }

    ImmutableLinkedListSequence<T> * insert_at(size_t index, T item) override
    {
        LinkedList<T> new_list;

        for (size_t i = 0; i < index; i++)
        {
            new_list.push_back(impl.get(i));
        }
        
        new_list.push_back(item);
        
        for (size_t i = index; i < impl.get_size(); i++)
        {
            new_list.push_back(impl.get(i));
        }

        return new ImmutableLinkedListSequence<T>(new_list);
    }
    ImmutableLinkedListSequence<T> * concat(ImmutableSequence<T> * list) override
    {
        LinkedList<T> new_list(impl);
        for (size_t i = 0; i < new_list.get_size(); i++)
        {
            new_list.push_back(list->get(i));
        }

        return new ImmutableLinkedListSequence<T>(new_list);
    }
};