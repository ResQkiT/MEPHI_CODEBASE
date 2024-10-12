#include <iostream>
#include <string>
#include <map>
#include <variant>
#include <memory>
#include "LinkedList.hpp" 

class ListManager {
private:
    std::map<std::string, std::shared_ptr<std::variant<
        LinkedList<int>, 
        LinkedList<double>, 
        LinkedList<std::string>, 
        LinkedList<float>>>> lists;

    std::string listAsString;

public:
    // Создает новый список заданного типа
    void createList(const std::string& type) {
        if (lists.find(type) == lists.end()) {
            // Создаем новый объект LinkedList
            switch (type)
            {
            case "int":
                auto list = std::make_shared<std::variant<
                LinkedList<int>, 
                LinkedList<double>, 
                LinkedList<std::string>, 
                LinkedList<float>
            >>(LinkedList<int>()); 
                lists["int"] = list;
                break;
            case "double":
                auto list = std::make_shared<std::variant<
                LinkedList<int>, 
                LinkedList<double>, 
                LinkedList<std::string>, 
                LinkedList<float>
            >>(LinkedList<double>()); 
                lists["double"] = list;
                break;
            case "string":
                auto list = std::make_shared<std::variant<
                LinkedList<int>, 
                LinkedList<double>, 
                LinkedList<std::string>, 
                LinkedList<float>
                >>(LinkedList<std::string>()); 
                lists["string"] = list;
                break;
            case "float":
                auto list = std::make_shared<std::variant<
                LinkedList<int>, 
                LinkedList<double>, 
                LinkedList<std::string>, 
                LinkedList<float>
            >>(LinkedList<float>()); 
                lists["float"] = list;
                break;
            default:
                throw std::invalid_argument("no such type");
                break;
            }
        
            
            std::cout << "Список типа " << type << " создан." << std::endl;
        } else {
            std::cout << "Список типа " << type << " уже существует." << std::endl;
        }
    }

    // Добавляет элемент в список заданного типа
    void append(const std::string& type, const std::variant<int, double, std::string, float>& value) {
        if (lists.count(type) > 0) {
            std::visit([&](auto& list) { 
                list.push_back(value); 
            }, *lists[type]);
            std::cout << "Элемент добавлен в конец списка типа " << type << std::endl;
        } else {
            std::cout << "Список типа " << type << " не существует." << std::endl;
        }
    }

    // Добавляет элемент в начало списка заданного типа
    void prepend(const std::string& type, const std::variant<int, double, std::string, float>& value) {
        if (lists.count(type) > 0) {
            std::visit([&](auto& list) { 
                list.push_front(value); 
            }, *lists[type]);
            std::cout << "Элемент добавлен в начало списка типа " << type << std::endl;
        } else {
            std::cout << "Список типа " << type << " не существует." << std::endl;
        }
    }

    // Вставляет элемент по индексу в список заданного типа
    void insert(const std::string& type, const T& value, size_t index) {
        if (lists.count(type) > 0) {
            std::visit([&](auto& list) { 
                list.insert_at(value, index); 
            }, *lists[type]);
            std::cout << "Элемент добавлен в список типа " << type << " по индексу " << index << std::endl;
        } else {
            std::cout << "Список типа " << type << " не существует." << std::endl;
        }
    }

    // Получает элемент по индексу из списка заданного типа
    std::variant<int, double, std::string, float> get(const std::string& type, size_t index) {
        if (lists.count(type) > 0) {
            return std::visit([&](auto& list) { 
                return list.get(index);
            }, *lists[type]);
        } else {
            throw std::invalid_argument("Список типа " + type + " не существует.");
        }
    }

    // Получает первый элемент из списка заданного типа
    std::variant<int, double, std::string, float> getfirst(const std::string& type) {
        if (lists.count(type) > 0) {
            return std::visit([&](auto& list) { 
                return list.front();
            }, *lists[type]);
        } else {
            throw std::invalid_argument("Список типа " + type + " не существует.");
        }
    }

    // Получает размер списка заданного типа
    size_t getsize(const std::string& type) {
        if (lists.count(type) > 0) {
            return std::visit([&](auto& list) { 
                return list.size();
            }, *lists[type]);
        } else {
            throw std::invalid_argument("Список типа " + type + " не существует.");
        }
    }

};
