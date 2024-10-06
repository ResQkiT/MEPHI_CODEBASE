#pragma once

template <typename T>
class WeekPtr;

template <typename T>
class SharedPtr {
private:
    struct RefCounter {
        size_t count;
        RefCounter() : count(1) {}
    };

    T* ptr;
    RefCounter* refCounter;

public:
    SharedPtr() : ptr(nullptr), refCounter(nullptr) {}

    explicit SharedPtr(T* p) : ptr(p), refCounter(p ? new RefCounter() : nullptr) {}

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCounter(other.refCounter) {
        if (refCounter) {
            ++refCounter->count;
        }
    }

    SharedPtr(const WeekPtr<T>& other) : ptr(other.ptr), refCounter(other.refCounter) {
        if (refCounter) {
            ++refCounter->count;
        }
    }

    SharedPtr(SharedPtr&& other) : ptr(other.ptr), refCounter(other.refCounter) {
        other.ptr = nullptr;
        other.refCounter = nullptr;
    }

    ~SharedPtr() {
        if (refCounter && --refCounter->count == 0) {
            delete ptr;
            delete refCounter;
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other) {
            return *this;
        }
        if (refCounter && --refCounter->count == 0) {
            delete ptr;
            delete refCounter;
        }
        ptr = other.ptr;
        refCounter = other.refCounter;
        if (refCounter) {
            ++refCounter->count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            if (refCounter && --refCounter->count == 0) {
                delete ptr;
                delete refCounter;
            }
            ptr = other.ptr;
            refCounter = other.refCounter;
            other.ptr = nullptr;
            other.refCounter = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    
    T* operator->() const { return ptr; }
    
    T* get() const { return ptr; }

    bool operator!() const {
        return ptr == nullptr;
    }
    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    void reset() {
        if (refCounter && --refCounter->count == 0) {
            delete ptr;
            delete refCounter;
        }
        ptr = nullptr;
        refCounter = nullptr;
    }

    void reset(T* newPtr) {
        if (refCounter && --refCounter->count == 0) {
            delete ptr;
            delete refCounter;
        }
        ptr = newPtr;
        refCounter = newPtr ? new RefCounter() : nullptr;
    }

    RefCounter* get_ref_counter() const { return refCounter; }

    size_t get_ref_count() const {
        return refCounter ? refCounter->count : static_cast<size_t>(0);
    }

    operator bool() const {
        return ptr != nullptr;
    }

    friend class WeekPtr<T>;
};

