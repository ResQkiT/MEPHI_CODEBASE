#pragma once

#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


template <class T, class Iterator = typename DynamicArray<T>::Iterator>
class ISorter
{
public:
    using Comparator = std::function<bool(const T&, const T&)>;

    virtual ~ISorter() = default;

    virtual void sort(Iterator begin, Iterator end, Comparator comp = std::less<T>()) = 0;
};
