#pragma once
#include <string>
#include "ICommand.h"

class MenuElement{
private:
    std::string element_name;
    ICommand * runtime_command; 
public:
    MenuElement();
    //требуется забрать доступ у переданного указателя
    MenuElement(std::string name, ICommand * command);
    MenuElement(const MenuElement & other);
    ~MenuElement();
    std::string get_name();
    void exec();
    MenuElement & operator=(const MenuElement & other);
};