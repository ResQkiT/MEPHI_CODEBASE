#pragma once
#include "WeakPtr.hpp"
#include "iostream"

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
private:
    struct RefCounter {
        size_t shared_count;
        size_t weak_count;
        RefCounter() : shared_count(1) , weak_count(0) {}

        size_t use_count(){
            return shared_count;
        }
    };

    T* ptr;
    RefCounter* ref_counter;

    bool deleteCounterIfValid(){
        if (ref_counter && --ref_counter->shared_count == 0) {
            delete ptr;

            return true;
        }
        return false;
    } 

public:

    SharedPtr() : ptr(nullptr), ref_counter(nullptr) {}

    explicit SharedPtr(T* p) : ptr(p), ref_counter(p ? new RefCounter() : nullptr) {}

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_counter(other.ref_counter) {
        if (ref_counter) {
            ++ref_counter->shared_count;
        }
    }

    SharedPtr(const WeakPtr<T>& other) : ptr(other.ptr), ref_counter(other.ref_counter) {
        if (ref_counter) {
            ++ref_counter->shared_count;
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), ref_counter(other.ref_counter) {
        other.ptr = nullptr;
        other.ref_counter = nullptr;
    }

    ~SharedPtr() {
        deleteCounterIfValid();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other) {
            return *this;
        }
        
        deleteCounterIfValid();

        ptr = other.ptr;
        ref_counter = other.ref_counter;
        if (ref_counter) {
            ++ref_counter->shared_count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            deleteCounterIfValid();

            ptr = other.ptr;
            ref_counter = other.ref_counter;
            other.ptr = nullptr;
            other.ref_counter = nullptr;
        }
        return *this;
    }

    T& operator*() {
        if (!ptr) {
            throw std::runtime_error("Trying to dereference a null ShrdPtr");
        }
        return *ptr;
    }

    const T& operator*() const {
        if (!ptr) {
            throw std::runtime_error("Trying to dereference a null ShrdPtr");
        }
        return *ptr;
    }

    T* operator->() {
        if (!ptr) {
            throw std::runtime_error("Trying to dereference a null ShrdPtr");
        }
        return ptr;
    }

    const T* operator->() const {
        if (!ptr) {
            throw std::runtime_error("Trying to dereference a null ShrdPtr");
        }
        return ptr;
    }

    T* get() const {
        return ptr;
    }
    
    bool operator!() const {
        return ptr == nullptr;
    }
    
    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    void reset() {
        deleteCounterIfValid();

        ptr = nullptr;
        ref_counter = nullptr;
    }

    void reset(T* newPtr) {
        deleteCounterIfValid();
        ptr = newPtr;
        ref_counter = newPtr ? new RefCounter() : nullptr;
    }

    RefCounter* get_ref_counter() const { return ref_counter; }

    size_t use_count() const {
        return ref_counter ? ref_counter->shared_count : static_cast<size_t>(0);
    }

    operator bool() const {
        return ptr != nullptr;
    }

    friend class WeakPtr<T>;
};

