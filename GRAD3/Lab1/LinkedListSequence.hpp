#pragma once

#include "iostream"
#include "Sequence.h"
#include "LinkedList.hpp"
#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"

template <typename T>
class LinkedListSequence : public Sequence<T>
{
private:
    UniquePtr<LinkedList<T>> list;

    explicit LinkedListSequence(UniquePtr<LinkedList<T>> &&other)
        : list(std::move(other))
    {
    }

public:
    LinkedListSequence() : list{new LinkedList<T>()} {}

    LinkedListSequence(const T *items, size_t count) : list{new LinkedList<T>(items, count)} {}

    LinkedListSequence(const LinkedListSequence<T> &listSequence) : list{new LinkedList<T>(*listSequence.list)} {}

    LinkedListSequence(LinkedListSequence<T> &&other) : list{std::move(other.list)}
    {
        other.list = nullptr;
    }

    LinkedListSequence(const LinkedList<T> &otherList) : list{new LinkedList<T>(otherList)} {}

    ~LinkedListSequence() override = default;

    void append(const T &item) override
    {
        list->push_back(item);
    }

    void prepend(const T &item) override
    {
        list->push_front(item);
    }

    UniquePtr<Sequence<T>> get_subsequence(size_t startIndex, size_t endIndex) const override
    {
        if (
            startIndex >= list->size() || endIndex >= list->size() ||
            startIndex > endIndex)
        {
            throw std::out_of_range("Invalid index range for get_subsequence");
        }

        UniquePtr<LinkedList<T>> subList = list->get_sublist(startIndex, endIndex);
        return UniquePtr<Sequence<T>>(new LinkedListSequence<T>(std::move(subList)));
    }

    void insert_at(const T &item, size_t index) override
    {
        list->insert_at(item, index);
    }

    T get_first() const override
    {
        if (list->size() == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        return list->front();
    }

    T get_last() const override
    {
        if (list->size() == 0)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        return list->back();
    }

    T get(size_t index) const override
    {
        if (list->size() <= index)
        {
            throw std::out_of_range("IndexOutOfRange");
        }
        return list->get(index);
    }

    size_t get_length() const override
    {
        return list->size();
    }

    void pop_front(){
        list->pop_front();
    }
};