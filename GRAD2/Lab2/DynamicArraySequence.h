#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class DynamicArraySequence : public Sequence<T>
{
private:
    const DynamicArray<T> *impl;

public:
    DynamicArraySequence() : impl{new DynamicArray<T>()} {}

    DynamicArraySequence(DynamicArray<T> *array) : impl{array} {}

    DynamicArraySequence(T *items, size_t size) : impl{new DynamicArray<T>(items, size)} {}
    
    T getFirst() override
    {
        return (*impl)[0];
    }

    T getLast() override
    {
        return (*impl)[impl->get_size() - 1];
    }

    T get(size_t index) override
    {
        return (*impl)[index];
    }

    DynamicArraySequence<T> getSubsequence(size_t startIndex, size_t endIndex) override
    {

        DynamicArray<T> subsequence(endIndex - startIndex + 1);

        auto cur_it =impl->begin() + startIndex;
        auto new_it =subsequence.begin();

        for (; new_it != subsequence.end(); cur_it++, new_it++)
        {
            *new_it = *cur_it;
        }
        return DynamicArraySequence<T>(subsequence);
    }

    size_t getLength() override
    {
        return impl->get_size();
    }

    void append(T item) override
    {
        impl->push_back(item);
    }

    void prepend(T item) override
    {
        // TODO реализовать добавление в начало.
    }

    void insertAt(size_t index, T item) override
    {
    }

    Sequence<T>& concat(Sequence<T> * list, size_t count) override
    {


        for (size_t i = 0; i < count; i++)
        {
            *this += list[i];
        }
        return *this;
    }

    DynamicArraySequence<T> operator+(const Sequence<T>& other) const
    {
        DynamicArray<T> newDynamicArray(this->getLength() + other.getLength());

        newDynamicArray+=(*this);
        newDynamicArray+=(other);

        return DynamicArraySequence<T>(newDynamicArray);
    }

    DynamicArraySequence<T> & operator+=(const Sequence<T>& other) const{
        for (size_t i = 0; i < other.getLength(); i++)
        {
            impl->push_back(other.get(i));
        }
        
        return *this;
    }
};
