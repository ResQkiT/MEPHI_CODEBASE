#pragma once

#include "SharedPtr.hpp"

template <typename T>
class WeekPtr {
private:
    T* ptr;
    typename SharedPtr<T>::RefCounter* refCounter;

public:
    WeekPtr() : ptr(nullptr), refCounter(nullptr) {}

    WeekPtr(const SharedPtr<T>& other) : ptr(other.get()), refCounter(other.get_ref_counter()) {}

    WeekPtr(const WeekPtr& other) = default;
    WeekPtr& operator=(const WeekPtr& other) = default;

    WeekPtr(WeekPtr&& other) noexcept = default;
    WeekPtr& operator=(WeekPtr&& other) noexcept = default;

    ~WeekPtr() = default;

    T* operator->() const {
        if (expired()) {
            throw std::runtime_error("Trying to dereference expired WeekPtr");
        }
        return ptr;
    }

    T& operator*() const {
        if (expired()) {
            throw std::runtime_error("Trying to dereference expired WeekPtr");
        }
        return *ptr;
    }

    bool expired() const { return !refCounter || refCounter->count == 0; }

    SharedPtr<T> lock() const {
        if (expired()) {
            return SharedPtr<T>();
        } else {
            SharedPtr<T> newSharedPtr(ptr);
            newSharedPtr.refCounter = refCounter;
            newSharedPtr.refCounter->count.fetch_add(1, std::memory_order_relaxed); 
            return newSharedPtr;
        }
    }

    friend class SharedPtr<T>;
};
