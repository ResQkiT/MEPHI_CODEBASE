#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"

template <typename T>
class QuickSorter : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override
    {
        quick_sort(begin, end, comp);
    }

    void quick_sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp)
    {
        if (begin + 1 == end)
        {
            return;
        }
        auto pivot = *(begin + (end - begin) / 2);
        auto left = begin;
        auto right = end - 1;
        while (left <= right)
        {
            while (comp(*left, pivot) < 0)
            {
                ++left;
            }
            while (comp(*right, pivot) > 0)
            {
                --right;
            }
            if (left <= right)
            {
                std::swap(*left, *right);
                ++left;
                --right;
            }
        }
        if (begin < right)
        {
            quick_sort(begin, right + 1, comp);
        }
        if (left < end)
        {
            quick_sort(left, end, comp);
        }
    }
};