#pragma once

template<class T>
class ImmutableSequence
{
protected:
    virtual void _add_to_end(T item) = 0;
    virtual ImmutableSequence<T> * create_instance() = 0;

public:
    virtual ~ImmutableSequence() = default;
    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(size_t index) = 0;
    virtual ImmutableSequence<T> * get_subsequence(size_t startIndex, size_t endIndex) = 0;
    virtual size_t get_length() const = 0;
    virtual ImmutableSequence<T> * append(T item) = 0;
    virtual ImmutableSequence<T> * prepend(T item) = 0;
    virtual ImmutableSequence<T> * insert_at(size_t index, T item) = 0;
    
    ImmutableSequence<T> * concat(ImmutableSequence<T> * list){
        ImmutableSequence<T> *new_sequence = create_instance();
        for (size_t i = 0; i < this->get_length(); i++)
        {
            new_sequence->_add_to_end(this->get(i));
        }

        for (size_t i = 0; i < list->get_length(); i++)
        {
            new_sequence->_add_to_end(list->get(i));
        }
        return new_sequence;
    }
};