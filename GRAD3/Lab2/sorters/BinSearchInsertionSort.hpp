#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"
#include <functional>

/*
    Сортировка вставками с бинарным поиском
    Принцип работы:
    1. Начиная со второго элемента массива, он сравнивается с предыдущими элементами
    2. Если он меньше предыдущего, то он сдвигается влево на позицию определяемую бинарным поиском
    3. Повторяем для всех элементов
*/
template <class T>
class BinSearchInsertionSort : public ISorter<T> {

private:
     ISorter<T>::Iterator bin_search( ISorter<T>::Iterator begin,  ISorter<T>::Iterator end, const T& key, ISorter<T>::Comparator comp) {
        auto left = begin;
        auto right = end;
        while (left < right) {
            auto mid = left + (right - left) / 2;
            if (comp(*mid, key)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
    
public:
    void sort( ISorter<T>::Iterator begin,  ISorter<T>::Iterator end, ISorter<T>::Comparator comp = std::less<T>()) override {
        for (auto i = begin + 1; i != end; ++i) {
            T key = *i;
            auto index = bin_search(begin, i, key, comp);
            for (auto j = i; j > index; --j) {
                *j = *(j - 1);
            }
            *index = key;
        }
    }

};
