#pragma once
#include <functional>
#include <concepts>
#include "../Lab2/Sequence.h"
#include "../Lab2/LinkedListSequence.h"
#include "MWRAble.hpp"

template <class T, template <class> class Container = LinkedListSequence>
    requires std::derived_from<Container<T>, Sequence<T>>
class Stack : public MWRAble<T, T>
{
private:
    Container<T> container;

public:
    Stack() : container{Container<T>()} {}
    Stack(T data[], size_t size) : container{Container<T>(data, size)} {}
    Stack(const Stack<T, Container> &other) : container{other.container} {}
    ~Stack() = default;

    T& top()
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
        container.pop_back();
    }
    void map(std::function<T(T)> function) override
    {
        T temp;
        Container<T> new_container = Container<T>();
        while (!container.is_empty())
        {
            temp = top();
            new_container.prepend(function(temp));
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
            temp = top();
            if (function(temp))
                new_container.prepend(temp);
            pop();
        }
        container = new_container;
    }
    T reduce(std::function<T(T, T)> function, T start_value) override
    {
        T temp = start_value ;
        while (!empty())
        {
            T front_value = top();
            T func_res(function(front_value, temp));
            temp = func_res;
            pop();
        }
        return temp;
    }
    Stack<T, Container> & operator=(const Stack<T, Container> & other){
        this->container = other.container;
        return *this;
    }
};