#pragma once
#include <stddef.h>

template<class T>
class IConcatable{
public:
    virtual ~IConcatable() = default;
    virtual void push_back(const T & value) = 0;
    virtual T & get(size_t index) = 0;
    virtual size_t get_size() const = 0;
    IConcatable<T> * concat(IConcatable<T> * other){
        for (size_t i = 0; i < other->get_size() ; i++)
        {
            this->push_back(other->get(i));
        }
        return this;      
    }
};