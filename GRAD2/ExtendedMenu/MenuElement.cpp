#include "MenuElement.h"
#include "ICommand.h"
#include <iostream>

MenuElement::MenuElement() : element_name{""}, runtime_command{nullptr}
{
}

MenuElement::MenuElement(std::string name, ICommand * command) : element_name{name} , runtime_command{command->clone()}{
}   

std::string MenuElement::get_name()
{
    return element_name;
}

MenuElement::MenuElement(const MenuElement &other) : element_name{other.element_name}, runtime_command{other.runtime_command->clone()}
{
}

MenuElement::~MenuElement() = default;

void MenuElement::exec(){
    if(runtime_command == nullptr){
        std::cout << "Runtime command is null"<<std::endl;
        return;
    }
    runtime_command->exec();
}
MenuElement & MenuElement::operator=(const MenuElement & other){

    element_name = other.element_name;
    runtime_command = other.runtime_command->clone();
    return *this;
}