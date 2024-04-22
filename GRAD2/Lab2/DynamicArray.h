#pragma once
#include <iostream>
#include <stdexcept>
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
        this->data = new T[capacity];
    }

    DynamicArray(const T *data , size_t size) : size{size}, capacity{2 * size}
    {
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



    T get(size_t index)
    {
        return *(data + index);
    }

    void set(size_t index, T value)
    {
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

            std::copy(data, data + size, data);

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
            reallocate(capacity * 2);
        }

        data[size] = value;
        size++;
    }

    void pop_back()
    {
        if (size == 0)
        {
            return;
        }

        size--;
    }

    void clear()
    {
        reallocate(0);
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
            throw std::out_of_range("Index out of range");
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

    class Iterator{
    private:
        T * cur;
    public:
        Iterator(T* first): cur{first}{}

        Iterator& operator+ (int n){
            cur += n;
            return *this;
        }
        
        Iterator& operator- (int n){
            cur -= n;
            return *this;
        }

        Iterator& operator++(int){
            cur++;
            return *this;
        }

        Iterator& operator--(int){
            cur--;
            return *this;
        }

        Iterator& operator++(){
            ++cur;
            return *this;
        }

        Iterator& operator--(){
            --cur;
            return *this;
        }

        bool operator!=(const Iterator& it){return cur != it.cur;}
        bool operator==(const Iterator& it){return cur == it.cur;}
        T& operator*(){return *cur;}
    };

    Iterator begin(){return Iterator(data);}
    Iterator end(){return Iterator(data+ size);}
};
