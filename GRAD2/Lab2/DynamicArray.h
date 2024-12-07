#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "IConcatable.h"

template <typename T>
class DynamicArray : public IConcatable<T>
{
private:
    T *data;
    size_t size;
    size_t capacity;

    void enlarge(size_t new_capacity)
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
    using value_type = T;
    
    DynamicArray() : data{nullptr}, size{0}, capacity{4}
    {
        this->data = new T[this->capacity];
    }

    DynamicArray(size_t size) : data{nullptr}, size{size}, capacity{2 * size}
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create DynamicArray with negative size");
        this->data = new T[capacity];
        for (size_t i = 0; i < size; i++) data[i] = T();    
    }

    DynamicArray(const T *data, size_t size) : data{nullptr}, size{size}, capacity{2 * size}
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create DynamicArray with negative size");
        if (data == nullptr)
            throw std::invalid_argument("DynamicArray constructor must take not null arguments");
        this->data = new T[capacity];
        std::copy(data, data + size, this->data);
    }

    DynamicArray(const std::initializer_list<T> &list) : data{nullptr}, size{list.size()}, capacity{2 * size}
    {
        if (list.size() < 0)
            throw std::invalid_argument("Cannot create DynamicArray with negative size");
        this->data = new T[capacity];
        std::copy(list.begin(), list.end(), this->data);
    }

    DynamicArray(const DynamicArray<T> &other) : data{nullptr}, size{other.size}, capacity{other.capacity}
    {
        *this = other;
    }

    DynamicArray(DynamicArray<T> &&other) noexcept : data{std::move(other.data)}, size{std::move(other.size)}, capacity{std::move(other.capacity)} {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    ~DynamicArray()
    {
        if (data)
        {
            delete[] data;
        }
    }

    T &get(size_t index) override
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Out of range");
        return *(data + index);
    }

    void set(size_t index, const T &value)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Out of range");
        *(data + index) = value;
    }

    /// Изменяет размер массива не очищая память, в случае если new_size > size, инициализирует переменные значениями по умолчанию
    void resize(size_t new_size)
    {
        if (new_size > size)
        {

            if (new_size > capacity)
            {
                enlarge(new_size);
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

    size_t get_size() const override
    {
        return size;
    }

    size_t get_capacity() const
    {
        return capacity;
    }

    void push_back(const T &value) override
    {
        if (size == capacity)
        {
            enlarge(std::max(capacity, (size_t)1) * 2);
        }

        data[size] = value;
        size++;
    }

    void pop_back()
    {
        if (size == 0)
            throw std::out_of_range("Array is empty");
        size--;
    }

    void clear()
    {
        resize(0);
    }

    bool empty() const
    {
        return size == 0;
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
        delete[] data;
        this->size = other.size;
        this->capacity = other.capacity;
        T *new_data = new T[capacity];
        std::copy(other.data, other.data + size, new_data);
        data = new_data;
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
        size_t index;
        DynamicArray<T> *ptr;

    public:
        Iterator() : cur{nullptr}, index{0}, ptr{nullptr} {}
        Iterator(T *first, size_t index, DynamicArray<T> *self) : cur{first}, index{index}, ptr{self} {}
        Iterator(const Iterator &other) : cur{other.cur}, index{other.index}, ptr{other.ptr} {}

        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator operator+(difference_type n) const
        {
            if (index + n > ptr->size)
                throw std::out_of_range("Iterator out of working zone(+)");
            return Iterator(cur + n, index + n, ptr);
        }

        Iterator operator-(difference_type n) const
        {
            if (index < n)
                throw std::out_of_range("Iterator out of working zone(-)");
            return Iterator(cur - n, index - n, ptr);
        }

        difference_type operator-(const Iterator &other) const
        {
            return cur - other.cur;
        }

        Iterator &operator++()
        {
            if (index + 1 > ptr->size)
                throw std::out_of_range("Iterator out of working zone(++|)");
            ++index;
            ++cur;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--()
        {
            if (index == 0)
                throw std::out_of_range("Iterator out of working zone(--|)");
            --index;
            --cur;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator &operator+=(difference_type n)
        {
            if (index + n > ptr->size)
                throw std::out_of_range("Iterator out of working zone(+=)");
            index += n;
            cur += n;
            return *this;
        }

        Iterator &operator-=(difference_type n)
        {
            if (index < n)
                throw std::out_of_range("Iterator out of working zone(-=)");
            index -= n;
            cur -= n;
            return *this;
        }

        bool operator!=(const Iterator &it) const { return cur != it.cur; }
        bool operator==(const Iterator &it) const { return cur == it.cur; }
        bool operator<(const Iterator &it) const { return cur < it.cur; }
        bool operator<=(const Iterator &it) const { return cur <= it.cur; }
        bool operator>(const Iterator &it) const { return cur > it.cur; }
        bool operator>=(const Iterator &it) const { return cur >= it.cur; }

        reference operator*()
        {
            if (cur != nullptr)
                return *cur;
            else
                throw std::runtime_error("Iterator refer to null");
        }

        pointer operator->()
        {
            if (cur != nullptr)
                return cur;
            else
                throw std::runtime_error("Iterator refer to null");
        }

        reference operator[](difference_type n) const
        {
            if (index + n >= ptr->size)
                throw std::out_of_range("Iterator out of working zone([])");
            return *(cur + n);
        }
    };

    class ConstIterator
    {
    private:
        const T *ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T *;
        using reference = const T &;

        ConstIterator(const T *ptr) : ptr(ptr) {}

        reference operator*() const
        {
            return *ptr;
        }

        pointer operator->() const
        {
            return ptr;
        }

        ConstIterator &operator++()
        {
            ++ptr;
            return *this;
        }

        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            ++ptr;
            return tmp;
        }

        ConstIterator &operator--()
        {
            --ptr;
            return *this;
        }

        ConstIterator operator--(int)
        {
            ConstIterator tmp = *this;
            --ptr;
            return tmp;
        }

        ConstIterator operator+(difference_type n) const
        {
            return ConstIterator(ptr + n);
        }

        ConstIterator operator-(difference_type n) const
        {
            return ConstIterator(ptr - n);
        }

        difference_type operator-(const ConstIterator &other) const
        {
            return ptr - other.ptr;
        }

        bool operator==(const ConstIterator &other) const
        {
            return ptr == other.ptr;
        }

        bool operator!=(const ConstIterator &other) const
        {
            return ptr != other.ptr;
        }

        bool operator<(const ConstIterator &other) const
        {
            return ptr < other.ptr;
        }

        bool operator>(const ConstIterator &other) const
        {
            return ptr > other.ptr;
        }

        bool operator<=(const ConstIterator &other) const
        {
            return ptr <= other.ptr;
        }

        bool operator>=(const ConstIterator &other) const
        {
            return ptr >= other.ptr;
        }
    };

    ConstIterator begin() const
    {
        return ConstIterator(data);
    }

    ConstIterator end() const
    {
        return ConstIterator(data + size);
    }
    
    Iterator begin() { return Iterator(data, 0, this); }

    Iterator end() { return Iterator(data + size, size, this); }

    friend Iterator;
};
