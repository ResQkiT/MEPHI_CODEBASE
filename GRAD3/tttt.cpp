#include <iostream>
#include <string>
#include <memory> // Для умных указателей

// Шаблон класса Object
template <typename T>
class Object {
public:
    T data;

    Object(const T& value) : data(value) {} 

    void print() {
        std::cout << "Значение: " << data << std::endl;
    }
};

// Шаблонная функция для создания объекта
template <typename T>
std::unique_ptr<Object<T>> createObject() {
    T value;
    std::cout << "Введите значение: ";
    std::cin >> value;

    // Создание объекта с использованием умного указателя
    return std::make_unique<Object<T>>(value); 
}

int main() {
    std::string type;

    std::cout << "Введите тип объекта (int или string): ";
    std::cin >> type;

    if (type == "int") {
        auto obj = createObject<int>(); // Создание объекта типа Object<int>
        obj->print();
    } else if (type == "string") {
        auto obj = createObject<std::string>(); // Создание объекта типа Object<string>
        obj->print();
    } else {
        std::cout << "Неверный тип!" << std::endl;
    }

    return 0;
}

