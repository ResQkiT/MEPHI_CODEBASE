#pragma once
#include <cstddef>
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class DynamicArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> impl; 

    DynamicArraySequence(DynamicArray<T> array) : impl{array} {}

public:

    DynamicArraySequence() : impl{DynamicArray<T>()} {}

    DynamicArraySequence(T items[], size_t size) : impl{DynamicArray<T>(items, size)} {}

    T& get_first() override
    {
        return (impl)[0];
    }

    T& get_last() override
    {
        return impl[impl.get_size() - 1];
    }

    T& get(size_t index) override
    {
        return impl[index];
    }

    const T& get(size_t index) const{
        return impl[index];
    }

    DynamicArraySequence<T> *get_subsequence(size_t startIndex, size_t endIndex) override
    {
        if(startIndex > endIndex || startIndex <0 || endIndex >=impl.get_size()) throw std::invalid_argument("invalid arguments");
        DynamicArray<T> subsequenceArray = DynamicArray<T>(endIndex - startIndex + 1);

        auto cur_it = impl.begin() + startIndex;
        auto new_it = subsequenceArray.begin();

        for (; new_it != subsequenceArray.end(); cur_it++, new_it++)
        {
            *new_it = *cur_it;
        }

        return new DynamicArraySequence(subsequenceArray);
    }

    void add_from(DynamicArray<T> array)
    {
        auto it = array.begin();
        for (; it != array.end(); it++)
        {
            impl.push_back(*it);
        }
    }

    size_t get_length() const override
    {
        return impl.get_size();
    }

    bool is_empty() const override{
        return impl.get_size() == 0;
    }

    void append(const T & item) override
    {
        impl.push_back(item);
    }

    void prepend(const T & item) override
    {
        DynamicArray<T> new_array;
        new_array.push_back(item);

        for (size_t i = 0; i < impl.get_size(); i++)
        {
            new_array.push_back(impl[i]);
        }
        impl = new_array;
    }

    void pop_front(){
        if(impl.get_size()==0) throw std::invalid_argument("Array is empty");
        DynamicArray<T> new_impl = DynamicArray<T>();
        for (size_t i = 1; i < impl.get_size(); i++)
        {
            new_impl.push_back(impl[i]);
        }
        
        impl = new_impl;
    }   

    void pop_back(){
        impl.pop_back();
    }

    void insert_at(size_t index,const T & item) override
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
        // alert двойное копирование
        impl = new_array;
    }

    typename DynamicArray<T>::Iterator get_begin()
    {
        return impl.begin();
    }

    typename DynamicArray<T>::Iterator get_end()
    {
        return impl.end();
    }


    DynamicArraySequence<T> operator+(const DynamicArraySequence<T> &other) const
    {
        DynamicArraySequence<T> newDynamicArraySequence;

        newDynamicArraySequence += (*this);
        newDynamicArraySequence += (other);

        return newDynamicArraySequence;
    }

    DynamicArraySequence<T> &operator+=(const DynamicArraySequence<T> &other)
    {
        impl += other.impl;
        return *this;
    }
    
    DynamicArraySequence<T> &operator=(const DynamicArraySequence<T> &other)
    {
        impl = other.impl;
        return *this;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &os, const DynamicArraySequence<T> &array)
{
    for (size_t i = 0; i < array.get_length(); i++)
    {
        os << array.get(i) << " ";
    }
    os << std::endl;
    return os;
}