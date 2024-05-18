#include <iostream>
#include "Menu.h"
#include "ICommand.h"
#include "PrintHelloCommand.h"
using namespace std;
int main(){
    Menu menu;
    ICommand * printHello = new PrintHelloCommand(); 
    menu.add_menu_element(MenuElement("first", printHello));
    
    Menu submenu;
    submenu.add_menu_element(MenuElement("first - first" , printHello));
    submenu.add_menu_element(MenuElement("first - second", printHello));

    menu.add_menu_element(MenuElement("second is menu", &submenu));

    menu.exec();
    
}