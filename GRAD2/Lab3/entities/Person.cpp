#include "Person.h"
#include <string>

Person::Person(std::string name, std::string surname) : name{name}, surname{surname}, email{""} {}
Person::Person(std::string name, std::string surname, std::string email) : Person(name, surname){
    this->email = email;
}
Person::~Person() = default;

std::string & Person::get_name(){
    return name;
}
std::string & Person::get_surname(){
    return surname;
} 
std::string & Person::get_email(){
    return email;
}