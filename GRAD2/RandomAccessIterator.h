#pragma once
#include "AbstractIterator.h"

template<class T>
class RandomAccessIterator : public AbstractIterator<T>{
protected:
    RandomAccessIterator(T * data): data{data}{}

public:

    AbstractIterator & operator++(int) override { return *(data++);}
    AbstractIterator & operator++() override { return *(++data);};

    AbstractIterator & operator--(int) override {return *(data--);};
    AbstractIterator & operator--() override {return *(--data);};

    T & operator*() override {return *data;};
    T * operator->() override{return this};

};