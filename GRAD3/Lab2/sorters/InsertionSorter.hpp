#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"
/*
    Сортировка вставками
    Принцип работы:
    1. Начиная со второго элемента массива, он сравнивается с предыдущими элементами
    2. Если он меньше предыдущего, то он сдвигается влево
    3. Повторяем для всех элементов
*/
template<class T, class Iterator = typename DynamicArray<T>::Iterator>
class InsertionSorter : public ISorter<T, Iterator> {
public:
    void sort(Iterator begin, Iterator end, typename ISorter<T, Iterator>::Comparator comp = std::less<T>()) override {
        for (auto i = begin + 1; i != end; ++i) {
            T key = *i;
            auto j = i;
            while (j != begin && comp(key, *(j - 1))) {
                *j = *(j - 1);
                --j;
            }
            *j = key;
        }
    }
};

