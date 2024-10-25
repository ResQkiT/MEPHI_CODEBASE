#pragma once

template <typename T>
class UniquePtr
{
private:
    T *ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *p) : ptr(p) {}

    UniquePtr(UniquePtr &&other) noexcept : ptr(std::move(other.ptr))
    {
        other.ptr = nullptr;
    }

    ~UniquePtr()
    {
        delete ptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    T &operator*()
    {
        if (!ptr)
        {
            throw std::runtime_error("Trying to dereference a null UniquePtr");
        }
        return *ptr;
    }

    const T &operator*() const
    {
        if (!ptr)
        {
            throw std::runtime_error("Trying to dereference a null UniquePtr");
        }
        return *ptr;
    }

    T *operator->()
    {
        if (!ptr)
        {
            throw std::runtime_error("Trying to dereference a null UniquePtr");
        }
        return ptr;
    }

    const T *operator->() const
    {
        if (!ptr)
        {
            throw std::runtime_error("Trying to dereference a null UniquePtr");
        }
        return ptr;
    }

    T *get()
    {
        return ptr;
    }

    const T *get() const
    {
        return ptr;
    }

    void swap(UniquePtr &other) noexcept
    {
        std::swap(ptr, other.ptr);
    }
};
