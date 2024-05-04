#pragma once
#include <iostream>

template<class T>
void console_get(T & target){
    T copy;
    std::cin >> copy;
    if(std::cin.fail ()){
        throw std::runtime_error("Incorrect input format");
    }
    target = copy;
}
