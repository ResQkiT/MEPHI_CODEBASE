#pragma once

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T* p) : ptr(p) {}

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }
};
