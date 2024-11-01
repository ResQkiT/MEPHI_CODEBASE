#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/listimplementation.h"
#include <functional>


template<class T>
class BubbleSorter : public ISorter<T> {
public:
    BubbleSorter() = default;
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<int(T, T)> comp) override {
        for (auto i = begin; i != end; ++i) {
            for (auto j = begin; j != end - 1; ++j) {
                if (comp(*j, *(j + 1)) > 0) {
                    std::swap(*j, *(j + 1));
                }
            }
        }
    }
};
