#pragma once
#include "SharedPtr.hpp"

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr
{
private:
    T *ptr;
    typename SharedPtr<T>::RefCounter *ref_counter;

    void deleteIfLast()
    {
        if (ref_counter)
        {
            ref_counter->weak_count--;
        }

        if (ref_counter && ref_counter->shared_count == 0 && ref_counter->weak_count == 0)
        {
            delete ref_counter;
        }
    }

public:
    WeakPtr() : ptr(nullptr), ref_counter(nullptr) {}

    WeakPtr(const SharedPtr<T> &other) : ptr(other.ptr), ref_counter(other.ref_counter)
    {
        if (ref_counter)
        {
            ref_counter->weak_count++;
        }
    }

    WeakPtr(const WeakPtr<T> &other) : ptr(other.ptr), ref_counter(other.ref_counter)
    {
        if (ref_counter)
        {
            ref_counter->weak_count++;
        }
    }

    WeakPtr(WeakPtr<T> &&other) noexcept : ptr(other.ptr), ref_counter(other.ref_counter)
    {
        other.ptr = nullptr;
        other.ref_counter = nullptr;
    }

    WeakPtr<T> &operator=(const WeakPtr<T> &other)
    {
        if (this != &other)
        {
            if (ref_counter)
            {
                ref_counter->weak_count--;
                deleteIfLast();
            }

            ptr = other.ptr;
            ref_counter = other.ref_counter;

            if (ref_counter)
            {
                ref_counter->weak_count++;
            }
        }
        return *this;
    }

    WeakPtr<T> &operator=(WeakPtr<T> &&other) noexcept
    {
        if (this != &other)
        {
            if (ref_counter)
            {
                ref_counter->weak_count--;
                deleteIfLast();
            }

            ptr = std::move(other.ptr);
            ref_counter = std::move(other.ref_counter);

            if (ref_counter)
            {
                ref_counter->weak_count++;
            }
        }
        return *this;
    }

    ~WeakPtr()
    {
        deleteIfLast();
    }

    size_t use_count() const
    {
        return ref_counter ? ref_counter->shared_count : static_cast<size_t>(0);
    }

    bool expired() const
    {
        return use_count() == 0;
    }

    SharedPtr<T> lock() const
    {
        return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }

    friend class SharedPtr<T>;
};
