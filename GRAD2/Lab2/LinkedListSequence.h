#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> impl;

    LinkedListSequence(LinkedList<T> list) : impl{list} {}

public:
    LinkedListSequence() : impl{LinkedList<T>()} {}

    LinkedListSequence(T items[], size_t size) : impl{LinkedList(items, size)} {}

    T & get_first() override
    {
        return impl.front();
    }

    T & get_last() override
    {
        return impl.back();
    }

    T & get(size_t index) override
    {
        return impl.get(index);
    }
    LinkedListSequence<T> *get_subsequence(size_t start_index, size_t end_index) override
    {
        LinkedList<T> subsequence = LinkedList<T>();
        auto it_from = impl.begin();

        for (size_t i = 0; i < start_index; i++){
            it_from ++;
        }
        for (size_t i = 0; i < end_index - start_index + 1; i++, it_from++)
        {
            subsequence.push_back(*it_from);
        }
        return new LinkedListSequence<T>(subsequence);
    }

    size_t get_length() const override
    {
        return impl.get_size();
    }

    void append(const T & item) override
    {
        impl.push_back(item);
    }

    void prepend(const T & item) override
    {
        impl.push_front(item);
    }

    void pop_front() override
    {
        impl.pop_front();
    }

    void pop_back() override
    {
        impl.pop_back();
    }
    
    bool is_empty() const override{
        return impl.is_empty();
    }

    void insert_at(size_t index,const T & item) override
    {
        auto it = impl.begin();
        LinkedList<T> new_list;
        for (size_t i = 0; i < index; i++, it++)
        {
            new_list.push_back(*it);
        }

        new_list.push_back(item);

        for (size_t i = index; i < impl.get_size(); i++, it++)
        {
            new_list.push_back(*it);
        }
        impl = new_list;
    }

    typename LinkedList<T>::Iterator get_begin()
    {
        return impl.begin();
    }

    typename LinkedList<T>::Iterator get_end()
    {
        return impl.end();
    }

    LinkedListSequence<T> operator+(const LinkedListSequence<T> &other) const
    {
        LinkedListSequence<T> newLinkedListSequence;
        newLinkedListSequence += *this;
        newLinkedListSequence += other;
        return newLinkedListSequence;
    }

    LinkedListSequence<T> &operator+=(LinkedListSequence<T> &other)
    {
        return concat(other);
    }
    
    LinkedListSequence<T> &operator=(const LinkedListSequence<T> & other){
        impl = other.impl;
        return *this;
    }
};
