#pragma once


template<class T>
class Sequence
{
public:
    virtual ~Sequence() = default;

    virtual T & get_first() = 0;
    virtual T & get_last() = 0;
    virtual T & get(size_t index) = 0;
    
    virtual Sequence<T> * get_subsequence(size_t startIndex, size_t endIndex) = 0;
    
    virtual size_t get_length() const = 0;
    virtual void append(const T & item) = 0;
    virtual void prepend(const T & item) = 0;
    virtual void insert_at(size_t index,const T & item) = 0;

    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    
    virtual bool is_empty() const = 0;
    Sequence<T> * concat(Sequence<T> * list){
        for (size_t i = 0; i < list->get_length(); i++)
        {
            append(list->get(i));
        }
        return this;
    }
};