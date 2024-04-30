#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicArray
{
private:
    T *data;
    size_t size;
    size_t capacity;

    void reallocate(size_t new_capacity)
    {
        if (new_capacity == 0)
        {
            delete[] data;
            data = nullptr;
            size = 0;
            capacity = 0;
            return;
        }

        T *new_data = new T[new_capacity];

        if (data)
        {
            std::copy(data, data + size, new_data);
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray() : data{nullptr}, size{0}, capacity{4}
    {
        this->data = new T[this->capacity];
    }

    DynamicArray(size_t size) : size{size}, capacity{2 * size}
    {
        if(size < 0) throw std::invalid_argument("Cannot create DynamicArray with negative size");
        this->data = new T[capacity];
    }

    DynamicArray(const T *data, size_t size) : size{size}, capacity{2 * size}
    {
        if(size < 0) throw std::invalid_argument("Cannot create DynamicArray with negative size");
        if(data == nullptr) throw std::invalid_argument("DynamicArray constructor must take not null arguments");
        this->data = new T[capacity];
        std::copy(data, data + size, this->data);
    }

    DynamicArray(const DynamicArray<T> &other) : size{other.size}, capacity{other.capacity}
    {
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }

    DynamicArray(DynamicArray<T> &&other) : size{std::move(other.size)}, capacity{std::move(other.capacity)}
    {
        this->data = std::move(other.data);
        other.capacity = 0;
        other.size = 0;
        other.data = nullptr;
    }

    ~DynamicArray()
    {
        if (data)
        {
            delete[] data;
        }
    }

    T &get(size_t index) const
    {
        if(index < 0 || index >= size) throw std::out_of_range("Out of range");
        return *(data + index);
    }

    void set(size_t index, const T &value)
    {
        if(index < 0 || index >= size) throw std::out_of_range("Out of range");
        *(data + index) = value;
    }

    void resize(size_t new_size)
    {
        if (new_size > size)
        {

            if (new_size > capacity)
            {
                reallocate(new_size);
            }

            for (size_t i = size; i < new_size; ++i)
            {
                data[i] = T();
            }
            size = new_size;
        }
        else if (new_size < size)
        {
            size = new_size;
        }
    }

    size_t get_size() const
    {
        return size;
    }

    size_t get_capacity() const
    {
        return capacity;
    }

    void push_back(const T &value)
    {
        if (size == capacity)
        {
            reallocate(std::max(capacity, (size_t)1) * 2);
        }

        data[size] = value;
        size++;
    }

    void pop_back()
    {
        if (size == 0) throw std::out_of_range("Array is empty");
        size--;
    }

    void clear()
    {
        reallocate(4);
        size = 0;
    }

    T &operator[](size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Out of range");
        }

        return data[index];
    }
    const DynamicArray<T> &operator=(const DynamicArray<T> &other)
    {
        this->capacity = other.capacity;
        this->size = other.size;
        reallocate(other.capacity);
        std::copy(other.data, other.data + size, data);
        return *this;
    }
    DynamicArray<T> &operator+=(const DynamicArray<T> &other)
    {

        for (size_t i = 0; i < other.get_size(); i++)
        {
            this->push_back(other[i]);
        }
        return *this;
    }

    class Iterator
    {
    private:
        T *cur;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &; 

        Iterator(T *first) : cur{first} {}

        Iterator &operator+(int n)
        {
            cur += n;
            return *this;
        }

        Iterator &operator-(int n)
        {
            cur -= n;
            return *this;
        }
        Iterator &operator++(int)
        {
            cur++;
            return *this;
        }

        Iterator &operator--(int)
        {
            cur--;
            return *this;
        }

        Iterator &operator++()
        {
            ++cur;
            return *this;
        }

        Iterator &operator--()
        {
            --cur;
            return *this;
        }

        bool operator!=(const Iterator &it) const { return cur != it.cur; }
        bool operator==(const Iterator &it) const { return cur == it.cur; }

        reference operator*() { return *cur; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
};
