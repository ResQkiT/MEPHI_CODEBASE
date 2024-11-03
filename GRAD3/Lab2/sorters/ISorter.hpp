#pragma once

#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


template <class T> 
class ISorter
{
public:
    virtual ~ISorter() = default;
    virtual void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) = 0;
};;