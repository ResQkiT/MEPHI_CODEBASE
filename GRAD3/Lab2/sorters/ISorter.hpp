#pragma once

#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


template <class T> 
class ISorter
{
public:
    using Comparator = std::function<bool(const T&, const T&)>;
    using Iterator = DynamicArray<T>::Iterator;

    virtual ~ISorter() = default;

    virtual void sort(Iterator begin, Iterator end, Comparator comp = std::less<T>()) = 0;
};
