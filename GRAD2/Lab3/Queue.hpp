#pragma once
#include <functional>
#include <concepts>
#include "../Lab2/Sequence.h"
#include "../Lab2/LinkedListSequence.h"
#include "MWRAble.hpp"

template <class T, template <class> class Container = LinkedListSequence>
    requires std::derived_from<Container<T>, Sequence<T>>
class Queue : public MWRAble<T, T>
{
private:
    Container<T> container;

public:
    Queue() : container{Container<T>()} {}
    Queue(T items[], size_t size) : container{Container<T>(items, size)} {}
    Queue(const Queue<T, Container> &other) : container{other.container} {}

    ~Queue() = default;

    T &front()
    {
        return container.get_first();
    }
    T &back()
    {
        return container.get_last();
    }
    bool empty() const
    {
        return container.is_empty();
    }
    size_t size() const
    {
        return container.get_length();
    }

    void push(const T &value)
    {
        container.append(value);
    }
    void pop()
    {
        container.pop_front();
    }

    void concat(Queue<T, Container> other)
    {
        T temp;
        while (!other.empty())
        {
            temp = other.front();
            push(temp);
            other.pop();
        }
    }

    void map(std::function<T(T)> function) override
    {
        T temp;
        Container<T> new_container = Container<T>();
        while (!container.is_empty())
        {
            temp = front();
            new_container.append(function(temp));
            pop();
        }
        container = new_container;
    }

    void where(std::function<bool(T)> function) override
    {
        T temp;
        Container<T> new_container = Container<T>();
        while (!container.is_empty())
        {
            temp = front();
            if (function(temp))
                new_container.append(temp);
            pop();
        }
        container = new_container;
    }
    
    T reduce(std::function<T(T, T)> function, T start_value) override
    {
        T temp = start_value;
        while (!empty())
        {
            T frontValue = front(); // Получаем значение из front()**
            T func_res(function(frontValue, temp));
            temp = func_res;
            pop(); // Удаляем первый элемент
        }
        return temp;
    }
};