#include "Menu.h"
#include <iostream>
#include "readio.h"

Menu::Menu() :menu{std::map<size_t, MenuElement>()}{};
Menu::~Menu() = default;

void Menu::run(){
    running = true;
}
void Menu::abort(){
    running = false;
}
bool Menu::is_running(){
    return running;
}
void Menu::print_menu(){
    std::cout<<std::endl << "Current working menu, 0 - for exit menu" << std::endl;
    for(auto var : menu)
    {
        std::cout << var.first << ": " <<var.second.get_name() <<std::endl;        
    }
}
void Menu::add_menu_element(const MenuElement & menu_element){
    menu[menu.size() + 1] = menu_element;
}
void Menu::exec(){
    run();
    while (is_running())
    {
        print_menu();
        handle_input();
    }
}
void Menu::handle_input(){
    size_t choice;
    std::cout << "Enter option-> ";
    
    console_get_kindly(choice);
    
    if(choice == 0) {
        std::cout << "Exiting menu..." << std::endl;
        abort();
        return;
    }

    if(menu.count(choice) == 0){
        std::cout << "No such command" << std::endl;
        return;
    }
    menu[choice].exec();
}
Menu * Menu::clone(){
    Menu * clone = new Menu();
    clone->menu = this->menu;
    return clone;
}