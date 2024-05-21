#pragma once
#include <iostream>

/// методы разные, поскольку при чтении данных необходимо сразу кидать исключение -
/// (вдруг данные искажены)
/// В то время как для меню, можно спросить пользователя несколько раз.
/// Однако не стоит наказывать пользователя за несуществующий выбор в меню.
/// (ответственность за это лежит на клиентком коде)


template<class T>
void console_get_or_throw(T & target){
    T copy;
    std::cin >> copy;
    if(std::cin.fail ()){
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        throw std::format_error("Incorrect input format");
    }
    target = copy;
}

static size_t TRY_AVAILABLE = 3;

template<class T>
void console_get_kindly(T & target){
    T copy;
    for (size_t i = 1; i <= TRY_AVAILABLE; i++)
    {
        try
        {
            std::cout << "Try to read data" << std::endl;
            console_get_or_throw(copy);
            target = copy;
            return;
        }
        catch(const std::format_error& e)
        {
            std::cout << e.what() << " \nPlease try again, attempts left: "<< TRY_AVAILABLE - i << std::endl;
        }
    }
    throw std::runtime_error("Timeout exception, requests limit exceeded");
};