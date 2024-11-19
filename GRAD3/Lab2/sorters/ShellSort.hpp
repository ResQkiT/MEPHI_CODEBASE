#pragma once
#include <functional>
#include "../../../GRAD2/Lab2/DynamicArray.h"


/*
    Сортировка Шелла
    Принцип работы:
    1. Выбираем шаг h
    2. Сортируем массивы с шагом h
    3. Уменьшаем шаг и повторяем
*/
template<class T, class Iterator = typename DynamicArray<T>::Iterator>
class ShellSort : public ISorter<T>
{
public:
    void sort(Iterator begin, Iterator end, ISorter<T>::Comparator comp = std::less<T>()) override
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