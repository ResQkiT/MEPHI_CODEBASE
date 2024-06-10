#pragma once

template <class T>
concept Comparable = requires(T a, T b) {
    a < b;
    a > b;
};
