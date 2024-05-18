#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include "Deque.hpp"
#include "../Lab2/Sequence.h"
#include "../Lab2/LinkedListSequence.h"

template <class T>
class SegmentedDeque
{
private:
    Deque<DynamicArraySequence<T>> buffer;
    size_t segment_size;

public:
    SegmentedDeque() : buffer{Deque<DynamicArraySequence<T>>()}, segment_size{5}{
        buffer.push_back(DynamicArraySequence<T>());
    };
    SegmentedDeque(size_t segment_size) : buffer{Deque<DynamicArraySequence<T>>()}, segment_size{segment_size}
    {
        buffer.push_back(DynamicArraySequence<T>());
    }
    SegmentedDeque(T data[], size_t size, size_t segment_size) : buffer{Deque<DynamicArraySequence<T>>()}, segment_size{segment_size}
    {
        buffer.push_back(DynamicArraySequence<T>());
        for (size_t i = 0; i < size; i++)
        {
            push_back(data[i]);
        }
    }
    SegmentedDeque(SegmentedDeque<T> &other) : buffer{Deque<DynamicArraySequence<T>>()}, segment_size{other.segment_size}
    {
        for (size_t i = 0; i < other.number_of_segments(); i++)
        {
            buffer.push_back(DynamicArraySequence<T>(other.buffer[i]));
        }
    }

    void push_back(const T &value)
    {
        if (buffer.back().get_length() < segment_size)
        {
            buffer.back().append(value);
        }
        else
        {
            DynamicArraySequence<T> container;
            container.append(value);
            buffer.push_back(container);
        }
    }

    void push_front(const T &value)
    {
        if (buffer.front().get_length() < segment_size)
        {
            buffer.front().prepend(value);
        }
        else
        {
            DynamicArraySequence<T> container = DynamicArraySequence<T>(new T[]{value}, 1);
            buffer.push_front(container);
        }
    }
    size_t get_segment_size() const
    {
        return segment_size;
    }
    size_t number_of_segments() const
    {
        return buffer.size();
    }
    bool empty() const{
        return buffer.empty();
    }
    T &back()
    {
        if (buffer.empty())
        {
            throw std::out_of_range("SegmentedDeque is empty");
        }
        return buffer.back().get_last();
    }
    T &front()
    {
        if (buffer.empty())
        {
            throw std::out_of_range("SegmentedDeque is empty");
        }
        return buffer.front().get_first();
    }
    T &get(size_t index)
    {
        return buffer[index / segment_size].get(index % segment_size);
    }
    T &operator[](size_t index)
    {
        return get(index);
    }
 
    size_t size() const
    {
        size_t size = 0;
        for (size_t i = 0; i < number_of_segments(); i++)
        {
            size += buffer[i].get_length();
        }
        return size;
    }
    void clear()
    {
        size_t c_size = size();
        for (size_t i = 0; i < c_size; i++)
        {
            pop_back();
        }
    }
    SegmentedDeque &operator=(SegmentedDeque<T> &other)
    {
        buffer = other.buffer;
        return *this;
    }

    T &pop_back()
    {
        if (buffer.empty())
        {
            throw std::out_of_range("SegmentedDeque is empty");
        }

        T &value = buffer.back().get_last();
        buffer.back().pop_back();
        if (buffer.back().is_empty())
        {
            buffer.pop_back();
        }
        return value;
    }

    T &pop_front()
    {
        if (buffer.empty())
        {
            throw std::out_of_range("SegmentedDeque is empty");
        }

        T &value = buffer.front().get_first();
        buffer.front().pop_front();
        if (buffer.front().is_empty())
        {
            buffer.pop_front();
        }
        return value;
    }
    void append_from(SegmentedDeque<T> &other)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            push_back(other[i]);
        }
    }
};