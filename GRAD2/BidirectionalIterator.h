#pragma once
#include "AbstractIterator.h" 

template<class T>   
class BidirectionalIterator : public AbstractIterator<T> {
protected:
    BidirectionalIterator(T * data): data{data}{}
public:
    AbstractIterator & operator++(int) override { return *(data++);}
    AbstractIterator & operator++() override { return *(++data);};

    AbstractIterator & operator--(int) override {return *(data--);};
    AbstractIterator & operator--() override {return *(--data);};

    T & operator*() override {return *data;};
    T * operator->() override {return data};
};