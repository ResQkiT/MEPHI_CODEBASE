#pragma once

template<class T>
class Iterable{
public:
    ~Iterable() = default;
    
    T* begin() = 0;
    T* end() =  0;

};