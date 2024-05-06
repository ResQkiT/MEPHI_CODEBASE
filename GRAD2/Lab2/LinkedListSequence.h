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

    LinkedListSequence<T> *get_subsequence(size_t start_index, size_t end_index) override
    {
        LinkedList<T> subsequence = LinkedList<T>();
        auto it_from = impl.begin();

        for (size_t i = 0; i < start_index; i++, it_from++);
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

    typename LinkedList<T>::Iterator get_begin()
    {
        return impl.begin();
    }

    typename LinkedList<T>::Iterator get_end()
    {
        return impl.end();
    }

    /// @brief Добавление любых Sequence за O(n)
    /// @param list - абстрактная последовательность
    /// @return возвращает измененный this
    LinkedListSequence<T> *concat(Sequence<T> *list) override
    {
        for (size_t i = 0; i < list->get_length(); i++)
        {
            append(list->get(i));
        }
        return this;
    }

    ///@brief склеивание будет выполнено за O(1) где n - размерность аргумента
    /// @attention состояние list после выполнения - неопределено!
    LinkedListSequence<T> &append(LinkedListSequence<T> &list) override
    {
        impl += list.impl;
        return *this;
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
        impl += other.impl;
        return *this;
    }
};
