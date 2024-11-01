#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/DynamicArray.h"

template<class T>
class InsertionSorter : public ISorter<T> {
public:
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override {
        for (auto i = begin + 1; i != end; ++i) {
            T key = *i;
            auto j = i - 1;
            while (j >= begin && comp(*j, key) > 0) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }
};
