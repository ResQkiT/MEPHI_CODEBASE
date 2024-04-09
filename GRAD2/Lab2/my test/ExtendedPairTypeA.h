#pragma once
#include "MyPair.h"
#include <iostream>
template<class T>
class ExtendedPairTypeA : public MyPair<T>{
public:
    ExtendedPairTypeA(T first, T second) : MyPair<T>(first, second){};

};

