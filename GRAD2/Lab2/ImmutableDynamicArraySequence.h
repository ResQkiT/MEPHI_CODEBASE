#pragma once
#include "ImmutableSequence.h"
#include "DynamicArray.h"

/// @brief math-liked implementation of Dynamic Sequence
/// @tparam T - type of collection
template <class T>
class ImmutableDynamicArraySequence : public ImmutableSequence<T>
{
private:
    DynamicArray<T> impl;
    ImmutableDynamicArraySequence(DynamicArray<T> & list) : impl{list} {}

public:
    ImmutableDynamicArraySequence() {}
    ImmutableDynamicArraySequence(T items[], size_t size) {}
    T get_first() const override
    {
        return (impl)[0];
    }

    T get_last() const override
    {
        return impl[impl.get_size() - 1];
    }

    T get(size_t index) override
    {
        return impl[index];
    }

    DynamicArraySequence<T> *get_subsequence(size_t startIndex, size_t endIndex) override
    {
        DynamicArray<T> subsequenceArray = DynamicArray<T>(endIndex - startIndex + 1);

        auto cur_it = impl.begin() + startIndex;
        auto new_it = subsequenceArray.begin();

        for (; new_it != subsequenceArray.end(); cur_it++, new_it++)
        {
            *new_it = *cur_it;
        }

        return new DynamicArraySequence(subsequenceArray);
    }

    size_t get_length() const override
    {
        return impl.get_size();
    }

    ImmutableDynamicArraySequence<T> *append(T item) override
    {
        DynamicArray<T> newDArray(impl);
        newDArray.push_back(item);
        return new ImmutableDynamicArraySequence<T>(newDArray);
    }
    ImmutableDynamicArraySequence<T> * prepend(T item) override
    {
        DynamicArray<T> newDArray;
        newDArray.push_back(item);
        for (size_t i = 0; i < impl.get_size(); i++)
        {
            newDArray.push_back(impl[i]);
        }
        
        return ImmutableDynamicArraySequence<T>(newDArray);
    }
    ImmutableDynamicArraySequence<T> * insert_at(size_t index, T item) override
    {
        DynamicArray<T> new_array;
        for (size_t i = 0; i < index; i++)
        {
            new_array.push_back(impl[i]);
        }

        new_array.push_back(item);

        for (size_t i = index; i < impl.get_size(); i++)
        {
            new_array.push_back(impl[i]);
        }
        return new ImmutableDynamicArraySequence<T>(new_array);
    }

    ImmutableDynamicArraySequence<T> * concat(ImmutableSequence<T> *list) override
    {
        
        for (size_t i = 0; i < list->get_length(); i++)
        {
            append(list->get(i));
        }
        return this;
    }

};