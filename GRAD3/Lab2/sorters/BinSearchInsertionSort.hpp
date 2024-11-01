#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class BinSearchInsertionSort : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override
    {
        for (auto i = begin + 1; i != end; ++i)
        {
            T key = *i;
            auto j = i - 1;
            auto index = bin_search(begin, j, key, comp);
            while (j >= begin && comp(*j, key) > 0)
            {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }

    DynamicArray<T>::Iterator bin_search(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, T key, std::function<int(T, T)> comp)
    {
        auto left = begin;
        auto right = end;
        while (left < right)
        {
            auto mid = left + (right - left) / 2;
            if (comp(*mid, key) < 0)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return left;
    }
};