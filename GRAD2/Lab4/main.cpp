#include <iostream>
#include "test.h"
#include "interface/StartTestCommand.h"
#include "../ExtendedMenu/Menu.h"

int main(){
    Menu menu;
    MenuElement main_menu_element_list[]={
        MenuElement("Start tests", new StartTestCommand())
    };
    menu.add_menu_element(main_menu_element_list[0]);
    menu.exec();

}