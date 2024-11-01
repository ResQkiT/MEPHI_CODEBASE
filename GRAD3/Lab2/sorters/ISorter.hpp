#pragma once

#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class ISorter
{
public:
    std::function<int(T, T)> DIRECT = [](T a, T b) { return a - b; };
    std::function<int(T, T)> REVERSE = [](T a, T b) { return b - a; };

    virtual ~ISorter() = default;
    
    virtual void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) = 0;
};