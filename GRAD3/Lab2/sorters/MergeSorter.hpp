#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


/*
    Сортировка слиянием
    Принцип работы:
    1. Разбиваем массив на две части
    2. Рекурсивно сортируем каждую часть
    3. Сливаем два отсортированных массива
*/
template<class T, class Iterator = typename DynamicArray<T>::Iterator>
class MergeSorter : public ISorter<T, Iterator>
{
private:
    void merge(Iterator begin, Iterator middle, Iterator end, typename ISorter<T, Iterator>::Comparator comp = std::less<T>())
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
            if (comp(*left_iter, *right_iter))
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
    void sort(Iterator begin, Iterator end, typename ISorter<T, Iterator>::Comparator comp = std::less<T>()) override
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
