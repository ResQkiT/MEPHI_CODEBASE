#pragma once
#include <iostream>
#include "IPair.h"
template<class T>
class MyPair : public IPair{
private:
    T first;
    T second;
public:
    MyPair() = delete;
    MyPair(T first, T second): first{NULL}, second{NULL}{
        this->first = first;
        this->second = second;
    }
    MyPair(const MyPair<T> & source){
        this->first = source.first;
        this->second = source.second;
    }
    ~MyPair() = default;


    T getFirst(){
        return this->first; 
    }
    T getSecond(){
        return this->second;
    }
    void print(){
        std::cout << this->first << " " << this->second << std::endl; 
    }

    void work(){
        std::cout<< "Working!" << std::endl;
    }
    void printWork(){
        std::cout << this->first + this->second << std::endl;
    }
};