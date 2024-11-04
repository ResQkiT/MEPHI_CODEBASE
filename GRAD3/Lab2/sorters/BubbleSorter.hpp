#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/listimplementation.h"
#include <functional>

/*
    Сортировка пузырьком
    Принцип работы:
    1. Проходим по массиву и сравниваем соседние элементы
    2. Если они стоят в неправильном порядке, то меняем их местами
    3. Повторяем для всех элементов
*/
template<class T>
class BubbleSorter : public ISorter<T> {
public:
    BubbleSorter() = default;
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override {
        for (auto i = begin; i != end; ++i) {
            for (auto j = begin; j != end - 1; ++j) {
                if (comp(*(j+1), *j)) {
                    std::swap(*j, *(j + 1));
                }
            }
        }
    }
};
