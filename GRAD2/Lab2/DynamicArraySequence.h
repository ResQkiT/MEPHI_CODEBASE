#include <cstddef>
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class DynamicArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> impl;

    explicit DynamicArraySequence(DynamicArray<T> array) : impl{array} {}

public:

    explicit DynamicArraySequence() : impl{DynamicArray<T>()} {}

    explicit DynamicArraySequence(T *items, size_t size) : impl{DynamicArray<T>(items, size)} {}
    
    T getFirst() const override
    {
        return (impl)[0];
    }
    T getLast() const override
    {
        return impl[impl.get_size() - 1];
    }
    T get(size_t index) const override
    {
        return  impl[index];
    }


    DynamicArraySequence<T> * getSubsequence(size_t startIndex, size_t endIndex) override
    {

        DynamicArray<T> subsequenceArray = DynamicArray<T>(endIndex - startIndex + 1);

        auto cur_it =impl.begin() + startIndex;
        auto new_it =subsequenceArray.begin();

        for (; new_it != subsequenceArray.end(); cur_it++, new_it++)
        {
            *new_it = *cur_it;
        }

        return new DynamicArraySequence(subsequenceArray);
    }
    
    void add_from(DynamicArray<T> array){
        auto it = array.begin();
        for(;it!= array.end(); it++){
            impl.push_back(*it);
        }
    }

    size_t getLength() const override
    {
        return impl.get_size();
    }

    void append(T item) override
    {
        impl.push_back(item);
    }

    void prepend(T item) override
    {
        DynamicArray<T> new_array;
        new_array.push_back(item);

        for (size_t i = 0; i < impl.get_size(); i++)
        {
            new_array.push_back(impl[i]);
        }
        impl = new_array;
    }

    void insertAt(size_t index, T item) override
    {
        DynamicArray<T> new_array;
        for (size_t i = 0; i < index; i++)
        {
            new_array.push_back(impl[i]);
        }
        new_array.push_back(item);

        for (size_t i = index ; i < impl.get_size(); i++)
        {
            new_array.push_back(impl[i]);
        }
        impl = new_array;
    }

    DynamicArraySequence<T> * concat(Sequence<T> * list) override
    {
        for (size_t i = 0; i < list->getLength(); i++)
        {
            append(list->get(i));
        }
        return this;
    }

    
    DynamicArraySequence<T> operator+(const DynamicArraySequence<T> & other) const
    {
        DynamicArraySequence<T> newDynamicArraySequence;

        newDynamicArraySequence+=(*this);
        newDynamicArraySequence+=(other);

        return newDynamicArraySequence;
    }

    DynamicArraySequence<T> & operator+=(const DynamicArraySequence<T>& other){
        for (size_t i = 0; i < other.getLength(); i++)
        {
            append(other.get(i));
        }
        
        return *this;
    }
};
template<class T>
std::ostream& operator << (std::ostream &os, const DynamicArraySequence<T> &array)
{
    for (size_t i = 0; i < array.getLength(); i++)
    {
        os << array.get(i) << " ";
    }
    os << std::endl;
    return os;
    
}