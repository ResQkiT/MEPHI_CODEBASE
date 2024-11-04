#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


/*
    Быстрая сортировка
    Принцип работы:
    1. Выбираем опорный элемент
    2. Разбиваем массив на две части, в одной все элементы меньше опорного, в другой больше
    3. Рекурсивно сортируем каждую часть
*/
template <class T>
class QuickSorter : public ISorter<T>
{
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override
    {
        quick_sort(begin, end, comp);
    }

private:
    void quick_sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> & comp)
    {
        if (begin + 1 >= end)
        {
            return;
        }
        auto pivot = *(begin + (end - begin) / 2);
        auto left = begin;
        auto right = end - 1;
        while (left <= right)
        {
            while (comp(*left, pivot))
            {
                ++left;
            }
            while (comp(pivot, *right))
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