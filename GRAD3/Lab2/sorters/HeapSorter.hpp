#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"

/*
    Пирамидальная сортировка
    Принцип работы:
    1. Строим пирамиду
    2. Первый элемент - максимальный, меняем его с последним
    3. Перестраиваем пирамиду
*/
template<class T, class Iterator = typename DynamicArray<T>::Iterator>
class HeapSorter : public ISorter<T, Iterator> {
public:
    void sort(Iterator begin, Iterator end, typename ISorter<T, Iterator>::Comparator comp = std::less<T>()) override {
        DynamicArray<T> array;
        std::copy(begin, end, std::back_inserter(array));

        int n = array.get_size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(array, n, i, comp);

        for (int i = n - 1; i > 0; i--) {
            std::swap(array[0], array[i]);
            heapify(array, i, 0, comp);
        }

        std::copy(array.begin(), array.end(), begin);
    }

private:
    void heapify(DynamicArray<T>& array, int n, int i, typename ISorter<T, Iterator>::Comparator comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comp(array[largest], array[left]))
            largest = left;

        if (right < n && comp(array[largest], array[right]))
            largest = right;

        if (largest != i) {
            std::swap(array[i], array[largest]);
            heapify(array, n, largest, comp);
        }
    }
};
