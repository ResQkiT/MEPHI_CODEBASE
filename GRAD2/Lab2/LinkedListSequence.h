#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence<T>
{
private:
    LinkedList<T> impl;

    explicit LinkedListSequence(LinkedList<T> list) : impl{list} {}

public:
    explicit LinkedListSequence() : impl{LinkedList<T>()} {}

    explicit LinkedListSequence(T items[], size_t size) : impl{LinkedList(items, size)} {}

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

    LinkedListSequence<T> * get_subsequence(size_t startIndex, size_t endIndex) override
    {

        LinkedList<T> subsequence = LinkedList<T>();
        auto it_from = impl.begin();

        for (size_t i = 0; i < startIndex; i++, it_from++);
        for (size_t i = 0; i < endIndex - startIndex; i++, it_from++)
        {
            subsequence.push_back(*it_from);
        }
        return new LinkedListSequence(subsequence);
    }
    size_t get_length() const override
    {
        return impl.get_size();
    }
    void append(T item) override
    {
        impl.push_back(item);
    }
    void prepend(T item) override
    {
        impl.push_front(item);
    }
    void insert_at(size_t index, T item) override
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
    //спорное архитектурное решение
    typename LinkedList<T>::Iterator get_begin(){
        return impl.begin();
    }
    typename LinkedList<T>::Iterator get_end(){
        return impl.end();
    }
    //примечание, в случае если аргумент приводим к типу LinkedListSequence, 
    //то склеивание будет выполнено за O(1), иначе за O(n), где n - размерность аргумента 
    LinkedListSequence<T> *concat(Sequence<T> *list) override
    {
        
        LinkedListSequence<T> * itislinkedlist = dynamic_cast<LinkedListSequence<T>*>(list);
        if (itislinkedlist != nullptr)
        {
            impl += itislinkedlist->impl;
            return this;
        }
        
        // попробовать поиграть с динамическим приведением
        for (size_t i = 0; i < list->get_length(); i++)
        {
            append(list->get(i));
        }
        return this;
    }
    LinkedListSequence<T> operator+(const LinkedListSequence<T> &other) const
    {
        LinkedListSequence<T> newLinkedListSequence;
        newLinkedListSequence += *this;
        newLinkedListSequence += other;
        return newLinkedListSequence;
    }
    LinkedListSequence<T> &operator+=(const LinkedListSequence<T> &other)
    {
        impl += other.impl;
        return *this;
    }
};

