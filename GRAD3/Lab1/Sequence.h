#pragma once
#include "smart_pointers/UniquePtr.hpp"

template <typename T>
class Sequence {
public:
    virtual void append(const T& item)  = 0;
    virtual void prepend(const T& item) = 0;
    virtual UniquePtr<Sequence<T>> get_subsequence(size_t startIndex, size_t endIndex) const  = 0;
    virtual void insert_at(const T& item, size_t index)  = 0;
    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(size_t index) const = 0;
    virtual size_t get_length() const = 0;
    virtual ~Sequence() = default;
};
