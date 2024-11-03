#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <class T>
class MergeSorter : public ISorter<T>
{
private:
    void merge(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator middle, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>())
    {
        DynamicArray<T> left(middle - begin);
        DynamicArray<T> right(end - middle);
        std::copy(begin, middle, left.begin());
        std::copy(middle, end, right.begin());
        auto left_iter = left.begin();
        auto right_iter = right.begin();
        auto current = begin;
        while (left_iter != left.end() && right_iter != right.end())
        {
            if (comp(*left_iter, *right_iter) < 0)
            {
                *current = *left_iter;
                ++left_iter;
            }
            else
            {
                *current = *right_iter;
                ++right_iter;
            }
            ++current;
        }
        while (left_iter != left.end())
        {
            *current = *left_iter;
            ++left_iter;
            ++current;
        }
        while (right_iter != right.end())
        {
            *current = *right_iter;
            ++right_iter;
            ++current;
        }
    }

public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override
    {
        if (begin + 1 == end)
        {
            return;
        }
        auto middle = begin + (end - begin) / 2;
        sort(begin, middle, comp);
        sort(middle, end, comp);
        merge(begin, middle, end, comp);
    }
};
