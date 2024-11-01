#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class ShellSort : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override
    {
        for (auto gap = (end - begin) / 2; gap > 0; gap /= 2)
        {
            for (auto i = begin + gap; i != end; ++i)
            {
                auto temp = *i;
                auto j = i;
                for (; j >= begin + gap && comp(*(j - gap), temp) > 0; j -= gap)
                {
                    *j = *(j - gap);
                }
                *j = temp;
            }
        }
    }
};