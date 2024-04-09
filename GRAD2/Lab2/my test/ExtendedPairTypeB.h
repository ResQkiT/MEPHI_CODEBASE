#pragma once
#include "MyPair.h"
#include <iostream>
template<class T>
class ExtendedPairTypeB : public MyPair<T>{
public:
    ExtendedPairTypeB(T first, T second) : MyPair<T>(first, second){};
};