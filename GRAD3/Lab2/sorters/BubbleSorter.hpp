#pragma once

#include "ISorter.hpp"
#include "../../../GRAD2/Lab2/listimplementation.h"
#include <functional>


template<class T>
class BubbleSorter : public ISorter<T> {
public:
    BubbleSorter() = default;
    void sort(DynamicArray<T>::Iterator begin, DynamicArray<T>::Iterator end, std::function<bool(const T&, const T&)> comp = std::less<T>()) override {
        for (auto i = begin; i != end; ++i) {
            for (auto j = begin; j != end - 1; ++j) {
                if (comp(*(j+1), *j) > 0) {
                    std::swap(*j, *(j + 1));
                }
            }
        }
    }
};
