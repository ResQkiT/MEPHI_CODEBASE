#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <class T>
class ShellSort : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override
    {
        for (auto gap = (end - begin) / 2; gap > 0; gap /= 2)
        {
            for (auto i = begin + gap; i != end; ++i)
            {
                auto temp = *i;
                auto j = i;
                while (j >= begin + gap && comp(temp, *(j - gap)))
                {
                    *j = *(j - gap);
                    j -= gap;
                }
                *j = temp;
            }
        }
    }
};