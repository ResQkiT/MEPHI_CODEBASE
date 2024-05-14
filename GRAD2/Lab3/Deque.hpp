#pragma once
#include <functional>
#include <concepts>
#include "../Lab2/Sequence.h"
#include "../Lab2/DynamicArraySequence.h"
#include "MWRAble.hpp"

template <class T, template <class> class Container = DynamicArraySequence>
    requires std::derived_from<Container<T>, Sequence<T>>
class Deque : public MWRAble<T, T>
{
private:
    Container<T> container;

public:
    Deque() : container{Container<T>()} {};

    Deque(T data[], size_t size) : container{Container<T>(data, size)} {};

    Deque(const Deque<T, Container> &other) : container{other.container} {};

    ~Deque() = default;

    T &front()
    {
        return container.get_first();
    }
    T &back()
    {
        return container.get_last();
    }
    bool empty()
    {
        return container.is_empty();
    }
    size_t size()
    {
        return container.get_length();
    }
    void push_back(const T & value)
    {
        container.append(value);
    }
    void push_front(const T & value)
    {
        container.prepend(value);
    }
    void pop_back()
    {
        container.pop_back();
    }

    void pop_front()
    {
        container.pop_front();
    }

    T &operator[](size_t index)
    {
        return container.get(index);
    }

    void map(std::function<T(T)> function) override
    {
        T temp;
        Container<T> new_container = Container<T>();
        while (!container.is_empty())
        {
            temp = back();
            new_container.prepend(function(temp));
            pop_back();
        }
        container = new_container;
    }

    void where(std::function<bool(T)> function) override
    {
        T temp;
        Container<T> new_container = Container<T>();
        while (!container.is_empty())
        {
            temp = back();
            if (function(temp))
                new_container.prepend(temp);
            pop_back();
        }
        container = new_container;
    }

    T reduce(std::function<T(T, T)> function, T start_value) override
    {
        T temp = start_value;
        while (!empty())
        {
            T front_value = front();
            T func_res(function(front_value, temp));
            temp = func_res;
            pop_front();
        }
        return temp;
    }
};
