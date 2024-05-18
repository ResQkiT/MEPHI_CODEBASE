#pragma once
#include <map>
#include "MenuElement.h"
#include "ICommand.h"

//realization of Composite pattern
class Menu: public ICommand{
private:
    std::map<size_t, MenuElement> menu;
    bool running;

    void run();
    void abort();
public:
    Menu();
    ~Menu();
    void print_menu();
    void add_menu_element(const MenuElement & menu_element);
    void exec() override;
    Menu * clone() override;
    void handle_input();
    bool is_running();
};