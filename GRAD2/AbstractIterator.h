#pragma once

template<class T>
class AbstractIterator{
protected:
    T * data;
public:
    virtual AbstractIterator & operator++(int) = 0;
    virtual AbstractIterator & operator++() = 0;

    virtual AbstractIterator & operator--(int) = 0;
    virtual AbstractIterator & operator--() = 0;

    virtual T & operator*() = 0;
    virtual T * operator->() = 0;
    bool operator!=(const AbstractIterator & other) const { return data != other.data;}

};